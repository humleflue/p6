import os
import pandas as pd
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, ConfusionMatrixDisplay
from sklearn.model_selection import StratifiedKFold
from sklearn.feature_selection import RFECV
from sklearn.datasets import make_classification
from SVC import create_and_fit_SVC_classifier, get_default_config, get_train_test_split, sample_flattened_dataset, average_sampling, feature_extraction
from transform_to_c_array import transform_coef_and_intercept_to_c
from dotenv import load_dotenv
import pickle
import numpy as np
import matplotlib.pyplot as plt
from manualPredictor import manual_predict


def main(use_existing_model=True):
    load_dotenv()

    # Load data
    dataset_path = os.getenv('BEST_DATASET')
    df = pd.read_csv(dataset_path)

    df_many_features = feature_extraction(df)
    #df_sampled_data = sample_flattened_dataset(df)
    #df_avg_data =  average_sampling(df)
    X_train, X_test, Y_train, Y_test = get_train_test_split(df_many_features, 0.25)

    filename = f'fitted_{os.getenv("BEST_KERNEL")}_OVO_model.sav'
    model_config = get_default_config()

    if use_existing_model:
        classifier = pickle.load(open(filename, 'rb'))
    else:
        # Create fit and save model 
        classifier = create_new_model(X_train, Y_train, model_config, filename)

    # Print model config, coefficients and intercepts 
    print('config\n', model_config)
    print(' \n\ncoef\n', classifier.coef_)
    print(' \n\nintercept\n', classifier.intercept_)

    #print(transform_coef_and_intercept_to_c(classifier.coef_, classifier.intercept_, ["DRIVING", "STATIONARY", "USING", "WALKING"]))

    # Get predictions and measure accuracy
    Y_pred = classifier.predict(X_test)
    accuracy = accuracy_score(Y_test.iloc[:,-1], Y_pred)
    model_config.set_accuracy(accuracy)
    report = classification_report(Y_test.iloc[:,-1], Y_pred)
    model_config.set_report(report)
    print(accuracy)
    print(report)
    
    ConfusionMatrixDisplay.from_predictions(Y_test.iloc[:,-1], Y_pred)
    plt.show()

    # #new_point_stationary = [1, 2, 1]
    # #manual_predict([new_point_stationary], classifier.coef_, classifier.intercept_)

    # # Plot a 3D plot
    # if model_config.kernel == 'linear':
    #     fig = plt.figure()
    #     line = np.linspace(-15, 100, 30)
    #     x, y = np.meshgrid(line, line)  
    #     ax = fig.add_subplot(111, projection='3d')
    #     for i in range(classifier.coef_.shape[0]):
    #         # This math is not understood yet
    #         z = lambda x,y: (-classifier.intercept_[i]-classifier.coef_[i][0]*x -classifier.coef_[i][1]*y) / classifier.coef_[i][2]
    #         ax.plot_surface(x, y, z(x, y))
    #     plt.show()


def create_new_model(X_train, Y_train, model_config, filename):
    print('start fitting')
    classifier = create_and_fit_SVC_classifier(X_train, Y_train, model_config)
    pickle.dump(classifier, open(filename, 'wb'))
    print('done dumping')
    return classifier

if __name__ == '__main__':
    main()
    