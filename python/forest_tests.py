import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
import data_api.retrieve_data as rd
import os
import printing as prt

data_path = '../datasets'

def train_model(data):
    x = data.iloc[:,0:3].values
    y = data.iloc[:,3].values
    x_train, x_test, y_train, y_test = train_test_split(x,y, test_size = 0.2, random_state = 0)
    sc = StandardScaler()
    x_train = sc.fit_transform(x_train)
    x_test = sc.fit_transform(x_test)

    return x_train, x_test, y_train, y_test

def predict(x_train, y_train, x_test, n_of_trees):
    classifier = RandomForestClassifier(n_estimators=n_of_trees,random_state=0)
    classifier.fit(x_train, y_train)
    y_pred = classifier.predict(x_test)
    return y_pred

def add_status_to_df(df, status):
    df.df["Status"] = status
    return df

def split_df_in_readings_and_class(df):
    return df.iloc[:,0:3].to_numpy(), df.iloc[:,3].to_numpy()

def run_model(x_train, y_train, x_test, y_test):
    for i in range(3):
        n_of_trees = 1*10**i
        y_pred = predict(x_train, y_train, x_test, n_of_trees)
        prt.print_random_forest_predictions(y_test, y_pred, n_of_trees)

def train_and_run_model(data):
    x_train, x_test, y_train, y_test = train_model(data)
    run_model(x_train, y_train, x_test, y_test)

### TEST ON SINGLE DATA SOURCE ###
def test_single_data_source(data, status, test_data):
    x_train, x_test, y_train, y_test = train_model(data)

    test_df = rd.get_file_by_path_and_name(data_path, test_data)
    test_df = add_status_to_df(test_df, status)
    test_data, test_data_class = split_df_in_readings_and_class(test_df.df)

    run_model(x_train, y_train, test_data, test_data_class)
    
##################################


### ALL DATA TEST ###
def all_data_random_forest(data_path):
    all_data = rd.combine_all_data_frames(data_path, "moving", "using", "stationary")
    all_data_df = []
    for df in all_data:
        all_data_df.append(df.df)
    all_data = pd.concat(all_data_df, axis=0, ignore_index=True)
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
