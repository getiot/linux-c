# Hello

## 交叉编译

设置环境变量

```bash
export PATH=/opt/buildroot/host:/opt/buildroot/host/bin:$PATH
export LD_LIBRARY_PATH=/opt/buildroot/host/lib
```

或者执行下面命令

```bash
source environment-setup-buildroot
```

创建并切换构建目录

```bash
$ mkdir build
$ cd build
```

指定交叉编译工具链配置进行编译

```bash
$ cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain.linux-aarch64-buildroot.cmake ..
$ make
```

部署到板子上运行

```bash
$ scp hello root@192.168.0.2:/root/
```
