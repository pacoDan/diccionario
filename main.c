#include <stdio.h>
#include <string.h>

char alfabeto[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
int base = sizeof(alfabeto) / sizeof(alfabeto[0]);
    char num1[]="000";
    char num2[]="001";

int sumar(char numero1, char numero2, int acarreo);

int obtenerPosicion(char numeroCaracter);

int main() {
    int _cantidadDeDigitos=3;
    char resultado[]="000";
    puts("Holas");
    int acarreo=0;
    for (int i = _cantidadDeDigitos-1; i >=0 ; --i)
    {
        int pos=i;
        int suma_numero=sumar(num1[pos],num2[pos],acarreo);
//        printf("probando Nº %d",pos);puts("");
        if(suma_numero<base)resultado[pos]=alfabeto[suma_numero];
        else{
            acarreo=1;
            int _res=suma_numero%base;
            resultado[pos]=alfabeto[_res];
        }
        printf("iteracion numero : %d \n",i);
    }
    
    printf("base -> %d\n",base);
    printf("resultado -> %s\n",resultado);
    puts("FIN");
    return 0;
}

int sumar(char numero1, char numero2, int acarreo) {
    int pos1=obtenerPosicion(numero1);
    int pos2=obtenerPosicion(numero2);
    int _suma=pos1+pos2+acarreo;
    return _suma;
}

int obtenerPosicion(char numeroCaracter) {
    for (int i = 0; i < base; ++i) {
        if (alfabeto[i] == numeroCaracter) {
            return i;
        }
    }
    perror("obtenerPosicion()");
    return -1; // hara que haya errores, pero de alguna forma debo manejar ese error
}
