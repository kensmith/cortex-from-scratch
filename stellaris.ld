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
        *(.isr_vector_rest0_section)
        . = 0x78;
        *(.isr_vector_rest1_section)
        . = 0xb0;
        *(.isr_vector_rest2_section)
        . = 0xc4;
        *(.isr_vector_rest3_section)
        . = 0xdc;
        *(.isr_vector_rest4_section)
        . = 0xec;
        *(.isr_vector_rest5_section)
        . = 0xf8;
        *(.isr_vector_rest6_section)
        . = 0x124;
        *(.isr_vector_rest7_section)
        . = 0x150;
        *(.isr_vector_rest8_section)
        . = 0x1b0;
        *(.isr_vector_rest9_section)
        . = 0x268;
    } > FLASH
}
