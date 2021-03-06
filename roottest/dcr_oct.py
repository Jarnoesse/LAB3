import pandas as pd
import glob
import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess

from utility import ReadTSV,ConvertTSV,GetNumberEvents

def Elaborazione(filepath,tau):
    print("inizializzata elaborazione")
    #prendo i file nella cartella
    filelist = glob.glob(filepath)

    mu_df = pd.DataFrame(columns=["gain","pvalue","media","errore"])

    for filename in filelist:
        #prendo il gain
        gain = (filename.split("_")[4]).split(".")[0]
        print("il gain è" ,gain)

        ConvertTSV(filename)

        sum = GetNumberEvents(filename)


        proc = subprocess.Popen("./HistFit")
        proc.wait()

        df = pd.read_csv("HistFit.txt",header=None)
        print(df)

        mu_df.loc[gain] = [int(gain),df.loc[0,0]/tau,df.loc[0,3]/tau,df.loc[0,5]/tau]
    print(mu_df)
    return mu_df


print("Macro avviata")
tau = 0.200 #s
#mi preparo a convertire i file gain
dcr_df = Elaborazione("./Data/DCR_counts/DCR_gain/*.txt",tau)
oct_df = Elaborazione("./Data/DCR_counts/OCT_gain/*.txt",tau)

print(dcr_df)
plt.errorbar(dcr_df["gain"],dcr_df["media"],yerr=dcr_df["errore"],fmt = 'o')
plt.errorbar(oct_df["gain"],oct_df["media"],yerr=oct_df["errore"],fmt = 'o')
plt.show()
