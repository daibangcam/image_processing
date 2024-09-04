# import thư viện OpenCV
import cv2
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original RGB", cv2.WINDOW_NORMAL)

# xoay ảnh một góc bất kỳ, ví dụ góc 45 độ
angle = 45
(h, w, d) = img.shape 
center = (w // 2, h // 2) 
M = cv2.getRotationMatrix2D(center, angle, 1.0) 
img_rotate = cv2.warpAffine(img, M, (w, h))
  
# hiển thị file ảnh
cv2.imshow('Original RGB', img)
cv2.imshow('Rotate image', img_rotate)

# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()