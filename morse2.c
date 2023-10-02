#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

#define LED_PIN 0  // Pretpostavimo da je LED povezan na pin 0

char* toMorse(char c) {
    switch (c) {
        case 'a': return ".-";    case 'b': return "-..."; case 'c': return "-.-.";
        case 'd': return "-..";   case 'e': return ".";    case 'f': return "..-.";
        case 'g': return "--.";   case 'h': return "...."; case 'i': return "..";
        case 'j': return ".---";  case 'k': return "-.-";  case 'l': return ".-..";
        case 'm': return "--";    case 'n': return "-.";   case 'o': return "---";
        case 'p': return ".--.";  case 'q': return "--.-"; case 'r': return ".-.";
        case 's': return "...";   case 't': return "-";    case 'u': return "..-";
        case 'v': return "...-";  case 'w': return ".--";  case 'x': return "-..-";
        case 'y': return "-.--";  case 'z': return "--..";
        case '0': return "-----"; case '1': return ".----"; case '2': return "..---";
        case '3': return "...--"; case '4': return "....-"; case '5': return ".....";
        case '6': return "-...."; case '7': return "--..."; case '8': return "---..";
        case '9': return "----.";
        default: return "";
    }
}

void signalMorse(char* morse) {
    for (int i = 0; morse[i] != '\0'; ++i) {
        if (morse[i] == '.') {
            digitalWrite(LED_PIN, HIGH);
            delay(100);
            digitalWrite(LED_PIN, LOW);
        } else if (morse[i] == '-') {
            digitalWrite(LED_PIN, HIGH);
            delay(300);
            digitalWrite(LED_PIN, LOW);
        }
        delay(100);  // Pauza između signala
    }
}

int main() {
    wiringPiSetup();
    pinMode(LED_PIN, OUTPUT);

    char text[100];
    printf("Unesite tekst: ");
    fgets(text, 100, stdin);

    for (int i = 0; text[i] != '\0'; ++i) {
        char* morse = toMorse(text[i]);
        signalMorse(morse);
        delay(300);  // Pauza između slova
    }

    return 0;
}
