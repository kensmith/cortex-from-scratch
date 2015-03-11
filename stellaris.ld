MEMORY
{
    FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x40000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000
}

ENTRY(reset_handler)

SECTIONS
{
    __ram_top = ORIGIN(SRAM) + LENGTH(SRAM);
    __initial_sp = __ram_top - 16;
    . = ALIGN(4);
    .text :
    {
        . = 0x0;
        LONG(__initial_sp);
        *(.isr_vector_first_six_section)
        . = 0x2c;
        *(.isr_sv_call_section)
        . = 0x38;
        *(.isr_vector_last_sys_section)
        . = 0x40;
        *(.isr_vector_rest_section)
        . = 0x208;
    } > FLASH
}
