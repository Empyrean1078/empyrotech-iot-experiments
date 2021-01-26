## What is thingspeak ?

ThingSpeak is an IoT analytics platform service that allows you to aggregate, visualize and analyze live data streams in the cloud. ThingSpeak provides instant visualizations of data posted by your devices to ThingSpeak. With the ability to execute MATLAB® code in ThingSpeak you can perform online analysis and processing of the data as it comes in. ThingSpeak is often used for prototyping and proof of concept IoT systems that require analytics.

For more information visit the following link.
https://thingspeak.com/pages/learn_more

## How to use thinspeak ?

Thinspeak provide a convenient way to store IoT data. Thingspeak contains channels which may further contain upto 8 fields. Fields can be thought of as containers where the actual data will be stored. Channels are collection of fields.
Generally, different fields are used to store IoT data for different IoT devices. For example, we may create a channel to store weather related data which contains fields - temperature, humidity, precipitation, wind_speed, wind_direction.

Thingspeak supports REST APIs and MQTT APIs to read from or write to a field.

For more information visit the following link.


* __thingspeak documentation__ https://in.mathworks.com/help/thingspeak/
* __get started with thingspeak__ https://in.mathworks.com/help/thingspeak/getting-started-with-thingspeak.html
* __channel creation and configuration__ https://in.mathworks.com/help/thingspeak/users.html
* __writing data__ https://in.mathworks.com/help/thingspeak/write-data.html
* __reading data__ https://in.mathworks.com/help/thingspeak/read-data-from-channel.html
* __REST API reference__ https://in.mathworks.com/help/thingspeak/rest-api.html
* __MQTT API reference__ https://in.mathworks.com/help/thingspeak/mqtt-api.html

## Important Credentials to keep handy while working with thingspeak.

Login with your thingspeak account. Use the navigation bar to visit Channels > My Channels ( Create one channel if required ). You will now see a list of your private channels. Click on the channel you want to work with. Now using the channel navigation bar visit API keys section. Here you will find the following credentials. Note down these credentials as they will be used everytime you work with thingpspeak. __Make sure that these credentials are not comprommised because this will give an intruder access to all you IoT data on thingspeak!__

* __Channel ID__
* __Channel Write API key__ 
* __Channel Read API key__