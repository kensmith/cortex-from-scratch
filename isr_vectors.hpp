#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

void reset_handler() __attribute__ ((interrupt ("IRQ")));
void nmi_handler() __attribute__ ((interrupt ("IRQ")));
void hard_fault_handler() __attribute__ ((interrupt ("IRQ")));
void memory_management_fault_handler() __attribute__ ((interrupt ("IRQ")));
void bus_fault_handler() __attribute__ ((interrupt ("IRQ")));
void usage_fault_handler() __attribute__ ((interrupt ("IRQ")));
void sv_call_handler() __attribute__ ((interrupt ("IRQ")));

void pend_sv_handler() __attribute__ ((interrupt ("IRQ")));
void sys_tick_handler() __attribute__ ((interrupt ("IRQ")));
void default_handler() __attribute__ ((interrupt ("IRQ")));


__attribute__ ((section(".isr_vector_first_six_section"))) extern void (* const isr_vectors[])();
__attribute__ ((section(".isr_sv_call_section"))) extern void (* const isr_sv_call[])();
__attribute__ ((section(".isr_vector_last_sys_section"))) extern void (* const isr_vector_last_sys[])();
__attribute__ ((section(".isr_vector_rest0_section"))) extern void (* const isr_vector_rest0[])();
__attribute__ ((section(".isr_vector_rest1_section"))) extern void (* const isr_vector_rest1[])();
__attribute__ ((section(".isr_vector_rest2_section"))) extern void (* const isr_vector_rest2[])();
__attribute__ ((section(".isr_vector_rest3_section"))) extern void (* const isr_vector_rest3[])();
__attribute__ ((section(".isr_vector_rest4_section"))) extern void (* const isr_vector_rest4[])();
__attribute__ ((section(".isr_vector_rest5_section"))) extern void (* const isr_vector_rest5[])();
__attribute__ ((section(".isr_vector_rest6_section"))) extern void (* const isr_vector_rest6[])();
__attribute__ ((section(".isr_vector_rest7_section"))) extern void (* const isr_vector_rest7[])();
__attribute__ ((section(".isr_vector_rest8_section"))) extern void (* const isr_vector_rest8[])();
__attribute__ ((section(".isr_vector_rest9_section"))) extern void (* const isr_vector_rest9[])();

#if defined(__cplusplus)
}
#endif

