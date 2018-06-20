include project.mk


.PHONY: test
COMPONENT_PATHS := $(foreach comp,$(COMPONENTS),$(firstword $(foreach cd,$(COMPONENT_DIRS),$(wildcard $(dir $(cd))$(comp) $(cd)/$(comp)))))
test:
	@echo $(fuck)
	@echo $(COMPONENT_PATHS)
	@echo $(wildcard $(RTOS_PATH))
	@echo $(realpath $(wildcard $(RTOS_PATH)))
	@echo $(COMPONENTS)
	@echo $(COMPONENT_DIRS)
	@echo $(foreach cd,$(COMPONENT_DIRS), $(wildcard $(cd)/*/component.mk))

define RunConf
    mkdir -p $(BUILD_DIR_BASE)/include/config
    cd $(BUILD_DIR_BASE); KCONFIG_AUTOHEADER=$(abspath $(BUILD_DIR_BASE)/include/sdkconfig.h) \
    COMPONENT_KCONFIGS="$(COMPONENT_KCONFIGS)" KCONFIG_CONFIG=$(SDKCONFIG) \
    COMPONENT_KCONFIGS_PROJBUILD="$(COMPONENT_KCONFIGS_PROJBUILD)" \
    $(KCONFIG_TOOL_DIR)/$1 $(RTOS_PATH)/Kconfig
endef

menuconfig: $(KCONFIG_TOOL_DIR)/mconf
	$(call RunConf,mconf)
