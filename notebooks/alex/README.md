## 11/13 Recap of Week 11/7
As with the last few weeks, a fair amount of progress was made, both on the hardware and software end. That being said, we did face some challenges, especially on the hardward end. Thus, this entry will cover the meetings that occured during the week of 11/7, the developments made, and the challenges faced.

First, due to Hojoon's business with his final examination, we postponed the weekly meeting to Friday. Thus, the early portion of this week for me was spent mainly on improving the software. For me, this meant adding extra user feedback in the instantaneous and integrated SPL LEDs. I programmed it so that the instananeous SPL LED would go off if the I2S reading was 2072 or higher (this number corresponds to 90 dB converted to I2S divded by $2^7$, and the integrated SPL LED should go off if the daily dose threshold was met. I say should, since the threshold is so high that to properly measure it with appropriate noise (90 dB, which is quite high) would take 8 hours. As a sidenote, to test this instantaneous SPL and demo it, I will likely modify the daily dose threshold or time interval assigned to each reading so that it will take closer to one or a few minutes. That being said, I was successfully able to add the instant SPL LED functionality, as can be seen in the media directory. 

Aside from refining the current code, I also prepared to add libraries to hopefully get the frequency of the samples we were reading. The library in question is arm_math.h that importantly includes types and functions related to FFT. I mainly followed this video (https://www.youtube.com/watch?v=vCcALaGNlyw) to get the library installed; however, there were a couple issues I had to resolve using another source. As a sidenote, I accidentally reset the libraries in the directory I was using to test the development board, and after an hour of effort of trying to get the code to work to no avail, created a new project with the same files copied over. That being said, after using the video was not enough to import the library, I followed this source (https://community.st.com/s/question/0D53W000003w7lsSAA/stm32cubeide-cant-find-dsp-static-library, spefically Rashad Shubita's response) to fix the issues. That source finally resolved issues I had trying to import the library. Thus, in the coming week, I may attempt to add frequency functionality to the dev board by doing an FFT on the samples, finding the maximum frequency with a built-in function, and using that frequency in calculations and just to output.

Those two developmenets occurred in the middle of the week. Now, on Friday, Jinzhi and I (Jake was busy) met with Hojoon. First, we discussed lab access. Apparently, we did not have access due to our team not finishing the lab safety training, and upon further inspection, Hojoon found that Jake did not complete his lab safety training. Additionally, Hojoon conveyed to us that our professor, Professor Arne, had already been concerned about our team's lack of progress that was conveyed in my individual progress report and has been asking Hojoon about our progress ever since. With that out of the way, Hojoon stressed that although getting the dev board working was good, making progress on the PCB was crutial. Last thing that I will mention is that Hojoon said that he should have much more time to help us with our project, which was a relief to hear for me. Afterwards, our team made plans to work on the PCB over the weekend.

## 11/7 Recap of Week 10/31
As with last week, a good amount of development occured, and I will likely have to add onto this week's notebook entry through code, images, etc. Regardless, it will cover the work I did on the development board, specifically with programming the STM32, as well as the updated schematic and PCB, the latter of which I ordered from PCBway.

First during Monday-Tuesday, I configured the STM32CubeIDE software to send I2S signals to the STM32. Using a logic analyzer, I confirmed that the microphone was behaving as usual (IMAGE TO BE ATTACHED TO NOTEBOOK). The main thing was confirming that the microphone only sent signals during one out of every two word cycles, since the microphone should only send during one out of every two cycles depending on the L/R pin. 

Next, on Wednesday, I spent some time fixing up the schematic and PCB. I do not have to do too much aside from switching out the old MCU for the STM32F401, fixing the input pins so that all of the voltage pins were covered and the data pins went to the right places, and adding in a DIP switch to control the BOOT0 pin. The last one is important because without it, we would have no way to program the MCU. After that, I generated the gerber and drill files, sent them to PCBway, got the PCB approved, then sent the files to Hojoon and ordered a copy of the PCB myself. I ordered it by myself in addition to sending it to Hojoon as last time, our group never received our PCB. I should be receiving my copy of the PCB sometime this week.

Finally, this weekend, I tried my best to develop software that would allow us to correctly read off the I2S readings. After a couple hours of development, I managed to get semi-working code (NOT THE CURRENT main.c) after trial and error in addition to using these website as a source: https://medium.com/@davidramsay/how-to-get-i2s-working-on-an-stm32-mcu-33de0e9c9ff8, https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/arduino-wiring-and-test. I will go into more detail as I develop the code further, but essentially, right now, the code takes around 1000 non-zero samples with a valid (non-zero reading) from the I2S microphone, corrects the data by subtracting the average from every sample, then sends out via USB the peak (max - min) reading. It works decently well, but its scale is still incorrect, but we can account for that later when doing the instantaneous and integrated SPL checks by modifying the values that we check for them. 

While I skipped over a lot of development, if need be I will add it later. Regardless, however, I feel like the group and I made a lot of progress this week. 

All for now. 

Edit: I added a media directory that visually illustrates some of the development I went through. 

## 10/30 Recap of Week 10/24
A lot of development happened this week, so I'll be covering events from meetings with Hojoon to soldering and testing the development board.

First, I met with Hojoon on Monday to confirm some information. Honestly, a lot of the time was spent covering my concerns about the class, ranging from the soldering and first teamwork assignment to general fears about how the project was going. He assuaged my fears and scheduled a meeting on Wednesday, later delayed to Thursday, to begin soldering parts. 

Having received the development board that night, I met with Hojoon and the rest of my team on Thursday to start soldering. Soldering was initially pretty rough as the station we were at had a relatively inefficient soldering iron and I did not have much experience, but due to the switch to a better station and learning the ropes, I was able to, with the help of my team, solder the board together. I also was able to solder the digital microphone together, but I have not tested it yet.

As a sidenote I completed the individual progress report on Friday. Now, today, I was able to test the development board. I used a couple videos/website as a reference: https://www.youtube.com/watch?v=VlCYI2U-qyM to help with programming the MCU using USB DFU, this video https://www.youtube.com/watch?v=92A98iEFmaA&t=367s to help me with USB communication, and this website to help with actually seeing what the MCU sent back through USB COM http://www.hydro-temp.com/support/assets/blue-board-with-usb.pdf. All in all, I was able to test the development board by creating and programming a working blinker code (https://wiki.st.com/stm32mcu/wiki/STM32StepByStep:Step2_Blink_LED) and by making sure I could actually communicate via USB.

The next step will be to test the digital microphone and make sure I am able to successful read some kind of output. Once we get that working, we will genuinely have a great chance of fully realizing this project as the rest is simply programming, soldering the PCB, and retesting. 

## 10/23 Recap of Week 10/17
Blue Pill dev board referenced: https://www.cytron.io/p-stm32f103c8t6-blue-pill-arduino-compatible-board

Due to this week's lack of a TA meeting this past week, this noteboko entry will cover what would have been discussed, mainly parts, software, and future plans for the project.

As for the parts, the STM32 arrived this past Thursday. Unfortunately, due to the fact that we do not have a functional PCB yet, we cannot test our MCU and digital microphone yet. As such, I made the decision to purchase a development board that uses the exact same MCU as well as a I2S microphone module. The reason behind my purchases is that the dev board and the module can be used on a breadboard. As such, testing should be much easier. I talked about my purchases with our TA, Hojoon, and he said that while we definitely should not plan to use the dev board and breadboard in the final demo as our final project, it's certainly better than nothing. Additionally, it will be helpful in explaining how we developed for testing and generally just help us explain ourselves in the final demo, presentation, and paper. Certainly, there is a drawback in that while developing the dev board and breadboard we won't directly be working on the final project, but I feel like this minor drawback is more than made up for due to the experience we will gain from developing and testing the development breadboard. I have received the dev board on 10/22 and should receive the mic module on 10/24.

Also this week, I was able to implement the basic daily dose function in the python code. Thus, at the very least, if the software is given a numpy array or a csv file to create an array from, it can successfully communicate the daily dose value as given by the OSHA equation. The GUI, however, is still pretty basic and no consideration is given to frequency yet. 

Last, I will talk about my plans going forward. While I was not able to solder the dev board together yet, in the following week, I plan to solder both the board and the mic module. Additionally, my team should begin basic testing of the dev board and possibly mic module. I hope to be able to get an idea of the pins used for a new PCB design as well as a basic idea of how to program the STM32. Last, I plan to complete my individual report by the end of this weekend, and if I have time, further develop the software.

All for now.

## 10/16 Recap of Weeks 10/3 and 10/10
This entry will cover what I did over the period after the design review in lieu of the two TA meetings that were supposed to happen that unfortunately, did not happen due to our TA, Hojoon being busy due to his degree defense. 

The design review went fairly well, as they seemed to be on board with the project. We managed to make our circuit schematic and PCB design before the review, so it was nice to be able to bring it up despite the fact we didn't have it ready for the PACE document upload. Also, I was very impressed by my teammates, as it felt like Jake knew exactly how the project should be pitched and Jinzhi was also able to give good input on certain questions. I took the following main points away from the review: we should keep up our focus on accessability, we should try to contact some professors like Andrew Singer, and we should try to make the software recommend certain types of ear protection if possible and give an estimate of how much damage was protected if we have time. Unfortunately, we have not to my knowledge contacted any professors yet, but I'm sure that we will in the coming weeks once our microprocessor arrives. 

After the design review, I was able to rest for a bit, albeit just a bit, as I had to complete the first teamwork assessment as well as order parts and send Hojoon our PCB schematic. The parts ordering went okay, but unfortunately our microprocessor was out of stock. I will talk more about this later. Additionally, I created the gerber and drill files needed for the PCB. Suprisingly and fortunately, they passed the audit once I submitted it to PCBway on my own. That being said, I first submitted only the gerber files when the sales representative informed me that I also needed the drill files. The parts ordering and assessment were completed around the week of 10/3 while I was able to submit the PCB schematic on the weekend, I think on 10/9, two days before the required date. 

That brings me to this past week. As previously mentioned, Hojoon, our TA, has been fairly busy so no TA meeting occured. In the start of this week, 10/10 or 10/11, I was informed by the ECE department that our microcontroller was out of stock. Thus, I ended up purchasing it on my own from Newark on the 12th. Unfortunately, I realized this weekend that my order had not been processed, and when I tried to submit a new order, I realized that order had also not been processed. Currently, both are "on hold" for order status. I contacted customer service, and they said to give them 24-48 hours for a response. As of this update, it has already been 24 hours. As a result of that and a bit of panicking, I ended up placing another order for our microcontroller from Win-source. They only had quantities of 13 at minimum, so the entire order come out to $102.072 after shipping. Unfortunately, as of this update, they have not yet shipped the order. Last, I purchased another microcontroller with similar features, I2S and USB connection and relatively fast processor speed, the MK20DN64VMP5 from Digikey. My reasoning was that in the worst case scenario where neither order from Newark or Win-source comes, we can at least have something to work with by next week, the week of 10/24, so that we are not too far behind. Thus, I put in an order yesterday, and hopefully it will come by next week. 

The rest of the parts came in this past Thursday, the 13th, and I picked it up the following day on the 14th. Unfortunately, we can not do too much now without the microprocessor, but it's encouraging to know that we almost having everything ready. 

Last thing, I think I will need to update the PCB. I made errors with the MCU pin connections, and thus have to correct it so that I2S, USB, and clock I/O wires connect to the right pins. The correct pin layout is being informed by the STM32 datasheet: https://www.st.com/resource/en/datasheet/stm32f103cb.pdf. I don't think that this issue is too pressing honestly, given that our current priority should just be to do some basic testing/coding with a breadboard, but it's something to keep in mind. This PCB update, along with adding on to the software, will likely be what I end up doing this week.

That's all for this recap.

## 09/29 Design Document Due Date
This entry will cover the current week's meeting due to the absence of a TA.

Over the past 4 days, I've been revising the Design Doc to hopefully get it to meet the standards given by Professor Fliflet as well as the TAs. I think I've been a decent job adding additional components to the design document to make it overall more coherent. 

1. Added a power management system in place of just a USB. This includes a voltage regulator for the new digital mic and the microprocessor, as well as a battery and a battery charger. I made the decision to add a battery and a charger because I felt like our project should reasonably have some utility without a computer, even if it's as simple as LED warnings.
2. I added the aforementioned digital mic and microcontroller. I realized that if we used an analog microphone, we would have to use an ADC among other devices that would needlessly increase complexity. I actually switched from a PDM MEM to a I2S MEM at the last moment because I realized the PDM mic I was considering, the IM69D120V01XTSA1, would require the microcontroller to preprocess the signal from the microphone, which would just be a general pain to work with. Also, I was unsure whether the STM32 model we were using would be able to communicate with PDM signals. I made the decision to switch to the STM32 model as well because I had read articles about using the STM32 with digital microphones, which I hadn't for the ATmega microcontroller.
3. Added on to the tolerance analysis to reason about the feasibility of calculating daily sound exposure. I found that after processing the dB values, which is just a simple log operation for the STM32, all we would have to do is keep track of around 80 values and average them. This should be quick work for the STM32, as it is also more powerful than the ATmega. 

However, I did encounter some issues when trying to revise the design doc. The major one was creating the circuit diagram. 

I left the PCB/Schematic design until the last minute as I was busy revamping the device itself with the new components until Thursday (today). I then realized using KiCad that they did not have the parts we used, meaning that unless I could figure out how to personally program all the missing components, I would not have it ready for the due date at midnight tonight. I contacted Hojoon, our TA, for help for the coming PCB check. I also have yet to contact Andrew Singer, but I plan to do it after meeting my TA tomorrow. 

Another big issue was lack of delegation between group members. While I worked a decent amount between Tuesday and today, around 4 hours average, I had some difficulty confirming what my other group members were doing. In the future I'll definitely have to convey workflows better so everyone can do something. Hopefully the schedule from the design doc can help.

Regardless, I feel happy with the final state of the design document even though it's likely missing a level of polish for the sheer amount I had to work on it to get it to the final state. In the future, I definitely have to coordinate with my team better to ensure that I'm not overworking myself when we should be spliting the work.

Adding equations from final draft of design document.
LEP'd equation: $8h=Leq+10log((T_2-T_1)/T_n)$ dB. From http://www.larsondavis.com/learn/industrial-hygiene/noise-dosimetry-terminology.

Percent of Daily Dose = D = 100(C1 / T1 + C2 / T2 + Cn / Tn). From https://www.osha.gov/laws-regs/regulations/standardnumber/1910/1910.95AppA#:~:text=If%20the%20dose%20as%20read,accumulated%20dose%20in%20percent%20exposure.

T equation: $T = \frac{8}{2^{(L-90)/5}}$. Used to calculate dB error. From same osha source.

All for today.

## 09/26 Design Document Check
In this meeting, only I attended due to some virtual/in-person confusion in the case of Jinzhi and a work trip in South Africa for Jake.

The main topic we went over was how our project was unique/useful: they pointed out that the user-friendly warning lights and frequency buckets for the sound report would be good distinguishers for us, as most products at a similar price (<$100) only show instant dB values. Also obviously the price difference between us and industry grade SPL dosimeters would be a big thing.

Also we went over how a few more plots and calculations would be nice. One thing that they pointed out that I liked was adding some calculations to the tolerance analysis part, specifically that we could do X instructions within Y cycles and capture 20Hz-20kHz due to the amount of instructions being pretty low and the speed of our microcontroller being pretty fast - obviously specify in the doc.

One last thing that they pointed out is that for our R/V tables, we want to make sure that each requirement isn't a spec but rather a reflection of our high-level requirements.

Aside from the changes with the document itself, they mentioned that I should reach out to Andrew Singer for help among others. Him specifically because he has personally dealt with audio projects before. He would probably be a good reference for R/V testing, design elements, etc.

All for today.
