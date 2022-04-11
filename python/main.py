import os
import math
import pandas as pd
from sklearn.metrics import accuracy_score, classification_report
from SVC import create_and_fit_SVC_classifier, get_default_config, get_train_test_split
from dotenv import load_dotenv

def main():
    load_dotenv()

    # Load data
    dataset_path = os.getenv('BEST_DATASET')
    df = pd.read_csv(dataset_path)
    df_sampled_data = sample_flattened_dataset(df)
    df_avg_data =  average_sampling(df)
    X_train, X_test, Y_train, Y_test = get_train_test_split(df_avg_data)

    # Create and fit model   
    model_config = get_default_config()
    classifier   = create_and_fit_SVC_classifier(X_train, Y_train, model_config)

    # Get predictions and measure accuracy
    Y_pred = classifier.predict(X_test)
    accuracy = accuracy_score(Y_test.iloc[:,-1], Y_pred)
    model_config.set_accuracy(accuracy)
    report = classification_report(Y_test.iloc[:,-1], Y_pred)
    model_config.set_report(report)
    
    print(model_config)

def sample_flattened_dataset(df):
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]
    df_with_sampling = df_without_last_two_columns.sample(frac = 0.25, axis = 1) # Axis = 1 means columns. 0 is rows
    res = pd.merge(df_with_sampling, df_last_two_columns, left_index=True, right_index=True) # Combines the two dataframes on index
    
    return res

def average_sampling(df):
    # Seperating the data labels from the actual data
    df_last_two_columns = df.iloc[:,-2:]
    df_without_last_two_columns = df.iloc[:,:-2]
    
    # New dataframe that will contain mean square data
    new_df = pd.DataFrame(columns = ["x","y","z"])

    # Loops through all rows
    for index1, row in df_without_last_two_columns.iterrows():
        # List containing the sum of x, y, and z squared.
        time_series_sum = [0,0,0]

        # Loops through all data points in a row and adds the squared value to time_series_sum
        for index2, ele in enumerate(row.to_list()):
            time_series_sum[index2 % 3] += (ele ** 2)

        #length_of_row = row.shape[0]

        # Takes the square root of the sum, and appends it to the new dataframe
        time_series_avg = [math.sqrt(x) for x in time_series_sum]
        new_df.loc[index1] = time_series_avg
    
    # Combines the two dataframes on index, thereby adding the label back
    res = pd.merge(new_df, df_last_two_columns, left_index=True, right_index=True) 
    print(res)
    return res



if __name__ == '__main__':
    main()
    