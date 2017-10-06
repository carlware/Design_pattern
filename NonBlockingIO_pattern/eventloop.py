import select

class EventLoop():
    def __init__(self):
        self.readers = []

    def addReader(self, reader):
        self.readers.append(reader)

    def runForever(self):
        while True:
            readers, _, _ = select.select(self.readers, [], [])
            for reader in readers:
                reader.onRead()
