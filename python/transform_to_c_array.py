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

if __name__ == '__main__':
    file_path = "./datasets/datasetsTU/Stationary/Dataset stationary highway.csv"
    df = pd.read_csv(file_path, delimiter=";")
    res = transform_data_frame_to_c_array(df, 36)
    print(res)
    