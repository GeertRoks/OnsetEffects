# Onset Augmented Effects
This repository is a collection of guitar effects that are augmented by onset detection. These effects are part of my Bachelor's thesis research.

### Examples


### Installation
~~~
git clone https://github.com/GeertRoks/OnsetEffects.git
make
sudo make install
~~~

### Usage
Import the VST or LV2 into your host of choice. Send audio through them and hear the result

##### Auto Sweller
Auto Sweller triggers an envelope generator for every onset detected. This envelope modulates the volume of the FX-loop. In the FX-loop can any effect be put.

###### Setup
- 1.) Send the instrument signal to input 1 (left channel).
- 2.) Send output 2 (right channel) to an effect of choice. Its output should be routed to input 2 (right) of the Auto Sweller effect. This creates a FX-loop.
- 3.) Output 1 (left) of the AutoSweller is the effect output and should be routed to the master.

##### Random Delay
Random Delay sets a new delay time for every note played. This note is chosen randomly, but the range of notes can be choosen. The delaytimes are note lenghts of the chosen bpm. So a halve note takes longer at 60bpm than at 140.


### License
This repository makes use of aubio, which is licensed under GPLv3. Therefore, is OnsetEffects also licensed under GPLv3.
OnsetEffects is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
Use this software at your own risk. The author is not accountable for any damage this software may produce.
