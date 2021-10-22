## Arduino Function Generator 
>the DIY function generator using an Arduino



## Table of contents
* [Project description](#Project-description)
* [Future set ](#Future-set)
* [Progress ](#current-progress-of-the-project.)
* [Schematic explanations](#EXPLANATION-OF-DIFFERENT-OP-AMP-STAGES)
* [Status](#Status)


## Project description 
This is my design files and progress on my take on building a Function generator . The main chip responsible for generating the waveforms is the Analog devices AD9833. This is a very capable chip  , it can gererate sine, triangle and square waves from 0.1 Hz to 12.5 MHz although the target will  be using it with a maximum of 10mhz.


## Future set 
The target future set will be the following 
* Bandwidth 10MHz
* 12vPP amplitude 
* 6v offset
* Full digital control of every parameter . 


# Current progress of the project. 
Building a Function generator proven to be quite a complex task , from the symmetrical psu needed to power the operational amplifiers to the voltage references used  to “normalize” the AD9833`s output that has a +300mV offset plus the lack of free time to debug hardware on the breadboard lead to the project be left aside . the following items are what is being found working at some point . 

# Schematics 
* Power supplies
    *Dual power supply without center tap transformer (not recommended ,it does not have full bridge rectifier)
    ![NoCenterTapTrafo](https://github.com/finos2/Arduino-Function-Generator/blob/main/IMG/Symetrical%20Power.png?raw=true)
    *Dual power supply with center tap transformer (recommended but more expencive)
    ![CenterTapTrafo](https://github.com/finos2/Arduino-Function-Generator/blob/main/IMG/Symetrical%20Power%20V2.png?raw=true)
* Front end : 
    ![frontEnd](https://github.com/finos2/Arduino-Function-Generator/blob/main/IMG/Front%20End.png?raw=true)

* offset control 
![offset](https://github.com/finos2/Arduino-Function-Generator/blob/main/IMG/Offset%20Dac.png?raw=true)
* UI design 
#  Explanation of different op amp stages 

* Offset correction 
The AD9833 as mentioned previously outputs a “bad” signal containing a +300mV DC offset , while outputting sine and triangle waves and this is quite undesirable. So to rectify this I used a voltage Summing circuit , to add -300mv so the signal will be back to “normal” AC , or how I want it to be output . the opamp there (NE5532) U10.1 , being part of the circuit , serves as a voltage follower . 
[…..] 
* Output amplification
    i wanted my generator to have a 10Vpp output , and the digital potentiometer (MCP41HV51) U8 cannot handle it , so up to this op-amp i have a "low" voltage then i boost it to the desired level.



## Status
Project is: _in progress_,  but  _no longer continue_  due to constrained free time cause of University , I might get back to it at some point
