#说明
这个程序基于systemd和systemd-swap来动态管理swap的gui程序

#关于zswap
zswap是一个linux下实现的内存压缩技术，实现在ram中压缩内存来缓解内存不足，也避免了内存换出的消耗

#关于zram
zram是另一种内存压缩技术，可以通过建立内存压缩区来充当作为swap分区来使用

#关于动态swap file
它是通过简单的检测内存free容量，来动态地生成和释放swap文件块

#编译
sudo apt-get install qt5-default
qtchooser -run-tool=qmake -qt=qt5
make

#debian 打包
sh package.sh
