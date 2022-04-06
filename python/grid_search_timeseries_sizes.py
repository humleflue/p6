import os
from telnetlib import GA
from dotenv import load_dotenv
import pandas as pd
import numpy as np
import modules.info as info
from typing import Final
from SVC import SVCConfiguration, get_train_test_split
from grid_search_hyper_parameters import run_svm
from grid_search_helper_functions import printNBestConfigs

# BEST RESULT SO FAR #
# 0.875195007800312: <kernel:rbf, soft_margin:24.5, gamma:0.0001>

# Cross validation parameters
# 1. Kernels
# 2. Degree (Only for poly)
# 3. Soft margin (C)
# 4. Gamma
# 5. Time series length
load_dotenv()
KERNEL:      Final = os.getenv('BEST_KERNEL')
GAMMA:       Final = float(os.getenv('BEST_GAMMA'))
SOFT_MARGIN: Final = float(os.getenv('BEST_SOFT_MARGIN'))
ROWS_PER_TIMESERIES_MIN:  Final = float(os.getenv('ROWS_PER_TIMESERIES_MIN'))
ROWS_PER_TIMESERIES_MAX:  Final = float(os.getenv('ROWS_PER_TIMESERIES_MAX'))
ROWS_PER_TIMESERIES_STEP: Final = float(os.getenv('ROWS_PER_TIMESERIES_STEP'))
ROWS_PER_TIMESERIES = np.arange(ROWS_PER_TIMESERIES_MIN, ROWS_PER_TIMESERIES_MAX, ROWS_PER_TIMESERIES_STEP)

def main():
    # Setup
    configs = []
    for timeseries_size in ROWS_PER_TIMESERIES:
        df = pd.read_csv(f"../datasetsModified/flattened_datasets/lessThanOneSecond/all_data_noise_removed_small{int(timeseries_size)}_points_series_flattened.csv")
        df["broad_category"] = "None" # This adds an extra column to the df
        df = info.add_classification_to_df(df)
        X_train, X_test, Y_train, Y_test = get_train_test_split(df)
        config = SVCConfiguration(KERNEL, SOFT_MARGIN, GAMMA, timeseries_size)
        config = run_svm(X_train, X_test, Y_train, Y_test, config)
        configs.append(config)

    printNBestConfigs(500, configs)

if __name__ == '__main__':
    main()
