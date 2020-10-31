
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#define NUMTOCHAR(n) ((n > 9) ? (n + '7') : (n + '0'))    //macro para convertir un numero entre 0 y 16 a hexadecimal
#define BASE10 10                                         //Constante de la base 10
#define BASE16 16                                         //Constante de la base 16

//Recibe un string y n-parametros. Imprime el string con los valores pasados por parametros leyendo los especificadores del texto.
void mi_printf(char* texto, ...);

//Calcula el modulo de num
int mod(int num);

//Convierte un numero en la base indicada a string, funciona para base10 y base16
int toString(unsigned int num, char* buffer, int i, int base);

//2147483647 max positivo signado
//-2147483648 max negativo signado
//4294967295 max positivo no signado

int main()
{
    mi_printf("Es %x + %d = %x? No %c%c%c, flasheastes %d %g %x", 4294967295, -2147483648, 2147483647, 'b', 'r', 'o', 2147483647, 175);

    return 0;
}

/*
 * mi_printf: La funcion recibe por parametros un string para imprimir con especificadores numeros enteros signados (%d),
 * numeros hexadecimales no signados(%x) y caracteres (%c) de la misma forma que hace la funcion printf de la libreria standard.
 * Ademas del string, se deben pasar los n-parametros correspondientes a los n especificadores validos para mostrar cada parametro
 * ingresado en la posicion del especificador. La funcion espera que existan la misma cantidad de especificadores validos que de parametros
 * pasados a la funcion.
 */
void mi_printf(char* texto, ...){
    
    char nextChar;      
    char stringNum[10];
    char numSize;
    signed int snum;
    unsigned int unum;
    int i = 0;

    //Creamos y cargamos el puntero a la lista de argumentos variables
    va_list listaParam;
    va_start(listaParam, texto);
    
   
    while(texto[i] != '\0'){    //Mientras no se haya recorrido todo el string
        
        nextChar = texto[i++];  //Leemos el siguiente caracter y avanzamos el indice al siguiente 
        
        if(nextChar == '%'){    //Si el caracter leido es un %
            
            nextChar = texto[i++];  //Leemos el tipo de variable del especificador
            
            switch(nextChar){
                case 'd':   
                    
                    snum = va_arg(listaParam, int);                         //Leemos la siguiente variable de la lista
                    numSize = toString(mod(snum), stringNum, 0, BASE10);    //Pasamos el numero leido a string y lo almacenamos en stringNum
                    
                    if(snum < 0){       //Si el numero ingresado es negativo
                        putchar('-');   //Imprimimos un signo menos (-) 
                    }
                    for(int j = numSize-1; j >= 0; j--){  //Imprimimos el numero en pantalla
                        putchar(stringNum[j]);  
                    }
                    break;
                    
                case 'x':
                
                    unum = va_arg(listaParam, int);                         //Leemos la siguiente variable de la lista
                    numSize = toString(unum, stringNum, 0, BASE16);         //Pasamos el numero leido a string y lo almacenamos en stringNum
                    
                    for(int j = numSize-1; j >= 0; j--){                    //Imprimimos el numero en pantalla
                        putchar(stringNum[j]);
                    }
                    break;
                    
                case 'c':
                    
                    nextChar = va_arg(listaParam, int);                     //Leemos la siguiente variable de la lista
                    putchar(nextChar);                                      //Imprimimos el caracter
                    break;
                    
                default:
                    
                    putchar('%');
                    putchar(nextChar);  //Si no es un especificador valido, lo imprimimos literal
                    break;
            }      
        }
        else{
            putchar(nextChar);  //Si no es un %, imprimimos el caracter
        }
    }
}

/*
 * toString: La funcion recibe por parametros, un numero a convertir a string sin el terminador, un buffer para almacenar
 * el string resultante, un indice para almacenar los elementos y un entero que indica la base a la cual se quiere
 * convertir el numero. Devuelve el largo de la cadena obtenida.
 */
int toString(unsigned int num, char* buffer, int i, int base){
    if(num < base){
        buffer[i++] = NUMTOCHAR(num%base);
        return i;
    }
    else{
        buffer[i++] = NUMTOCHAR(num%base);
        return toString(num/base, buffer, i, base);
    }
}

/*
 * La funcion recibe un entero, realiza la funcion modulo y devuelve el numero obtenido.
 */
int mod(int num){
    if(num < 0){
        num = -num;
    }
    return num;
}