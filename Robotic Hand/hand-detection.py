import cvzone
import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject

# Initialize the webcam capture
cap = cv2.VideoCapture(0)

# Create a HandDetector object for hand tracking
detector = HandDetector(maxHands=1, detectionCon=0.7)

# Create a SerialObject for communication with Arduino over serial port
mySerial = SerialObject("COM5", 9600, 1)

while True:
    # Read a frame from the webcam
    success, img = cap.read()

    # Detect hands in the frame using the HandDetector
    hands, bboxInfo = detector.findHands(img)

    if hands:
        # Get the finger positions using the HandDetector
        fingers = detector.fingersUp(hands[0])
        print(fingers)

        # Send the finger positions to the Arduino over serial
        mySerial.sendData(fingers)

    # Display the image with any detected hands
    cv2.imshow("Image", img)

    # Exit the loop when the Esc key is pressed
    if cv2.waitKey(1) & 0xFF == 27:  # Press Esc key to exit
        break

# Release the webcam and close all OpenCV windows
cap.release()
cv2.destroyAllWindows()
