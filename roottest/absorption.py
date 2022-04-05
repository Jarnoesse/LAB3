import glob
import numpy as np
import pandas as pd
import os
import subprocess
import matplotlib.pyplot as plt

from utility import ConvertTSV,getfilename,GetNumberEvents

print("Absorption.py started")
print("---------------------")

#faccio la lista di file di dati da utilizzare.
filelist = glob.glob("./Data/Assorbimento/*.txt")

mu_df = pd.DataFrame(columns=["fogli","pvalue","media","mediaerr","varianza","varianzaerr"])
bridge_df = pd.DataFrame(columns=["L","sigmaL","N","sigmaN"])

#Elaboro i dati sullo spessore della CARTA
total_width = 2
total_error = 1.5
width = total_width/20       #mm
width_error = total_error/20 #mm

#utilizzo un loop per navigare fra i fogli di dati
for filename in filelist:

    #splitto la stringa per prendere il numero di fogli
    fogli = filename.split("_")[1]

    #Converto il tsv in qualcosa di comprensibile per lo script di ROOT
    ConvertTSV(filename)
    sum = GetNumberEvents(filename)

    #runno il mio script root
    proc = subprocess.Popen("./Absorption")
    proc.wait()

    #leggo il risultato
    df = pd.read_csv("fitresults.txt",header=None)
    #organizzo i dati letti in un nuovo dataframe
    mu_df.loc[fogli] = [fogli,df.loc[0,0],df.loc[0,1],df.loc[0,2],df.loc[0,3],df.loc[0,4]]

    #fillo il dataframe per il secondo fit.
    bridge_df.loc[fogli] = [float(fogli)*width,width_error,df.loc[0,1],np.sqrt(df.loc[0,1])]


    print(mu_df)
    print(bridge_df)

#ora faccio i preparativi per il fit con l'esponenziale negativa.
#salvo il secondo dataframe, che è quello che contiene i dati da fittare!
np.savetxt(r'./bridge.txt', bridge_df.values, fmt='%f')


#plotto il grafico
plt.errorbar(bridge_df["N"],bridge_df["L"],yerr=bridge_df["sigmaL"],xerr=bridge_df["sigmaN"],fmt='o')
plt.show()




