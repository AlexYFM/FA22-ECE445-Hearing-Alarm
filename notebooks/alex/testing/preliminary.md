*Alex Yuan ayuan20*
# Basic SPL Testing/Calibration 11/12/22 

Using the phone app  I inferred that the snaps that were able 
to cause the LED to light up, i.e., a greater raw value than 2072, only peaked around 85 dB. Using another app that appears to be more reputable (it is able to be calibrated with 
a real SPL meter), I found that snaps peaked at around 80 dB (corresponding to traffic, a loud alarm clock among other things according to https://decibelpro.app/blog/how-loud-is-80-decibels/). What these app show is that our LED does not actually indicate dangerous sound levels, but rather "loud" or potentially dangerous sound levels.
 I believe that this is not a bad thing, but we will have to keep in mind while presenting or calibrating our software, as a reading of 2072 definitely does not correspond to 90 dB.
Using the screenshots in the media directory, we can see that this implies a peak of even 5000 may not be 90 dB. The software I wrote as of writing only allows a peak value of 16383. Thus, 
90 dB probably lies somewhere around 6-8k. In the future, I may need to modify the software to increase the bounds allowed so that the peak values are distinct are at least more distinct than now.
This means that I will likely change the bounds to allow the either half of the full value or the full 65535 value that data[0] is allowed to show. My only concern now 
is that noise will mean decibel values may be inaccurate.
                                                             
Ultimately, while the current bound of 2072 is okay (snapping near someone's ear is fairly loud by colloquial standards), that does mean that for the integrated SPL
and for accurate dB readings, we must realize that a reading of 2072 is not especially close to 90 dB. 
