import cv2

cap = cv2.VideoCapture('01.mp4')
if not cap.isOpened():
    print("Error opening video stream or file")

# Lấy chiều rộng và chiều cao của video
frame_width = int(cap.get(3))
frame_height = int(cap.get(4))

# Định nghĩa codec và tạo đối tượng VideoWriter
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
output_video = cv2.VideoWriter('Nhom13_BT2.mp4', fourcc, 30, (frame_width, frame_height)  # Tăng FPS lên 60
)
detector = cv2.QRCodeDetector()
val = ''
x, y, w, h = 0, 0, 0, 0

while cap.isOpened():
    ret, frame = cap.read()
    if ret:
        frame_copy = frame.copy()
        val_temp, points, _ = detector.detectAndDecode(frame)

        if val_temp:
            # Nếu tìm thấy QR code mới, cập nhật giá trị và vị trí
            val = val_temp
            x, y, w, h = 0, 0, 0, 0

        if val:
            if points is not None:
                if len(points) > 0:
                    points = points[0].astype(int)
                    x, y, w, h = cv2.boundingRect(points)
                    cv2.rectangle(frame_copy, (x, y), (x + w, y + h), (0, 255, 0), 3)

        cv2.putText(frame_copy, val, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (244, 244, 44), 5)
        cv2.putText(frame_copy, 'Nhom13', (x, y + h +30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 5)

        output_video.write(frame_copy)

        cv2.imshow('Nhom13', frame_copy)
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break
    else:
        break

# Giải phóng tài nguyên
cap.release()
output_video.release()
cv2.destroyAllWindows()