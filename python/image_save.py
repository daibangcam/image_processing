# import thư viện OpenCV
import cv2
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original RGB", cv2.WINDOW_NORMAL)
  
# hiển thị file ảnh img
cv2.imshow('Original RGB', img)

# save ảnh img thành ảnh mới với tên 02.jpg
cv2.imwrite('02.jpg', img)

# gán file ảnh 02.jpg vừa save vào biến img_save
img_save = cv2.imread('02.jpg')

# hiển thị file ảnh img_save
cv2.imshow('Save Image', img_save)
  
# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()