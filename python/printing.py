from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay, accuracy_score, precision_recall_fscore_support as score


def print_random_forest_predictions(y_test, y_pred, n_of_trees):
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
