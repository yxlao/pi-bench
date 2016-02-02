#!/usr/bin/python
from __future__ import print_function

import os
import numpy as np

txts = [f for f in os.listdir(".") if f.endswith(".txt")]

for txt in txts:
    # print name
    print("#####")
    print(txt)
    # load to matirx
    data = np.loadtxt(txt)
    # process
    print("num:", len(data))
    print("std:", np.std(data))
    print("mean:", np.mean(data))
