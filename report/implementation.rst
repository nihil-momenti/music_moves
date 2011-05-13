Implementation
==============

Hand Tracking
-------------

To make this simpler the mark based tracking was chosen, specifically a pair of
brightly coloured gloves.  This will limit the subjects clothing in that it
cannot contain the same colour as the gloves.  However it greatly simplifies the
hand tracking to just following the specific colour of the gloves.

The tracking will involve two stages, target acquisition & learning and the
actual tracking.  During acquisition and learning the user will start with their
hands behind their back, then hold them in a few positions in front of the
camera.  This will produce a series of images which will be automatically
processed to attempt to compensate for the lighting conditions.  Once an
accurate enough colour sample has been achieved the actual tracking will be
started.

Neural Network
----------------

To simplify the creation of the neural network it was decided that this should
be a separate program.  Writing the network in Erlang would be much easier than
using C, and by having a separate program the training would be simpler to
setup.

