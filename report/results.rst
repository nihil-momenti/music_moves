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

`Figure 5`__ shows an example of what happens when conditions are non-ideal.
The brown of both the shirt and jacket are being picked up as skin coloured so
the tracking completely fails.

FULLWIDTH

__
.. figure:: images/bad_colour
  :width: 100%

  Failure of the skin colour masking.

Strike Detection
----------------

When the hand tracking was working well the strike detection was very good.
After extensive testing the results shown in `Table 1` were found.  These results were
gathered under near perfect conditions to purely test the strike detection,
there was only a few small patches of non skin that was being detected by the
hand tracking algorithm.

.. raw:: latex

  \begin{table}
  \centering
  \renewcommand{\arraystretch}{1.8}
  \caption{Results of the strike detection testing.}
  \label{strike-results}
  \begin{tabularx}{\linewidth}{X|lp{30px}p{30px}}
  Test & Strikes & Correct Positive & False Positive\\
  \hline
  Slow single handed drumming (1 bps) & 100 & 92 & 13\\
  Slow double handed drumming (2 bps) & 100 & 87 & 19\\
  Fast single handed drumming (4 bps) & \textasciitilde 200 & \textasciitilde 184 & \textasciitilde 40\\
  Fast double handed drumming (8 bps) & \textasciitilde 200 & \textasciitilde 175 & \textasciitilde 60\\
  \hline
  Slow single handed drumming (1 bps) & & 92\% & 13\%\\
  Slow double handed drumming (2 bps) & & 87\% & 19\%\\
  Fast single handed drumming (4 bps) & & 92\% & 20\% \\
  Fast double handed drumming (8 bps) & & 87.5\% & 30\%
  \end{tabularx}
  \end{table}

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
