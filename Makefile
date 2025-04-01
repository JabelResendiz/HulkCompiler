BUILD_DIR = build
SCRIPT = $(BUILD_DIR)/script.hulk

.PHONY: build run clean

build:
	mkdir -p $(BUILD_DIR)
	touch $(SCRIPT)
	echo "Compiling Hulk script..."

run: build
	echo "Running Hulk script..."

clean:
	rm -rf $(BUILD_DIR)
