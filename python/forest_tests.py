import pandas as pd
import matplotlib.pyplot as plt
from sklearn import tree
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay, accuracy_score, precision_recall_fscore_support as score
import data_api.retrieve_data as rd
import os

data_path = 'datasets'

def train_model(data):
    X = data.iloc[:,0:3].values
    Y = data.iloc[:,3].values
    X_train, X_test, Y_train, Y_test = train_test_split(X,Y, test_size = 0.2, random_state = 0)
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.fit_transform(X_test)

    return X_train, X_test, Y_train, Y_test

def predict(X_train, Y_train, X_test, n_of_trees):
    classifier = RandomForestClassifier(n_estimators=n_of_trees,random_state=0)
    classifier.fit(X_train, Y_train)
    Y_pred = classifier.predict(X_test)
    return Y_pred

def print_prediction_results(Y_test, Y_pred, n_of_trees):
    print(f"----------------------- {n_of_trees} trees -----------------------")
    ConfusionMatrixDisplay.from_predictions(Y_test, Y_pred)
    print(confusion_matrix(Y_test,Y_pred))
    # Uncomment if visualisation of confusion matrix is wanted
    # plt.show()
    precision = classification_report(Y_test,Y_pred)
    print(precision)

    # Uncomment if you want results seperated by type
    # precision,recall,fscore,support=score(Y_test,Y_pred,average=None)
    
    accuracyScore = accuracy_score(Y_test, Y_pred)
    print(accuracyScore)
    print()
    print()

def add_status_to_df(df, status):
    df["Status"] = status
    return df

def split_df_in_readings_and_class(df):
    return df.iloc[:,0:3].to_numpy(), df.iloc[:,3].to_numpy()

def run_model(X_train, Y_train, X_test, Y_test):
    for i in range(3):
        n_of_trees = 1*10**i
        Y_pred = predict(X_train, Y_train, X_test, n_of_trees)
        print_prediction_results(Y_test, Y_pred, n_of_trees)

def train_and_run_model(data):
    X_train, X_test, Y_train, Y_test = train_model(data)
    run_model(X_train, Y_train, X_test, Y_test)

### TEST ON SINGLE DATA SOURCE ###
def test_single_data_source(data, status, test_data):
    X_train, X_test, Y_train, Y_test = train_model(data)

    test_df = rd.get_file_by_path_and_name(data_path, test_data)
    test_df = add_status_to_df(test_df, status)
    test_data, test_data_class = split_df_in_readings_and_class(test_df)

    run_model(X_train, Y_train, test_data, test_data_class)
    
##################################


### ALL DATA TEST ###
def all_data_random_forest(data_path):
    all_data = rd.combine_all_data_frames(data_path)
    train_and_run_model(all_data)
#####################

### ONLY DRILL ######
def only_drill_random_forest(data_path):
    data_li = []
    data_li.append(rd.get_stationary_data(data_path))
    using = rd.get_file_by_path_and_name(os.path.join(data_path,'Hand tools'), 'Dataset drill and screw electric.csv')
    using = add_status_to_df(using, 'using')
    data_li.append(using)
    data_li.append(rd.get_moving_data(data_path))
    df = pd.concat(data_li, axis=0, ignore_index=True)
    train_and_run_model(df)
#####################

def main():
    all_data_random_forest(data_path)

if __name__ == '__main__':
    main()
