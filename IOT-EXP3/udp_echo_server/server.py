import socket

localIP     = socket.gethostname()
localPort   = 45555
bufferSize  = 1024

# Create a datagram socket
server = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Bind to address and ip
server.bind(("0.0.0.0", localPort))

print("UDP server up and listening on ", localIP)
 
# Listen for incoming datagrams
while(True):
    (message, address) = server.recvfrom(bufferSize)

    print("Message from Client:{}".format(message))
    print("Client IP Address:{}".format(address))

    # Sending a reply to client
    server.sendto(message, address)