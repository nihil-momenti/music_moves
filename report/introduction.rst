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

The method decided on is based on the pipelining used in standard Unix systems,
this will allow for multi-threading to be utilised in the future.
As seen in `Figure 1`__ this system will utilise three processing stages.  The
first is hand tracking, this will identify the position of the users hands and
track them through subsequent frames.  Next the hand positions will enter the
strike detector, this will determine when the hands hit one of the virtual
drums.  Finally the sound production stage will take the strikes and output the
sound.

FULLWIDTH

__
.. figure:: images/pipeline
  :width: 90%

  The pipelining approach.

Hand Tracking
-------------

There are many possibilities for hand tracking, both marker-based tracking where
the user has something like a pair of brightly coloured gloves for the computer
to track and marker-less tracking where the computer tracks the users hands
without any additional marker.

There were three major methods looked at for this system; feature tracking, skin
colour masking with blob tracking and ??????????.

Feature tracking would likely be the most effective tracking method when used
with a high quality camera and fast processing speeds.  This system was limited
to run on a mid-range laptop however and the lower quality camera and slow
processor produced significant blurring in the images taken, see `Figure 2`__.

__
.. figure:: images/blurring
  :width: 90%

  The blurring produced by the low quality camera.

Because of this blurring feature detection would be almost useless, the features
that get detected would disappear into the noise whenever the hands move too
quickly.

Skin colour masking with blob tracking would be more resilient to the blurring
occurring with the camera.  

Strike Detection
----------------

Sound Output
------------


.. [jensen] temp
.. [yetton] temp
.. [godoy] temp
.. [pan] temp
