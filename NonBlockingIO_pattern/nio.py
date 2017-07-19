import socket
import sys
from eventloop import EventLoop

class Connection():
    def __init__(self):
        self.sock = socket.socket()
        self.sock.connect(('localhost', 1234))

    def fileno(self):
        return self.sock.fileno()

    def onRead(self):
        msg = self.sock.recv(1000).decode('utf-8')
        print(msg)

    def send(self, msg):
        self.sock.send(msg)

class Input():
    def __init__(self, sock):
        self.sock = sock

    def fileno(self):
        return sys.stdin.fileno()

    def onRead(self):
        msg = sys.stdin.readline().encode('utf-8')
        self.sock.send(msg)

sock = Connection()
inputReader = Input(sock)

eventLoop = EventLoop()
eventLoop.addReader(sock)
eventLoop.addReader(inputReader)
eventLoop.runForever()
