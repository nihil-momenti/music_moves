Results
=======

Hand tracking
-------------

The hand tracking was the least reliable part of the system.  Under ideal
conditions it worked almost perfectly, as long as the hands were the only skin
coloured objects and they didn't occlude one another there was no problem
tracking them.

However, under non-ideal conditions the tracking deteriorated rapidly.  If there
was another patch of skin colour larger than one of the hands then the simple
blob tracking in use would prefer to follow that instead, and there was no way
to take the marker back from the patch.  If there were smaller patches of skin
colour then the centroid would jump around a lot as the hand joined on to
different patches.

Strike Detection
----------------

When the hand tracking was working well the strike detection was very good.
After extensive testing the results shown below were found.  These results were
gathered under near perfect conditions to purely test the strike detection,
there was only a few small patches of non skin that was being detected by the
hand tracking algorithm.

.. raw:: latex

  \vspace{10pt}

  \begin{tabular}{l|rrr}
  Test                             & Strikes & Correct +ve & False +ve\\
  \hline
  S1 (1 bps) &  100    &   92             &  13\\
  S2 (2 bps) &  100    &   87             &  19\\
  F1 (4 bps) & ~200    & ~184             & ~40\\
  F2 (8 bps) & ~200    & ~175             & ~60
  \end{tabular}

  \vspace{10pt}

Key: S1 = Slow single handed, S2 = Slow double handed, F1 = Fast single handed,
F2 = Fast double handed.

These results show that the strike detection is 87-92% accurate, with a false
positive rate of 13-30%.  Most of the false positives were occuring as double
hits, this could be because of a series of five frames showing the hand moving
down, the hand stopping, then the hand heading back up.  Both the hand stopping
and the hand heading back up could have high enough second derivatives to
register as strikes under the current system.

Sound Playing
-------------

The playing of sounds worked perfectly, thanks to such an easy to use MIDI
library.  There was no noticeable delay between when the program detected a
strike and when the sound from the strike was played.
