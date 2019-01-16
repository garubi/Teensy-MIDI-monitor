# Teensy-MIDI-monitor
Display on Arduino Serial Monitor the incoming MIDI messages

This sketch reads the incoming MIDI messages from a "standard" MIDI port, i.e. the serial one, those classic 5 pin DIN ports, ok? Here we are not dealing (at the moment) with usbMIDI

It proved to be very useful during the test / dubug phase of MIDI IN interfaces.

## Building the MIDI interface

First of all you have to work a hardware level to build a MIDI IN interface (in fact I wrote this sketch with the aim of testing that type of hardware).

**If you are using a Teensy board** (you really should, it's a great board for MIDI and AUDIO Arduino works) you can find a schematic for the MIDI interface here: https://www.pjrc.com/teensy/td_libs_MIDI.html

If you are on a Arduino board you can find useful directions on Notes and Volts http://www.notesandvolts.com/2015/02/midi-and-arduino-build-midi-input.html or Sand, software and sound http://sandsoftwaresound.net/5-pin-midi-interface-arduino/

## Using this sketch ##

This sketch requires the Midi library that is included in Arduino. Be sure to have it installed

Upload the sketch, connect your instrument (keyboard etc) to the MIDI IN that you have just built, then open the Arduino Serial Monitor.

Now start play your instruments: if the MIDI IN interface is ok you'll see the MIDI messages on the Arduino Serial Monitor


