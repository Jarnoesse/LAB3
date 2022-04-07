import glob
import numpy as np
import pandas as pd
import os
import subprocess
import matplotlib.pyplot as plt

from utility import ConvertTSV,getfilename,GetNumberEvents

print("Absorption.py started")
print("---------------------")

#dato che c'è da copiere la stessa operazione per carta e metallo definisco una funzione.
def Elaborazione(filepath,total_width,total_error,nsheets):

    tau = 0.8
    #faccio la lista di file di dati da utilizzare.
    filelist=glob.glob(filepath)
    
    mu_df = pd.DataFrame(columns=["fogli","pvalue","media","mediaerr","varianza","varianzaerr"])
    bridge_df = pd.DataFrame(columns=["L","sigmaL","N","sigmaN"])
    
    width = total_width/nsheets      #mm
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
        bridge_df.loc[fogli] = [float(fogli)*width,width_error,df.loc[0,1]/tau,np.sqrt(df.loc[0,1])/tau]
        
    #ora faccio i preparativi per il fit con l'esponenziale negativa.
    #salvo il secondo dataframe, che è quello che contiene i dati da fittare!
    np.savetxt(r'./bridge.txt', bridge_df.values, fmt='%f')
        
    #runno il mio altro  script root
    proc = subprocess.Popen("./ExpFit")
    proc.wait()

    pars_df = pd.read_csv("ExpFit.txt",header=None)

    return bridge_df["N"],bridge_df["L"],bridge_df["sigmaN"],bridge_df["sigmaL"],pars_df.loc[0,1],pars_df.loc[0,3]
    
#CARTA
N,L,sN,sL,p0,p1 = Elaborazione("./Data/Assorbimento/carta/*.txt",2,1.5,22)

# il grafico
x = np.linspace(700,1800,1000)
y = p0*np.exp(-p1*x)

plt.errorbar(N,L,yerr=sL,xerr=sN,fmt='o')
plt.plot(x,y,'b')

#ALUMINIO
N2,L2,sN2,sL2,p02,p12 = Elaborazione("./Data/Assorbimento/metallo/*.txt",3,1.5,20)

x2 = np.linspace(1200,1800,1000)
y2 = p02*np.exp(-p12*x2)

plt.errorbar(N2,L2,yerr=sL2,xerr=sN2,fmt='o')
plt.plot(x2,y2,'r')
plt.show()




