# import thư viện OpenCV
import cv2  
# gán file ảnh 01.jpg vào biến img
img = cv2.imread('01.jpg')
# đặt tên cửa sổ hiển thị file ảnh với tham số WINDOW_AUTOSIZE
# kích thước cửa sổ được auto xác định theo kích thước file ảnh
cv2.namedWindow("Original RGB", cv2.WINDOW_AUTOSIZE)
# hiển thị file ảnh img
cv2.imshow('Original RGB', img)
# gọi h1, w1, d1 là 3 biến chứa thông tin ảnh img, bao gồm
# h1 = height = chiều cao ảnh
# w1 = width = chiều rộng ảnh
# d1 = depth = độ sâu ảnh (bit màu)
(h1, w1, d1) = img.shape
# in ra giá trị w1, h1
print("width={}, height={}".format(w1, h1))
# khai báo width của ảnh resize
w2 = 360
# tính height của ảnh resize với tỉ lệ w/h của ảnh gốc
h2 = int(w2*h1/w1)
img_resize = cv2.resize(img, (w2,h2))
cv2.imshow('Resize Image', img_resize)
# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()