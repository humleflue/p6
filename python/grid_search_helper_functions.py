def printNBestConfigs(n, configs):
    configs.sort(key=lambda x: x.accuracy, reverse=True)
    print("--------")
    for index, config in enumerate(configs):
        if(index < 500):
            print(config)
            