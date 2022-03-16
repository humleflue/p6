import os
import data_api.retrieve_data as rd
import data_visualisation as visualise

base_dir_path = "../"
data_path = 'datasets'


def main():
    moving_data = rd.get_moving_data(os.path.join(base_dir_path, data_path))

    # sample_sizes = [1, 50, 200, 500]
    # for sample_size in sample_sizes:
    #     sampled_moving_data = sample_every_n_elements_list(moving_data, sample_size)
    #     visualise.save_all_plots(sampled_moving_data, f'{sample_size}')
    # print(moving_data)
    for dataframe in moving_data:
        sampled_data = dataframe.vector_length_df()
        visualise.save_plot(sampled_data, "vector length")

def sample_every_n_elements_list(data_frames: list[rd.DataFrameContainer], n: int) -> list[rd.DataFrameContainer]:
    result = []

    for dfc in data_frames:
        sampled_dfc = dfc.sample_every_n_elements(n)
        result.append(sampled_dfc)

    return result


if __name__ == '__main__':
    main()
