import PySimpleGUI as sg                        
import numpy as np 
import pandas as pd
import random 
##Sample code modified from official PSG website
spl = 5 #For easy coding, compute this beforehand using pandas and numpy to extract values out of csv and compute using tables and basic arithmetic
dd = 5
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