Run the server:

nc -l 1234


------------------

1) send() will only wait until the data are put into the local socket buffer

2) Setting a socket non-blocking causes it to fail when putting data into a 
full socket buffer instead of blocking until there is space in the socket buffer.

	`self.sock.setblocking(0)`


3) `recv()` call blocks until it receives a message in it's buffer
	`select()` call help us deal this situation


