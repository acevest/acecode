include $(RTOS_PATH)/make/project.mk

.PHONY: test
test:
	@echo $(COMPONENT_KCONFIGS_PROJBUILD)

define RunConf
    mkdir -p $(BUILD_DIR_BASE)/include/config
    cd $(BUILD_DIR_BASE); KCONFIG_AUTOHEADER=$(abspath $(BUILD_DIR_BASE)/include/sdkconfig.h) \
    COMPONENT_KCONFIGS="$(COMPONENT_KCONFIGS)" KCONFIG_CONFIG=$(SDKCONFIG) \
    COMPONENT_KCONFIGS_PROJBUILD="$(COMPONENT_KCONFIGS_PROJBUILD)" \
    $(KCONFIG_TOOL_DIR)/$1 $(RTOS_PATH)/Kconfig
endef

.PHONY: menuconfig
menuconfig: $(KCONFIG_TOOL_DIR)/mconf $(KCONFIG_TOOL_DIR)/conf
	$(call RunConf,mconf)
	$(call RunConf,conf --silentoldconfig)

