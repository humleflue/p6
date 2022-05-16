from numpy import integer
import pandas as pd

def transform_data_frame_to_c_array(df: pd.DataFrame, amountOfRows: integer):
    data_points = df.head(amountOfRows)
    string_elems = data_points.to_string(header=False,
                          index=False,
                          index_names=False).split('\n')
    each_point_as_string_array = ['{' + ', '.join(ele.split()) + '}' for ele in string_elems]
    
    c_array_as_string = '{\n'

    for i, array in enumerate(each_point_as_string_array):
        c_array_as_string += array
        if i != len(each_point_as_string_array) - 1:
            c_array_as_string += ','
        c_array_as_string += '\n' 
    
    c_array_as_string += '};'

    return c_array_as_string

def transform_coef_and_intercept_to_c(coefs, intercepts, labels):
    string_result = "{"
    coef_intercept_index = 0

    for idx, label in enumerate(labels):
        for otherLabel in (labels[idx + 1:]):
            string_result += "{ " + label + ", " + otherLabel + ", {"

            # Adds the correct coefficients for this pair of labels
            for coef in coefs[coef_intercept_index]:
                string_result += str(coef) + ", "

            # Removes the last ", "
            string_result = string_result[:-2]
            # Adds intercept
            string_result += "}, " + str(intercepts[coef_intercept_index]) + "},\n"
            
            coef_intercept_index += 1

    string_result += "};"

    print(string_result)



if __name__ == '__main__':
    file_path = "./datasets/datasetsTU/Stationary/Dataset stationary highway.csv"
    df = pd.read_csv(file_path, delimiter=";")
    res = transform_data_frame_to_c_array(df, 36)
    print(res)
    