#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Postavljanje pinova za LED diodu i brzinu Morseovog koda (brže vrednosti zahtevaju kraće pauze između tačaka i crta)
#define LED_PIN 1 // Ovo je BCM brojčanik (GPIO 18 na Raspberry Pi 3)
#define MORSE_SPEED 500 // Brzina u milisekundama

// Morseova azbuka
const char *morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void translateToMorse(char text[], char morse[]) {
    int i, j;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            strcat(morse, " ");
        } else {
            for (j = 0; j < 36; j++) {
                if (toupper(text[i]) == (char)(j + 65)) {
                    strcat(morse, morseCode[j]);
                    strcat(morse, " ");
                    break;
                }
            }
        }
    }
}

void blinkMorseCode(char morse[]) {
    int i, j;
    for (i = 0; i < strlen(morse); i++) {
        if (morse[i] == '.') {
            digitalWrite(LED_PIN, HIGH);
            delay(MORSE_SPEED);
            digitalWrite(LED_PIN, LOW);
            delay(MORSE_SPEED);
        } else if (morse[i] == '-') {
            digitalWrite(LED_PIN, HIGH);
            delay(3 * MORSE_SPEED);
            digitalWrite(LED_PIN, LOW);
            delay(MORSE_SPEED);
        } else if (morse[i] == ' ') {
            delay(2 * MORSE_SPEED);
        }
    }
}

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("Greška pri postavljanju WiringPi biblioteke.\n");
        return 1;
    }

    pinMode(LED_PIN, OUTPUT);

    char text[256];
    char morse[512] = "";

    printf("Unesite tekst za prevođenje u Morseov kod: ");
    fgets(text, sizeof(text), stdin);

    translateToMorse(text, morse);
    printf("Tekst u Morseovom kodu: %s\n", morse);

    blinkMorseCode(morse);

    return 0;
}
