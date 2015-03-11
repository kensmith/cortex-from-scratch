#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

void reset_handler(void) __attribute__ ((interrupt ("IRQ")));
void nmi_handler(void) __attribute__ ((interrupt ("IRQ")));
void hard_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void memory_management_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void bus_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void usage_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void sv_call_handler(void) __attribute__ ((interrupt ("IRQ")));

void pend_sv_handler(void) __attribute__ ((interrupt ("IRQ")));
void sys_tick_handler(void) __attribute__ ((interrupt ("IRQ")));
void default_handler(void) __attribute__ ((interrupt ("IRQ")));


__attribute__ ((section(".isr_vector_first_six_section"))) extern void (* const isr_vectors[])();
__attribute__ ((section(".isr_sv_call_section"))) extern void (* const isr_sv_call[])();
__attribute__ ((section(".isr_vector_last_sys_section"))) extern void (* const isr_vector_last_sys[])();
__attribute__ ((section(".isr_vector_rest_section"))) extern void (* const isr_vector_rest[])();

#if defined(__cplusplus)
}
#endif

