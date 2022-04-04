import pandas as pd
import numpy as np
# from sklearn import svm
# from sklearn.model_selection import train_test_split
# from sklearn.model_selection import cross_val_score
# from sklearn.metrics import accuracy_score
# from sklearn.metrics import confusion_matrix
# from sklearn.metrics import ConfusionMatrixDisplay
import modules.info as info
from typing import Final
from cross_validate import SVCConfiguration, get_train_test_split, run_svm

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
SOFT_MARGIN: Final = [24.5]
GAMMAS: Final = [0.0001]
ROWS_PER_TIMESERIES: Final = np.arange(1, 13, 1)

def main():
    # Setup
    configs = []
    for timeseries_size in ROWS_PER_TIMESERIES:
        df = pd.read_csv(f"../datasetsModified/flattened_datasets/lessThanOneSecond/all_data_noise_removed_small{timeseries_size}_points_series_flattened.csv")
        df["broad_category"] = "None" # This adds an extra column to the df
        df = info.add_classification_to_df(df)
        X_train, X_test, Y_train, Y_test = get_train_test_split(df)
        for kernel in KERNELS:
            print("kernel", kernel)
            for soft_margin in SOFT_MARGIN:
                print("soft_margin", soft_margin)
                for gamma in GAMMAS:
                    print(gamma)
                    config = SVCConfiguration(kernel, soft_margin, gamma, timeseries_size)
                    config = run_svm(X_train, X_test, Y_train, Y_test, config)
                    configs.append(config)

    print("--------")
    configs.sort(key=lambda x: x.accuracy, reverse=True)
    for index, config in enumerate(configs):
        if(index < 500):
            print(config)

if __name__ == '__main__':
    main()
