HOSTCC := gcc
HOSTCXX := g++
HOSTLD	:= ld
HOSTAR	:= ar
HOSTOBJCOPY := objcopy
HOSTSIZE := size

CONFIG_TOOLPREFIX := "xtensa-esp32-elf-"
CC := $(call dequote,$(CONFIG_TOOLPREFIX))gcc
CXX := $(call dequote,$(CONFIG_TOOLPREFIX))c++
LD := $(call dequote,$(CONFIG_TOOLPREFIX))ld
AR := $(call dequote,$(CONFIG_TOOLPREFIX))ar
OBJCOPY := $(call dequote,$(CONFIG_TOOLPREFIX))objcopy
SIZE := $(call dequote,$(CONFIG_TOOLPREFIX))size
export CC CXX LD AR OBJCOPY SIZE

.PHONY: all_binaries
all: all_binaries

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
export COMPONENT_DIRS := $(RTOS_PATH)/components $(PROJECT_PATH)/components $(PROJECT_PATH)/main
endif

#ifndef COMPONENTS
COMPONENTS := $(dir $(foreach cd,$(COMPONENT_DIRS),	\
					$(wildcard $(cd)/*/component.mk) $(wildcard $(cd)/component.mk)))

COMPONENTS := $(sort $(foreach comp,$(COMPONENTS),$(lastword $(subst /, ,$(comp)))))
export COMPONENTS
#endif

COMPONENT_PATHS := $(foreach comp,$(COMPONENTS),$(firstword $(foreach cd,$(COMPONENT_DIRS),$(wildcard $(dir $(cd))$(comp) $(cd)/$(comp)))))
COMPONENT_KCONFIGS := $(foreach component,$(COMPONENT_PATHS),$(wildcard $(component)/Kconfig))
    # COMPONENT_KCONFIGS_PROJBUILD 会在$(RTOS_PATH)/Kconfig里用到
COMPONENT_KCONFIGS_PROJBUILD := $(foreach component,$(COMPONENT_PATHS),$(wildcard $(component)/Kconfig.projbuild))

SDKCONFIG ?= $(PROJECT_PATH)/sdkconfig
KCONFIG_TOOL_DIR=$(RTOS_PATH)/tools/kconfig

COMMON_MAKEFILES := $(abspath $(RTOS_PATH)/make/project.mk $(firstword $(MAKEFILE_LIST)))
export COMMON_MAKEFILES

COMPONENT_INCLUDES :=
COMPONENT_LDFLAGS :=
COMPONENT_SUBMODULES :=
COMPONENT_LIBRARIES :=
COMPONENT_PROJECT_VARS := $(addsuffix /component_project_vars.mk,$(notdir $(COMPONENT_PATHS) ))
COMPONENT_PROJECT_VARS := $(addprefix $(BUILD_DIR_BASE)/,$(COMPONENT_PROJECT_VARS))
# this line is -include instead of include to prevent a spurious error message on make 3.81
-include $(COMPONENT_PROJECT_VARS)


# Workaround to run make parallel (-j). mconf and conf cannot be made simultaneously
$(KCONFIG_TOOL_DIR)/mconf: $(KCONFIG_TOOL_DIR)/conf

# reset MAKEFLAGS as the menuconfig makefile uses implicit compile rules
$(KCONFIG_TOOL_DIR)/mconf $(KCONFIG_TOOL_DIR)/conf: $(wildcard $(KCONFIG_TOOL_DIR)/*.c)
	MAKEFLAGS="" CC=$(HOSTCC) LD=$(HOSTLD) \
	$(MAKE) -C $(KCONFIG_TOOL_DIR)


APP_ELF:=$(BUILD_DIR_BASE)/$(PROJECT_NAME).elf
APP_MAP:=$(APP_ELF:.elf=.map)
APP_BIN:=$(APP_ELF:.elf=.bin)

all_binaries: $(APP_BIN) $(COMPONENT_PROJECT_VARS)



$(APP_BIN): $(APP_ELF)
	cp $(APP_ELF) $(APP_BIN)


$(APP_ELF):


define RunConf
    mkdir -p $(BUILD_DIR_BASE)/include/config
    cd $(BUILD_DIR_BASE); KCONFIG_AUTOHEADER=$(abspath $(BUILD_DIR_BASE)/include/sdkconfig.h) \
    COMPONENT_KCONFIGS="$(COMPONENT_KCONFIGS)" KCONFIG_CONFIG=$(SDKCONFIG) \
    COMPONENT_KCONFIGS_PROJBUILD="$(COMPONENT_KCONFIGS_PROJBUILD)" \
    $(KCONFIG_TOOL_DIR)/$(1) $(RTOS_PATH)/Kconfig
endef

.PHONY: menuconfig
menuconfig: $(KCONFIG_TOOL_DIR)/mconf $(KCONFIG_TOOL_DIR)/conf
	$(call RunConf,mconf)
	$(call RunConf,conf --silentoldconfig)



# Macro for the recursive sub-make for each component
# $(1) - component directory
# $(2) - component name only
#
# Is recursively expanded by the GenerateComponentTargets macro
define ComponentMake
+$(MAKE) -C $(BUILD_DIR_BASE)/$(2) -f $(RTOS_PATH)/make/component_wrapper.mk COMPONENT_MAKEFILE=$(1)/component.mk COMPONENT_NAME=$(2)
endef

# Generate top-level component-specific targets for each component
# $(1) - path to component dir
# $(2) - name of component
#
define GenerateComponentTargets
.PHONY: component-$(2)-build component-$(2)-clean

component-$(2)-build: check-submodules $(call prereq_if_explicit, component-$(2)-clean) | $(BUILD_DIR_BASE)/$(2)
	$(call ComponentMake,$(1),$(2)) build

component-$(2)-clean: | $(BUILD_DIR_BASE)/$(2) $(BUILD_DIR_BASE)/$(2)/component_project_vars.mk
	$(call ComponentMake,$(1),$(2)) clean


$(BUILD_DIR_BASE)/$(2):
	@mkdir -p $(BUILD_DIR_BASE)/$(2)

$(BUILD_DIR_BASE)/$(2)/lib$(2).a: component-$(2)-build
	$(details) "Target '$$^' responsible for '$$@'" # echo which build target built this file

$(BUILD_DIR_BASE)/$(2)/component_project_vars.mk: $(1)/component.mk $(COMMON_MAKEFILES) $(SDKCONFIG_MAKEFILE) | $(BUILD_DIR_BASE)/$(2)
	$(call ComponentMake,$(1),$(2)) component_project_vars.mk
endef
$(foreach component,$(COMPONENT_PATHS),$(eval $(call GenerateComponentTargets,$(component),$(notdir $(component)))))
