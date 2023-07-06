#include <stdio.h>
#include <string.h>

char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int alphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);

int getIndex(char character) {
    for (int i = 0; i < alphabetSize; i++) {
        if (alphabet[i] == character) {
            return i;
        }
    }
    return -1;  // Carácter no encontrado en el alfabeto
}

char getNextCharacter(char character) {
    int currentIndex = getIndex(character);
    if (currentIndex == -1) {
        return character;  // Carácter no encontrado, no se puede incrementar
    }

    int nextIndex = (currentIndex + 1) % alphabetSize;
    return alphabet[nextIndex];
}

void incrementString(char *string) {
    int length = strlen(string);
    int carry = 1;

    for (int i = length - 1; i >= 0; i--) {
        if (carry == 0) {
            break;
        }

        char current = string[i];
        char next = getNextCharacter(current);

        // Actualizar el carácter actual
        string[i] = next;

        // Si el carácter actual no cambió, es un desbordamiento
        if (next != current) {
            carry = 0;
        }
    }

    if (carry == 1) {
        // Desbordamiento
        int newSize = length + 2;
        char newString[newSize];
        newString[0] = alphabet[0];
        strncpy(newString + 1, string, length + 1);
        newString[newSize - 1] = '\0';
        printf("Overflow occurred! New string: %s\n", newString);
        strcpy(string, newString);
    }
}

int main() {
    char input[] = "ASaDqEz";
    printf("Current: %s\n", input);
    incrementString(input);
    printf("Next: %s\n", input);

    char input2[] = "AA";
    printf("Current: %s\n", input2);
    incrementString(input2);
    printf("Next: %s\n", input2);

    return 0;
}
