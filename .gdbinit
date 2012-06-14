target remote localhost:3333
symbol-file app.elf
monitor poll on

define syms
    symbol-file app.elf
end

define flash
    #monitor soft_reset_halt
    monitor reset halt
    monitor flash write_image app.elf
    symbol-file app.elf
    monitor reset halt
end

define reboot
    monitor reset halt
    continue
end

define flashboot
    monitor at91sam7 gpnvm 2 set
end

document flash
flash: write app.elf and reset the processor
end
