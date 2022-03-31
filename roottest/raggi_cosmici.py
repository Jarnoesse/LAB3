import pandas
import matplotlib.pyplot as plt

from utility import ReadTSV

#Leggo il filename
filename = "./Data/RaggiCosmici/Raggi_cosmici_nella_notte.txt"
df = ReadTSV(filename)

#creo il grafico
plt.figure()
plt.plot(df.iloc[:,0].to_numpy(),df.iloc[:,1].to_numpy())
plt.yscale("log")
plt.savefig("./Results/RaggiCosmici/Cosmici.png")
print("Cosmici Saved")
