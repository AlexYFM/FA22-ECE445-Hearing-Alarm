import PySimpleGUI as sg                        
import numpy as np 
import pandas as pd
import random 
#Alex Yuan Fall 2022 Senior Design Project

##Sample code modified from official PSG website
spl = 5 #For easy coding, compute this beforehand using pandas and numpy to extract values out of csv and compute using tables and basic arithmetic
dd = 0
test_array=np.array([89, 91])
#below function returns the daily dose for a given data structure
def daily_dose(data, time_interval=1): #data is some numpy array that can be taken from a pandasdataframe, time interval is default one second
    daily = 0
    for i in range(len(data)): #assume that data is 1-D and only holds decibel values
        dBdiff = data[i]-90 #baseline is 90
        daily += time_interval/(8*60*60*(2**(-dBdiff/5))) #modified time interval based on 5 dB tradeoff/exchange rate -- daily gets incremented by time interval of data instance and modified time period 
    return round(daily*100, 2) #because we want percent, take 2 decimal points : https://stackoverflow.com/questions/20457038/how-to-round-to-2-decimals-with-python
dd = daily_dose(test_array, 4*60*60)

# Define the window's contents
layout = [  [sg.Text(f"Average Weighted SPL Value: {spl} dBA")],    
            [sg.Text(f"Sound Exposure Daily Dose: {dd} %")],
            [sg.Button('Click to See Detailed Frequency Overview')] ] #f in front of string is equivalent to .format() 
            #https://matthew-brett.github.io/teaching/string_formatting.html

# Create the window
window = sg.Window('Hearing Alarm Software', layout, size=(600, 300), element_justification='c')      

# Display and interact with the Window
event, values = window.read()                   # Event loop or Window.read call

# Do something with the information gathered

# Finish up by removing from the screen
window.close()                                   # - Close the Window