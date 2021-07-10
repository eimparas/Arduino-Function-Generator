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

#Schematics 

* Front end : 
    ![frontEnd](/IMG/Front End.png)


* offset correction , signal offset &final amplification opamp stages (front end SCH) 
* offset control 
* UI design 
#  Explanation of different op amp stages 

* offset correction 
The AD9833 as mentioned previously outputs a “bad” signal containing a +300mV offset , while outputting sine,  triangle and square waves , and this is quite undesirable. So to rectify this I used a voltage Summing circuit , to add -300mv so the signal will be back to “normal” , or how I want it to be output . the opamp there (NE5532), being part of the circuit , serves as a voltage follower . 
[…..] 


## Status
Project is: _in progress_,  but  _no longer continue_  due to constrained free time cause of University , I might get back to it at some point
