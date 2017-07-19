"""
EventLoop help subject,
1) to maintain the observers
2) to notify observers
3) to process different types of events
"""
import queue
import time

class EventLoop():
    def __init__(self):
        self.events = queue.Queue()
        self.observers = []
        self.timedCallbacks = []
        self.pleaseShutDown = False
        self.startTime = None

    def sendEvent(self, *args):
        self.events.put(args)
        print('Got an event') # Debugging

    def runForever(self):
        while True:
            e = self.events.get()
            self.processEvent(e)
            if self.pleaseShutDown:
                break
            now = time.time()
            toRun = [(t,cb) for (t, cb) in self.timedCallbacks if t < now]
            for t, cb in toRun:
                if t < now:
                    cb()
                    self.timedCallbacks.remove((t,cb))

    def runLater(self, when, callback):
        self.timedCallbacks.append((time.time() + when, callback))

    def processEvent(self, e):
        for pred, action in self.observers:
            if pred(e):
                action(e, self)

    def shutDown(self):
        self.pleaseShutDown = True

    def addEventListener(self, predicate, action):
        self.observers.append((predicate, action))

# Singleton
eventLoop = EventLoop() # To maintain observers and notify them
 
