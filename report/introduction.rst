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
algorithm for turning their motions into sound will be needed.  One possibility
would be to write an algorithm that looks for differences in the hand positions
that indicate the *strike* of the swing.  However, this would be a rather
complex algorithm and be difficult to derive manually.

Instead a segmented approach was decided upon, the traditional unix-like piping
approach; see `Figure 1`__.  The individual frames of the camera will first
enter a hand-tracking algorithm.  This will output the current (x, y)
co-ordinate of each hand.

FULLWIDTH

__
.. figure:: ./images/flow
  :width: 80%

  The pipeline of the approach (draft image, will be converted to svg at some
  point).

These (x, y) co-ordinate sets will then enter a buffer.  This allows the next
part of the pipe to compare the last set of frames, necessary for detecting the
*strike* of a swing.

Each co-ordinate set in the buffer will be input into a neural network, this
will compare all the values and decide if one of the drums was just struck.
This will almost necessarily introduce at least a one frame delay in the output,
part of the optimization of the neural network will be testing out different
delays.

The strikes from the neural network will then pass into the output stage, this
will either output the sound directly or convert the strikes into the
appropriate signals to be passed along to the sound controller.

Hand Tracking
-------------

There are a few possibilities for the hand tracking, with or without marks.
With marks we could have the user wearing a pair of brightly coloured gloves, or
holding a pair of brightly coloured drumsticks.  Without marks we could attempt
an implementation of the Kalman filter to track the front/tops of the users
fisted hands.

Neural Network
--------------

The neural network would have a large input layer, four nodes per frame of the
video.  To provide context it is assumed that at least a second of video will be
required, at say 30 frames a second this means the input layer would be at least
120 nodes.  The actual length of the context will be part of the optimisation of
the neural network.

Sound Output
------------


.. [jensen] temp
.. [yetton] temp
.. [godoy] temp
.. [pan] temp
