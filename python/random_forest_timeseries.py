from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay, accuracy_score, precision_recall_fscore_support as score
import data_api.retrieve_data as rd
import numpy as np


data_path = '../datasets'
driving_labels = ['Driving']
using_labels = ['Industrial equipment', 'High vibration', 'Hand tools']
stationary_labels = ['Stationary']
walking_labels = ['Walking']

def get_flattened_data():
    all_data = rd.get_file_by_path_and_name('all_data_noise_removed_3_second_series_flattened.csv', ',')
    return all_data

def add_classification(dfc : rd.DataFrameContainer):
    dfc.df['broad_category'] = 'None'

    for index, row in dfc.df.iterrows():
        dataset_name = row[-2].split("/")[2]
        if dataset_name in driving_labels:
          dfc.df.iloc[index, -1] = "Driving"
        elif dataset_name in using_labels:
          dfc.df.iloc[index, -1] = "Using"
        elif dataset_name in stationary_labels:
          dfc.df.iloc[index, -1] = "Stationary"
        elif dataset_name in walking_labels:
          dfc.df.iloc[index, -1] = "Walking"

def transform_data(dfc : rd.DataFrameContainer):
    x = dfc.df.iloc[:,:-2].values
    y = dfc.df.iloc[:,-1:].values
    x_train, x_test, y_train, y_test = train_test_split(x,y, test_size = 0.2, random_state = 0)
    sc = StandardScaler()
    x_train = sc.fit_transform(x_train)
    x_test = sc.fit_transform(x_test)

    return x_train, x_test, y_train, y_test

def train_model(x_train, y_train, n_of_trees):
    classifer = RandomForestClassifier(n_estimators=n_of_trees, random_state=0)
    classifer.fit(x_train, np.ravel(y_train))
    return classifer

def predict(classifier, x_test):
    y_pred = classifier.predict(x_test)
    return y_pred

# This is a 1:1 copy of the function in forest_test.py
# Maybe we should have a different file for printing?
def print_prediction(y_test, y_pred, n_of_trees):
    print(f"----------------------- {n_of_trees} trees -----------------------")
    ConfusionMatrixDisplay.from_predictions(y_test, y_pred)
    conf_matrix = confusion_matrix(y_test,y_pred)
    print(conf_matrix)
    # Uncomment if visualisation of confusion matrix is wanted
    # plt.show()
    precision = classification_report(y_test,y_pred)
    print(precision)

    # Uncomment if you want results seperated by type
    # precision,recall,fscore,support=score(y_test,y_pred,average=None)

    acc_score = accuracy_score(y_test, y_pred)
    print(acc_score)
    print()
    print()

def main():
    all_data_class = get_flattened_data()
    add_classification(all_data_class)
    x_train, x_test, y_train, y_test = transform_data(all_data_class)
    for i in range(1,10):
        # n_of_trees = 1*10**i
        n_of_trees = i
        classifier = train_model(x_train, y_train, n_of_trees)
        y_pred = classifier. predict(x_test)
        print_prediction(y_test, y_pred, n_of_trees)


if __name__ == '__main__':
    main()
