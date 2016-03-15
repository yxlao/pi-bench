import socket
import time
import sys
import math
import numpy as np

sizes = [int(math.pow(2,i)) for i in range(10, 25)]
num_trail = 3
port = 50016

def time_size_to_bandwidth(time, size):
    """
    time in sec, size in bytes, return in MB/s
    """
    return float(size) / float(time) / float(1024 * 1024)

def times_size_to_bandwidths(times, size):
    bandwidths = []
    for time in times:
        bandwidths.append(time_size_to_bandwidth(time, size))
    return bandwidths

def reliable_recv(skt, size):
    buffer = "" 
    while len(buffer) < size: 
        data = skt.recv(size-len(buffer)) 
        if not data: 
            break
        buffer += data
    return buffer

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "plese specify host ip"
        exit(0)

    # specify host and port
    host = sys.argv[1]

    # establish connection
    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    skt.connect((host, port))
    skt.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    for size in sizes:
        # prepare data
        data_send = '0' * size

        # init array for saving time
        times = []

        # experiments
        for trail in range(num_trail):
            time_start = time.time()
            num_bytes = skt.send(data_send)
            time_end = time.time()
            times.append(time_end - time_start)
            print 'sent %s bytes' % num_bytes

        # print stats
        bandwidths = times_size_to_bandwidths(times, size)
        print ("bandwidth, size, %s, mean, %s, std, %s, max, %s" % 
               (size, np.mean(bandwidths), np.std(bandwidths), np.max(bandwidths)))

    # clean up
    skt.close()
