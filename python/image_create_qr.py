# import thư viện
import cv2
import qrcode

# nhập nội dung cần mã hóa QR
my_url = "https://hano.cf"

# cấu hình thông số code QR
qr = qrcode.QRCode(version=1, box_size=10, border=5)
qr.add_data(my_url)
qr.make(fit=True)

# tạo code QR
img = qr.make_image(fill='black', back_color='white')

# save mã QR ra thành file
img.save("qr_code.png")

# load ảnh QR code
img_qr = cv2.imread("qr_code.png")

# show code qr
cv2.imshow("QR Code", img_qr)

# chờ nhấn phím rồi thoát
cv2.waitKey(0)
cv2.destroyAllWindows()