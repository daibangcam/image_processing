# import thư viện OpenCV
import cv2
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original RGB", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("Gray image", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("BW image Inverse", cv2.WINDOW_AUTOSIZE)

# chuyển sang ảnh xám
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# chuyển sang ảnh nhị phân (nền đen, chủ thể trắng)
(ret, img_bw) = img_bw = cv2.threshold(img_gray,50,255,cv2.THRESH_BINARY)

# chuyển sang ảnh nhị phân (nền trắng, chủ thể đen)
(ret, img_bw_inv) = img_bw = cv2.threshold(img_gray,50,255,cv2.THRESH_BINARY_INV)

# hiển thị ảnh
cv2.imshow('Original RGB', img)
cv2.imshow('Gray image', img_gray)
cv2.imshow('BW image', img_bw)
cv2.imshow('BW image Inverse', img_bw_inv)

# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()