#编译
sudo apt-get install qt5-default
qtchooser -run-tool=qmake -qt=qt5
make

#debian 打包
sh package.sh
