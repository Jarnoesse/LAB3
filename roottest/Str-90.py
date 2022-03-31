# apro e leggo da file
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import optimize as opt
from scipy.optimize import curve_fit
from scipy.stats import poisson
import glob
from lmfit.models import GaussianModel

from utility import ReadTSV

print("Started str-90.py")
filename = "./Data/Str90/istogramma_energie.txt"

tsv_str_90 = ReadTSV(filename)

#Grafico dello spettro dello stronzio-90
plt.figure()
plt.plot(tsv_str_90.iloc[:,0].to_numpy(),tsv_str_90.iloc[:,1].to_numpy())
plt.savefig("./Results/Str90/istogramma_energie.png")
print("Str90 graph saved")

#Ora penso all' altro istogramma
filename = "./Data/Str90/Istogramma_rosso.txt"
tsv_conteggi = ReadTSV(filename)

#definisco la gaussiana
#model = GaussianModel()

#dichiaro la x
x=tsv_conteggi.iloc[:,0]
#dichiaro la y
y=tsv_conteggi.iloc[:,1]

#uso scipy
def Gauss(x, A, B,C):
    y = A*np.exp(-1/B*(x-C)**2)
    return y

guess = [25,1,1525]
parameters, covariance = curve_fit(Gauss, x, y,p0=guess)
fit_y = Gauss(x, parameters[0], parameters[1],parameters[2])


#fitto i dati
#params = model.guess(y,x=x)
#result = model.fit(y,params,x=x)
#print(result.fit_report())

#creo il grafico
plt.figure()
plt.scatter(x, y)
#plt.plot(x,result.best_fit,label = 'fit')
plt.plot(x,fit_y,label='fit')
plt.savefig("./Results/Str90/Istogramma_rosso.png")
print("Str90 count graph saved")

#ora vado a costruire i multigraph
print("MultiGraphStarted")
filelist = glob.glob("./Data/Str90Multigraph/*.txt")          #guardo tutti i file di tipo txt, in questo modo escludo i png

df = pd.DataFrame()

#non normalizzati
plt.figure()
for filename in filelist:
    print("leggendo")
    print(filename)
    tsv_generico = ReadTSV(filename)
    plt.plot(tsv_generico.iloc[:,0].to_numpy(),tsv_generico.iloc[:,1].to_numpy(),)
plt.savefig("./Results/Str90/str90_notnorm_comparison.png")
print("Saved str90_notnorm_comparison.png")

#normalizzati
plt.figure()
for filename in filelist:
    tsv_generico = ReadTSV(filename)
    plt.plot(tsv_generico.iloc[:,0].to_numpy(),tsv_generico.iloc[:,1].to_numpy()/tsv_generico.iloc[:,1].to_numpy().sum())
plt.savefig("./Results/Str90/str90_norm_comparison.png")
print("Saved str90_norm_comparison.png")



print("Str-40.py executed Correctly")

