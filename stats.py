#!/usr/bin/python
from __future__ import print_function

import os
import numpy as np
from collections import defaultdict

txts = [f for f in os.listdir(".") if f.endswith(".txt")]

def get_safe_std_mean(data):
    data = np.array(data).copy()
    std = np.std(data)
    mean = np.mean(data)
    upper_limit = mean + std * 2.0
    lower_limit = mean - std * 2.0
    data = data[data < upper_limit]
    data = data[data > lower_limit]
    return (np.std(data), np.mean(data))

for txt in txts:
    # print name
    print("#####")
    print(txt)
    if "test_proc" in txt:
        time_dict = defaultdict(list)
        with open(txt) as f:
            lines = f.readlines()
        lines = [line.strip() for line in lines]
        for line in lines:
            key = int(line.strip().split()[2][:-1])
            value = int(line.strip().split()[3])
            time_dict[key].append(value)
        for k in range(8):
            std, mean = get_safe_std_mean(time_dict[k])
            print("#")
            print("time dict of:", k)
            print("num:", len(time_dict[k]))
            print("std:", std)
            print("mean:", mean)

    else:
        # load to matirx
        data = np.loadtxt(txt)
        # process
        std, mean = get_safe_std_mean(data)
        print("num:", len(data))
        print("std:", std)
        print("mean:", mean)
