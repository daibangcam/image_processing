# khai báo thư viện
import numpy as np 
import cv2 
import time 
  
# Tạo đối tượng videocapture và đọc từ tệp video đầu vào 
# Thay đổi thành 0 nếu muốn đọc từ webcam 
cap = cv2.VideoCapture('01.mp4')  

# đánh dấu thời gian khi xử lý khung hình thứ n-1
prev_frame_time = 0  

# đánh dấu thời gian khi xử lý khung hình thứ n 
new_frame_time = 0
  
# Đọc tệp video cho đến khi hoàn thành 
while(cap.isOpened()):   

    # đọc lần lượt từng frame hình 
    ret, frame = cap.read()   
    
    # nếu ko đọc được frame hình (do hết video hoặc nguồn video lỗi)
    if not ret: 
        break  

    # cấu hình font sử dụng để hiển thị FPS 
    font = cv2.FONT_HERSHEY_SIMPLEX  

    # đánh dấu thời gian kết thúc xử lý cho khung hình này 
    new_frame_time = time.time()   

    # Tính toán FPS   
    # FPS sẽ là số khung hình được xử lý trong khoảng thời gian cụ thể 
    # vì thường có sai số là 0,001 giây nên chúng ta sẽ trừ nó để có kết quả chính xác hơn 
    fps = 1 / (new_frame_time - prev_frame_time)

    # cập nhật thời gian của khung hình thứ n thành thứ n-1
    prev_frame_time = new_frame_time 

    # Chuyển đổi FPS thành số nguyên 
    fps = int(fps)   

    # Chuyển đổi FPS thành chuỗi để hiển thị trên khung hình 
    fps = str(fps)   

    # Ghi số FPS lên khung hình 
    cv2.putText(frame, fps, (7, 70), font, 3, (100, 255, 0), 3, cv2.LINE_AA) 

    # Hiển thị khung hình với FPS 
    cv2.imshow('frame', frame )  

    # Ấn 'q' nếu muốn thoát 
    if cv2.waitKey(1) & 0xFF == ord('q'): 
        break  

# Khi hoàn thành, giải phóng việc chụp video 
cap.release() 

# Đóng tất cả các cửa sổ
cv2.destroyAllWindows()