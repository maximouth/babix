# ############################################################################
# Arduino Makefile for Due board.
# (c) François Pessaux 2015.
# History:
#   29 jan 2015: initial version.
# Credits: was mostly franckenstein-ed from Paul Dreik and olikraus@gmail.com
#          ones, digging in the Arduino devkit directories and googling all
#          over the net ^_^
# Licence: this Makefile can be freely distributed and modified.
# Requirements: an Unix-like environment (works fine on Mac OS).
# Limitations:
#   Only tested with an Arduino Due board.
#   Warning sbrkr.c:(.text._sbrk_r+0xc): warning: undefined reference to `_sbrk'
#	    remains. Does not seems to hurt at me.
# Main targets: compile, upload, monitor, clean (self-explanatory).
# ############################################################################


# **No** "path" variables must have a '/' at the end.
# ***** [User] tag indicates what has to be changed to suit the user's stuff.



# ***** [User]
# Set the installation path for Arduino devkit.
ARDUINO_BASE=/Applications/Arduino.app/Contents/Resources/Java/hardware

# ***** [User]
# Set upload port.
PORT=/dev/tty.usbmodem1451

# ***** [User]
# Set -v if want to verify the upload.
VERIFY_UPLOAD =

# ***** [User]
# Set the board type (refer to the file 'boards.txt').
BOARD=arduino_due_x

# ***** [User]
# Set the directory where to find the 'boards.txt' file describing the boards'
# characteristics.
# ATTENTION: for boards not based on SAM (like Uno and derived), this directory
# may be instead $(ARDUINO_BASE)/arduino/avr.
# And for such boards, using BOSSAC won't work. Using avrude is required
# instead.
SAM_DIR=$(ARDUINO_BASE)/arduino/sam

# ***** [User]
# Set the compiler and tools paths.
GCC=$(ARDUINO_BASE)/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-gcc
GXX=$(ARDUINO_BASE)/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-g++
AR=$(ARDUINO_BASE)/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-ar
OBJCOPY=$(ARDUINO_BASE)/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-objcopy
BOSSAC=$(ARDUINO_BASE)/tools/bossac

# ***** [User]
# Set the project name.
PROJ_NAME=Babix

# ***** [User]
# Set the C source files **EXCEPT** the one with setup () and loop ().
C_SOURCES =

# ***** [User]
# Set the **main** (entry point with setup () and loop ()) source file.
MAIN_SOURCE = Babix.cpp

# ***** [User]
# Set the list of all libaries which should be included.
# EXTRA_DIRS=$(ARDUINO_BASE)/libraries/LiquidCrystal/
# EXTRA_DIRS+=$(ARDUINO_BASE)/libraries/.../

# ***** [User]
# Set the user-defined flags to pass when compiling C/C++ source files.
USER_C_FLAGS = -DDEBUG
USER_CXX_FLAGS = -DDEBUG



# ###########################################################################
# ######################### NOTHING TO CHANGE BELOW #########################
# ########## (unless you really know what you do and what you need) #########
# ###########################################################################
TMPDIR=build

# We will make a new mainfile from the ino file.
NEWMAINFILE=$(TMPDIR)/$(PROJ_NAME).cpp

BOARDS_FILE=$(SAM_DIR)/boards.txt
# Get the MCU value from the $(BOARD).build.mcu variable.
MCU=$(shell sed -n -e "s/$(BOARD).build.mcu=\(.*\)/\1/p" $(BOARDS_FILE))
# Get the F_CPU value from the $(BOARD).build.f_cpu variable.
F_CPU=$(shell sed -n -e "s/$(BOARD).build.f_cpu=\(.*\)/\1/p" $(BOARDS_FILE))
# Get variant subfolder.
VARIANT=$(shell sed -n -e "s/$(BOARD).build.variant=\(.*\)/\1/p" $(BOARDS_FILE))
LDSCRIPT=$(SAM_DIR)/variants/$(VARIANT)/$(shell sed -n -e "s/$(BOARD).build.ldscript=\(.*\)/\1/p" $(BOARDS_FILE))
SYSLIB=$(SAM_DIR)/variants/$(VARIANT)/$(shell sed -n -e "s/$(BOARD).build.variant_system_lib=\(.*\)/\1/p" $(BOARDS_FILE))

# Build C and C++ flags. Include path information must be placed here
COMMON_FLAGS = -DF_CPU=$(F_CPU) -mcpu=$(MCU) $(DEFS) -DARDUINO=152
COMMON_FLAGS += -D__SAM3X8E__ -mthumb -DUSB_PID=0x03e -DUSB_VID=0x2341
COMMON_FLAGS += -DUSBCON
COMMON_FLAGS += -Os -w -ffunction-sections -fdata-sections -Wl,--gc-sections
COMMON_FLAGS += --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf
COMMON_FLAGS += -Wall -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
COMMON_FLAGS += -I.
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/system/libsam
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/system/CMSIS/CMSIS/Include
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/system/CMSIS/Device/ATMEL
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/cores/arduino
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/variants/$(VARIANT)
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/cores/arduino/USB
COMMON_FLAGS += -I$(ARDUINO_BASE)/arduino/sam/cores/arduino/avr
COMMON_FLAGS += $(addprefix -I,$(EXTRA_DIRS))

CFLAGS = $(USER_C_FLAGS) $(COMMON_FLAGS) -std=gnu99 -Wstrict-prototypes
CXXFLAGS = $(USER_CXX_FLAGS) $(COMMON_FLAGS)

SAM_LD_FLAGS = -T $(LDSCRIPT) -Wl,--Map=output.map
SAM_LD_FLAGS += -lm -lgcc -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all
SAM_LD_FLAGS +=-Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols


