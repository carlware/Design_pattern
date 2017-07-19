import shared

registryList = []

def registry(f):
    def callbackRegistration():
        registryList.append(f())
        return f
    callbackRegistration()


def predicate1(e):
    if e[0] == 'data':
        return True

def action1(e, eventLoop):
    shared.cbkCalled +=1
    print('do whatever')

@registry
def registerCallback():
    return (predicate1, action1)
