// CONFIG1H
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))
// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)
// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)
// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)
// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)
// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)
// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)
// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)
// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#define _XTAL_FREQ 4000000
#include <xc.h>

void setup_Ports();


void main(void) 
{
    setup_Ports();      // Llamamos funcion setup_Ports.

    unsigned char A ,B ,C , D, PB, SALIDA, AUX1, AUX2;  // Declaramos Variables.
    A = B = C = D = PB = SALIDA= AUX1 = AUX2 = 0;         // Iniciamos variables en 0.

    LATD    =   SALIDA;

    while(1)
    {
        PB  =   PORTB;          //  Guardamos datos de PORTB en una variable auxiliar.
        A   =   PB  >>  4;      //  Guardamos en variable A el valor de PB desplazado en 4 posiciones a la derecha.
        B   =   PB  &   0x0F;   //  Guardamos B valor de 4 bits de menor peso de PB.
        S   =   PORTA & 0x0F;   //  En S guardamos los 4 bits de menor peso de A.

        switch (S)
        {
            case 0000:      // CASO 0
                SALIDA  =   A   +   B;
                break;

            case 0001:      // CASO 1
                SALIDA  =   A   -   B;
                if (SALIDA  <   0)
                {
                    SALIDA  =   0;
                }
                break;

            case 0010:      // CASO 2
                SALIDA  =   A   *   B;
                break;

            case 0011:      // CASO 3
                SALIDA  =   A   /   B;
                break;

            case 0100:      // CASO 4
                SALIDA  =   A   &   B;
                break;

            case 0101:      // CASO 5   OR
                SALIDA  =   A   |   B;
                break;

            case 0110:      // CASO 6   XOR
                SALIDA  =   A   ^   B;
                break;

            case 0111:      // CASO 7   NAND
                SALIDA  =   A   &   B;
                SALIDA  =   ~SALIDA;
                break;

            case 1000:      // CASO 8   NOR
                SALIDA  =   A   |   B;
                SALIDA  =   ~SALIDA;
                break;

            case 1001:      // CASO 9   XNOR
                SALIDA  =   A   ^   B;
                SALIDA  =   ~SALIDA;
                break;
            
            case 1010:      // CASO 10
                AUX1    =   PB    <<  7;
                AUX2    =   PB    >>  1;
                SALIDA  =   AUX1  |   AUX2;
                break;

            case 1011:      // CASO 11
                SALIDA  =   PB  >>  5;
                break;

            case 1100:      //CASO 12
                SALIDA  =   A   -   B;
                if (SALIDA < 0)
                {
                    //LLAMAR ULTIMO BIT PUERTO D    =   1;
                }
                else()
                {
                    SALIDA;
                }
                break;

            case 1101:      // CASO 13  
                SALIDA  =   A   *   B;
                if (SALIDA>99)
                {
                    SALIDA  =   0;
                }
                break;

            case 1110:      // CASO 14  261,63 Hz DO 4 OCTAVA
                //  PONER EN 1 SALIDA HACIA SPEAKER
                __delay_ms(1.911095822);
                //  PONER EN 0 SALIDA HACIA SPEAKER
                __delay_ms(1.911095822);
                break;

            case 1111:      // CASO 15  349,2282 (1.431728595) o 369,9944  (0.0013513718)
                //  PONER EN 1 SALIDA HACIA SPEAKER
                __delay_ms(1.431728595);
                //  PONER EN 0 SALIDA HACIA SPEAKER
                __delay_ms(1.431728595);
                break;

            default:
                break;
        }
    }
}

void setup_Ports(void)  // Función que configura pines de entrada y salida de PIC18F452.
{
    TRISB   =   0xFF;     // Configuramos Puerto B de ENTRADA
    LATB    =   0;        // Limpiamos puerto LATB
    PORTB   =   0;        // Limpiamos puerto PORTB

    TRISA   =   0xFF;     // Configuramos puerto A como ENTRADA
    LATA    =   0;        // Limpiamos puerto LATA
    PORTA   =   0;        // Limpiamos puerto PORTA
    ADCON1  =   0x06;     // Definimos puerto A como Digital

    TRISD   =   0x00;     // Configuramos puerto D como SALIDA
    LATD    =   0;        // Limpiamos puerto LATD
    PORTD   =   0;        // Limpiamos puerto PORTD
}
