# Build requirements

Building this project will require having the PortMIDI library and headers
installed.  Building has only been tested on Mac OS 10.6 using XCode 3.2.5, it
should work fine on any Unix-like system though.  Windows is completly
untested, you're on your own in terms of working out how to translate the
Makefile.

# Quick file overview

## `Boss DR-5.xrni`

This file is a freely available drum sound file for the Renoise synthesiser.

## `blob`

This module takes care of the initialisation, location and scoring of the blobs
in the HSV masked image.

## `drums`

This module takes care of drawing the virtual drums on the image.

## `masker`

This module performs the smoothing, masking and closing of the input image.

## `music`

This module contains all the MIDI related code, taking care of finding and
connecting to the stream, sending beats down the stream and disconnecting when
finished.

## `player`

This module takes the history of the hand movements and performs the strike
detection.

## `main`

This takes all the other modules and ties them together into a working program.
