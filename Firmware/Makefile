
CLI       ?= arduino-cli
FQBN      ?= esp32:esp32:esp32
PORT      ?= /dev/ttyACM0

SKETCH    := $(CURDIR)
BUILD_DIR := $(CURDIR)/build

.PHONY: upload

setup: core libs

core:
	$(CLI) core update-index
	$(CLI) core install esp32:esp32

libs:
	$(CLI) lib install "RF24"
	$(CLI) lib install "Adafruit GFX Library"
	$(CLI) lib install "Adafruit SSD1306"
	$(CLI) lib install "Adafruit BusIO"

compile:
	$(CLI) compile \
		--fqbn $(FQBN) \
		--build-path $(BUILD_DIR) \
		$(SKETCH)

upload: compile
	$(CLI) upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--input-dir $(BUILD_DIR) \
		$(SKETCH)

clean:
	rm -rf $(BUILD_DIR)
