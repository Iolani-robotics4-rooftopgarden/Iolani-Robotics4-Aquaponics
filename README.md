# Aquaponics-Robotics-4-Project
This is a file of code that was used to create our aquaponics monitoring system that consist of the following:
* Temperature of the water
* Water level

  It also consist of a fish feeder that is autonomously and manually activated. This project is used to help the teachers and staff
help with taking care of the aquaponics system. This project will make their job easier by allowing them to monitor the aquaponics
system from their laptop /computer instead of going out and looking/taking tests for the system. This project is  specified
to the aquaponics system at our school, but it can be modififed if needed to suite the needs of others that use this project. 
## Getting Started
These are the supplies needed to recreate this project:
* ESP8266 which can be found here: [ESP8266 NodeMCU]( https://www.amazon.com/HiLetgo-Version-NodeMCU-Internet-Development/dp/B010O1G1ES/ref=sr_1_3?s=electronics&ie=UTF8&qid=1505504360&sr=1-3&keywords=esp8266)
* Temperature sensor which can be found here: [Temperature Sensor](https://www.sparkfun.com/products/11050)
* Arduino Uno which can be found here: [Arduino](https://www.amazon.com/MakerBest-Quality-Compatible-ATmega328P-Development/dp/B00Q6ZW4NO/ref=sr_1_7?s=electronics&ie=UTF8&qid=1505504649&sr=1-7&keywords=arduino+uno)
* Water level sensor which can be found here: [Water Level Sensor](https://www.amazon.com/uxcell-Pieces-ZP4510-Vertical-Switches/dp/B00FHAEBIA/ref=sr_1_3?s=industrial&ie=UTF8&qid=1505504811&sr=1-3&keywords=float+sensor)
* RTC "Real Time Clock" which can be found here: [RTC](https://www.amazon.com/DS3231-AT24C32-module-precision-Arduino/dp/B00HCB7VYS)

### Prerequisites
  For an IoT (Internet of Things) interface, we use [Ubidots](https://ubidots.com/) to create a platform for the ESP8266 to send and receive
data from. This website allows you to customize your interface so that data can be shown in graphs or in tables. The website also allows you
to create  buttons that can be used to send HIGH or LOW values to the device. For example, we used a table to layout the temperatuer data
and we used a meter that consisted of values 1 - 5 in order to show the water level that the qauaponics system was at. We also used a button
to manually activate the fish feeder.

Here are the programs that will be needed:
* [Arduino IDE](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwio8JOU_afWAhWGvLwKHVbQChoQFgglMAA&url=https%3A%2F%2Fwww.arduino.cc%2Fen%2FMain%2FSoftware&usg=AFQjCNHz_7o9OaPrjA55KOEPASoC8HSgK)

Here is the libraries needed in order to use the code:
* [Ubidots ESP8266 Library](https://github.com/ubidots/ubidots-esp8266-serial/archive/master.zip)
* [OneWire Library](https://github.com/PaulStoffregen/OneWire)
* [Dallas Temperature Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)
* [Servo Library](https://github.com/arduino-libraries/Servo)

### Installing
After installing the libraries needed and the Arduino IDE, open the IDE and keep the libraries on the desktop. Once the IDE is open, these are the steps to downloading the board and placing the libraries into the IDE. 
#### Getting the Board onto the IDE
* Go to File > Prefrences
* Copy the url and place it into the Additional Boards Manager URLs box.                                                                   (Copy this URL http://arduino.esp8266.com/stable/package_esp8266com_index.json)
* Press OK 
* Go to Tools > Board > Boards Manager 
* In the search box, type ESP8266
* Click on box and then click on the install button (the installation process may take a couple of minutes depending on your WiFi)
#### Getting the Libraries onto the IDE
* Go to Sketch > Include Library > Add .zip Library
* Drag the library folder from your desktop into the library folder that was just opened 
* Close the folder and the IDE is ready to go
### Coding (For the esp8266)
Once you have set up the IDE for the esp8266, follow the steps bellow to program the microcontroller:
#### Changing the Code
* Copy and Paste the code in the Master-Code-ESP.ino, that can be found in the Source folder on this GitHub, into the Arduino IDE
* Change the ID1, ID2, ID3, and ID4 tokens based on the ID tokens that is in Ubidots
* Change the WIFISSID to the name of the WiFi router
* Change the PASSWORD to the passwrod of the WiFi router
#### Uploading the Code
Once the steps from above have been followed and done, follow these steps to upload the code onto the esp8266:
* Plug in the esp8266 into the computer by using a USB to microUSB connector
* Go to Tools > Port > choose the port that the USB is plugged into (normally it would be the only port that shows up if there is nothing else plugged into the computer except for the USB connected to the esp8266)
* Press the arrow on the top right corner that is pointing toward the right (this is the upload button that is used to upload code onto the board; The check-mark icon is to verify your code just incase something is wrong)
### Setting up Ubidots
Ubidots is an IoT website that allows user to send and receive data to a microcontroller via WiFi or Cellular. This website will be used to gather the temperature and water level from the aquaponics system and that data will be displayed on the Ubidots dashboard. Ubidots is also being used for the fish feeder manual button that will allow users to activate the fish feeder at any specfific time. 
#### Creating an Account
Use the following steps to create an account for Ubidots:
* Go the the [Ubidots](https://app.ubidots.com/accounts/signup/) website
* Click on "Sign Up"
* Go through the registering application and the account will be created
Note that Ubidots has an education platform and a busniness platform. The difference between the two is data storage and the range of widgets that can be used on the dashboard. The education application suits this project the best becuase it is not only free but it allows the user to have an easier time looking at data. 
#### Connecting the ESP8266 to Ubidots
In order for the esp8266 to send data to Ubidots, the device must be connected to the users Ubidots account. The following steps will showcase what to do:
* Click on the option menu on the top right hand corner (looks like three lines stacked ontop of each other)
* Click on devices and then click on the yellow circle with the plus sign inside of it
* Name the device whatever suits the project best (For this case, the name given to the device was Rooftop_Garden_io)
* Once the device is created click on the device block (This block will showcase the the ID for that sepcific device)  
#### Creating a Variable in Ubidots
Once the device has been created, the variables will be declared in the device dashboard so that the information coming from the esp8266 can be recieved on Ubidots side. This declaring of variables is so that Ubidots knows what data points are what in when it is received. The following steps will showcase how to do this:
* Once you are in the designated device's dashboard, click on the "Add Variable" icon on the bottom (choose the default variable and a yellow box will be created)
* Name the first variable "Temp" (this variable will be for the temperature data)
* Create three more variables with the names "FloatSensor", "FishFeeder", and "Time"
* Click on the variables that were just created and the ID's for each variable must be placed in the code for the esp8266 (See the coding section of the document to find where to place these ID's)
The variables needed for thsi project should all be created after this step
#### Creating the Dashboard in Ubidots
If the variables needed for the dashboard where not created, please see the section above. Once the variables are created for the dashboard, follow the following steps to creating and customizing the dashbaord.
* Click on the three bar tab on the top right corner of the page and click on Dashbaords
* Once in the dashbaord, click on the yellow button with the "+" sign in it. This will be where widgets can be added to the dashboard
* Once in the New Widget page, seven widget options are available to the use
----------------------------------------------------------------------------
##### Widget's and What they do
Each widget being added to the dashboard has its own functions. Here are the seven widgets and what they do:
* Chart: creates a chart with data points on what variable data it has been receiving. Some of the charts that can be used in this widget are Line, Double axis, Scatter Plot, Histogram, and a Bar chart
* Metric: creates a display for different kinds of data evaluation. Some of the evaluations are Average, Maximum, Minimum, Sum, Count, and Last value
* Map: allows users to see where there gps sensor is or a specific location the user puts into the map function
* Table: creates a table based on the last value received or a table with historical value
* Indicator: creates an indicator that can be an on/off switch, a gauge, or a tank (liquid)
* Control: creates a widget that can send data to the Electron or microcontroller being used. This widget is normally used to control a motor or used as an on/off switch on the microcontroller 
* HTML Canvas: creates a box that can be placed with text using HTML code
----------------------------------------------------------------------------
* The widget that are being used is the table widget and select the last value 
* Add the temperature variable
* Once done, click finish and the widget is created
* Create a widget for the float sensor using the gauge widget under the indicator branch
###### Note: the sensors may ask to select a device. If this happens, select the device name given for the ESP8266
* Create a widget for the fish feeder using the switch widget under the control branch
* Once hte widgets have been created, the widgets are ablel to move around the dashboard in order to personlize it for the user. If the user chooses to move the widgets, they must make sure that the dashboard is unlocked (which can be seen using the lock icon). If the dashboard is unlocked, widgets are ablel to move free. But, if the dashboard is locked, widgets will stay in the place they were last put in. 


