#include <stdio.h>

char nextCharacter(char current) {
    // Definir el alfabeto personalizado
    char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int alphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);

    // Encontrar el índice del carácter actual en el alfabeto
    int currentIndex = 0;
    for (int i = 0; i < alphabetSize; i++) {
        if (alphabet[i] == current) {
            currentIndex = i;
            break;
        }
    }

    // Calcular el índice del siguiente carácter según las reglas
    int nextIndex;
    if (current == 'A') {
        nextIndex = (currentIndex + 1) % alphabetSize;  // Incrementar de A a B
    } else if (current == 'Y') {
        nextIndex = (currentIndex + 1) % alphabetSize;  // Incrementar de Y a Z
    } else if (current == 'Z') {
        nextIndex = 0;                                  // Z + 1 = 0
    } else if (current == '9') {
        nextIndex = (currentIndex + 1) % alphabetSize;  // Incrementar de 9 a A
    } else {
        // Si el carácter no cumple ninguna regla, devolvemos el mismo carácter
        return current;
    }

    // Devolver el siguiente carácter según el índice calculado
    return alphabet[nextIndex];
}

int main() {
    char input = 'A';
    char next = nextCharacter(input);
    printf("Next character after %c: %c\n", input, next);

    input = 'Y';
    next = nextCharacter(input);
    printf("Next character after %c: %c\n", input, next);

    input = 'Z';
    next = nextCharacter(input);
    printf("Next character after %c: %c\n", input, next);

    input = '9';
    next = nextCharacter(input);
    printf("Next character after %c: %c\n", input, next);

    return 0;
}
