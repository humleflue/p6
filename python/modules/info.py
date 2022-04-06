from typing import Final
from . import retrieve_data as rd
import pandas as pd

data_path: Final = '../datasets'
driving_labels: Final = ['Driving']
using_labels: Final = ['Industrial equipment', 'High vibration', 'Hand tools']
stationary_labels: Final = ['Stationary']
walking_labels: Final = ['Walking']

def add_classification(dfc: rd.DataFrameContainer):
    return rd.DataFrameContainer(add_classification_to_df(dfc.df), dfc.caption)

def add_classification_to_df(df: pd.DataFrame):
    df['broad_category'] = 'None'

    for index, row in df.iterrows():
        dataset_name = row[-2].split("/")[2]
        if dataset_name in driving_labels:
          df.iloc[index, -1] = "Driving"
        elif dataset_name in using_labels:
          df.iloc[index, -1] = "Using"
        elif dataset_name in stationary_labels:
          df.iloc[index, -1] = "Stationary"
        elif dataset_name in walking_labels:
          df.iloc[index, -1] = "Walking"

    return df
