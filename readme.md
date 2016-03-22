# pi-bench

## NFS setup for raspberry pi

```sh
# mount
sudo mount 192.168.0.18:/host_path/to/nfs /mnt
# unmount
sudo umount -l /mnt
```

## NFS set up for host
Please see [ref 0](https://help.ubuntu.com/community/SettingUpNFSHowTo) and [ref 1](http://serverfault.com/questions/611007/unable-to-write-to-mount-point-nfs-server-getting-permission-denied).

```sh
echo /etc/exports
/host_path/to/nfs/       192.168.0.17(rw,no_root_squash)
sudo exportfs -av
sudo service nfs-kernel-server restart
```

## Steup
* Install gcc 4.7, resolve depedency issues
* Install corresponding linux header

```sh
# for kernel 4.1.17+
wget https://www.niksula.hut.fi/~mhiienka/Rpi/linux-headers-rpi/linux-headers-4.1.17%2B_4.1.17%2B-2_armhf.deb
sudo dpkg -i linux-headers-4.1.17+_4.1.17+-2_armhf.deb
```

## Kernel module

```sh
# compile
cd raspbian-ccr/
sudo make
# to list current kernel module
lsmod
# to insert a kernel module
sudo insmod enable-ccr.ko
# to remove a kernel module
sudo rmmod enable-ccr
```

