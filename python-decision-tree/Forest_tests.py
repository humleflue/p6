import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
import Retrieve_data as rd

path = "../Data"


### ALL DATA TEST ###

all_data = rd.CombineAllDataFrames(path)

def TrainAndPrintTree(data):
    X = data.iloc[:,0:3].values
    Y = data.iloc[:,3].values
    
    X_train, X_test, Y_train, Y_test = train_test_split(X,Y, test_size = 0.2, random_state = 0)
    
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.fit_transform(X_test)
    
    
    for i in range(3):
        classifier = RandomForestClassifier(n_estimators=1*10**i,random_state=0)
        print(f"----------------------- {1*10**i} trees -----------------------")
        classifier.fit(X_train, Y_train)
        y_pred = classifier.predict(X_test)
    
        print(confusion_matrix(Y_test,y_pred))
        precision = classification_report(Y_test,y_pred)
        print(precision)
        print(accuracy_score(Y_test, y_pred))
        print()
        print()

#TrainAndPrintTree(all_data)


### ONLY DRILL ### 

stationary = rd.GetCSVFilesByFolderAndReturnDataFrame(path, "Stationary", "stationary")
using = pd.read_csv(path + "/Hand tools/Dataset drill and screw electric.csv", sep=";", index_col=None, header=0)
# moving = 


# df["Status"] = status_value