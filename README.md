# cap
一个类似于tcpcopy的流量复制小工具，用于把目标端口的流量复制到另一个流量

# 编译
使用scons编译链工具进行编译，在编译之前记得安装好libtins,

debian ubuntu16.04可以通过如下命令安装
``` bash
git clone --branch v4.0 https://github.com/mfontanini/libtins.git
apt-get install libpcap-dev libssl-dev cmake
cd libtins && mkdir build && cd build 
cmake .. && make && make install
```

centos可以使用如下命令安装
``` bash
git clone --branch v4.0 https://github.com/mfontanini/libtins.git
yum install libpcap-devel openssl-devel cmake
cd libtins && mkdir build && cd build 
cmake .. && make && make install
```

编译cap
``` bash
git clone https://github.com/zeusxs/cap.git
cd cap && scons
```

使用
``` shell
./cap -d [device_name] -i [rule]
```

比如现在要把本地回路网卡上端口为8000的流量复制到172.17.0.2:9000的地址上
``` shell
# lo为本地网卡
./cap -d lo -i 8000-172.17.0.2:9000

# 如果需要抓取eth0网卡的流量, 使用如下命令
./cap -d eth0 -i 8000-172.17.0.2:9000
```

# example:
![example](https://github.com/zeusxs/cap/blob/master/images/example.gif)

# 依赖
- [libpcap](https://github.com/the-tcpdump-group/libpcap)
- [libtins](https://github.com/mfontanini/libtins)

# Other Open project Thanks
如下两个库已经集成到本项目中，所以不需要单独安装
- [spdlog](https://github.com/gabime/spdlog)
- [tclap](http://tclap.sourceforge.net/)
