> In this experiment we will connect to a **UDP** echo server using ESP32 SoC.

Before viewing the code, have a look at Arduino UDP
[APIs](ArduinoUdpAPIs.md).

### You will need following components to perform this experiment -

1. ESP32 development board - x1.

### You will need following software / accounts to perform this experiment -

1. Arduino IDE - https://www.arduino.cc/en/software
2. Python3 - should be installed on your computer; update or reinstall if required.

##### ESP32 development board pinout ( image source - https://circuits4you.com )

![ESP32](../images/ESP32_pinout.jpg)

### Instructions -

> Python3 must be installed on your system!

1. Inside the directory  **'empyrotech-iot-experiments/IOT-EXP3/udp_echo_server'** you will find the python script for echo server. This is named as **server.py**. Now, use the terminal application on your system to navigate to this directory. To start the echo server use the command - **python3 server.py**.

2. You can test the server by lauching the script **client.py** using another instance of the terminal applicaton. If every thing is alright then you get the following response upon launching the client script -
    
    `Echo from Server b'ping pong'`

> Arduino IDE must be installed for next step.

3. Open the source file **'IOT-EXP3.ino'**  location in the experiment directory. Now locate the follosing section and type in your WiFi credentials :

```cpp
/* Put your wifi credentials here */
const char* ssid = "xxxx";
const char* password = "xxxx";
```

> Next step is platform dependent.

4. Now determine the IP address of the machine on which the server program is running and substitute it in the following section of the source code :

```cpp
/* IP address and port of the echo server*/
const int port = 45555;
const char * host = "xx.xx.xx.xx";
```

5.  Compile the source code and check for errors (if any).

6.  Connect the ESP32 development board to your computer using the USB cable.

7.  Obtain the serial port number assigned to your development board __(this step varies with operating system)__.

8.  In Arduino IDE go to __Tools > Board > ESP32 Arduino__ and select __DOIT ESP32 DEVKIT V1__.

9.  In Arduino IDE go to __Tools > Board > Port__ and select __{COM port identified in step 7}__.

10. Upload the code to your development board.

## Testing - 

1. With the echo server running, power up the ESP32 development board.
2. Now determine the serial port of the ESP32 board and lauch the serial terminal application from Arduino IDE.
3. ESP32 will connect to your WiFi access point and start communicating with the echo server every 5 seconds.
4. The output on Serial Monitor would be like :

```
...
...

Sending
Echo - Seconds since boot: 1

Sending
Echo - Seconds since boot: 6

Sending
Sending
Sending
Echo - Seconds since boot: 21

Sending
Echo - Seconds since boot: 26


...
...

```
5. This indicates that ESP32 was able to communicate with the echo server using UDP protocol.

### Caution :

Disable firewalls on the computer running the server program. If any firewall is active then, it will prevent external connections.
