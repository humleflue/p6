import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay, accuracy_score, precision_recall_fscore_support as score
import Retrieve_data as rd
import math

path = "../../Data"

def TrainAndPrintRandomForest(data):
    X = data.iloc[:,0:3].values
    Y = data.iloc[:,3].values
    X_train, X_test, Y_train, Y_test = train_test_split(X,Y, test_size = 0.2, random_state = 0)
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.fit_transform(X_test)

    trees_arr = []
    accuracy_arr = []
    precision_arr = []
        
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
        # precision,recall,fscore,support=score(Y_test,y_pred,average=None)
        # print(f"precision: {precision}")
        print(precision)
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



### ALL DATA TEST ###
def AllDataRandomForest(path):
    all_data = rd.CombineAllDataFrames(path)
    TrainAndPrintRandomForest(all_data)
# AllDataRandomForest(path)
#####################

### ONLY DRILL ######
def OnlyDrillRandomForest(path):
    data_li = []
    data_li.append(rd.GetStationaryData(path))
    # data_li.append(rd.GetUsingData(path))
    using = pd.read_csv(path + "/Hand tools/Dataset drill and screw electric.csv", sep=";", index_col=None, header=0)
    using["Status"] = "using"
    data_li.append(using)
    data_li.append(rd.GetMovingData(path))
    df = pd.concat(data_li, axis=0, ignore_index=True)
    TrainAndPrintRandomForest(df)
OnlyDrillRandomForest(path)
#####################