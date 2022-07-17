.PHONY: clean All

All:
	@echo "----------Building project:[ Vector_Processor - Debug ]----------"
	@cd "Vector_Processor" && "$(MAKE)" -f  "Vector_Processor.mk"
clean:
	@echo "----------Cleaning project:[ Vector_Processor - Debug ]----------"
	@cd "Vector_Processor" && "$(MAKE)" -f  "Vector_Processor.mk" clean
