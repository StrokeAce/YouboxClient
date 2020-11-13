# YouboxClient
基于FreeRDP开发的远程桌面工具

## 依赖
sudo apt-get install qt5-default qt5-qmake qtcreator qttools5-dev

## 编译
mkdir build  
cd build && cmake .. && make

## 打包
执行 package/build_install_dir.sh 可一键打包，注意：在虚拟机的共享文件夹目录下打包会失败