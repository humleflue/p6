import pandas as pd
import glob as glob
import os


def get_all_files_in_folder(path, folder_name, extension):
    return glob.glob(os.path.join(path,folder_name, extension))

def get_csv_files_by_folder_and_return_data_frame(path, folder_name, status_value):
    li = []
    all_files = get_all_files_in_folder(path, folder_name, '*.csv')
    for filename in all_files:
        df = pd.read_csv(filename, sep=";", index_col=None, header=0)
        df["Status"] = status_value
        li.append(df)
    return pd.concat(li, axis=0, ignore_index=True)

def combine_all_data_frames(path):
    data_list = []
    data_list.append(get_moving_data(path))
    data_list.append(get_using_data(path))
    data_list.append(get_stationary_data(path))

    return pd.concat(data_list, axis=0,ignore_index=True)

def get_moving_data(path):
    moving = "moving"
    driving_df = get_csv_files_by_folder_and_return_data_frame(path, "Driving", moving)
    high_vibration_df = get_csv_files_by_folder_and_return_data_frame(path, "High vibration", moving)
    walking_df = get_csv_files_by_folder_and_return_data_frame(path, "Walking", moving)
    return pd.concat([driving_df, high_vibration_df, walking_df], axis=0, ignore_index=True)


def get_using_data(path):
    using = "using"
    hand_tools_df = get_csv_files_by_folder_and_return_data_frame(path, "Hand tools", using)
    industrial_tools_df = get_csv_files_by_folder_and_return_data_frame(path, "Industrial equipment", using)
    return pd.concat([hand_tools_df, industrial_tools_df])

def get_stationary_data(path):
    stationary = "stationary"
    stationary_df = get_csv_files_by_folder_and_return_data_frame(path, "Stationary", stationary)
    return stationary_df

def get_file_by_path_and_name(path, name):
    print(os.path.abspath(os.path.join(path, name)))
    df = pd.read_csv(os.path.join(path, name), sep=";", index_col=None, header=0)
    return df



def main():
    print("running")

if __name__ == '__main__':
    main()