import pandas as pd

df = pd.read_csv('./flattened_1sec_with_broad_category.csv')

df = df.iloc[:, 1:]
df.to_csv('./flattened_1sec_with_broad_category1.csv', index=False)