import pandas as pd

sus = pd.read_csv("susamogus.csv",header = None)
sus = sus.iloc[:,1:]
sus.drop(8,axis=1,inplace=True)
sus.drop(9,axis=1,inplace=True)
print(sus)
sus.to_csv("processed_csv.csv",header = None)
