# 长者社区管理系统
NEU软院 程序设计课大作业


## 编译安装

### 从源码编译

- Linux
1. 安装cmake与GNU make
2. 在项目目录下执行`cmake . -DCMAKE_BUILD_TYPE=Release`, 然后执行`make`, 编译后会生成可执行文件`ecms`

- Windows
1. 安装cmake与Mingw, 并添加环境变量
2. 在项目目录下执行`cmake . -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"`, 然后执行`mingw32-make`, 编译后会生成可执行文件`ecms.exe`
(注意: Windows下请使用UTF-8编码, 否则可能1出现中文乱码问题)

### 从Releases下载预编译版本

- Linux : ecms-linux-64.zip
- Windows : ecms-windows-64.zip (中文使用GBK编码编译)


## 使用方法

- 运行程序

  使用`-f`选项来指定输入文件路径, 如不指定, 则会在当前目录下生成相关文件
  ```
  ecms -f [FILE 1] [FILE 2] ...
  ```
- 使用`-h`选项打印帮助文档
  ```
  ecms -h
  ```
- 使用`-v`选项查看当前版本信息
  ```
  ecms -v
  ```

