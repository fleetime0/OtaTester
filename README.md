# otatester

## 初始化子模块

如果在拉取仓库的时候，没有`--recurse-submodules`同步拉取子模块，则需要输入一下命令拉取子模块：

```bash
git submodule update --init --recursive
```

## 编译

目前该项目仅在ubuntu18.04进行编译。不过提供了docker，如果有docker环境，可以由docker容器代为编译。

```bash
mkdir build
cmake ..
cmake --build .
cmake --install .
```

### docker编译

```bash
./docker-build.sh
```

## 运行

```bash
cd otatester-output/bin
export VSOMEIP_APPLICATION_NAME='otatester'
export VSOMEIP_CONFIGURATION='../etc/vsomeip.json'
./otaclient
```