# import thư viện
import cv2
import numpy as np

# load ảnh
img = cv2.imread('03.png')

# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original Image", cv2.WINDOW_NORMAL)
cv2.namedWindow("Gray Image", cv2.WINDOW_NORMAL)
cv2.namedWindow("Blur Image", cv2.WINDOW_NORMAL)
cv2.namedWindow("Edge Detection", cv2.WINDOW_NORMAL)
cv2.namedWindow("Shape Detection", cv2.WINDOW_NORMAL)

# hiển thị ảnh gốc
cv2.imshow("Original Image", img)

# chuyển ảnh xám
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow("Gray Image", img_gray)

# tiền xử lý - giảm các điểm ảnh nhiễu
img_blur = cv2.GaussianBlur(img_gray, (5, 5), 0)
cv2.imshow("Blur Image", img_blur)

# thuật toán Canny để phát hiện cạnh
edges = cv2.Canny(img_blur, 30, 150)
cv2.imshow("Edge Detection", edges)

# tìm các đường viền trong ảnh
contours, _ = cv2.findContours(edges.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# lần lượt xử lý từng đường viền tìm được trong biến contours
for contour in contours:
    # xấp xỉ hình dạng (giảm bớt đỉnh mà vẫn giữ dc hình dạng cơ bản)
    epsilon = 0.04 * cv2.arcLength(contour, True)
    approx = cv2.approxPolyDP(contour, epsilon, True)
    # gọi biến vertices là số cạnh trong đường viền
    vertices = len(approx)
    # nếu 3 cạnh thì đây là hình tam giác
    if vertices == 3:
        shape = "Triangle"
    # nếu 4 cạnh thì đây là hình tứ giác
    elif vertices == 4:
        (x, y, w, h) = cv2.boundingRect(approx)
        ar = w / float(h)
        # A square will have an aspect ratio(ar) that is approximately
        # equal to one, otherwise, the shape is a rectangle
        shape = "square" if ar >= 0.95 and ar <= 1.05 else "rectangle"
    # nếu 5 cạnh thì đây là hình ngũ giác
    elif vertices == 5:
        shape = "Pentagon"
    # các trường hợp còn lại (nhiều hơn 5 cạnh) coi là hình tròn
    else:
        shape = "Circle"
    # ghi text hình dạng của đường viền
    cv2.putText(img, shape, (approx[0][0][0], approx[0][0][1]+5), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2)

# show ảnh kết quả
cv2.imshow('Shape Detection', img)
cv2.waitKey(0)
cv2.destroyAllWindows()