# 如何将TencentOS tiny移植到RISC-V

## 背景

在2019年8月份，腾讯面向物联网领域开发的实时操作系统TencentOS tiny开始向公司内部员工开放限量内测，最初看到这个公告便火速提交了申请，当时并不是对这个内核有什么好奇，而是作为开发板爱好者，单纯地想薅一块免费的开发板来玩玩。当然内测也是有条件的，需要做一个简单的项目，写写报告，最好给开发同学提提建议和修修BUG，于是就有了我之前写的一篇文章《在中移动标准板上利用TencentOS tiny实现GPS追踪功能》。

在完成这个程序的同时也偶尔给内核提提BUG，加点驱动。后来内核开发组的同事说要不你玩的时候顺便支持一下RISC-V吧，于是内核代码就有了RISC-V相关的部分。

初次尝试移植必然要走很多弯路，写这文章的主要目的并不是要记录我是怎么掉坑和爬坑的经历，而是经过自己的整理，以一条自认为最简单和清晰的移植路径来阐述移植过程，希望能对移植其它芯片或对这部分有兴趣的同学有点帮助。

现在TencentOS tiny内核代码已经正式开源，地址:`https://github.com/Tencent/TencentOS-tiny`。

阅读这这篇文章需要你有比较扎实的C和汇编的功底和RISC-V相关的知识。

RISC-V相关的大家可以到`https://github.com/riscv/riscv-isa-manual/releases`下载《riscv-spec.pdf》和《riscv-privileged.pdf》两个PDF文件了解相关信息。另再从《RISC-V架构与嵌入式开发快速入门》这本书中拣选些信息就足够了。


## 开发环境准备

其实需要准备的工具很简单

1. 下载最新的qemu的最新版本4.1.0的代码

```
wget https://download.qemu.org/qemu-4.1.0.tar.xz
tar xvJf qemu-4.1.0.tar.xz
cd qemu-4.1.0
./configure --target-list=riscv32-softmmu
make
make install
```

2. 安装`riscv-none-gcc`

	下载地址`https://github.com/gnu-mcu-eclipse/riscv-none-gcc/releases`
	
	加入环境变量，以v8.2.0-2.2 20190521版本为例
	
	假设解压到`$HOME`目录下，则`export PATH=$PATH:$HOME/riscv-none-gcc/8.2.0-2.2-20190521-0004/bin`
	

## 开发环境验证

在开始前我们先写个小程序验证一下环境，把开发环境各个环节打通。

首先我们编写个简单到极致的程序

```
// start.S
.global _start
.section .text
.align 2
_start:
	nop
	nop
	nop
```

然后我们写个链接脚本

```
/*link.lds*/
OUTPUT_ARCH( "riscv" )
ENTRY( _start )

SECTIONS
{
	. = 0x800000000;
	.text : {
  		*(.text);
	}
}
```
编写一个简单的调试器脚本

```
# gdbscript
file kernel.elf
target remote :1234
b _start
c
```

编译链接程序

```
riscv-none-embed-gcc start.S -T link.lds  -nostdlib -o kernel.elf
```

用虚拟机启动这个最简单的内核

```
qemu-system-riscv32  -machine spike -kernel kernel.elf -S -s
```

然后用gdb连接到qemu

```
riscv-none-embed-gdb -x gdbscript
```

如果你在gdb中看到如下输出，并在执行n后有nop，那就说明整个环境没有问题了。

```
Breakpoint 1 at 0x80000000: file start.S, line 5.

Breakpoint 1, _start () at start.S:5
5		nop
(gdb) n
6		nop
(gdb)
7		nop
```


## 移植准备

TencentOS tiny 的代码目录树如下

```
TencentOS_tiny
├── arch
├── board
├── components
├── devices
├── doc
├── examples
├── kernel
├── net
├── osal
├── platform
├── test
└── tools
```

目前的移植过程中只需要保留`kernel`目录下的代码，还有`arch`, `board`两个目录，其它的都可以暂时删掉。