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
CSRC =	$(ALLCSRC)		\
		src/main.c		\
		src/modular_sensor_board.c \
		src/peripherals/peripherals.c \
		common/src/peripherals/i2c/mc24lc32.c \
		src/peripherals/i2c/max11614.c \
		src/peripherals/can/msb_can.c \
		src/peripherals/i2c/daughterADC.c \
		src/peripherals/eeprom_map.c


# Common library includes
include common/src/debug.mk
include common/src/fault_handler.mk

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
ULIBS +=

# Common toolchain includes
include common/common.mk
include common/make/openocd.mk

# ChibiOS compilation hooks
PRE_MAKE_ALL_RULE_HOOK: $(BOARD_FILES) $(CLANGD_FILE)