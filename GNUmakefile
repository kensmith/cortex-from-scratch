opt := -g

linker-script := lpc-1766-stk.ld

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
preprocs := $(if $(preproc),$(secondary-processed:.o=.E))
genassms := $(if $(genassm),$(secondary-processed:.o=.S))

output-suffixes := .elf .bin .xxd

.PHONY: app flash clean
app: \
    $(addprefix app,$(output-suffixes)) \
    $(preprocs) \
    $(genassms)
flash: app; ./flash.py app.elf
clean:; rm -f $(sort $(strip \
    *.d \
    *.o \
    *.E \
    *.S \
    app.elf \
    app.bin \
    app.map \
    app.xxd))

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
      -nostartfiles \
      -std=gnu++0x \
      -mfpu=vfp \
      -mcpu=cortex-m3 \
      -march=armv7-m \
      -msoft-float \
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
    -msoft-float \
    -mfpu=vfp \
    -mcpu=cortex-m3 \
    -march=armv7-m)

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
    -std=gnu++0x


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
