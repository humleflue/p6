import pandas as pd
import glob as glob


def GetCSVFilesByFolderAndReturnDataFrame(path, folder_name, status_value):
    li = []
    all_files = glob.glob(path + "/" + folder_name + "/*.csv")
    for filename in all_files:
        df = pd.read_csv(filename, sep=";", index_col=None, header=0)
        df["Status"] = status_value
        li.append(df)
    return pd.concat(li, axis=0, ignore_index=True)

def CombineAllDataFrames(path):
    moving = "moving"
    driving_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Driving", moving)
    high_vibration_df = GetCSVFilesByFolderAndReturnDataFrame(path, "High vibration", moving)
    walking_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Walking", moving)

    using = "using"
    hand_tools_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Hand tools", using)
    industrial_tools_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Industrial equipment", using)

    stationary = "stationary"
    stationary_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Stationary", stationary)

    all_data_list = [driving_df, high_vibration_df, walking_df, hand_tools_df, industrial_tools_df, stationary_df]
    return pd.concat(all_data_list, axis=0,ignore_index=True)
