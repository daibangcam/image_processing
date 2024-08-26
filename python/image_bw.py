# import thư viện OpenCV
import cv2
import matplotlib.pyplot as plt
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# đặt tên cửa sổ hiển thị file ảnh 
# cv2.WINDOW_AUTOSIZE -> autosize window theo ảnh
# cv2.WINDOW_NORMAL -> fit ảnh trong window
cv2.namedWindow("Original RGB", cv2.WINDOW_NORMAL)
  
# hiển thị giá trị pixel (50,50)
(B, G, R) = img[50, 50]
print("R={}, G={}, B={}".format(R, G, B))

# chuyển sang ảnh xám
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# chuyển sang ảnh nhị phân
img_bw = cv2.threshold(img_gray,50,255,cv2.THRESH_BINARY)

# hiển thị ảnh
cv2.imshow('Original RGB', img)
cv2.imshow('Gray image', img_gray)
cv2.imshow('BW image', img_bw)

# chuyển ảnh gốc hệ màu BGR sang hệ màu RGB 
# để hiển thị trên matplotlib
img_RGB = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)

# hiển thị 3 ảnh trên cùng 1 cửa sổ
plt.subplot(131), 
plt.imshow(img_RGB, cma = 'gray'), 
plt.title('Original Image'),
plt.axis('off')

plt.subplot(132), 
plt.imshow(img_gray, cma = 'gray'), 
plt.title('Gray Image'),
plt.axis('off')

plt.subplot(133), 
plt.imshow(img_bw, cma = 'gray'), 
plt.title('BW Image'),
plt.axis('off')

plt.show()

# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()