import os
import numpy as np
import pandas as pd
from dotenv import load_dotenv
from sklearn import svm
from sklearn.model_selection import train_test_split
import math

class SVCConfiguration:
    def __init__(self, kernel, soft_margin, gamma=0.0001, poly_degrees=2):
        self.kernel = kernel
        self.soft_margin = soft_margin
        self.gamma = gamma
        self.poly_degrees = poly_degrees
        self.accuracy=None
        self.report=None

    def __str__(self):
        poly_degrees = f', poly_degrees:{self.poly_degrees}' if self.kernel == 'poly' else ''
        return f'{self.accuracy}: <kernel:{self.kernel}, soft_margin:{self.soft_margin}, gamma:{self.gamma}{poly_degrees}>'

    def set_accuracy(self, accuracy: float):
        self.accuracy = accuracy

    def set_report(self, report):
        self.report = report

def create_and_fit_SVC_classifier(X_train, Y_train, conf: SVCConfiguration) -> SVCConfiguration:
    classifier = svm.SVC(kernel=conf.kernel, C=conf.soft_margin, gamma=conf.gamma, degree=conf.poly_degrees, verbose=False)
    classifier.fit(X_train, Y_train.iloc[:,-1])
    return classifier

def get_default_config() -> SVCConfiguration:
    load_dotenv()
    kernel      = os.getenv('BEST_KERNEL')
    gamma       = float(os.getenv('BEST_GAMMA'))
    soft_margin = float(os.getenv('BEST_SOFT_MARGIN'))
    return SVCConfiguration(kernel, soft_margin, gamma)

def get_train_test_split(df: pd.DataFrame, split=0.25):
    X = df.iloc[:,:-2]
    Y = df.iloc[:,-2:]
    return train_test_split( X, Y, test_size=split)

def sample_flattened_dataset(df):
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]
    df_with_sampling = df_without_last_two_columns.sample(frac = 0.25, axis = 1) # Axis = 1 means columns. 0 is rows
    res = pd.merge(df_with_sampling, df_last_two_columns, left_index=True, right_index=True) # Combines the two dataframes on index
    
    return res

def average_sampling(df):
    # Seperating the data labels from the actual data
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]
    
    # New dataframe that will contain mean square data
    new_df = pd.DataFrame(columns = ["x","y","z"])

    # Loops through all rows
    for index1, row in df_without_last_two_columns.iterrows():
        # List containing the sum of x, y, and z squared.
        time_series_sum = [0,0,0]

        # Loops through all data points in a row and adds the squared value to time_series_sum
        for index2, ele in enumerate(row.to_list()):
            time_series_sum[index2 % 3] += (ele ** 2)

        #length_of_row = row.shape[0]

        # Takes the square root of the sum, and appends it to the new dataframe
        time_series_avg = [math.sqrt(x) for x in time_series_sum]
        new_df.loc[index1] = time_series_avg
    
    # Combines the two dataframes on index, thereby adding the label back
    res = pd.merge(new_df, df_last_two_columns, left_index=True, right_index=True) 
    # print(res)

    return res

# Splits a flattened row into X, Y, Z arrays.
def split_flattened_row_into_xyz(df):
    xyz_list = [[],[],[]]

    for index, ele in enumerate(df.to_list()):
        xyz_list[index % 3].append(ele)

    return xyz_list[0], xyz_list[1], xyz_list[2]


# Extracts a bunch of features from the flattened dataset, and returns a dataframe with each feature being its own column.
def feature_extraction(df):
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]

    new_df = pd.DataFrame(columns = ["x_mean","y_mean","z_mean",
        "x_max","y_max","z_max",
        "x_min","y_min","z_min",
        "x_abs_sum","y_abs_sum","z_abs_sum",
        "x_abs_mean","y_abs_mean","z_abs_mean",
        "x_abs_std","y_abs_std","z_abs_std",
        "total_max",
        "total_min",
        "total_abs_sum",
        "total_abs_mean",
        "total_abs_std"])

    for index, row in df_without_last_two_columns.iterrows():
        # List containing the sum of x, y, and z squared.
        x, y, z = split_flattened_row_into_xyz(row)

        new_row = [np.mean(x), np.mean(y), np.mean(z), 
            np.max(x), np.max(y), np.max(z), 
            np.min(x), np.min(y), np.min(z), 
            sum([abs(num) for num in x]), sum([abs(num) for num in y]), sum([abs(num) for num in z]),
            np.mean([abs(num) for num in x]), np.mean([abs(num) for num in y]), np.mean([abs(num) for num in z]),
            np.std([abs(num) for num in x]), np.std([abs(num) for num in y]), np.std([abs(num) for num in z]),
            np.max(row),
            np.min(row),
            sum([abs(num) for num in row]),
            np.mean([abs(num) for num in row]),
            np.std([abs(num) for num in row]),
        ]

        new_df.loc[index] = new_row

    # Merges the dataframe containing the features back with the dataframe containing the labels.
    res = pd.merge(new_df, df_last_two_columns, left_index=True, right_index=True) 

    return res