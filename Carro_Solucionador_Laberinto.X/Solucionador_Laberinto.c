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
#define EN RC3      // Pin 18
#define RS RC0      // Pin 15
#define bus LATD
#define M1IN1 RB4   // Pin 37
#define M1IN2 RB5   // Pin 38
#define M2IN3 RB6   // Pin 39
#define M2IN4 RB7   // Pin 40

#define Umbral 682  // Definimos umbral de sensores.

//..............variables globales y prototipos de funcion.........................................................
//      VARIABLES PARA LCD
unsigned char buffer[40];
float voltaje = 0;

//      DECLARACIÓN VARIABLES DE LECTURA DE SENSORES
int valor = 0b11111111;
int aux ;
int s[7];

//      FUNCIÓN CONFIGURACIÓN PUERTOS DE ENTRADA Y SALIDA
void setup_Ports_In_Out(void);

//      FUNCIONES FUNCIONAMIENTO LCD
void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);  
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);

//      FUNCIONES CONVERSOR ANALOGO - DIGITAL
void setup_AnalogDigitalConverter(void);
unsigned int Conversor_ADC(unsigned char canal);

//      FUNCIONES PWM
void conf_PWM(void);
void duty_1(unsigned char dc);
void duty_2(unsigned char dc);

//      FUNCION PRUEBA ********************************************
unsigned char Read_Sensor(void);
void Seguidor_Linea(unsigned char sensores);

//      FUNCIONES MARCHA
void Left(void);
void Right(void);
void Go(void);
void Reverse(void);
void Stop(void);

//-----------------------       INICIO FUNCIÓN | RUTINA PRINCIPAL
void main(void)
{
    //      CONFIGURAMOS PINES DE ENTRADA Y SALIDA, CONVERSOR AD Y PWM.
    setup_Ports_In_Out();
    setup_AnalogDigitalConverter();
    conf_PWM();
    ini_LCD();

    // ins_LCD(128);
    // write_LCD(sprintf(buffer, " Solucionador de"));
    // ins_LCD(192);
    // write_LCD(sprintf(buffer, "   LABERINTO"));
    // __delay_ms(2000);

    duty_1(30);
    duty_2(70);
    ins_LCD(1);

    while(1)
    {
        // Read_Sensor();


        Left();
        __delay_ms(1000);
        Stop();
        __delay_ms(1000);

        Right();
        __delay_ms(1000);

        Stop();
        __delay_ms(1000);

        Go();
        __delay_ms(1000);

        Stop();
        __delay_ms(1000);

        Reverse();
        __delay_ms(1000);

        Stop();
        __delay_ms(1000);

    }
}
//-----------------------       FIN RUTINA PRINCIPAL

//-----------------------       DECLARACIÓN FUNCIONES
void setup_Ports_In_Out(void)
{
    TRISB   =   0x00;           // puerto B de salida
    LATB    =   0;              // limpiar puerto B
    PORTB   =   0;              // limpiar puerto B
    
    TRISD   =   0x00;           // puerto D de salida
    LATD    =   0;              // limpia puerto D
    PORTD   =   0;              // limpia puerto D
    
    TRISC   =   0x00;           // puerto C de salida
    LATC    =   0;              // limpia puerto C
    PORTC   =   0;              // limpia puerto C
    
    TRISE   =   0x07;
    LATE    =   0;
    PORTE   =   0;
}
void setup_AnalogDigitalConverter(void)
{
    ADCON0  =   0b00000001;
    ADCON1  =   0;
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
        ADRESL  =   ADRESL >>  6;
        temp    =   ADRESH;
        temp    =   temp   <<  2;
        temp    =   temp   |   ADRESL;

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
    CCPR2L=0;
    T2CON=0b00000101;
    CCP1CON=0b00001100;
    CCP2CON=0b00001100;
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

//      DUTY_CICLE_2
void duty_2(unsigned char dc)
{
    unsigned int lamda=0;
    lamda=dc;
    lamda*=5;
    CCPR2L=lamda>>2;
    lamda<<=4;
    lamda&=0x30;
    CCP2CON&=0xCF;
    CCP2CON|=lamda;
}


//      FUNCION PRUEBA  **********************
unsigned char Read_Sensor(void)
{
    unsigned char lectura = 0, i = 0;
    unsigned int resultadoADC = 0;

    ins_LCD(128);
    for ( i = 0; i < 8; i++)
    {
        resultadoADC = Conversor_ADC(7-i);
        if ( resultadoADC < Umbral )
        {
            lectura |= 1;
            dato_LCD('1');
        }
        else
        {
            dato_LCD('0');
        }
        if ( i != 7)
        {
            lectura <<= 1;
        }
    }
    return lectura;
}

void Seguidor_Linea(unsigned char sensores)
{
    switch (sensores)
    {
        case 0b00011000:
            duty_1(60);
            duty_2(60);
            break;
        case 0b00001100:
            duty_1(65);
            duty_2(55);
            break;
        case 0b00000110:
            duty_1(70);
            duty_2(50);
            break;
        case 0b00000011:
            duty_1(75);
            duty_2(30);
            break;
        case 0b00000001:
            duty_1(75);
            duty_2(0);
            break;

        case 0b00110000:
            duty_1(55);
            duty_2(65);
            break;
        case 0b01100000:
            duty_1(50);
            duty_2(70);
            break;
        case 0b11000000:
            duty_1(30);
            duty_2(75);
            break;
        case 0b10000000:
        duty_1(0);
        duty_2(75);
        break;

        default:
            break;
    }
}



//      FUNCIONES MARCHA
void Left(void)
{
    ins_LCD(192);
    write_LCD(sprintf(buffer, "   LEFT  " ));
    M2IN3  =  0;       //  Out 3 en 0
    M2IN4  =  1;       //  Out 4 en 1
}

void Stop(void)
{
    ins_LCD(192);
    write_LCD(sprintf(buffer, "   STOP  "));
    M1IN1  =  0;       //  Out 1 en 1
    M1IN2  =  0;       //  Out 2 en 0
    M2IN3  =  0;       //  Out 3 en 0
    M2IN4  =  0;       //  Out 4 en 0
}

void Right(void)
{
    ins_LCD(192);
    write_LCD(sprintf(buffer, "  RIGHT  "));
    M1IN1  =  1;       //  Out 1 en 1
    M1IN2  =  0;       //  Out 2 en 0
}

void Go(void)
{
    ins_LCD(192);
    write_LCD(sprintf(buffer, "    RUN  "));
    Left();
    Right();
}

void Reverse(void)
{
    ins_LCD(193);
    write_LCD(sprintf(buffer, "REVERSE "));
    M1IN1  =  0;       //  Out 1 en 0
    M1IN2  =  1;       //  Out 2 en 1
    M2IN3  =  1;       //  Out 3 en 1
    M2IN4  =  0;       //  Out 4 en 0
}




