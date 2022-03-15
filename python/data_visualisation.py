import os

import matplotlib.pyplot as plt
import pandas as pd
import data_api.retrieve_data as rd

base_dir_path = "../"
data_path = 'datasets'
directories = ["Driving", "High vibration", "Walking", "Hand tools", "Industrial equipment", "Stationary"]


def save_plot(dfc: rd.DataFrameContainer, sampling: str):
    dfc.df.plot(title=dfc.caption, kind='line')
    figure_filename = f'{sampling} - {dfc.caption}'
    # Relative path from p6
    plt.savefig(os.path.join(base_dir_path, 'visualisations', 'plots', f'{figure_filename}.png'), format='png')


# def save_all_plots(path, folder_name, sampling):
#     all_files = rd.get_all_files_in_folder(path, folder_name, '*.csv')
#     print(os.getcwd(), all_files)
#     for filepath in all_files:
#         filename = get_file_name_from_path(filepath)
#         title = f'{filename} ({sampling})'
#         pandas_data_frame = pd.read_csv(filepath, sep=";", index_col=None, header=0)
#         save_plot(pandas_data_frame, title)


def save_all_plots(data_frames: list[rd.DataFrameContainer], sampling: str):
    for df in data_frames:
        save_plot(df, sampling)


def main():
    for element in directories:
        save_all_plots(os.path.join(base_dir_path, data_path), element, "None")


if __name__ == '__main__':
    main()
