import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay, accuracy_score, precision_recall_fscore_support as score
import data_api.retrieve_data as rd
import os

data_path = 'datasets'

def TrainModel(data):
    X = data.iloc[:,0:3].values
    Y = data.iloc[:,3].values
    X_train, X_test, Y_train, Y_test = train_test_split(X,Y, test_size = 0.2, random_state = 0)
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.fit_transform(X_test)

    return X_train, X_test, Y_train, Y_test

def TrainAndPrintRandomForest(data):
    X_train, X_test, Y_train, Y_test = TrainModel(data)

    trees_arr = []
    accuracy_arr = []
        
    for i in range(3):
        classifier = RandomForestClassifier(n_estimators=1*10**i,random_state=0)
        trees = 10*10**i
        print(f"----------------------- {trees} trees -----------------------")
        classifier.fit(X_train, Y_train)
        y_pred = classifier.predict(X_test)
        ConfusionMatrixDisplay.from_predictions(Y_test, y_pred)
        print(confusion_matrix(Y_test,y_pred))
        plt.show()
        precision = classification_report(Y_test,y_pred)
        print(precision)
        # precision,recall,fscore,support=score(Y_test,y_pred,average=None)
        # print(f"precision: {precision}")
        accuracyScore = accuracy_score(Y_test, y_pred)
        print(accuracyScore)

        trees_arr.append(trees)
        accuracy_arr.append(accuracyScore)

        print()
        print()

    plt.plot(trees_arr, accuracy_arr, marker='o')
    plt.xlim(0, trees + 1)
    # plt.ylim(0, 1)
    # plt.show()


### TEST ON SINGLE DATA SOURCE ###
def TestSingleDataSource(data, status, test_data):
    X_train, X_test, Y_train, Y_test = TrainModel(data)

    trees_arr = []
    accuracy_arr = []
    precision_arr = []
        
    for i in range(3):
        classifier = RandomForestClassifier(n_estimators=1*10**i,random_state=0)
        trees = 10*10**i
        print(f"----------------------- {trees} trees -----------------------")
        classifier.fit(X_train, Y_train)
        test_df = pd.read_csv(data_path + test_data, sep=";", index_col=None, header=0)
        test_df["Status"] = status
        test_data = test_df.iloc[:,0:3].to_numpy()
        test_data_class = test_df.iloc[:,3].to_numpy()
        y_pred = classifier.predict(test_data)
        ConfusionMatrixDisplay.from_predictions(test_data_class, y_pred)
        print(confusion_matrix(test_data_class,y_pred))
        plt.show()
        precision = classification_report(test_data_class,y_pred)
        print(precision)
        # precision,recall,fscore,support=score(test_data_class,y_pred,average=None)
        # print(f"precision: {precision}")
        accuracyScore = accuracy_score(test_data_class, y_pred)
        print(accuracyScore)
        trees_arr.append(trees)
        accuracy_arr.append(accuracyScore)

        print()
        print()

    plt.plot(trees_arr, accuracy_arr, marker='o')
    plt.xlim(0, trees + 1)
    # plt.ylim(0, 1)
    # plt.show()
##################################


### ALL DATA TEST ###
def AllDataRandomForest(data_path):
    all_data = rd.CombineAllDataFrames(data_path)
    # TestSingleDataSource(all_data, "using", "/Hand tools/Dataset drill and screw electric.csv")
    TrainAndPrintRandomForest(all_data)
#####################

### ONLY DRILL ######
def OnlyDrillRandomForest(data_path):
    data_li = []
    data_li.append(rd.GetStationaryData(data_path))
    # data_li.append(rd.GetUsingData(data_path))
    using = pd.read_csv(data_path + "/Hand tools/Dataset drill and screw electric.csv", sep=";", index_col=None, header=0)
    using["Status"] = "using"
    data_li.append(using)
    data_li.append(rd.GetMovingData(data_path))
    df = pd.concat(data_li, axis=0, ignore_index=True)
    TrainAndPrintRandomForest(df)
#####################

def main():
    AllDataRandomForest(data_path)

if __name__ == '__main__':
    main()
