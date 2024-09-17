# import thư viện
import cv2
import qrcode

# đọc file ảnh chứa qr code
img = cv2.imread("qr_code.png")

# show code qr
cv2.imshow("QR Code", img)

# gọi bộ giải mã qr code
detector=cv2.QRCodeDetector()

# giải mã qr code
val,b,c=detector.detectAndDecode(img)

# in ra nội dung qr code
print(val)

# chờ nhấn phím rồi thoát
cv2.waitKey(0)
cv2.destroyAllWindows()