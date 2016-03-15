import socket
import time
import sys


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "plese specify host ip"
        exit(0)

    # specify host and port
    host = sys.argv[1]
    port = 50015

    # establish connection
    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    skt.connect((host, port))

    # determine size
    size = 1024

    # prepare data
    data = '1' * size

    # init array for saving time
    times = []

    # send the data!
    time_start = time.time()
    skt.send(data)
    time_end = time.time()
    times.append(time_end - time_start)

    # clean up
    skt.close()
