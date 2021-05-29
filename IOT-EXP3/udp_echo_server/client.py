import socket

msgFromClient       = "ping pong"
bytesToSend         = msgFromClient.encode()
serverAddressPort   = (socket.gethostname(), 45555)
bufferSize          = 1024 

# Create a UDP socket at client side
client = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
# Send to server using created UDP socket
client.sendto(bytesToSend, serverAddressPort)

(message, address) = client.recvfrom(bufferSize)
print("Echo from Server {}".format(message))