
    # ?= 的意思是如果没有赋值过则赋值?=后面的值
OS ?=

    # ifeq 的意思是判断是否相等
ifeq ("$(OS)", "Windows_NT")
$(error "Unsupport build platform")
else
    # wildcard 展开通配符
    # realpath 对于名称中的每个文件名返回规范绝对名称。规范名称不包含任何.或..成分，也没有任何重复的路径分隔符（/）或符号链接
export RTOS_PATH := $(realpath $(wildcard $(RTOS_PATH)))
endif

ifndef RTOS_PATH
$(error "RTOS_PATH not define")
endif

ifndef PROJECT_PATH
    # MAKEFILE_LIST 列出make用到的所有文件
    # firstword 取第一个单词
    # dir 求路径
    # abspath 求绝对路径
    # export定义一个变量、下级makefile可以访问, export VAR := 'var' <==> VAR := 'var' 和 export VAR 两条命令
PROJECT_PATH := $(abspath $(dir $(firstword $(MAKEFILE_LIST))))
export PROJECT_PATH
else
$(error "PROJECT_PATH was polluted")
endif

ifndef BUILD_DIR_BASE
export BUILD_DIR_BASE := $(PROJECT_PATH)/build
endif

ifndef COMPONENT_DIRS
export COMPONENT_DIRS := $(PROJECT_PATH)/components $(RTOS_PATH)/components $(PROJECT_PATH)/main
endif

#ifndef COMPONENTS
COMPONENTS := $(dir $(foreach cd,$(COMPONENT_DIRS),	\
					$(wildcard $(cd)/*/component.mk) $(wildcard $(cd)/component.mk)))

export COMPONENTS
#endif
