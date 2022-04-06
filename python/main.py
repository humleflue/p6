import os
import pandas as pd
from sklearn.metrics import accuracy_score
from SVC import create_and_fit_SVC_classifier, get_default_config, get_train_test_split
from dotenv import load_dotenv

def main():
    load_dotenv()

    # Load data
    dataset_path = os.getenv('BEST_DATASET')
    df = pd.read_csv(dataset_path)
    X_train, X_test, Y_train, Y_test = get_train_test_split(df)

    # Create and fit model   
    model_config = get_default_config()
    classifier   = create_and_fit_SVC_classifier(X_train, Y_train, model_config)

    # Get predictions and measure accuracy
    Y_pred = classifier.predict(X_test)
    accuracy = accuracy_score(Y_test.iloc[:,-1], Y_pred)
    model_config.setAccuracy(accuracy)
    
    print(model_config)

if __name__ == '__main__':
    main()
    