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

``` bash
git clone https://github.com/zeusxs/cap.git
cd cap && scons
```

# 依赖

- [libpcap](https://github.com/the-tcpdump-group/libpcap)
- [libtins](https://github.com/mfontanini/libtins)

# example:
![example](https://github.com/zeusxs/cap/blob/master/images/example.gif)

# Other Open project Thanks
如下两个库集成到本项目中，所以不需要单独安装
- [spdlog](https://github.com/gabime/spdlog)
- [tclap](http://tclap.sourceforge.net/)
