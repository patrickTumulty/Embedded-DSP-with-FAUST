# Embedded-DSP-with-FAUST

This project was the product of a workshop attended at CCRMA, Stanford University. For one week, we sat in on lectures taught by Romain Michon (GRAME-CNCM, Lyon (France) & CCRMA, Stanford University (USA)) and John Berger (University of Michigan (USA)). We learned about the FAUST programming language and how it can be utilized to create and implement extremely low latency DSP algorithms in embedded systems. For our projects we used a Teensy 3.6 and the SGTL5000 Audio Shield . We were able to achieve extremely low latency by overriding the Teensy to get our buffer size down to only 8 samples. In addition we also modified our FAUST algorithms to account for the limited system memory available on the Teensy 3.6.

My project was a harmonizer guitar pedal. I was interested in exploring the momentary pitch shift that occures when you modify the delay time during playback. My pedal featured four knobs. Three of the knobs would control the three voices that were being pitch shifted. One knob controlled pitches between unison and one octave, the other one to two octaves and the last controlled unison to one octave below. Each pitch knob cycles through a thirteen tone (0 - 12), chromatic scale. The fourth knob is a simple wet dry parameter to control how much the original guitar signal would be added to the output.    

![In Progress](/Images/GTR_PDL_APRT.jpg)

![Finished](/Images/GTR_PDL.jpg)

