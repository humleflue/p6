import os
import pandas as pd
from dotenv import load_dotenv
from sklearn import svm
import math
from sklearn.model_selection import train_test_split

class SVCConfiguration:
    def __init__(self, kernel, soft_margin, gamma, poly_degrees=2):
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
    classifier = svm.SVC(kernel=conf.kernel, C=conf.soft_margin, gamma=conf.gamma, degree=conf.poly_degrees)
    classifier.fit(X_train, Y_train.iloc[:,-1])

    return classifier

def get_default_config() -> SVCConfiguration:
    load_dotenv()
    kernel      = os.getenv('BEST_KERNEL')
    gamma       = float(os.getenv('BEST_GAMMA'))
    soft_margin = float(os.getenv('BEST_SOFT_MARGIN'))
    return SVCConfiguration(kernel, soft_margin, gamma)

def get_train_test_split(df: pd.DataFrame):
    X = df.iloc[:,:-2]
    Y = df.iloc[:,-2:]
    return train_test_split( X, Y, test_size=0.25)

# Returns a dataframe equal in structure to the flattened dataframe, but only with "percentage" amount of columns.
def sample_flattened_dataset(df, percentage):
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]
    df_with_sampling = df_without_last_two_columns.sample(frac = percentage, axis = 1) # Axis = 1 means columns. 0 is rows
    res = pd.merge(df_with_sampling, df_last_two_columns, left_index=True, right_index=True) # Combines the two dataframes on index
    
    return res

# TODO: This is not acutally the magnitude. Find out what it is, or if something else should be used
def flattened_dataframe_square_sum(df):
    # Seperating the data labels from the actual data
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]
    
    # New dataframe that will contain the smaller data
    new_df = pd.DataFrame(columns = ["x","y","z"])

    # Loops through all rows (This is bad practice)
    for index1, row in df_without_last_two_columns.iterrows():
        # List containing the sum of x, y, and z squared and summed.
        time_series_sum = [0,0,0]

        # Loops through all data points in a row and adds the squared value to time_series_sum
        for index2, ele in enumerate(row.to_list()):
            time_series_sum[index2 % 3] += (ele ** 2)

        # Takes the square root of the sum, and appends it to the new dataframe
        time_series_avg = [math.sqrt(x) for x in time_series_sum]
        new_df.loc[index1] = time_series_avg
    
    # Combines the two dataframes on index, thereby adding the label back
    res = pd.merge(new_df, df_last_two_columns, left_index=True, right_index=True) 
    return res