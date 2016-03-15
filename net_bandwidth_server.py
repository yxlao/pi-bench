import socket
import time
import sys
import math

from net_bandwidth_client import sizes, num_trail, port, reliable_recv

if __name__ == "__main__":
    # specify host and port
    host = ''

    # bind to socket and listen
    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    skt.bind((host, port))
    skt.listen(1)
    skt.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    skt.settimeout(20)

    # accepts client connection
    conn, addr = skt.accept()
    print 'client address: ', addr

    for size in sizes:
        data_send = '0' * size
        for trail in range(num_trail):
            data_recv = reliable_recv(conn, size)
            print 'redeived %s bytes' % len(data_recv)
            num_bytes = conn.send(data_send)
            print 'sent %s bytes' % num_bytes

    # clean up
    conn.close()
    skt.close()
