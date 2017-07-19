from  cbk import registryList


if __name__ == '__main__':
    genEvent = ('data', 1.2)
    for pred, action  in registryList:
        if pred(genEvent) == True:
            action(genEvent, None)
