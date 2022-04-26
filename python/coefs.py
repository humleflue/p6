from cProfile import label
import os
import pandas as pd
from pygments import highlight
from sklearn.metrics import accuracy_score, classification_report
from SVC import create_and_fit_SVC_classifier, get_default_config, get_train_test_split, sample_flattened_dataset, average_sampling
from dotenv import load_dotenv
import pickle
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import LinearSVC, SVC

def main():
    x1 = 1
    x2 = 2
    y1 = 1
    y2 = 2


    X = np.array([
                [x1+0.8,y1],[x1+0.8,y2],[x2,y1],[x2,y2],                 #upper right
                [x1,-y1],[x1,-y2],[x2,-y1],[x2,-y2],                     #lower right
                [-x1,-y1+0.5],[-x1,-y2+0.5],[-x2,-y1+0.5],[-x2,-y2+0.5], #lower left
                [-x1,y1],[-x1,y2],[-x2,y1],[-x2,y2]                      #upper left
                ])                    
    y = np.array([
                'Walking','Walking','Walking','Walking', 
                'Stationary','Stationary','Stationary','Stationary',    
                'Using','Using','Using','Using',
                'Driving','Driving','Driving','Driving',
                ]) 

    y_colors = np.array([
                2,2,2,2,
                3,3,3,3, 
                4,4,4,4,    
                1,1,1,1,
                ]) 

    colors = {0:'red', 1:'blue', 2:'green', 3:'yellow', 4:'black', 5:'gray'}

    method = 'ovr'
    clf = SVC(kernel='linear', C=1)
    clf.fit(X, y)


    new_point_driving = [-2, 1.5]
    new_point_stationary = [2, -1.5]

    print('driving', np.dot(clf.coef_[0], new_point_driving) + clf.intercept_[0])
    print('stationary', np.dot(clf.coef_[0], new_point_stationary) + clf.intercept_[0])


    print('coef_\n', clf.coef_)
    print('intercept_', clf.intercept_)

    number_of_coefficients = len(clf.coef_)
    figure, axis = plt.subplots(1, 6)
    for j in range(number_of_coefficients):
        for i in range(j+1):
            w = clf.coef_[i]
            w = [w[0], w[1] + 0.0001]
            a = -w[0] / w[1]

            xx = np.linspace(-4,12)
            yy = a * xx - clf.intercept_[i] / w[1]

            axis[j].plot(xx, yy, label=f'h{i}', c=colors[i])
        axis[j].set_xlim([-4, 4])
        axis[j].set_ylim([-4, 4])
        axis[j].set_title(method)
        axis[j].scatter(X[:, 0], X[:, 1], c = y_colors)
        axis[j].legend()
            
    plt.show()



if __name__ == '__main__':
    main()
    