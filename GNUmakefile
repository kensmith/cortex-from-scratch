opt := -g -Og

linker-script := stellaris.ld

srcs := \
    $(wildcard *.cpp) \
    $(wildcard *.c) \

src-suffixes := \
    .c \
    .cpp \
    .s

objs := $(srcs)
$(foreach suffix,$(src-suffixes), \
  $(eval \
    objs := $$(patsubst %$(suffix),%.o,$(objs)) \
   ) \
 )
header-deps := $(objs:.o=.d)
secondary-processed := $(filter-out boot.%,$(objs))
preprocs := $(secondary-processed:.o=.E)
genassms := $(secondary-processed:.o=.S)

output-suffixes := .elf .bin .xxd .S .symtab

.PHONY: app flash clean gdb
app: \
    $(addprefix app,$(output-suffixes)) \
    $(preprocs) \
    $(genassms)
flash: app; ./flash.py app.bin
clean:; rm -f $(sort $(strip \
    *.d \
    *.o \
    *.E \
    *.S \
    app.*))

gdb:;\
    arm-none-eabi-gdb

app.symtab \
    : app.elf \
    ; arm-none-eabi-readelf -s app.elf > $@

app.S \
    : app.elf \
    ; arm-none-eabi-objdump -S app.elf > $@

app.xxd \
    : app.bin \
    ; xxd $< > $@

app.bin \
    : app.elf \
    ; arm-none-eabi-objcopy $< -O binary $@

app.elf \
    : $(objs) \
    ; $(strip arm-none-eabi-g++ \
      -mthumb \
      -mno-thumb-interwork \
      -nostartfiles \
      -std=c++11 \
      -mcpu=cortex-m3 \
      -fno-rtti \
      -fno-exceptions \
      $(objs) \
      -Xlinker -M -Xlinker -Map=app.map \
      -T $(linker-script) \
      -o $@)

common-deps := $(strip \
    $(MAKEFILE_LIST) \
    $(linker-script))

assembler-flags := $(strip \
    -mthumb \
    -mno-thumb-interwork \
    -nostartfiles \
    -std=c++11 \
    -mcpu=cortex-m3 \
    -fno-rtti \
    -fno-exceptions)

compiler-flags = $(strip \
    $(if $(filter ARM%,$@), \
      $(comment building ARM), \
     ) \
    $(assembler-flags) \
    $(opt) \
    -I . \
    -MMD \
    -Ifreetype-2.4.8/include \
    -Wall \
    -Wextra \
    -Wmissing-declarations  \
    -Wno-strict-aliasing  \
    -D FT2_BUILD_LIBRARY)

c-compiler-flags = \
    $(compiler-flags) \
    -std=gnu99 \
    -Wmissing-prototypes

c++-compiler-flags = \
    $(compiler-flags) \
    -std=c++11


%.o \
    : %.s $(common-deps) \
    ; arm-none-eabi-gcc $(assembler-flags) $< -c -o $@


%.o \
    : %.c $(common-deps) \
    ; arm-none-eabi-gcc $(c-compiler-flags) $< -c -o $@
%.E \
    : %.c $(common-deps) \
    ; arm-none-eabi-gcc $(c-compiler-flags) $< -E -o $@
%.S \
    : %.c $(common-deps) \
    ; arm-none-eabi-gcc $(c-compiler-flags) $< -S -o $@


%.o \
    : %.cpp $(common-deps) \
    ; arm-none-eabi-g++ $(c++-compiler-flags) $< -c -o $@
%.E \
    : %.cpp $(common-deps) \
    ; arm-none-eabi-g++ $(c++-compiler-flags) $< -E -o $@
%.S \
    : %.cpp $(common-deps) \
    ; arm-none-eabi-g++ $(c++-compiler-flags) $< -S -o $@

-include $(header-deps)
