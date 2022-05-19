import os
import pandas as pd
import numpy as np
from dotenv import load_dotenv
from sklearn.metrics import accuracy_score, precision_recall_fscore_support
from typing import Final
from SVC import SVCConfiguration, average_sampling, create_and_fit_SVC_classifier, get_train_test_split, feature_extraction
from modules.grid_search_helper_functions import printNBestConfigs

# BEST RESULT SO FAR #
# 0.875195007800312: <kernel:rbf, soft_margin:24.5, gamma:0.0001>

# Cross validation parameters
# 1. Kernels
# 2. Degree (Only for poly)
# 3. Soft margin (C)
# 4. Gamma
# 5. Time series length
load_dotenv()
gammas_min       = float(os.getenv('GAMMAS_MIN'))
gammas_max       = float(os.getenv('GAMMAS_MAX'))
gammas_step      = float(os.getenv('GAMMAS_STEP'))

soft_margin_min  = float(os.getenv('SOFT_MARGIN_MIN'))
soft_margin_max  = float(os.getenv('SOFT_MARGIN_MAX'))
soft_margin_step = float(os.getenv('SOFT_MARGIN_STEP'))

POLY_DEGREES     = [float(x) for x in os.getenv('POLY_DEGREES').split(",")]

GAMMAS:       Final = np.arange(gammas_min, gammas_max, gammas_step)
KERNELS:      Final = os.getenv('KERNELS').split(",")
SOFT_MARGIN:  Final = np.arange(soft_margin_min, soft_margin_max, soft_margin_step)

# Returns a precision score
def run_svm(X_train, X_test, Y_train, Y_test, conf: SVCConfiguration) -> SVCConfiguration:
    classifier = create_and_fit_SVC_classifier(X_train, Y_train, conf)
    Y_pred = classifier.predict(X_test)
    accuracy = accuracy_score(Y_test.iloc[:,-1], Y_pred)
    conf.set_accuracy(accuracy)
    conf.set_weighted(precision_recall_fscore_support(Y_test.iloc[:,-1], Y_pred, average='weighted'))
    return conf

def run_grid_search_on_configurations(X_train, X_test, Y_train, Y_test):
    configs = []
    for kernel in KERNELS:
        print(kernel)
        for margin in SOFT_MARGIN:
            if kernel == 'linear':
                config = SVCConfiguration(kernel, margin)
                config = run_svm(X_train, X_test, Y_train, Y_test, config)
                print(config)
                configs.append(config)
            else:
                for gamma in [0.0001]:
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
    return configs
        
def main(path_to_dataset="./datasets/flattened_datasets/flattened_3.0sec_with_broad_category.csv"):
    # Setup
    df = pd.read_csv(path_to_dataset)
    #df_avg_data =  average_sampling(df)
    df_many_features = feature_extraction(df)
    X_train, X_test, Y_train, Y_test = get_train_test_split(df_many_features)

    configs = run_grid_search_on_configurations(X_train, X_test, Y_train, Y_test)
    printNBestConfigs(500, configs)

if __name__ == '__main__':
    main()
