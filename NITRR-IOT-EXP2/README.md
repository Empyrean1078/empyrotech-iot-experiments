> In this experiment we will connect to a socket echo server using ESP32 SoC.

### You will need following components to perform this experiment -

1. ESP32 development board - x1.

### You will need following software / accounts to perform this experiment -

1. Arduino IDE - https://www.arduino.cc/en/software
2. Python3 - should be installed on your computer; update or reinstall if required.

##### ESP32 development board pinout ( image source - https://circuits4you.com )

![ESP32](/images/ESP32_pinout.jpg)

### Instructions -

> Python3 must be installed on your system!

1. Inside the directory  **'empyrotech-iot-experiments/NITRR-IOT-EXP2/echo_server'** you will find the python script for echo server. This is named as **server.py**. Now, use the terminal application on your system to navigate to this directory. To start the echo server use the command - **python3 server.py**.

2. You can test the server by lauching the script **client.py** using another instance of the terminal applicaton. If every thing is alright then you get the following response upon launching the client script -
    ```
    Connected to server!
    Message sent to server
    Echo :  ping ping pong pong
    ```

> Arduino IDE must be installed for next step.

3. Open the source file **'NITRR-IOT-EXP2.ino'**  location in the experiment directory. Now locate the follosing section and type in your WiFi credentials :

```cpp
/* Put your wifi credentials here*/
const char* ssid = "xxxx";
const char* password = "xxxx";
```

> Next step is platform dependent.

4. Now determine the IP address of the machine on which the server program is running. Now substitute the IP address in the following section of the source code :

```cpp
/* IP address and port of the echo server*/
const uint16_t port = 8534;
const char * host = "xx.xx.xx.xx";
```

5.  Compile the source code and check for errors (if any).

6.  Connect your ESP32 development board to your computer using the USB cable.

7.  Obtain the port number assigned to your development board __(this step varies with operating system)__.

8.  In Arduino IDE go to __Tools > Board > ESP32 Arduino__ and select __DOIT ESP32 DEVKIT V1__.

9.  In Arduino IDE go to __Tools > Board > Port__ and select __{COM port identified in step 7}__.

10. Upload the code to your development board.

### Testing - 

1. With the echo server running, power up the esp32 development board.
2. Now determine the serial port of the esp32 board and lauch the serial terminal application in Arduino IDE.
3. Now, ESP32 will connect to your WiFi network and start communicating with the echo server every 5 seconds.
4. The output on Serial Monitor would be :

```
...
...
WiFi connected with IP: 192.168.225.55

Connected to server...
Sent : ping pong
9
Echo :ping pong
Disconnecting...

Connected to server...
Sent : ping pong
9
Echo :ping pong
Disconnecting...

```
5. This indicates that ESP32 was successfully able to communicate with the echo server over TCP connection.

### Caution :

Disable firewalls on the computer running the server program. If any firewall is active then, it will prevent external connections.
