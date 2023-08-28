import cvzone
import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject

cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands = 1, detectionCon = 0.7)
mySerial = SerialObject("COM5",9600,1)

while True:
    success, img = cap.read()
    hands, bboxInfo = detector.findHands(img)
    if hands:
        fingers = detector.fingersUp(hands[0])
        print(fingers)
        mySerial.sendData(fingers)
    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == 27:  # Press Esc key to exit
        break

cap.release()
cv2.destroyAllWindows()

