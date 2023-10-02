#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUTTON_PIN 17
#define LED_PIN 18

const char *morse_code[] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.", "....", "..",   ".---",
    "-.-",  ".-..", "--",   "-.",   "---", ".--.", "--.-", ".-.",  "...",  "-",
    "..-",  "...-", ".--",  "-..-", "-.--", "--..", ".----", "..---", "...--", "....-",
    ".....", "-....", "--...", "---..", "----.", "-----"
};

void blinkMorse(const char *code) {
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '.') {
            digitalWrite(LED_PIN, HIGH);
            delay(200);
            digitalWrite(LED_PIN, LOW);
            delay(200);
        } else if (code[i] == '-') {
            digitalWrite(LED_PIN, HIGH);
            delay(600);
            digitalWrite(LED_PIN, LOW);
            delay(200);
        } else {
            delay(400);
        }
    }
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("Greška pri inicijalizaciji WiringPi biblioteke.\n");
        return 1;
    }

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    while (1) {
        if (digitalRead(BUTTON_PIN) == LOW) {
            printf("Unesite tekst za Morseov kod: ");
            char input[256];
            scanf("%s", input);
            for (int i = 0; i < strlen(input); i++) {
                char letter = input[i];
                if (letter >= 'a' && letter <= 'z') {
					letter -= 'a' - 'A'; // Pretvaranje malog u veliko slovo
				}
				if (letter >= 'A' && letter <= 'Z') {
                    const char *code = morse_code[letter - 'A'];
					blinkMorse(code);
                } else if (letter >= '0' && letter <= '9') {
                    const char *code = morse_code[26 + letter - '0'];
                    blinkMorse(code);
                } else {
                    printf("Nepoznati znak: %c\n", letter);
                }
                delay(400); // Pauza između znakova
            }
        }
    }

    return 0;
}
