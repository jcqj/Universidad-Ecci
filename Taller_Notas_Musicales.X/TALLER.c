//..................librerias......................................................................................
#include <xc.h>
#include <stdio.h>

//....................conf_fusibles................................................................................
#pragma config OSC  = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON         // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR  = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT  = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP  = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

#define _XTAL_FREQ 4000000
#define EN RE2
#define RS RE0
#define bus LATD
//..............variables globales y prototipos de funcion.........................................................

unsigned char buffer[40];

void conf_puertos(void);
void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);  
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);

//..............codigo principal................................................................

void main(void)
{
    //************************* CONFIGURACIÓN PERIFERICOS *************************
    conf_puertos();
    ini_LCD(); //inicializa la LCD

    //************************* MENSAJE DE BIENVENIDA *************************
    write_LCD(sprintf(buffer," ACA VA MENSAJE DE BIENVENIDA  "));
    ins_LCD(192);
    write_LCD(sprintf(buffer," ACÁ TAMBIÉN PUEDE IR EL MENSAJE "));
    __delay_ms(2000);
    ins_LCD(1);


    while (1)
    {
        if (RB0     ==     0)// DO   CUARTA OCTAVA 
        {
            write_LCD(sprintf(buffer,"do de 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"261.63 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do{
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.911095822);
                RA2=0;
                __delay_ms(1.911095822);
            }while (RB0==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1);// BORRA PANTALLA
        }

        else if (RB1==0)// RE   CUARTA OCTAVA 
        {
            write_LCD(sprintf(buffer,"re de 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"293.66 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.702649322);
                RA2=0;
                __delay_ms(1.702649322);
            }while (RB1==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1);  
        }

        else if (RB2==0)// MI   CUARTA OCTAVA 329.63 HZ
        {
            write_LCD(sprintf(buffer,"mi de 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"329.63 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.516852228);
                RA2=0;
                __delay_ms(1.516852228);
            }while (RB2==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1); 
        }

        else if (RB3==0)// FA   CUARTA OCTAVA 349.23 HZ
        {
            write_LCD(sprintf(buffer,"fa de 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"349.23 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.431721215);
                RA2=0;
                __delay_ms(1.431721215);
            }while (RB3==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1); 
        }

        else if (RB4==0)// SOL  CUARTA OCTAVA 392.00 HZ
        {
            write_LCD(sprintf(buffer,"sol de 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"392.00 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.275510204);
                RA2=0;
                __delay_ms(1.275510204);
            }while (RB4==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1); 
        }

        else if (RB5==0)//LA   CUARTA OCTAVA 440.00 HZ
        {
            write_LCD(sprintf(buffer,"la 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"440.00 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.136363636);
                RA2=0;
                __delay_ms(1.136363636);
            }while (RB5==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1); 
        }

        else if (RB6==0)// SI   CUARTA OCTAVA 
        {
            write_LCD(sprintf(buffer,"si de 4 octava"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"493.88 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(1.012391674);
                RA2=0;
                __delay_ms(1.012391674);
            }while (RB6==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1); 
        }

        else if (RB7==0)// DO   QUINTA OCTAVA 523.25 HZ
        {
            write_LCD(sprintf(buffer,"DO 5 OCTAVA"));// IMPRIME MENSAJE
            ins_LCD(192);// SE MUEVE A SEGUNDO RENGLON
            write_LCD(sprintf(buffer,"523.25 Hz"));// IMPRIME FRECUENCIA A REPRODUCIR

            do
            {
                RA2=1;// ENVIA UN ALTO AL SPEAKER.
                __delay_ms(0.955566173);
                RA2=0;
                __delay_ms(0.955566173);
            }while (RB7==0);// SIEMPRE QUE ESTE PULSADO HARÁ LO DEL BUCLE
            ins_LCD(1);
        }
        
        else
        {
            write_LCD(sprintf(buffer, "SIGUE TOCANDO"));
            ins_LCD(1);
        }
    }
}

//......................funciones............................................................

void conf_puertos(void)
{
    RBPU    = 0;        //PUERTO B COMO PULL UP

    TRISD   = 0x00;     // puerto D de salida
    LATD    = 0;        // limpia puerto D
    PORTD   = 0;        // limpia puerto D

    TRISA   = 0x00;     // puerto A de salida
    LATA    = 0;        // limpia puerto A
    PORTA   = 0;        // limpia puerto A

    TRISE   = 0x00;     // puerto E de salida
    LATE    = 0x00;     // Limpia puerto 
    PORTE   = 0x00;     // Limpia puerto
    ADCON1  = 0x06;     //Puerto E digital
}

//...................ini_LCD....................................
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

//...................enable....................................
void enable (void)
{
	EN=1;	// enable en alto
	__delay_ms(1);
	EN=0;	// enable en bajo
}

//...................dato....................................
void dato_LCD(unsigned char dato)
{
	RS=1;	//RS en 1 (envia dato)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(1);		//tiempo de ejecucion
}

//...................instruccion..................................
void ins_LCD(unsigned char dato)
{
	RS=0;	//RS en 0 (envia instruccion)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(1);		//tiempo de ejecucion
}

void write_LCD(unsigned char tam){
    
    unsigned char i;
    
    for(i=0;i<tam;i++){
        dato_LCD(buffer[i]);
    }
}