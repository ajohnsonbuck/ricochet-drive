# -*- coding: utf-8 -*-
"""
Created on Wed Jul  9 10:40:02 2025

@author: aledb
"""

import pandas as pd
import numpy as np
import copy

def isolate_beat(dT, Cutoff):
    Center = np.median(dT)    # Assumes majority of events are ~1 beat apart, and no events are less than 1 beat in size    
    dT_Trimmed = []
    for index,item in enumerate(dT):
        if np.abs(item - Center) <= Cutoff:
            dT_Trimmed.append(item)
    dT_Trimmed = np.array(dT_Trimmed)
    return np.mean(dT_Trimmed)

def fit_beats_to_bounds(Time, Time_Snapped):
    Duration = Time[-2]-Time[0]
    Duration2 = Time_Snapped[-2]-Time_Snapped[0]
    StretchFactor = Duration/Duration2
    for index, item in enumerate(Time_Snapped):
        Time_Snapped[index] = (Time_Snapped[index]-Time_Snapped[0])*StretchFactor+Time_Snapped[0]
    return Time_Snapped
    

def snap_beats(InFileName,OutFileName,Quantization):
    DataTable = pd.read_csv(InFileName)
    Time = DataTable.Time.values
    dT = Time[1:-1] - Time[0:-2]
    Beat = isolate_beat(dT, 0.25)

    dT_Snapped = copy.deepcopy(dT)
    for index, item in enumerate(dT):
        dT_Snapped[index] = np.round(item/(Beat*Quantization))*Beat*Quantization
    
    Time_Snapped = copy.deepcopy(Time)
    for index in range(1,Time_Snapped.size-1):
        Time_Snapped[index] = Time_Snapped[index-1]+dT_Snapped[index-1]
    
    Time_Snapped = fit_beats_to_bounds(Time, Time_Snapped)
    
    DataTable.Time = Time_Snapped
    
    DataTable.to_csv(OutFileName)
    
    return Time_Snapped

FileName = 'C:\\Users\\aledb\\OneDrive\\Documents\\Unreal Projects\\RicochetDrive\\Content\\Music\\CosmicShoresBeats1.csv'
OutFileName = 'C:\\Users\\aledb\\OneDrive\\Documents\\Unreal Projects\\RicochetDrive\\Content\\Music\\CosmicShoresBeats1_quantized.csv'

Time_Snapped = snap_beats(FileName,OutFileName,0.5)
    
from matplotlib import pyplot as plt

