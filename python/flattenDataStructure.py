import pandas as pd
import math
import numpy as np
import os
from typing import Final
from dotenv import load_dotenv

load_dotenv()
SOFT_MARGIN: Final = float(os.getenv('BEST_SOFT_MARGIN'))
ROWS_PER_TIMESERIES_MIN:  Final = float(os.getenv('ROWS_PER_TIMESERIES_MIN'))
ROWS_PER_TIMESERIES_MAX:  Final = float(os.getenv('ROWS_PER_TIMESERIES_MAX'))
ROWS_PER_TIMESERIES_STEP: Final = float(os.getenv('ROWS_PER_TIMESERIES_STEP'))
ROWS_PER_TIMESERIES: Final = np.arange(ROWS_PER_TIMESERIES_MIN, ROWS_PER_TIMESERIES_MAX, ROWS_PER_TIMESERIES_STEP)

def create_dataframe_with_flattened_datasets(rows_per_time_series, dirName="../datasetsTU"):
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

def create_all_file_paths(dirName="../datasetsTU"):
    all_file_paths = []
    for subDir in os.listdir(dirName):
        for fileName in os.listdir(f"{dirName}/{subDir}"):
            all_file_paths.append(f"{dirName}/{subDir}/{fileName}")
    return all_file_paths

def main():
    for timeseries_size in ROWS_PER_TIMESERIES:
        create_dataframe_with_flattened_datasets(int(timeseries_size)).to_csv(f"all_data_noise_removed_small{timeseries_size}_points_series_flattened.csv", index=False)
        print(timeseries_size, "done")

if __name__ == '__main__':
    main()
