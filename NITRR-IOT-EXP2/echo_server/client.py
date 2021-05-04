import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect( (socket.gethostname(), 8534) )
print("Connected to server!")

client.send(b'ping ping pong pong')
print("Message sent to server")

data = client.recv(1024)
print("Echo : ", data.decode())

client.close()