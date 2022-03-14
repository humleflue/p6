import pandas as pd
import glob as glob
import os


def GetAllFilesInFolder(path, folder_name, extension):
    return glob.glob(os.path.join(path,folder_name, extension))

def GetCSVFilesByFolderAndReturnDataFrame(path, folder_name, status_value):
    li = []
    all_files = GetAllFilesInFolder(path, folder_name, '*.csv')
    for filename in all_files:
        df = pd.read_csv(filename, sep=";", index_col=None, header=0)
        df["Status"] = status_value
        li.append(df)
    return pd.concat(li, axis=0, ignore_index=True)

def CombineAllDataFrames(path):
    data_list = []
    data_list.append(GetMovingData(path))
    data_list.append(GetUsingData(path))
    data_list.append(GetStationaryData(path))

    return pd.concat(data_list, axis=0,ignore_index=True)

def GetMovingData(path):
    moving = "moving"
    driving_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Driving", moving)
    high_vibration_df = GetCSVFilesByFolderAndReturnDataFrame(path, "High vibration", moving)
    walking_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Walking", moving)
    return pd.concat([driving_df, high_vibration_df, walking_df], axis=0, ignore_index=True)


def GetUsingData(path):
    using = "using"
    hand_tools_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Hand tools", using)
    industrial_tools_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Industrial equipment", using)
    return pd.concat([hand_tools_df, industrial_tools_df])

def GetStationaryData(path):
    stationary = "stationary"
    stationary_df = GetCSVFilesByFolderAndReturnDataFrame(path, "Stationary", stationary)
    return stationary_df

def GetFileByPathAndName(path, name):
    df = pd.read_csv(os.path.join(path, name), sep=";", index_col=None, header=0)
    return df



def main():
    print("running")

if __name__ == '__main__':
    main()