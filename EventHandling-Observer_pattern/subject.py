"""
An object called subject,
1) Maintains the list of dependents, called observers 
2) Automatically notifies observers, about different type of events
"""
import random
import threading
import time
from eventloop import eventLoop

import pdb

def generateEventHelper(eventLoop):
    for i in range(10):
        time.sleep(random.random())
        eventLoop.sendEvent('data', i+random.random())
        print('Event sent')
    eventLoop.sendEvent('done')
    
def launchThreadHelper(eventLoop):
    t = threading.Thread(target=generateEventHelper, args=(eventLoop, ))
    t.start()

# action code for a specific event
acc = 0
def addToAccAction(e, eventLoop): # Not sure, how to avoid 2nd arg
    global acc
    global numOfEvents
    acc += e[1]
    print(acc)

# action code for done event
doneEvents = 0
def shutDownAction(e, eventLoop):
    global doneEvents
    doneEvents += 1
    if doneEvents == 4: # After 4 done events
        print('Event loop is shutting down')
        eventLoop.shutDown()

def subject():
    # Add observer, in this case
    eventLoop.addEventListener( lambda x: x[0] == 'data',
                                addToAccAction)

    eventLoop.addEventListener( lambda x: x[0] == 'done',
                                shutDownAction)

    # Now generate events - can be data or state or whatever
    launchThreadHelper(eventLoop)
    launchThreadHelper(eventLoop)
    launchThreadHelper(eventLoop)
    launchThreadHelper(eventLoop)

    # Notifying those events to relevant observers
    eventLoop.runLater(2, lambda: print('2 seconds are up***********************'))
    eventLoop.runForever()

# pdb.set_trace()
if __name__ == '__main__':
    subject()
