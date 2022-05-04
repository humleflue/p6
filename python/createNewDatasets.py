from numpy import broadcast_arrays
import pandas as pd

numbers = [1.0, 2.0, 3.0, 4.0, 5.0]

categories = {
    'Driving': 'Driving',
    'Hand tools': 'Using',
    'High vibration': 'Using',
    'Industrial equipment': 'Using',
    'Stationary': 'Stationary',
    'Walking': 'Walking'
}

# filename = f'all_data_noise_removed_{number}_second_series_flattened_with_broad.csv'
# newFilename = f'flattened_{number}sec_with_broad_category.csv'

for number in numbers:
    df = pd.read_csv(f'datasets/flattened_datasets/all_data_noise_removed_{number}_second_series_flattened.csv')
    cols = df.columns.tolist()
    df = df.assign(broad_category = lambda x: x[cols[-1]].str.split('/'))

    broad_category = pd.DataFrame(df['broad_category'].tolist())[2]

    df = df.assign(broad_category = broad_category)
    df['broad_category'] = df['broad_category'].map(categories)
    print(df.isnull().values.any())
    df.to_csv(f'flattened_{number}sec_with_broad_category.csv')
