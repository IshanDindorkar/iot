MagicMirror DIY Project -->>

This project is kind of DIY project where we can see interplay of various modules working in tandem with each other to give us information like what are holidays, current time, weather, forecast, news etc. All this information is made to be displayed in the context of a mirror and information makes a normal 2-way mirror appears as "SMART".

Lot of open source material is already available and this exercise use one such Github repository to see how we can make a mini MagicMirror ourseleves using RaspberryPi

Steps for getting started --

1. Clone this repo -
https://github.com/MichMich/MagicMirror

2. Explore the repo to check general codebase

3. You will find dependencies to be installed in package.json

4. Install npm manager if not so

5. Run npm install to install all dependencies, will take some time

6. Copy config/config.js.sample to config/config.js

7. All changed config and other source code is available under IoT/tutorials/RaspberryPi/magic_mirror

8. You will also have to create an account on openweathermap to get API keys in order to access weather information. Put these API keys in config.js

Steps for creating own module: Fortune --

1. you will find all code under magic_mirror/fortune folder

2. also install fortune utility using this command -
sudo apt-get install fortune

3. make sure all new JS files for your module are placed in folder of the same name like in this case our module is named as fortune so we created a folder called as fortune and placed it under MagicMirror/modules/
Note: Do not create your module under default/

4. For every module there is a main JS file and in case if we have to use some shell command like invoke "fortune -s" command and print its output as widget in the smart mirror, we use node_helper JS which is created in the same folder - fortune along with main JS fortune.js