# These source files are the ones forming core.a
CORESRCXX = $(shell ls ${SAM_DIR}/cores/arduino/*.cpp ${SAM_DIR}/cores/arduino/USB/*.cpp ${SAM_DIR}/variants/${BOARD}/variant.cpp)
CORESRC = $(shell ls ${SAM_DIR}/cores/arduino/*.c)

# Convert the core source files to object files. Assume no clashes.
PRE_COREOBJSXX = $(addprefix $(TMPDIR)/core/,$(notdir $(CORESRCXX)) )
COREOBJSXX = $(addsuffix .o,$(PRE_COREOBJSXX))
PRE_COREOBJS = $(addprefix $(TMPDIR)/core/,$(notdir $(CORESRC)) )
COREOBJS = $(addsuffix .o,$(PRE_COREOBJS))


USER_OBJ_FILES=$(addsuffix .o,$(addprefix $(TMPDIR)/,$(notdir $(C_SOURCES))))
USER_OBJ_FILES+=$(addsuffix .o,$(addprefix $(TMPDIR)/,$(notdir $(MAIN_SOURCE))))

# Empty default rule to force the user to specify what he wants to do.
.PHONY: donothing
donothing:
	@echo "Invoke 'make compile', 'make upload' or 'make clean'."


# Creates a cpp file from the "main" source file to add some wrapping stuff
# to fit the compilation scheme on the board.
$(NEWMAINFILE): $(MAIN_SOURCE) $(TMPDIR)
	cat $(ARDUINO_BASE)/arduino/sam/cores/arduino/main.cpp > $(NEWMAINFILE)
	cat $(MAIN_SOURCE) >> $(NEWMAINFILE)
	echo 'extern "C" void __cxa_pure_virtual() {while (true);}' >> $(NEWMAINFILE)


# Temporary build directory.
$(TMPDIR):
	mkdir -p $(TMPDIR)


# Sub-temporary-directory to get and compile the source files making the core
# library for the board.
$(TMPDIR)/core:
	mkdir -p $(TMPDIR)/core


# Compile core sources depending on where they are.
$(TMPDIR)/core/%.c.o:$(SAM_DIR)/cores/arduino/%.c
	$(GCC) $(CFLAGS) -c $< -o $@
$(TMPDIR)/core/%.cpp.o:$(SAM_DIR)/cores/arduino/%.cpp
	$(GXX) $(CXXFLAGS) -c $< -o $@
$(TMPDIR)/core/%.c.o:$(SAM_DIR)/cores/arduino/USB/%.c
	$(GCC) $(CFLAGS) -c $< -o $@
$(TMPDIR)/core/%.cpp.o:$(SAM_DIR)/cores/arduino/USB/%.cpp
	$(GXX) $(CXXFLAGS) -c $< -o $@
$(TMPDIR)/core/%.c.o:$(SAM_DIR)/variants/$(BOARD)/%.c
	$(GCC) $(CFLAGS) -c $< -o $@
$(TMPDIR)/core/%.cpp.o:$(SAM_DIR)/variants/$(BOARD)/%.cpp
	$(GXX) $(CXXFLAGS) -c $< -o $@


# Compile user sources.
$(TMPDIR)/%.c.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

$(TMPDIR)/%.cpp.o: %.cpp
	$(GXX) $(CXXFLAGS) -c $< -o $@


# Create the core library from the core objects. Do this EXACTLY as the
# arduino IDE does it, seems *really* picky about this.
$(TMPDIR)/core.a: $(TMPDIR)/core $(COREOBJS) $(COREOBJSXX)
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/wiring_shift.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/wiring_analog.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/itoa.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/cortex_handlers.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/hooks.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/wiring.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/WInterrupts.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/syscalls_sam3.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/iar_calls_sam3.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/wiring_digital.c.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/Print.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/USARTClass.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/WString.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/USBCore.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/CDC.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/HID.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/wiring_pulse.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/UARTClass.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/main.cpp.o
# File below seems to have disappeared... Works without.
#	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/cxxabi-compat.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/Stream.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/RingBuffer.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/IPAddress.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/Reset.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/WMath.cpp.o
	$(AR) rcs $(TMPDIR)/core.a $(TMPDIR)/core/variant.cpp.o

# Link our own object files with core to form the elf file.
$(TMPDIR)/$(PROJ_NAME).elf: $(TMPDIR)/core.a $(USER_OBJ_FILES)
	$(GXX) $(COMMON_FLAGS) $(SAM_LD_FLAGS) -Wl,--start-group $(TMPDIR)/core.a $(SYSLIB) $(USER_OBJ_FILES) -Wl,--end-group -o $@


# Build the binary executable file.
$(TMPDIR)/$(PROJ_NAME).bin: $(TMPDIR)/$(PROJ_NAME).elf
	$(OBJCOPY) -O binary $< $@

.PHONY: compile
compile: $(TMPDIR)/$(PROJ_NAME).elf

.PHONY: upload
upload: $(TMPDIR)/$(PROJ_NAME).bin
	stty -f $(PORT) cs8 1200 hupcl
	$(BOSSAC) -U false -e -w $(VERIFY) -b $(TMPDIR)/$(PROJ_NAME).bin -R

# View the serial port with screen.
.PHONY: monitor
monitor:
	stty -f $(PORT) cs8 9600 hupcl
	screen $(PORT) 9600

.PHONY: clean
clean:
	test ! -d $(TMPDIR) || rm -rf $(TMPDIR)
	rm -f output.map $(TMPDIR)/$(PROJ_NAME).elf *~
