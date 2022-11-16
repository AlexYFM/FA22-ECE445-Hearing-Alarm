## Here is a description of all the photos and videos in this directory.

### Added 11/15/2022

VID_20221115_204014.mp4 -- Verifying that dev board lights up USB when "loud" and software is able to process sound and convey instataneous SPL in both "absolute" and decibel values. 

VID_20221115_204516.mp4 -- Same as above except only decibel and board, no "absolute" SPL values.

### Added 11/08/2022

VID_20221030_153623.mp4 -- Verifying that basic programming worked. Basic blinker code. 

VID_20221030_212021.mp4 -- Getting USB communication from the chip to my laptop working. Warning: video has sound coming from music I was listening to. 

IMG_20221106_111339.jpg -- View of the development board with LED on. 

IMG_20221106_111341.jpg -- View of the development board with LED off. As of this update, the LED's state at any moment doesn't mean anything, but the change from on to off or off to on represents the completion of one audio value sample being processed and sent to the USB port. 

pcb 10_26.png, schematic 10_26.png -- Fairly self-explanatory; these are the updated version of the PCB and schematic. 

better.png -- This image shows the readings the laptop receives via USB from the board. If need be, I will later add earlier versions of the readings; however, this image represents the best I was able to get. As one can see, the readings are fairly consistent at around 500 without noise. However, when I snapped directly over the mic, the values peaked at aroudn 23k and 5k respectively. We can use these readings to scale what we expect 90 dB and above to look like by comparing them to another SPL reader. To calibrate/corroborate the readings for the past week, I have been using an app on my phone, Sound Meter, that seems to be fairly accurate https://play.google.com/store/apps/details?id=com.splendapps.decibel&hl=en_US&gl=US&pli=1. 
