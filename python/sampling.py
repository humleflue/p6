import os
from .modules import retrieve_data as rd
import data_visualisation as visualise

base_dir_path = "../"
data_path = 'datasets'


def main():
    moving_data = rd.get_moving_data(os.path.join(base_dir_path, data_path))
    data = rd.get_using_data(os.path.join(base_dir_path, data_path))

    sample_sizes = [100,200]
    # for sample_size in sample_sizes:
    #     # sampled_moving_data = sample_every_n_elements_list(data, sample_size)
    #     sampled_moving_data = sample_every_n_elements_list(moving_data, sample_size)
    #     visualise.save_all_plots(sampled_moving_data, f'{sample_size}')

    for dataframe in moving_data:
        vector_length = dataframe.vector_length_df()
        for sample_size in sample_sizes:
            vector_length = vector_length.sample_every_n_elements(sample_size)
            visualise.save_plot(vector_length, f'({sample_size}) Vector length')

def sample_every_n_elements_list(data_frames: list[rd.DataFrameContainer], n: int) -> list[rd.DataFrameContainer]:
    result = []

    for dfc in data_frames:
        sampled_dfc = dfc.sample_every_n_elements(n)
        result.append(sampled_dfc)

    return result


if __name__ == '__main__':
    main()
