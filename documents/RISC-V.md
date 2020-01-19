# RISC-V

## Bumblebee的中断

### 1. CSR `mtvec`的功能

Bumblebe内核遵循的标准 RISC-V 特权架构文档版本为:“特权架构文档版本 1.10” (riscv-privileged-v1.10.pdf)，在这个版本中关于`mtvec`的变更是这样表述的: 
>"Optional vectored interrupt support has been added to the mtvec and stvec CSRs."

也就是说支持`pc=BASE+4*CAUSE`的向量跳转的中断方式是可选的，而Bumblebee就恰好没有实现这个功能。

### 2. CSR `mtvec`的MODE部分

在riscv-privileged-v1.10.pdf文档中，`mtvec`MODE的合法值为:

|Value|Name|Description|
|:-:|:-:|:--|
|0|Direct|All exceptions set pc to BASE.|
|1|Vectored|Asynchronous interrupts set pc to BASE+4×cause.|
|&ge;2| -| Reserved |

但是Bumblebe的文档里却说：

1. `mtvec.MODE != 6'b000011`则采用“默认中断模式”
2. `mtvec.MODE == 6'b000011`则采用“ECLIC 中断模式”

这里有两个问题：

1. RISC-V官方文档里MODE只有2个bit, Bumblebe却占6个bit
2. RISC-V官方文档里MODE有效取值只有1、2，但是Bumblebe却能取到3

所以这是直接的违反RISC-V的定义？

### 3. `mtvt`、`mtvt2`、`mtvec`

相对于标准文档，Bumblebe添加了`mtvt`、`mtvt2`两个CSR。

`mtvt` 存放中断向量表起始地址

`mtvt2` 存放非向量(矢量)中断**共享**入口地址，这里有两点

 1. `mtvt2`的最低位`mtvt2.MTVT2EN == 0`，则所有非向量中断共享的入口地址由CSR寄存器`mtvec`的值(忽略最低2位的值)指定
 2. `mtvt2`的最低位`mtvt2.MTVT2EN == 1`，则所有非向量中断共享的入口地址由CSR寄存器`mtvt2`的值(忽略最低2位的值)指定

**注:**

**向量中断模式** *指各个中断直接跳到各个中断的入口地址，由`mtvt`指定*

**非向量中断模式** *指各个中断共享同一个入口地址，由`mtvt2`指定*

每个中断源均可以设置成向量或者非向量处理(通过寄存器`clicintattr[i].shv`)。


*疑问：如果`mtvt2.MTVT2EN==0` 且在clicintattr[i]中配置成向量中断，就与riscv-privileged-v1.10.pdf中的"vectored interrupt"基本等价？只是一个是从`mtvt`中取出基址，一个是从`mtvec`中取出基址？*