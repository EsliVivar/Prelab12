/* 
 * File:  PreLab_12.c
 * Author: Esli Vivar 20286
 *
 * Created on 18 de mayo de 2022
 */
// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000

void setup(void); 

//---------INTERRUPCION----------//
void __interrupt() isr (void){
    if(PIR1bits.ADIF){                          // ADC
        if(ADCON0bits.CHS == 0){                // CANAL: AN0
            PORTC = ADRESH;
        }PIR1bits.ADIF = 0;
    }
    if(INTCONbits.RBIF){
        if (PORTBbits.RB0)
            SLEEP(); 
        INTCONbits.RBIF = 0;} 
    }
//--------CICLO PRINCIPAL--------//
void main(void) {
    setup();
   while(1){
       PORTDbits.RD0 = STATUSbits.nPD;
       if(ADCON0bits.GO == 0){             // No hay proceso de conversion
            ADCON0bits.GO = 1;              // Iniciamos proceso de conversi n?
        } }
     
    return;
    }
    
       

//--------CONFIGURACIONES--------//

   void setup(void){
    ANSEL = 0b00000001; // AN0 como entrada anal gica?
    ANSELH = 0;         // I/O digitales)
    TRISA = 0b00000001; // AN0 como entrada
    PORTA = 0; 
    TRISC = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    
    //PUERTO B
    OPTION_REGbits.nRBPU = 0; 
    WPUB = 0b11;
    IOCB = 0b11;
    
    // Configuraci n reloj interno?
    OSCCONbits.IRCF = 0b0110;   // 4MHz
    OSCCONbits.SCS = 1;         // Oscilador interno
    
    // Configuraci n ADC?
    ADCON0bits.ADCS = 0b01;     // Fosc/8
    ADCON1bits.VCFG0 = 0;       // VDD
    ADCON1bits.VCFG1 = 0;       // VSS
    ADCON0bits.CHS = 0b0000;    // Seleccionamos el AN0
    ADCON1bits.ADFM = 0;        // Justificado a la izquierda
    ADCON0bits.ADON = 1;        // Habilitamos modulo ADC
    __delay_us(40);             // Sample time
    
    // INTERRUPCIONES
    
    PIR1bits.ADIF = 0; 
    PIE1bits.ADIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.PEIE = 1; 
    INTCONbits.RBIF = 0;
    INTCONbits.GIE = 1; 
    
   }