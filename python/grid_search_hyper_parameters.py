import os
import pandas as pd
import numpy as np
import modules.info as info
from dotenv import load_dotenv
from sklearn.metrics import accuracy_score
from typing import Final
from SVC import SVCConfiguration, create_SVC_classifier, create_and_fit_SVC_classifier, get_train_test_validation_split
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
    conf.set_classifier(classifier)
    return conf

def run_grid_search_on_configurations(X_train, X_test, Y_train, Y_test):
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
    return configs

def get_validation_set_accuracy(configs, X_validation, Y_validation):
    for conf in configs:
        Y_pred = conf.classifier.predict(X_validation)
        accuracy = accuracy_score(Y_validation.iloc[:,-1], Y_pred)
        conf.set_validation_accuracy(accuracy)

    return configs
        
def main(path_to_dataset="./datasets/flattened_datasets/flattened_1sec_with_broad_category.csv"):
    # Setup
    df = pd.read_csv(path_to_dataset)
    df["broad_category"] = "None" # This adds an extra column to the df
    df = info.add_classification_to_df(df)
    X_train, X_test, X_validation, Y_train, Y_test, Y_validation = get_train_test_validation_split(df)

    configs = run_grid_search_on_configurations(X_train, X_test, Y_train, Y_test)
    configs = get_validation_set_accuracy(configs, X_validation, Y_validation)
    printNBestConfigs(500, configs)

if __name__ == '__main__':
    main()
