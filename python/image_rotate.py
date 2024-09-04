# import thư viện OpenCV
import cv2
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original RGB", cv2.WINDOW_NORMAL)

# xoay ảnh 90 độ
img_rotate_90 = cv2.rotate(img, cv2.ROTATE_90_CLOCKWISE)

# xoay ảnh 180 độ
img_rotate_180 = cv2.rotate(img, cv2.ROTATE_180)

# xoay ảnh 270 độ
img_rotate_270 = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)
  
# hiển thị file ảnh
cv2.imshow('Original RGB', img)
cv2.imshow('Rotate 90 image', img_rotate_90)
cv2.imshow('Rotate 270 image', img_rotate_270)
cv2.imshow('Rotate 180 image', img_rotate_180) 
  
# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()