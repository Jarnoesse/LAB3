import pandas as pd
import numpy as np





#questa roba legge i TSC che sputa fuori CAEN Educational
def ReadTSV(filepath):

    dataframe = pd.read_csv(filepath, sep="\t", lineterminator="\n")
    dataframe = dataframe.iloc[:,:-1]
    return dataframe

def getfilename(filepath):

    #manage to automate filesaving
    filename = filepath.split("/")
    filename = filename[len(filename)-1]
    filename = filename.split(".")[0]
    return filename

def ConvertTSV(filepath):

    dataframe = ReadTSV(filepath)
    filename = getfilename(filepath)

    np.savetxt(r'./np.txt', dataframe.values, fmt='%f')

def GetNumberEvents(filepath):
    dataframe = ReadTSV(filepath)
    sum = dataframe.iloc[:,1].sum()
    return sum
