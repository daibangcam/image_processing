﻿# import thư viện OpenCV
import cv2
  
# gán video 01.mp4 vào biến cap
cap = cv2.VideoCapture('01.mp4') 

# kiểm tra xem video đã được load vào cap chưa
# nếu chưa được (file lỗi/ko tồn tại) thì báo
if (cap.isOpened()== False): 
  print("Error opening video stream or file")

# đọc video đến khi kết thúc (hết frame hình)
while(cap.isOpened()):
  # load lần lượt frame 1, 2, 3... đến frame cuối
  ret, frame = cap.read()
  # nếu load dc frame
  if ret == True: 
    # hiện frame
    cv2.imshow('Frame',frame) 
    # nếu nhấn phím Q thì thoát vòng lặp -> ngừng video
    if cv2.waitKey(25) & 0xFF == ord('q'):
      break 
  # nếu ko load dc frame -> thoát vòng lặp -> ngừng video
  else: 
    break 
    
# giải phóng bộ nhớ
cap.release() 
# đóng hết cửa sổ
cv2.destroyAllWindows()