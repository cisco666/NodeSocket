#include<18F4550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV2,VREGEN
#use delay(clock=20000000)
#include <Flex_lcdheader.c>
#include <usb_cdc.h>

int16 lectura, grados;

void reader()
{
   set_adc_channel(0);
   lectura=read_adc();
   grados=(lectura*2);
   lcd_gotoxy(1,1);
   printf(LCD_PUTC,"\fTEMP = %Lu",grados);
   printf(usb_cdc_putc,"\f%Lu\r",grados);
}

void main()
{
   lcd_init();
   usb_init(); 
   usb_cdc_init();
   set_tris_a(0xff);
   set_tris_b(0x00);
   setup_adc_ports(AN0_ANALOG);
   setup_adc(adc_clock_internal);
   
   while(true)
   {
      usb_task();//habilita periferico usb e interrupciones
      while(!usb_cdc_connected()){}
      if (usb_enumerated())
      {
         reader();
         delay_ms(1000);
      }     
   }
}
