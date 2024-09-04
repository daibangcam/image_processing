# import thư viện OpenCV
import cv2
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original RGB", cv2.WINDOW_NORMAL)

# lật ảnh theo chiều ngang (trái qua phải)
img_flip_vertical = cv2.flip(img, 0)

# lật ảnh theo chiều dọc (trên xuống dưới)
img_flip_horizontal = cv2.flip(img, 1)

# lật ảnh theo cả chiều ngang và chiều dọc
img_flip_both = cv2.flip(img, -1) 
  
# hiển thị file ảnh
cv2.imshow('Original RGB', img)
cv2.imshow('Flipped vertical image', img_flip_vertical)
cv2.imshow('Flipped horizontal image', img_flip_horizontal)
cv2.imshow('Flipped both image', img_flip_both) 
  
# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()