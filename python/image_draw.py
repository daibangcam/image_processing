# import thư viện
import cv2
import numpy as np
  
# Đặt kích thước file ảnh muốn tạo
height = 360
width = 480

# tạo file ảnh trắng với kích thước định trước
img = np.ones((height,width,3), np.uint8)
img = 255*img 

# vẽ đoạn thẳng line màu xanh
# điểm bắt đầu đoạn thẳng
start_point_line = (50, 200)
# điểm kết thúc đoạn thẳng
end_point_line = (400, 30)
# màu đoạn thẳng trong format BGR
blue_color = (255, 0, 0)
# độ đậm đoạn thẳng line
thickness_line = 5
cv2.line(img, start_point_line, end_point_line, blue_color, thickness_line)

# Vẽ đường tròn xanh lá cây
# tọa độ tâm đường tròn
center_circle = (200, 200)
# bán kính đường tròn
radius_circle = 100
# màu đường tròn trong format BGR
green_color = (0, 255, 0)
# độ đậm đường tròn (giá trị âm để tô màu hình tròn)
thickness_circle = 3
cv2.circle(img, center_circle, radius_circle, green_color, thickness_circle)

# Vẽ hình chữ nhật màu đỏ
# tọa độ đầu hình chữ nhật (góc trên bên trái)
start_point_rect = (100, 100)
# tọa độ đuôi hình chữ nhật (góc dưới bên phải)
end_point_rect = (300, 300)
# màu hình chữ nhật trong format BGR
red_color = (0, 0, 255)
# độ rộng nét vẽ
thickness_rect = 2
cv2.rectangle(img, start_point_rect, end_point_rect, red_color, thickness_rect)

# ghi chữ
# nội dung text
text = "I LOVE HUIT"
# font chữ
font = cv2.FONT_HERSHEY_SIMPLEX
# tỉ lệ scale
font_scale = 1
# màu chữ
font_color = (0, 0, 0)  # Black color in BGR format
# độ đậm nét chữ
font_thickness = 2
# vị trí bắt đầu chữ
text_position = (50, 50)
cv2.putText(img, text, text_position, font, font_scale, font_color, font_thickness)

# hiển thị file ảnh img
cv2.imshow('Image', img)
  
# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()