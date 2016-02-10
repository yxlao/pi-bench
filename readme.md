# System Measurement Project
[git@git.ucsd.edu:yuw258/cse221.git](git@git.ucsd.edu:yuw258/cse221.git)

## Steup
* Install gcc 4.7, resolve depedency issues
* Install corresponding linux header

## Kernel module
```sh
# to list current kernel module
lsmod
# to insert a kernel module
sudo insmod enable-ccr.ko
# to remove a kernel module
sudo rmmod enable-ccr
```

## CPU Operations
```sh
$ cd raspbian-ccr
$ sudo make
$ sudo insmod enable-ccr.ko
```

