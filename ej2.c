#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "ej2.h"


static void print_entero(int numero);
static void print_hexa(unsigned int numero);

int main (void){	//DE PRUEBA

	mi_printf("Viva Peron %c\n%c\n%c\n", 'S', 'I', 'i');
	
	mi_printf("De desayuno, como %d %d %d %c\n", 123456, -444, 678, 'P');
	
	mi_printf("mila mila milanessssssa %x %c %x %c %x\n", 15, 'A', 15, 'A', 65535);

	return 0;
}

void mi_printf(char* string, ...){

	va_list parametros;
	
	va_start(parametros, string);
	
	char * p2string = string;
	
	while( (*p2string) != '\0'){
	
		if(*p2string == '%'){
		
			if( *(p2string+1) == 'd' ){
			
				print_entero( va_arg(parametros, int) );
				p2string +=2;
			}
			else if( *(p2string+1) == 'x' ){
			
				print_hexa( va_arg(parametros, int) );
				p2string +=2;
			}
			else if( *(p2string+1) == 'c' ){
			
				putchar( va_arg(parametros, int) );
				p2string += 2;
			}
		}
		else{
			
			putchar(*p2string);
			p2string++;
		}
	}
	
	va_end(parametros);
}		

static void print_entero(int numero){

	if (numero <0){
		
		putchar('-');
		numero = -numero;
	}

	int cifras = 1;
	int aux = numero;
	
	while( (aux/10) != 0 ){
	
		aux/=10;
		cifras++;
	}

	aux = 0;
	
	while(--cifras != -1){
		
		putchar( ((numero / (int) pow(10,cifras) ) - aux*10) + '0' );
		
		aux = numero / ( (int) pow(10,cifras));
	}
}

static void print_hexa(unsigned int numero){

	int hexchar[ MAX_HEX_CHARS ] = {0};
	int i = 0;
	
	while( (numero/16) != 0 ){
		
		hexchar[i] = numero%16;
		numero/=16;
		i++;
	}
	
	hexchar[i] = numero;

	for (;i>=0;i--){
	
		numero = hexchar[i];
		putchar( hexaCharConvertidor(numero) );
	}
}
