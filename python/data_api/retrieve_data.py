import math

import pandas as pd
import glob as glob
import os


class DataFrameContainer:
    def __init__(self, data_frame: pd.DataFrame, caption: str):
        self.df = data_frame
        self.caption = caption

    def sample_every_n_elements(self, n: int):
        return DataFrameContainer(self.df.iloc[::n], self.caption)

    def vector_length_df(self):
        length_li = []
        for index, row in self.df.iterrows():
            length_li.append(math.sqrt(row["X"] ** 2 + row["Y"] ** 2 + row["Z"] ** 2))
        return DataFrameContainer(pd.DataFrame(length_li, columns=['Length']), self.caption)


def get_file_name_from_path(file_path):
    # Removes parent directories
    with_type = os.path.basename(file_path)
    # Removes file extension
    without_type = with_type.split(".")[0]
    return without_type


def get_all_file_paths_in_folder(path, folder_name, extension):
    return glob.glob(os.path.join(path, folder_name, extension))


def get_csv_files_by_folder_and_return_data_frame(dataset_base_dir_path, folder_name, status_value=None):
    li = []
    all_file_paths = get_all_file_paths_in_folder(dataset_base_dir_path, folder_name, '*.csv')
    for file_path in all_file_paths:
        df = get_file_by_path_and_name(file_path)
        if status_value is not None:
            df.df["Status"] = status_value
        li.append(df)
    return li


def combine_all_data_frames(path):
    return get_moving_data(path) + get_using_data(path) + get_stationary_data(path)


def combine_all_data_frames(path, moving_label, using_label, stationary_label):
    return get_moving_data(path, moving_label) + get_using_data(path, using_label) + get_stationary_data(path, stationary_label)



def get_moving_data(path, status_value=None):
    driving_df = get_csv_files_by_folder_and_return_data_frame(path, "Driving", status_value)
    high_vibration_df = get_csv_files_by_folder_and_return_data_frame(path, "High vibration", status_value)
    walking_df = get_csv_files_by_folder_and_return_data_frame(path, "Walking", status_value)
    return driving_df + high_vibration_df + walking_df


def get_using_data(path, status_value=None):
    hand_tools_df = get_csv_files_by_folder_and_return_data_frame(path, "Hand tools", status_value)
    industrial_tools_df = get_csv_files_by_folder_and_return_data_frame(path, "Industrial equipment", status_value)
    return hand_tools_df + industrial_tools_df


def get_stationary_data(path, status_value=None):
    stationary_df = get_csv_files_by_folder_and_return_data_frame(path, "Stationary", status_value)
    return stationary_df


def get_file_by_path_and_name(path) -> DataFrameContainer:
    df = pd.read_csv(path, sep=";", index_col=None, header=0)
    file_name_without_file_extension = get_file_name_from_path(path)
    return DataFrameContainer(df, file_name_without_file_extension)

def get_file_by_path_and_name(path, sep = ';') -> DataFrameContainer:
    df = pd.read_csv(path, sep=sep, index_col=None, header=0)
    file_name_without_file_extension = get_file_name_from_path(path)
    return DataFrameContainer(df, file_name_without_file_extension)


def main():
    print("running")


if __name__ == '__main__':
    main()
