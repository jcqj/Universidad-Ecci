//--------------------------    LIBRERIAS
#include <xc.h>

//--------------------------    CONFIGURACIÓN FUSIBLES
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

#define _XTAL_FREQ	4000000		// Definición del valor del cristal

//--------------------------    VARIABLES GLOBALES
unsigned char A=0;

//--------------------------    PROTOTIPO FUNCIONES
void conf_puertos(void);

//--------------------------    FUNCION PRINCIPAL | RUTINA PRINCIPAL
void main(void)
{
    //--------------------------    CONFIGURACIÓN PERIFERICOS
    conf_puertos();

 }

//--------------------------    FUNCIONES
void conf_puertos(void)
{
    TRISB=0xFF;         // puerto B de entrada
    LATB=0;             // limpiar puerto B
    PORTB=0;            // limpiar puerto B
    
    TRISD=0x00;         // puerto D de salida
    LATD=0;             // limpia puerto D
    PORTD=0;            // limpia puerto D
}