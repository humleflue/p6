import pandas as pd
import matplotlib.pyplot as plt
import glob
import os
import data_api.retrieve_data as rd

data_path = 'datasets'
Directories = ["Driving", "High vibration", "Walking", "Hand tools", "Industrial equipment", "Stationary"]

def GetFileNameFromPath(file):
    # Removes parent directories
    with_type = os.path.basename(file)
    # Removes file extension
    without_type = with_type.split(".")[0]
    return without_type
    
def SavePlot(filepath, filename):
    ax = pd.read_csv(filepath, sep=";", index_col=None, header=0)
    ax.plot(title=filename, kind='line')
    # Relative path from p6
    plt.savefig(os.path.join('visualisations', 'plots',f'{filename}.png'), format='png')

def SaveAllPlots(path, folder_name, sampling):
    all_files = rd.GetAllFilesInFolder(path, folder_name, '*.csv')
    print(all_files)
    for filepath in all_files:
        filename = GetFileNameFromPath(filepath)
        title = f'{filename} ({sampling})'
        SavePlot(filepath, title)

def main():
    for element in Directories:
        SaveAllPlots(data_path, element, "None")

if __name__ == '__main__':
    main()