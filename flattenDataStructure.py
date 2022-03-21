import pandas as pd
import numpy as np
import math
shortest_file_length = 768
shortest_file_name = "Dataset air wrench 1.csv"
number_of_measurements_for_time_series = 180 #15 seconds of measurements

from os import listdir
def load_dataset(dirName="datasets"):
    all_datasets_flattened = []
    length_of_shortest_dataset = 1000000
    name_of_shortest_dataset = "foo"
    for subDir in listdir(dirName):
        for fileName in listdir(f"{dirName}/{subDir}"):
            if(fileName == "Dataset air wrench 1.csv" or True):
                path_to_file = f"{dirName}/{subDir}/{fileName}"
                df = pd.read_csv(path_to_file, delimiter=";")
                number_of_rows_in_df = df.shape[0]
                for partition in range(math.floor(number_of_rows_in_df/number_of_measurements_for_time_series)):
                    time_series = df.iloc[partition*number_of_measurements_for_time_series:(partition + 1 )*number_of_measurements_for_time_series,:]
                    time_series = time_series.unstack().to_frame().sort_index(level=1).T
                    time_series = time_series.assign(label=[fileName])
                    for list in time_series.values.tolist():
                        all_datasets_flattened.append(list)
    
    return pd.DataFrame(all_datasets_flattened)
    
load_dataset().to_csv("all_data_flattened.csv", index=False)