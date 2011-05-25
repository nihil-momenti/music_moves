Future Work
===========

Because of the pipelined architecture it will be very simple to replace parts of
the system with different implementations.  This means it can make a good
testbed for future research into hand tracking and strike detection algorithms.

Hand Tracking
-------------

This is definitely the weakest link of the system.  Purely skin colour based
algorithms rarely work well.  If a better webcam could be used then adding in
some feature tracking could make this much more effective.

Otherwise the skin colour detection could be improved, using a more complex set
of boundary conditions such as those found by Wang, Ren, Jiang and Ipson [wang]_
could provide better detection of just the areas of interest.  With this a
better blob determination algorithm could also be used, with better tracking of
the previous frames hands and tracking all contours in each frame automatic
subtraction of noise could be achieved.

Another possible improvement would be adding in background subtraction.  One
problem with this on the current system is the automatic brightness scaling,
this causes the background to change significantly when the subject enters the
frame and no way to disable it was found.


Strike Detection
----------------

To improve the strike detection a few more checks could be added.  The main
problem was the false positives, one solution would be to check a few more
frames back and ensure that two beats from one hand are not too close together
without an *anti-beat* (when the users hands stop moving up and start moving
down again) occurring.
