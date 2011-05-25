Implementation
==============

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
without any additional marker [yilmaz]_.

There were two major methods looked at for this system; feature tracking and skin
colour masking with blob tracking.

Feature tracking would likely be the most effective tracking method when used
with a high quality camera and fast processing speeds.  This system was limited
to run on a mid-range laptop, however, and the lower quality camera and slow
processor produced significant blurring in the images taken, see `Figure 2`__.

__
.. figure:: images/blurring
  :width: 90%

  The blurring produced by the low quality camera.

Because of this blurring feature detection would be almost useless, the features
that get detected would disappear into the noise whenever the hands move too
quickly.  Even using something like Kalman filtering the absolute destruction
of the features would be too much.

Skin colour masking with blob tracking would be more resilient to the blurring
occurring with the camera; the blurred hands will move the outsides of the blob,
but the centroid will remain in approximately the right position.  

Skin colour masking
+++++++++++++++++++

Again there are various possibilities for the skin colour masking.  Some methods
that have been employed are Gaussian chromatic color segmentation [robles]_, more
complex YCbCr/HSV color space division [wang]_ or just simple linear HSV color
space division [andol]_.

The Gaussian chromatic color segmentation and complex YCbCr/HSV color space
division provide more accurate results than the simple linear HSV color space
division, however they are more complex to implement and designed for the
specific datasets used in their studies.

The chosen algorithm was simple HSV colour masking for the reasons listed above.
The implementation was a simple range check, if a pixel's HSV value fell within
the range (0, 0.12, 0.31) -> (0.08, 0.59, 1.00) then it was counted as skin
coloured.  The result of this check was stored as a mask with skin-coloured
pixels fully white and non-skin coloured pixels fully black.

To make the masking more resilient to noise such as specular reflection spots
the colour image was smoothed before the conversion to HSV colour space.  This
increased the mis-classification of other colours as being skin, but it was felt
that the trade-off was worth it in terms of better tracking of real skin.

Once the mask was produced it was dilated then eroded to close up the blobs.
Regions such as the lines between fingers on a closed fist had too much shadow
to detect as skin coloured so this helped to form the hand into a single blob
for the tracking stage.

Blob tracking
+++++++++++++

Once the skin regions have been detected a simple algorithm that tracks the
hands via centroid, size and movement can be used effectively [tarabella]_.
First the contours of the skin mask are found using the Suzuki85 algorithm
[suzuki]_.  This uses a border following method to find all edges between black
and white and returns a set of contours.

These contours then have their spatial and central moments calculated and used
to determine the centroid and area covered by the contour.  These are used to
determine a score for the contour, this is a simple heuristic score proportional
to the size of the contour (it is assumed that the hands will be the largest
blobs in the frame) and the distance from the contour's centroid to the last
centroid for that hand.  The score is calculated separately for each contour for
both hands and the two highest scoring contours are selected as the new contours
representing that hand for this frame.

This will give as a final value the current centroid of each hand, ready to be
used for the strike detection.

Strike Detection
----------------

The next step in the pipeline is detecting when the user strikes the virtual
drum.  Possible options explored for this was training up a neural network that
took a few frames of (x,y) locations of the hands to determine when a drum was
struck, attempting to derive a hand model based system for detecting the drum
strike and using a simple kinematic first and second order derivative detection
system [popa]_.

The problem with using a neural network based solution would be the large amount
of training required.  Building the set of training data would involve recording
a lot of video then painstakingly annotating where it was believed the drum
strike sound should occur.  This would introduce a human error element in that
if the annotation of the training set was off the neural network would be
incorrectly trained.

Using a hand model would also require a lot of working in deriving a valid
model, there is previous work in this area that could be used as a starting
point [buczek]_ [cerveri]_ [kerd]_ [cobos]_.

The simple kinematic system for detecting the strike would be a lot simpler to
implement, the hand co-ordinates captured by the hand tracking can be used to
directly generate first and second order derivatives.  Once these values are
found a strike can easily be detected via its kinematic properties, when the
hand hits a drum its movement abruptly changes from downwards to upwards.  This
abrupt change can be approximated by the velocity of the hand following a
sigmoid function (`Figure 3a`).  Taking the derivative of this function we can
see that there is a large spike when this strike happens (`Figure 3b`).

.. raw:: latex

  \begin{figure*}
    \centerline{
      \subfloat[Velocity]{
        \includegraphics[width=0.45\textwidth]{images/sigmoid}
        \label{figure-3a}
      }
      \hfill
      \subfloat[Acceleration]{
        \includegraphics[width=0.45\textwidth]{images/sigmoid-deriv}
        \label{figure-3b}
      }
    }
    \caption{The approximation of the hands kinematic motions.}
    \label{figure-3}
  \end{figure*}

Sound Output
------------

Two methods were explored for outputting the sound.  The first was using OpenAL
and manually outputting the sound from the program developed.  The second was
using MIDI to send the sound output to a synthesiser and let that handle the
actual sound generation.

Using OpenAL was very quickly discarded as the effort required was simply too
great.  The focus of this project was on the computer vision, not the sound
production.

For MIDI a very easy to use library known as PortMIDI was found.  This allows a
stream based approach to MIDI production, it simply needs to be given an output
stream to write to and it will send the MIDI commands required to make sound.
The synthesiser used is known as Renoise, this was the only soft-synth found
that provided a stream to be written to; all the others wanted to be given an
input stream that they would then read from and play, which was not supported by
PortMIDI.

.. [robles] temp
.. [wang] temp
.. [andol] temp
.. [buczek] temp
.. [cerveri] temp
.. [suzuki] temp
.. [kerd] temp
.. [cobos] temp
.. [tarabella] temp
.. [popa] temp
.. [yilmaz] temp
