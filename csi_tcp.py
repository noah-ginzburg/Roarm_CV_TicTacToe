# pi_stream_server.py
import cv2
import socket
import struct
import pickle

# TCP socket setup
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("0.0.0.0", 9999))  # Listen on all interfaces, port 9999
server_socket.listen(1)
print("📡 Waiting for connection...")
conn, addr = server_socket.accept()
print("✅ Connected to:", addr)

# Open Pi camera via OpenCV
gst_str = ("libcamerasrc ! video/x-raw,width=1280,height=720,framerate=30/1 "
           "! videoconvert ! appsink")

cap = cv2.VideoCapture(gst_str, cv2.CAP_GSTREAMER)


while True:
    ret, frame = cap.read()
    if not ret:
        break

    #cv2.imshow("Camera", frame)
    #cv2.waitKey(1)  # 1ms delay so the window refreshes

    # Encode to JPEG to compress data
    encoded, buffer = cv2.imencode(".jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, 60])
    data = pickle.dumps(buffer)

    try:
        conn.sendall(struct.pack(">L", len(data)) + data)
    except BrokenPipeError:
        print("Client disconnected.")
        break
    

cap.release()
conn.close()
cv2.destroyAllWindows()