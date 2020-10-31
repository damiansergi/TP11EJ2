#include <stdio.h>
#include <stdarg.h>

void miPrintf(const char* str, ...); 

int main(void){
    miPrintf("Hola: %d en hexa: %x un caracter: %c ", 2805, 0xFA23, 'C');
}

void miPrintf(const char* str, ...){
    va_list args;
    int i;
    int j;
    int num;
    int base;
    int aux;
    int cantArgs;
    char buffer[256];

    va_start(args, str);

    for(j = 0; str[j] != '\0'; j++){
        if(str[j] != '%'){
            putchar(str[j]);
        }
        else{
            cantArgs++;
            j++;
            switch(str[j]){
                case 'd':
                    cantArgs++;
                    num = va_arg(args, int);
                    base = 10;
                    for(i = 0; num != 0; i++){
                        buffer[i] = (num % base) + '0';
                        num /= base;
                    }
                    for( i; i >= 0; i--){
                        putchar(buffer[i]);
                    }
                    break;
                case 'x':
                    cantArgs++;
                    num = va_arg(args, int);
                    base = 16;
                    for(i = 0; num != 0; i++){
                        aux = num % base;
                        buffer[i] = (aux < 10) ? (aux + '0') : (aux + 'A' - 10);
                        num /= base;
                    }
                    for( i; i >= 0; i--){
                        putchar(buffer[i]);
                    }
                    break;
                case 'c':
                    putchar((char) va_arg(args, int));
                    break;
            }
        }
    }
    va_end(args);
}
