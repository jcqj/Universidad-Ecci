//..................librerias......................................................................................
#include <xc.h>
#include <stdio.h>

//....................conf_fusibles................................................................................
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

#define _XTAL_FREQ	4000000		// Definición del valor del cristal
#define EN RC5
#define RS RC4
#define bus LATD

//..............variables globales y prototipos de funcion.........................................................
unsigned char buffer[40];
unsigned char A=0;
unsigned int x=0;
unsigned int num=0;

void setup_Ports_In_Out(void);
void setup_AnalogDigitalConverter(void);

void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);  
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);

unsigned int Conversor_ADC(unsigned char canal);

void conf_PWM(void);
void duty_1(unsigned char dc);

//..............codigo principal................................................................
void main(void) 
{    
    //.........................conf perifericos.................................................
    setup_Ports_In_Out();
    setup_AnalogDigitalConverter();
    conf_PWM();
    //.........................bucle.............................................................
    while(1)
    {
        ini_LCD();
        while (1)
        {
            __delay_ms(500);
            ins_LCD(1);
            num++;
            write_LCD(sprintf(buffer,"LCD OKI DOKI",num));
        }
    }
}

//......................funciones............................................................
void setup_Ports_In_Out(void)
{
    TRISB=0xFF;         // puerto B de entrada
    LATB=0;             // limpiar puerto B
    PORTB=0;            // limpiar puerto B
    
    TRISD=0x00;         // puerto D de salida
    LATD=0;             // limpia puerto D
    PORTD=0;            // limpia puerto D
    
    TRISC=0x00;         // puerto C de salida
    LATC=0;             // limpia puerto C
    PORTC=0;            // limpia puerto C
    
    // TRISE=0x07;
    // LATE=0;
    // PORTE=0;
}
void setup_AnalogDigitalConverter(void)
{
    ADCON0      =       0b00000001;
    ADCON1      =       0;
}

unsigned int Conversor_ADC(unsigned char canal)
{
    unsigned int temp=0;
    if(canal>7)
    {
        return 0;
    }
    else
    {
        canal   =    canal  << 3;
        ADCON0  =    ADCON0 &  0xC7;
        ADCON0  =    ADCON0 |  canal;
        __delay_us(50);
        GO=1;
        while(GO==1);
        ADRESL  =    ADRESL >>  6;
        temp    =    ADRESH;
        temp    =   temp    <<  2;
        temp    =   temp    |   ADRESL;

        return temp;
    }
}

//      INICIANDO_LCD
void ini_LCD (void)
{
	__delay_ms(20);     // delay 20 ms
	bus=0x30;			// VALOR DE INICIALIZACION
	enable();

	__delay_ms(5);		// delay 5 ms
	bus=0x30;			// VALOR DE INICIALIZACION
	enable();

	__delay_ms(1);		// delay 1 ms
	bus=0x30;			// VALOR DE INICIALIZACION
	enable();

	bus=0b00111000;	// Function set 8 bits - 2 lineas - 5*8
	enable();

	bus=0b00001000;	// display off
	enable();

	bus=0b00000001;	// display clear
	enable();

	bus=0b00000110;	// entry mode set - incrementa la posicion del cursor
	enable();

	bus=0b00001110;	// display on/off control - LCD on - cursor on - blink off
	enable();
}

//      ENABLE_LCD
void enable (void)
{
	EN=1;	// enable en alto
	__delay_ms(1);
	EN=0;	// enable en bajo
}

//      DATO_LCD
void dato_LCD(unsigned char dato)
{
	RS=1;	//RS en 1 (envia dato)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(2);		//tiempo de ejecucion
}

//      INSTRUCCION_LCD_(CRUD)
void ins_LCD(unsigned char dato)
{
	RS=0;	//RS en 0 (envia instruccion)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(2);		//tiempo de ejecucion
}

//      ESCRIBIR_EN_LCD
void write_LCD(unsigned char tam)
{
    unsigned char i;
    for(i=0;i<tam;i++)
    {
        dato_LCD(buffer[i]);
    }
}

//      CONFIGURACION_PWM
void conf_PWM(void)
{
    PR2=124;
    CCPR1L=0;
    T2CON=0b00000101;
    CCP1CON=0b00001100;
}

//      DUTY_CICLE_1
void duty_1(unsigned char dc)
{
    unsigned int lamda=0;
    lamda=dc;
    lamda*=5;
    CCPR1L=lamda>>2;
    lamda<<=4;
    lamda&=0x30;
    CCP1CON&=0xCF;
    CCP1CON|=lamda;
}