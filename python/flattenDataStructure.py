import pandas as pd
import math
from os import listdir

shortest_file_length = 768
shortest_file_name = "Dataset air wrench 1.csv"
rows_per_time_series = 36 #15 seconds of measurements

def create_dataframe_with_flattened_datasets(dirName="../datasets"):
    all_datasets_flattened = []
    all_file_paths = create_all_file_paths(dirName)

    for file in all_file_paths:
        df = pd.read_csv(file, delimiter=";")
        number_of_rows_in_df = df.shape[0]
        for partition in range(math.floor(number_of_rows_in_df/rows_per_time_series)):
            time_series_partition = create_time_series_partition(partition, rows_per_time_series, df, file)
            all_datasets_flattened.append(time_series_partition)
    return pd.DataFrame(all_datasets_flattened)

def create_time_series_partition(partition, rows_per_time_series, dataFrame, label):
    time_series = dataFrame.iloc[partition*rows_per_time_series:(partition + 1 )*rows_per_time_series:] # +1 because partition starts at 0, and we don't want the upper bound to be multiplied by 0
    time_series = time_series.unstack().to_frame().sort_index(level=1).T #Flattens the dataframe putting all rows after each other in one row
    time_series = time_series.assign(label=[label])
    return time_series.values.tolist()[0]

def create_all_file_paths(dirName="../datasets"):
    all_file_paths = []
    for subDir in listdir(dirName):
        for fileName in listdir(f"{dirName}/{subDir}"):
           all_file_paths.append(f"{dirName}/{subDir}/{fileName}")
    return all_file_paths

create_dataframe_with_flattened_datasets().to_csv("all_data_noise_removed_3_second_series_flattened.csv", index=False)
