target remote localhost:3333
symbol-file app.elf
monitor poll on
monitor reset 
monitor wait 500
monitor soft_reset_halt

define hook-step
    mon cortex_m3 maskisr on
end
define hookpost-step
    mon cortex_m3 maskisr off
end

define syms
    symbol-file app.elf
end

define flash
    #monitor soft_reset_halt
    #monitor reset init
    #monitor halt
    monitor reset halt
    #monitor adapter_khz 600
    #monitor flash write_image app.elf
    monitor flash write_image erase unlock app.bin 0x0 bin
    #monitor flash write_image app.bin 0x0 bin
    monitor verify_image app.bin 0x0 bin
    symbol-file app.elf
    monitor reset init
    #monitor adapter_khz 600
end

define reboot
    monitor reset init
    continue
end
