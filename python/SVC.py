import os
import pandas as pd
from dotenv import load_dotenv
from sklearn import svm
from sklearn.model_selection import train_test_split

class SVCConfiguration:
    def __init__(self, kernel, soft_margin, gamma, poly_degrees=2):
        self.kernel = kernel
        self.soft_margin = soft_margin
        self.gamma = gamma
        self.poly_degrees = poly_degrees
        self.accuracy=None
        self.report=None
        self.validation_accuracy=None
        self.classifier=None

    def __str__(self):
        poly_degrees = f', poly_degrees:{self.poly_degrees}' if self.kernel == 'poly' else ''
        return f'{self.accuracy}, {self.validation_accuracy}: <kernel:{self.kernel}, soft_margin:{self.soft_margin}, gamma:{self.gamma}{poly_degrees}>'

    def set_accuracy(self, accuracy: float):
        self.accuracy = accuracy
    
    def set_validation_accuracy(self, accuracy: float):
        self.validation_accuracy = accuracy

    def set_report(self, report):
        self.report = report

    def set_classifier(self, classifier):
        self.classifier = classifier

def create_SVC_classifier(conf: SVCConfiguration):
    return svm.SVC(kernel=conf.kernel, C=conf.soft_margin, gamma=conf.gamma, degree=conf.poly_degrees)

def create_and_fit_SVC_classifier(X_train, Y_train, conf: SVCConfiguration):
    classifier = create_SVC_classifier(conf)
    classifier.fit(X_train, Y_train.iloc[:,-1])
    return classifier

def get_default_config() -> SVCConfiguration:
    load_dotenv()
    kernel      = os.getenv('BEST_KERNEL')
    gamma       = float(os.getenv('BEST_GAMMA'))
    soft_margin = float(os.getenv('BEST_SOFT_MARGIN'))
    return SVCConfiguration(kernel, soft_margin, gamma)

def get_train_test_validation_split(df: pd.DataFrame):
    X = df.iloc[:,:-2]
    Y = df.iloc[:,-2:]
    return train_test_split( X, Y, test_size=0.25)

def get_train_test_validation_split(df: pd.DataFrame):
    X = df.iloc[:,:-2]
    Y = df.iloc[:,-2:]
    X_train_validation, X_test, Y_train_validation, Y_test = train_test_split( X, Y, test_size=0.20)
    X_train, X_validation, Y_train, Y_validation = train_test_split( X_train_validation, Y_train_validation, test_size=0.10)
    return X_train, X_test, X_validation, Y_train, Y_test, Y_validation