import socket
import time
import sys


if __name__ == "__main__":
    # specify host and port
    host = ''
    port = 50015

    # bind to socket and listen
    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    skt.bind((host, port))
    skt.listen(1)

    # accepts client connection
    conn, addr = skt.accept()
    print 'client address: ', addr

    # receive data
    data = conn.recv(1024)
    print 'get data of size %s' % len(data)

    # clean up
    conn.close()
    skt.close()
