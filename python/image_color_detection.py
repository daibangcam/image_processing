# import thư viện
import numpy as np
import cv2

# đọc file ảnh:
img = cv2.imread("02.png")

# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
#cv2.namedWindow("Color Detection", cv2.WINDOW_NORMAL)
#cv2.namedWindow("Mask", cv2.WINDOW_NORMAL)

# chuyển ảnh sang không gian màu HSV:
hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

# xác định giới hạn trên và giới hạn dưới cho màu sắc cần phân loại:
lower_limit = np.array([106, 60, 90])
upper_limit = np.array([124, 255, 255])

# Sau đó, sử dụng hàm cv2.inRange() để tạo một mặt nạ cho khoảng màu được chỉ định
# Hàm này nhận vào hình ảnh HSV và giới hạn dưới + giới hạn trên của khoảng màu (ở bước trước) làm đầu vào
# và trả về một hình ảnh mặt nạ nhị phân.

# tạo mặt nạ phân đoạn màu
mask = cv2.inRange(hsv_img, lower_limit, upper_limit)

# show ảnh mặt nạ
cv2.imshow("Mask", mask)

# sử dụng hàm cv2.boundingRect() để lấy hộp giới hạn của đối tượng trong hình ảnh
# ở đây là phần ảnh chứa màu sắc cần phân đoạn
# Hàm này nhận hình ảnh mặt nạ làm đầu vào và trả về tọa độ hộp giới hạn (x, y, w, h)
# trong đó (x, y) là góc trên cùng bên trái của hộp giới hạn và (w, h) là chiều rộng và chiều cao của hộp giới hạn.

# lấy thông số hộp giới hạn bao quanh vùng màu cần phân đoạn
bbox = cv2.boundingRect(mask)

# kiểm tra xem biến bbox có khác rỗng hay không (tức là có tìm được hộp giới hạn bao quanh vùng chứa màu cần phân đoạn)
# Nếu khác rỗng, tức là có tồn tại hộp giới hạn thì vẽ một hình chữ nhật trên hình ảnh 
# bằng cách sử dụng hàm cv2.rectangle() với các thông số (x,y,w,h) của hộp giới hạn tìm được.

# nếu có hộp giới hạn bao quanh vùng màu cần phân đoạn thì vẽ hình chữ nhật theo thông số hộp giới hạn đó
if bbox is not None:
    print("Object detected")
    x, y, w, h = bbox
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
else:
    print("Object not detected")

# show ảnh kết quả
cv2.imshow('Color Detection', img)
cv2.waitKey(0)