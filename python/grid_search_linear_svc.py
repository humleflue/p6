from matplotlib import pyplot as plt
import pandas as pd
from sklearn.metrics import confusion_matrix
from sklearn.svm import LinearSVC
from sklearn.model_selection import cross_val_score

from SVC import average_sampling, get_train_test_split
from modules.grid_search_helper_functions import printNBestConfigs

path_to_dataset="./datasets/flattened_datasets/flattened_1sec_with_broad_category.csv"

class Data:
    def __init__(self, c, score):
        self.c = c
        self.score = score

    def __str__(self):
        return f'C={self.c}, score={self.score}'
# Setup
df = pd.read_csv(path_to_dataset)
df_avg_data =  average_sampling(df)
X_train, X_test, Y_train, Y_test = get_train_test_split(df_avg_data)

# Comment in/out the wanted/unwanted sections
results = []
for c_val in [1]:
    svc = LinearSVC(C=c_val, max_iter=10000, dual=False)
    svc.fit(X_train, Y_train.iloc[:,-1])

    # SECTION START: Confusion matrix
    Y_pred = svc.predict(X_test)
    conf = confusion_matrix(Y_test.iloc[:,-1], Y_pred)
    print(c_val, conf)
    # SECTION END: Confusion matrix

    # SECTION START: Cross validation
    # scores = cross_val_score(svc, X_train, Y_train.iloc[:,-1], cv=10)
    # mean = scores.mean()
    # print(c_val, mean, scores.std())
    # results.append(Data(c_val, mean))
    # SECTION END: Cross validation

# Print the 20 best results
results.sort(key=lambda x: x.score, reverse=True)
print("--------")
for index, res in enumerate(results):
    if(index < 20):
        print(res)
