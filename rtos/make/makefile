include project.mk


.PHONY: test
test:
	echo $(OS)
	@echo $(wildcard $(RTOS_PATH))
	@echo $(realpath $(wildcard $(RTOS_PATH)))
	@echo $(COMPONENTS)
	@echo $(COMPONENT_DIRS)
	@echo $(foreach cd,$(COMPONENT_DIRS), $(wildcard $(cd)/*/component.mk))

