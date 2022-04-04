import pandas as pd
import numpy as np
from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn.model_selection import cross_val_score
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
import modules.info as info
from typing import Final
from tqdm.notebook import tqdm

# BEST RESULT SO FAR #
# 0.875195007800312: <kernel:rbf, soft_margin:24.5, gamma:0.0001>

# Cross validation parameters
# 1. Kernels
# 2. Degree (Only for poly)
# 3. Soft margin (C)
# 4. Gamma
# 5. Time series length
KERNELS: Final = ['rbf']
POLY_DEGREES: Final = [2, 3, 4]
SOFT_MARGIN: Final = np.arange(24.5, 24.6, 0.2)
GAMMAS: Final = np.arange(0.0001, 10.0, 0.01)

class SVCConfiguration:
    def __init__(self, kernel, soft_margin, gamma, poly_degrees=2):
        self.kernel = kernel
        self.soft_margin = soft_margin
        self.gamma = gamma
        self.poly_degrees = poly_degrees
        self.accuracy=None

    def __str__(self):
        poly_degrees = f', poly_degrees:{self.poly_degrees}' if self.kernel == 'poly' else ''
        return f'{self.accuracy}: <kernel:{self.kernel}, soft_margin:{self.soft_margin}, gamma:{self.gamma}{poly_degrees}>'

    def setAccuracy(self, accuracy: float):
        self.accuracy = accuracy

def get_train_test_split(df: pd.DataFrame):
    X = df.iloc[:,:-2]
    Y = df.iloc[:,-2:]
    return train_test_split( X, Y, test_size=0.25)

# Returns a precision score
def run_svm(X_train, X_test, Y_train, Y_test, conf: SVCConfiguration) -> SVCConfiguration:
    clf = svm.SVC(kernel=conf.kernel, C=conf.soft_margin, gamma=conf.gamma, degree=conf.poly_degrees)
    clf.fit(X_train, Y_train.iloc[:,-1])
    Y_pred = clf.predict(X_test)
    accuracy = accuracy_score(Y_test.iloc[:,-1], Y_pred)
    conf.setAccuracy(accuracy)
    return conf

def main():
    # Setup
    df = pd.read_csv("../datasetsModified/flattened_datasets/flattened_1sec_with_broad_category.csv")
    df["broad_category"] = "None" # This adds an extra column to the df
    df = info.add_classification_to_df(df)
    X_train, X_test, Y_train, Y_test = get_train_test_split(df)

    configs = []
    for kernel in KERNELS:
        print(kernel)
        for margin in SOFT_MARGIN:
            for gamma in GAMMAS:
                if kernel != 'poly':
                    config = SVCConfiguration(kernel, margin, gamma)
                    config = run_svm(X_train, X_test, Y_train, Y_test, config)
                    print(config)
                    configs.append(config)
                else:
                    for degree in POLY_DEGREES:
                        config = SVCConfiguration(kernel, margin, gamma, degree)
                        config = run_svm(X_train, X_test, Y_train, Y_test, config)
                        print(config)
                        configs.append(config)
        
    configs.sort(key=lambda x: x.accuracy, reverse=True)
    print("--------")
    for index, config in enumerate(configs):
        if(index < 500):
            print(config)

if __name__ == '__main__':
    main()
