## 2. Hiển thị nhiều ảnh trên 1 plot dùng thư viện matplotlib

```python
# khai báo thư viện
import cv2
import matplotlib.pyplot as plt
  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
  
# chuyển sang ảnh xám
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# chuyển ảnh gốc hệ màu BGR sang hệ màu RGB để hiển thị trên matplotlib
# vì matplotlib chỉ hiển thị ảnh màu RGB
img_RGB = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)

# sử dụng thư viện matplotlib
# ví dụ hiển thị 3 ảnh trên cùng 1 plot dưới dạng ma trận 1 hàng 3 cột
# thứ tự ảnh sẽ được tính từ trái qua phải, từ trên xuống dưới

# tạo ô hiển thị ảnh đầu tiên ở vị trí 1 (hàng 1 cột 1)
plt.subplot(131), 
# show ảnh màu RGB
plt.imshow(img), 
# đặt tiêu đề cho ảnh
plt.title('Original Image'),
# tắt trục tọa độ
plt.axis('off')

# tạo ô hiển thị ảnh đầu tiên ở vị trí 2 (hàng 1 cột 2)
plt.subplot(132), 
# show ảnh xám
plt.imshow(img_RGB), 
# đặt tiêu đề cho ảnh
plt.title('RGB Image'),
# tắt trục tọa độ
plt.axis('off')

# tạo ô hiển thị ảnh đầu tiên ở vị trí 3 (hàng 1 cột 3)
plt.subplot(133), 
# show ảnh ảnh màu RGB
plt.imshow(img_gray, cmap = 'gray'),
# đặt tiêu đề cho ảnh
plt.title('Gray Image'),
# tắt trục tọa độ
plt.axis('off')

# hiển thị plot
plt.show()