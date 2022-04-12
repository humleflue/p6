from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
import modules.retrieve_data as rd
import numpy as np
from .modules import printing as prt
import modules.info as info

def get_flattened_data():
    all_data = rd.get_file_by_path_and_name('all_data_noise_removed_3_second_series_flattened.csv', ',')
    return all_data

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

def main():
    all_data_class = get_flattened_data()
    info.add_classification(all_data_class)
    x_train, x_test, y_train, y_test = transform_data(all_data_class)
    for i in range(1,10):
        # n_of_trees = 1*10**i
        n_of_trees = i
        classifier = train_model(x_train, y_train, n_of_trees)
        y_pred = classifier. predict(x_test)
        prt.print_random_forest_predictions(y_test, y_pred, n_of_trees)


if __name__ == '__main__':
    main()
