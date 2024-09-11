# import thư viện OpenCV
import cv2

# load thư viện nhận diện khuôn mặt vào biến haar_cascade (đặt tên biến tùy ý)
haar_cascade = cv2.CascadeClassifier('Haarcascade_frontalface_default.xml')
  
# load ảnh
img = cv2.imread('01.jpg')
  
# chuyển sang ảnh xám
gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
  
# nhận diện khuôn mặt có trong hình bằng cách gọi thư viện nhận diện mặt đã khai báo
# kết quả trả về là biến faces_rect (đặt tên biến tùy ý) chứa thông tin các khuôn mặt phát hiện được
# trong đó mỗi khuôn mặt sẽ gồm 4 thông số x,y,w,h của hình chữ nhật nhỏ nhất bao quanh khuôn mặt
# x, y: tọa độ điểm bắt đầu (góc trên bên trái) của hình chữ nhật nhỏ nhất bao quanh khuôn mặt
# w: chiều rộng của hình chữ nhật nhỏ nhất bao quanh khuôn mặt
# h: chiều cao của hình chữ nhật nhỏ nhất bao quanh khuôn mặt
faces_rect = haar_cascade.detectMultiScale(gray_img, 1.1, 9)
# tham số 1.1 được điều chỉnh để đảm bảo nhận diện chính xác, ko bỏ sót khuôn mặt
  
# vẽ lại đường bao các khuôn mặt lên ảnh gốc
# vòng lặp xét lần lượt khuôn mặt đầu tiên đến khuôn mặt cuối cùng đã phát hiện được
for (x, y, w, h) in faces_rect:
    # vẽ hình chữ nhật bao quanh khuôn mặt phát hiện được
    cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)

# show ảnh kết quả
cv2.imshow('Detected faces', img)

# đợi người dùng nhấn phím bất kì
cv2.waitKey(0)
  
# xóa toàn bộ cửa sổ đã tạo ra
cv2.destroyAllWindows()