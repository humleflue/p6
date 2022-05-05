import pandas as pd
import numpy as np
from flattenDataStructure import *

second_intervals = [1.0, 2.0, 3.0, 4.0, 5.0]

categories = {
    'Driving': 'Driving',
    'Hand tools': 'Using',
    'High vibration': 'Using',
    'Industrial equipment': 'Using',
    'Stationary': 'Stationary',
    'Walking': 'Walking'
}

category_min_max = {
    'Driving': {'min': 10, 'max': 20},
    'Stationary': {'min': 0, 'max': 10},
    'Using': {'min': 100, 'max': 10000},
    'Walking': {'min': 0, 'max': 200},
}

interval_time_in_seconds = 3
amount_of_axes = 3
measure_frequency = 12


def add_broad_category_to_second_intervals():
    for number in second_intervals:
        df = pd.read_csv(f'datasets/flattened_datasets/all_data_noise_removed_{number}_second_series_flattened.csv')
        cols = df.columns.tolist()
        df = df.assign(broad_category = lambda x: x[cols[-1]].str.split('/'))

        broad_category = pd.DataFrame(df['broad_category'].tolist())[2]

        df = df.assign(broad_category = broad_category)
        df['broad_category'] = df['broad_category'].map(categories)
        print(df.isnull().values.any())
        df.to_csv(f'flattened_{number}sec_with_broad_category.csv', index=False)


def filter_abs_XYZ_sum(df, min, max):
    df = df.loc[ ((abs(df['X']) + abs(df['Y']) + abs(df['Z']) ) > min) ]
    df = df.loc[ ((abs(df['X']) + abs(df['Y']) + abs(df['Z']) ) < max) ]
    return df
    

def apply_min_max_filter_on_category(df, filter, min, max):
    df = filter(df, min, max)
    return df


def find_broad_category(file):
    file_category = file.split('/')[3]
    broad_category = categories[file_category]
    return broad_category

def main():
    all_file_paths = create_all_file_paths()
    all_data_filtered_flattened_partitioned = pd.DataFrame() 

    for file in all_file_paths:
        broad_category = find_broad_category(file)
        df = pd.read_csv(file, delimiter=';')

        min = category_min_max[broad_category]['min']
        max = category_min_max[broad_category]['max']

        df = apply_min_max_filter_on_category(df, filter_abs_XYZ_sum, min, max)

        flattened_df = df.to_numpy().ravel()

        numbers_per_partition = interval_time_in_seconds * amount_of_axes * measure_frequency
        partitions_amount = math.floor( len(flattened_df) / numbers_per_partition )

        for i in range(partitions_amount):
            row = flattened_df[i*numbers_per_partition: (i+1) * numbers_per_partition]
            row = np.append(row, broad_category)
            row_as_df = pd.DataFrame(row).T
            all_data_filtered_flattened_partitioned = all_data_filtered_flattened_partitioned.append(row_as_df)
            
    cols = all_data_filtered_flattened_partitioned.columns
    all_data_filtered_flattened_partitioned.rename(columns={cols[-1]: 'broad_category'}, inplace=True)
    all_data_filtered_flattened_partitioned.to_csv(f'all_data_filtered_flattened_partitioned_{interval_time_in_seconds}_seconds.csv', index=False)
    
if __name__ == '__main__':
    main()
