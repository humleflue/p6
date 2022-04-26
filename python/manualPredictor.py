import numpy as np

# Sets of labels corresponding to the 6 hyperplanes 
hyperplanes = [('Driving', 'Stationary'), ('Driving', 'Using'), ('Driving','Walking'), ('Stationary' ,'Using'), ('Stationary', 'Walking'), ('Using','Walking')]    

def predict(datapoints, coefs, intercepts):
    vectors_coefs_intercepts = zip(hyperplanes, coefs, intercepts) # Creating 3 tuples consisting of a label sets, vectors/coefs and intercepts
    for point in datapoints:
        point_classification_scores = {'Driving':0, 'Using':0, 'Stationary':0, 'Walking':0} # set or reset the score for the datapoint
        for vector_coef_intercept in list(vectors_coefs_intercepts):

            dot_product_result = np.dot(point, vector_coef_intercept[1]) 
            classification = dot_product_result + vector_coef_intercept[2]

            # If classification is positive then the score/count for index 0 label is incremented otherwise the label for index 1 is incremented
            if classification > 0: 
                point_classification_scores[vector_coef_intercept[0][0]] += 1
            else:
                point_classification_scores[vector_coef_intercept[0][1]] += 1

        print(point_classification_scores)
