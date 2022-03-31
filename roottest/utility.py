import pandas as pd





#questa roba legge i TSC che sputa fuori CAEN Educational
def ReadTSV(filepath):
    dataframe = pd.read_csv(filepath, sep="\t", lineterminator="\n")
    dataframe = dataframe.iloc[:,:-1]
    return dataframe
