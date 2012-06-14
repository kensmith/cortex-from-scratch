MEMORY
{
    FLASH (rx) : ORIGIN = 0x0 LENGTH = 0x40000
    SRAM (rwx) : ORIGIN = 0x10000000 LENGTH = 0x8000
    AHBRAM0 : ORIGIN = 0x2007C000 LENGTH = 0x4000
    AHBRAM1 : ORIGIN = 0x20080000 LENGTH = 0x4000
}

ENTRY(reset_handler)

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text*)
        *(.rodata*)
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __end_of_flash = .;
    } > FLASH

    .bss :
    {
        __bss_start = .;
        *(.bss*)
        __bss_end = .;
    } > SRAM

    .data : AT (__end_of_flash)
    {
        __data_start = .;
        *(vtable)
        *(.data*)
        __data_end = .;
    } > SRAM

    __heap_start = .;
    __ram_top = ORIGIN(SRAM) + LENGTH(SRAM);
    __stack_top = __ram_top - 16;
}
