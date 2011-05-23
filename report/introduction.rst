Introduction
============

The goal of this project is to create an interactive music program that can
generate music based by analysing the movement of a human body or hand position.
This will be capable of running in real time on a consumer pc utilising a single
webcam.

A lot of different methods for producing movement from sound have been
researched.  Some of these involve using the hands to "shape" the music, for
example having a 2d pointer (which could easily be generated from a hand
tracking algorithm) that affects the music based on a set of simple gestures
[jensen]_.  Others attempt to provide a more traditional musical interface,
albeit without the actual instrument.  This can be a simple interface such as a
DJ's deck [yetton]_, or a more complex interface like a full piano [godoy]_ or
guitar [pan]_.

Whilst the first approach will probably lead to a more novel category of
research, it would also require a deep understanding of music theory.  Therefore
the second approach was the one chosen for investigation.

One instrument that hasn't been widely studied for video based playing is the
air drum.  It would have to be wondered why; the drum simultaneously provides
both a complex interface, the 3d position of the imaginary sticks, and a simple
interface, only around 3-10 different drums/cymbals to hit depending on the drum
set.

To enable the user to play the air drum just via a normal webcam a robust
algorithm for turning their motions into sound will be needed.

Hand Tracking
-------------

There are a few possibilities for the hand tracking, with or without marks.
With marks we could have the user wearing a pair of brightly coloured gloves, or
holding a pair of brightly coloured drumsticks.  Without marks we could attempt
an implementation of the Kalman filter to track the front/tops of the users
fisted hands.

Strike Detection
----------------

Sound Output
------------


.. [jensen] temp
.. [yetton] temp
.. [godoy] temp
.. [pan] temp
