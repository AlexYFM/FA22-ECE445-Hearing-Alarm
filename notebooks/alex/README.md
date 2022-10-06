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
