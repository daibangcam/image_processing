# import thư viện
import cv2
import numpy as np
  
# Đặt kích thước file ảnh muốn tạo
height = 360
width = 480
  
# tạo file ảnh đen với kích thước định trước
# trong đó "3" là depth (ảnh màu) - số lớp (BGR)
img_black = np.zeros((height,width,3), np.uint8)

# tạo file ảnh trắng với kích thước định trước
# trong đó "3" là depth (ảnh màu) - số lớp (BGR)
img_white = np.ones((height,width,3), np.uint8)
# mỗi giá trị pixel của file ảnh mới tạo đều = 1
# để ảnh trắng hoàn toàn thì mỗi giá trị pixel phải = 255
# nên ta nhân 255 với từng giá trị điểm ảnh
img_white = 255*img_white 

# tạo file ảnh xanh dương với kích thước định trước
# trong đó "3" là depth (ảnh màu) - số lớp (BGR)
img_blue = np.ones((height,width,3), np.uint8)
# 3 lớp màu BGR + ảnh màu xanh dương
# suy ra lớp G, R giá trị pixel = 0
# còn lớp B giá trị mỗi pixel = 255 (tùy mức mà xanh đậm nhạt khác nhau)
img_blue[:,:] = (255,0,0) 

# tạo file ảnh trắng với kích thước định trước
# trong đó "3" là depth (ảnh màu) - số lớp (BGR)
img_mix = np.ones((height,width,3), np.uint8)
# mỗi giá trị pixel của file ảnh mới tạo đều = 1
# để ảnh trắng hoàn toàn thì mỗi giá trị pixel phải = 255
# nên ta nhân 255 với từng giá trị điểm ảnh
img_mix = 255*img_mix 
# tô màu đỏ từ từ (0,0) đến (100,100)
img_mix[0:100,0:100]=(0,0,255)

# hiển thị file ảnh img
cv2.imshow('Black Image', img_black)
cv2.imshow('White Image', img_white)
cv2.imshow('Blue Image', img_blue)
cv2.imshow('Mixed Image', img_mix)
  
# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()