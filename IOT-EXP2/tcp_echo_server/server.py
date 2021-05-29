import socket

HOST = socket.gethostname()
PORT = 8534

server = socket.socket( socket.AF_INET, socket.SOCK_STREAM)
server.bind(("0.0.0.0", PORT))
server.listen(5)

print("Listening on :", HOST, ",", PORT)

while True:
      (clientsocket, address) = server.accept()

      print("Client at : ", address)

      data = clientsocket.recv(1024)

      print("Data from client : ", data)

      clientsocket.send(data)

      clientsocket.close()

      print("Closed connection\n")

