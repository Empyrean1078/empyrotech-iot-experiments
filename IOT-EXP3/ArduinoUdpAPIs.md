## Arduino APIs for UDP protocol based communication

- `begin()`	Initializes the UDP instance at the specified port	`Udp.begin(port);`

- `available()`	Returns number of bytes in the data that has arrived and can only be called after Udp.parsePacket() function	`Udp.available();`

- `beginPacket()`	Begins connection with another instance of UDP with specified IP and Port.	`Udp.beginPacket(hostIP, port);`

- `endPacket()`	Closses the connection in which data is being sent and returns 1 if data was sent successfully.	`Udp.endPacket();`

- `write()`	Writes data to the other UDP instance.	`Udp.write(Data);`

- `parsePacket()`	Process the data that has arrived and has to be called before `Udp.read()`.	`Udp.parsePacket();`

- `peek()`	Reads 1 byte from the data without continuing the stream of data.	`Udp.peek();`

- `read()`	Reads data in a specified buffer	`Udp.read(buffer,maxsize);`

- `flush()`	Clears the buffer.	`Udp.flush();`

- `stop()`	Disconnect from current server.	`Udp.stop();`

- `remoteIP()`	Returns the IP address of the current incoming packet after `Udp.parsePacket();	Udp.remoteIP();`

- `remotePort()`	Returns the port of the UDP connection.	`Udp.remotePort();`