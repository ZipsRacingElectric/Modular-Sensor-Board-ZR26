# Project name
PROJECT = msb_zr26

# Imported files
CHIBIOS  := $(CHIBIOS_SOURCE_PATH)

# Directories
CONFDIR		:= ./config
BUILDDIR	:= ./build
DEPDIR		:= ./build/dep
BOARDDIR	:= ./build/board
COMMONDIR	:= ./common

# Includes
ALLINC += src

# Source files
CSRC = $(ALLCSRC) 							\
	src/main.c 								\
											\
	src/peripherals.c						\
	src/peripherals/eeprom_map.c			\
	src/peripherals/i2c/max11614.c 			\
	src/peripherals/i2c/daughterADC.c		\
											\
	src/can.c								\
	src/can/receive.c						\
	src/can/transmit.c

# Common library includes

include common/src/debug.mk
include common/src/fault_handler.mk

include common/src/peripherals/interface/eeprom.mk
include common/src/peripherals/adc/analog_linear.mk
include common/src/peripherals/adc/thermistor_pulldown.mk
include common/src/peripherals/i2c/mc24lc32.mk

include common/src/can/eeprom_can.mk
include common/src/can/can_thread.mk

# Compiler flags
USE_OPT += -Og -Wall -Wextra

# C macro definitions
UDEFS +=

# ASM definitions
UADEFS +=

# Include directories
UINCDIR +=

# Library directories
ULIBDIR +=

# Libraries
ULIBS += -lm

# Common toolchain includes
include common/common.mk
include common/make/openocd.mk

# ChibiOS compilation hooks
PRE_MAKE_ALL_RULE_HOOK: $(BOARD_FILES) $(CLANGD_FILE)