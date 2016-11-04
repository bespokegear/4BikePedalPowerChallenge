# 4BikePedalPowerChallenge
Code for a 4- bike pedal power challenge unit. Arduino Mega Code and Processing code


#Pedal Power Unit Program Specifications
#####Written by: 	Matt Little
#####Date:		3/11/2016	
#Overview
This unit has:
* 4 x Pedal generators as inputs
* 4 x Current and Voltage sensors (measuring the 4 inputs)
* 4 x Resistive loads controlled by PWM controllers
* 4 x LED output panels (each Neopixel based (ws2811) LED units. 60-180 LEDs in each display
* 2 x Input Switches
* 2 x Remote input switches
* 1 x Serial output (wired) 115200 Baud
* 1 x Serial output (wireless) 115200 Baud
* 1 x Timer display 3 digits (Serial data clocked out)
* 1 x Arduino Mega for control functions

At ALL times the units will control the PWM output of each ‘player’ to ensure the voltage over goes above 50V DC.
The Load will kick in at 12V DC (PWM = 0%) and go to a maximm at 50V DC (PWM = 100%). This might not be linear. This depends upon ‘feel’ of units...


The idea is that four cyclists will be in a race and each one is trying to generate the highest power. (At present this is POWER to be measured. This might change to ENERGY, which will be cumulative power over time).

Each 'race' will take 30 - 180 seconds (this will vary and be adjustable).

The race will start by pressing the GREEN button (or A on remote).
A reset can be performed at any time by pressing RED button (or B on remote)

Serial Data: 'aRESET'

We want to give a 5...4...3..2...1.. Countdown on the timer.

Serial Data: '''"aSTART"'''

Timer will then start to count down from (say) 30 Seconds in 0.1 Second intervals.

Every 0.25 Seconds the power for all 4 players will be calculated.
The maximum power will be stored within the Arudino for EACH player.

This data will be streamed out on the serial port in the format:
'''"aA*****B*****C*****D*****T******t"'''

This will have the data:
Cyclist A has power '***.**', where this will be a number in Watts from 000.00 to 999.99.
Cyclist B has power '***.**', where this will be a number in Watts from 000.00 to 999.99.
Cyclist C has power '***.**', where this will be a number in Watts from 000.00 to 999.99.
Cyclist D has power '***.**', where this will be a number in Watts from 000.00 to 999.99.

T is the time since the race started in milliseconds (so 0.0001 seconds up to 999.9999 seconds).

The power will also be displayed on each of the LED outputs.
This will light up four different colours depending upon the player:

* Player A = Red
* Player B = Green
* Player C = Blue
* Player D = Yellow

The display will show the proportion of the maximum power (Pmax is the same for all players).

This will be updated every 0.25 seconds, but we might need to smooth it….depends how it looks.

At the end of the race (when timer = 0).
The race will finish with the command:
'''"aEND"'''
The arduino will then send the data of the highest score from each cyclist in the format:
'''"aRESULTA*****B*****C*****D***** t"'''

The person with the highest power will get a ‘reward’ on their LED display.
This can be a flashing reward, as we worked with on LED fairy lights. Not sure what is required here, but need to keep this configurable.

#Adjustable parameters:
We will need to be able to adjust some parameters ‘on the fly’.
These need to be stored in EEPROM when adjusted.

##Timer Value: This can be in whole seconds from 0-999. 
Set using the Timer display.

##Number of LED units attached to each LED output.
The LED units are configurable to have either 1,2 or 3 units. This equates to 60/120/180 in a string.

##The maximum power displayed.
This is a value from 100-999W.
Set using the Timer display.
#Overview Diagram:

#Arduino Pins:
Arduino Mega Connections

|Pin | Function | Notes|
|----|:----------:|------|
|D0:|Rx0 |DEBUG|
|D1:|Tx0 |DEBUG|
|D2:~||| 
|D3:~|||
|D4:~|||
|D5:~|||
|D6:~ |PWM1||
|D7:~ |PWM2||
|D8:~ |PWM3||
|D9:~ |PWM4||
|D10:~ |REM 1|Remote Switch A|
|D11: ~ |REM 2|Remote Switch B|
|D12: ~|||
|D13: ~ |||
|D14: |LED 1||
|D15: |LED 2||
|D16: |LED 3||
|D17: |LED 4||
|D18:|Tx1 EXT|XRF wireless output|
|D19:|Rx1 EXT|XRF wireless output|
|D20: |SW1|GREEN switch|
|D21: |SW2|RED Switch|
|D22: |sLATCH||
|D23: |||
|D24: |sDATA||
|D25: |sENABLE|Enable display. Low = ON|
|D26:|||
|D27: |sCLK||
|D28:|||
|D29:|||
|D30:|||
|D31: |||
|D32: |||
|D33: |||
|D34:|||
|D35:|||
|D36:|||
|D37:|||
|D38:|||
|D39:|||
|-----|-----|------|
|A0: |V1||
|A1: |I1||
|A2: |V2||
|A3: |I2||
|A4:| V3||
|A5:| I3||
|A6:| V4||
|A7:| I4||
|A8:||| 
|A9:|||
|A10:|||
|A11:||| 
|A12:|||
|A13:|||
|A14:|||
|A15:|||

#Voltage and Current Sensors:
These monitor the power from the cyclist.
They have a resistive voltage sensor with the values:
R1 = 560k and R2 = 10k.
The actual voltage = read voltage * (570k /10k)

Current sensors are Allegro ACS756SCB-050B-PFF-T  Bi-Directional 50A hall effect current sensors:
http://www.allegromicro.com/en/Products/Current-Sensor-ICs/Fifty-To-Two-Hundred-Amp-Integrated-Conductor-Sensor-ICs/ACS756.aspx

They output a voltage proportional to the current flowing.
The voltage at NO current is ½ of the supply voltage.
They output (either + or – from the no current voltage) 40mV/A (at 5V supply)
But the output is proportional to the supply voltage, so at 3.3V they will output 40 *3.3/5 mV/A.
We can assume that the supply voltage is 5V and tweak for actual values.
So conversion is:
Current = (Read Voltage – (Vs/2)) / 0.04
Voltage at +50A = 4.5V or -50A = 1V

The power is then calculated.


#PWM Motor Controllers:

4 x PWM outputs required.
Measuring the voltage and increasing/decreasing the PWM as required.
PWM = 0% at 12V (equals 0 power)
PWM = 100% at 50V (equals 833W)
LED Outputs:

There will be 4 neopixel LED outputs.
Each controlled by a different digital pin.
Each LED array can be built from 1,2 or 3 lots of 60 LED units (so 60/120/180 LEDs in a string).
Need to do the same thing for each ‘pair’ of LEDs, as they are arranged to give 30 levels.
Serial Output:
115200 Baud 8N1
Same data on Serial( lead) and Serial1 (wireless)

#Display Program:
This has been written in processing and take the serial output from the Arduino and displays and records the data.

The display program will be a separate program which will run on a PC and display information via a projector.

The application must be stand-alone, easy to install with no additional programs and cross-platform.

"Processing" is suggested as the program to use for this. It is multi-platform, free, open and easy to use/alter.

The display program will take a serial string of data and display the information within four quadrants of the screen, one for each cyclist.
Each cyclist (A,B,C,D) has a different colour. These are (but need to be adjustable):
A = Red
B = Green
C = Blue
D = Yellow

The application will need to keep a record of the power data and the time.

This data will be saved as a .csv file with the date and time used as the filename. This is for any future analysis.

The race is totally controlled by the Power Control Box. This uses an Arduino Mega which will send commands via an 8-N-1 serial connection at 115200 baud.

This might be a direct Serial-USB connection or it could be a wireless serial link, both should work the same.

The reset command will be sent 5 seconds before the race starts. This will reset the power values to zero.
"aRESET"

The race will start with the command:

"aSTART"

Data will then be sent every (approx) 0.25 seconds in the format:
"aA*****B*****C*****D*****T******t"

This will have the data:
Cyclist A has power ***.**, where this will be a number in Watts from 000.00 to 999.99.
Cyclist B has power ***.**, where this will be a number in Watts from 000.00 to 999.99.
Cyclist C has power ***.**, where this will be a number in Watts from 000.00 to 999.99.
Cyclist D has power ***.**, where this will be a number in Watts from 000.00 to 999.99.

T is the time since the race started in milliseconds (so 0.0001 seconds up to 999.9999 seconds).

This data will also be written to a .csv file along with the timestamp.

The race will finish with the command:
"aEND"
The arduino will then send the data of the highest score from each cyclist in the format:
"aRESULTA*****B*****C*****D***** t"
 
These will then be displayed on the screen with the winning cyclist flashing in their colour, while the other cyclists will see their score but in slightly smaller/subdued lettering.

The yellow colour would be flashing to make it more obvious.

This will be shown until the next race is started.

What if two people get the same power?
We might need to show the power with a decimal point, just in case two people get the same max power. 
OR
We could just highlight both the power readings and say they are equal
This is to be decided....
Future add-ons:

Want to be able to show the power values as a graph behind the actual value. This will show the peak through the race.

Convert this into showing the energy generated. This will be done within the Arduino and the data sent out as Energy within the previous time period (rather than power).
We should be able to calculate this as well.

