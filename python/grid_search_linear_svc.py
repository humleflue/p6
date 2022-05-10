from matplotlib import pyplot as plt
import pandas as pd
from sklearn.metrics import confusion_matrix
from sklearn import svm
from sklearn.model_selection import cross_val_score

from SVC import average_sampling, get_train_test_split, feature_extraction
from modules.grid_search_helper_functions import printNBestConfigs

path_to_dataset="./datasets/flattened_datasets/flattened_3.0sec_with_broad_category.csv"

class Data:
    def __init__(self, c, score):
        self.c = c
        self.score = score

    def __str__(self):
        return f'C={self.c}, score={self.score}'
# Setup
df = pd.read_csv(path_to_dataset)

df_many_features = feature_extraction(df)
#df_abs_sum = average_sampling(df)
X_train, X_test, Y_train, Y_test = get_train_test_split(df_many_features, 0.01)

# Comment in/out the wanted/unwanted sections
results = []
for c_val in [1]:
    svc = svm.SVC(kernel='linear', C=24.5, gamma=0.0001)
    print("Fitting...")
    svc.fit(X_train, Y_train.iloc[:,-1])
    print("Done fitting.")

    # SECTION START: Confusion matrix
    # Y_pred = svc.predict(X_test)
    # conf = confusion_matrix(Y_test.iloc[:,-1], Y_pred)
    # print(c_val, conf)
    # SECTION END: Confusion matrix

    # SECTION START: Cross validation
    print("Cross validating...")
    scores = cross_val_score(svc, X_train, Y_train.iloc[:,-1], cv=5)
    print("Done cross validating.")
    mean = scores.mean()
    print(c_val, scores, mean, scores.std())
    results.append(Data(c_val, mean))
    # SECTION END: Cross validation

# Print the 20 best results
results.sort(key=lambda x: x.score, reverse=True)
print("--------")
for index, res in enumerate(results):
    if(index < 20):
        print(res)
