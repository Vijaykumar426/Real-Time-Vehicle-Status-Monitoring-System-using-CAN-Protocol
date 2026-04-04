/**
 * @file interrupt.h
 * @brief External interrupt initialisation and ISR declarations.
 *
 * Configures EINT0 (left indicator button) and EINT2 (right indicator button)
 * as falling-edge-triggered vectored IRQs through the LPC21xx VIC.
 */

/* Initialise EINT0 and EINT2: pin select, VIC vectors, edge mode */
void init_ext_interrupt(void);

/* ISR for EINT0 — toggles left indicator state and sends CAN frame */
void eint0_isr(void) __irq;

/* ISR for EINT2 — toggles right indicator state and sends CAN frame */
void eint2_isr(void) __irq;
