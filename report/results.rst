Results
=======

Hand tracking
-------------

The hand tracking worked successfully, using the bright red gloves provided a
very distinct edge in the filtered image.  This could then simply have the
centroid calculated for the hand position.  An example is shown in `Figure 2`__.

__
.. figure:: ./images/hands
  :width: 90%

  The hand tracking (draft image, real image will come soon).

Neural Network
--------------

The neural network was also quite successful, with an 87% pass rate on the test
cases.

The network was tested with a large variety of different parameters, via a
series of automated tests.  The number of input frames was varied between 10 and
55 with a step of 15, corresponding to around 0.3 to 2 secs at the nominal
output rate of 30 fps that the hand tracking algorithm was able to sustain.  The
number of hidden layers was also varied between 1 and 2, in case the required
learning pattern was of a higher order.
