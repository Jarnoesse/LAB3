import pandas as pd
import glob
import matplotlib.pyplot as plt
import numpy as np
from lmfit.models import GaussianModel
from lmfit.models import ExpressionModel

from utility import ReadTSV

print("Calcolo DCR count")

def getfilename(filepath):
    #manage to automate filesaving
    filename = filepath.split("/")
    filename = filename[len(filename)-1]
    filename = filename.split(".")[0]
    return filename

#cerco i file di dati del DCR
filelist = glob.glob("./Data/DCR_counts/DCR_gain/*.txt")

for filepath in filelist:

    filename = getfilename(filepath)

    #leggo i file di dati
    print("reading", filename)
    df = ReadTSV(filepath)

    #creo il grafico
    plt.figure()
    plt.hist(df.iloc[:,1])


    #joino le stringe per salvare le immagini
    plt.savefig("".join(["./Results/DCR_counts/",filename,".png"]))
    print("Saved graph",filename)

print("DCR counts eseguito correttamente")

#cerco i file di dati dell' OCR
filelist = glob.glob("./Data/DCR_counts/OCT_gain/*.txt")
print (filelist)

for filepath in filelist:

    filename = getfilename(filepath)

    #leggo i file di dati
    print("reading", filename)
    df = ReadTSV(filepath)

    #creo il grafico
    plt.figure()
    plt.hist(df.iloc[:,1])


    #joino le stringe per salvare le immagini
    plt.savefig("".join(["./Results/OCT_counts/",filename,".png"]))
    print("Saved graph",filename)
print("Calcolo OCT eseguito correttamente")
