#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char character_set[36] = "abcdefghijklmnopqrstuvwxyz0123456789";

void inverse_authentication(int pic_length);
void authenticate(int pic_length);


int find_in_set(char c) {
    for (int i = 0; i < 36; i++) {
        if (character_set[i] == c) {
            return i;
        }
    }

    return 0;
}

void authenticate(int pic_length) {
  
    int plaintext[6];
    int index;
    char input_container[12];
    char PIN_container[7];

    // encoding of the plaintext to be encrypted with your PIC_length (offsec)
    // the encoding is referred to the alphabet shown above
    plaintext[0] = 0xe;   // o
    plaintext[1] = 5;     // f
    plaintext[2] = 5;     // f
    plaintext[3] = 0x12;  // s
    plaintext[4] = 4;     // e
    plaintext[5] = 2;     // c
    
    
    // get your own secret PIN
    printf("Enter Secret 6 Character Code:\n");
    scanf("%s", input_container);

    printf("\nSupplied secret is: *****\n");
   
    index = 0;
    do {
        PIN_container[index] = input_container[index];
        index = index + 1;
    } while (index != 6);
    PIN_container[6] = '\0';

    // encrypt 
    for (int i = 0; i < 6; i++) {
        char new_character = character_set[(plaintext[i] + pic_length) % 0x1a];
        if (new_character != PIN_container[i]) {
            return;
        }
    }

    printf("Great job, well done! The flag is: %s\n", PIN_container);
    return;    

    
}

void inverse_authentication(int pic_length) {
    int plaintext[6];
    int index;
    char PIN_container[7];

    // encoding of the plaintext to be encrypted with your PIC_length (offsec)
    // the encoding is referred to the alphabet shown above
    plaintext[0] = 0xe;   // o
    plaintext[1] = 5;     // f
    plaintext[2] = 5;     // f
    plaintext[3] = 0x12;  // s
    plaintext[4] = 4;     // e
    plaintext[5] = 2;     // c

    // encrypt
    for (int i = 0; i < 6; i++) {
        char new_character = character_set[(plaintext[i] + pic_length) % 0x1a];
        PIN_container[i] = new_character;
    }
    PIN_container[6] = '\0';

    printf("Your secret code is: %s\n", PIN_container);
}


void main(int argc, char** argv) {

    printf("\nUsage: %s option\n\nOptions:\n- crack : is used to discover what is the right secret\n- authenticate (default) : is used to validate your secret\n\n", argv[0]);


    char character_in_PIC;
    int index;
    int PIC_length;
    char PIC_container[4];
    char input_container[12];

    printf("Enter Personal Identification Code: ");
    scanf("%s", input_container);

    printf("Your PIC is: %s\n", input_container);
   
    index = 0;
    do {
        PIC_container[index] = input_container[index];
        index = index + 1;
    } while (index != 4);

    PIC_length = 0;
    for (index = 0; index < 4; index++) {
        character_in_PIC = PIC_container[index];
        int int_value_of_character = -0x30 + (int)character_in_PIC;
        PIC_length = (PIC_length + int_value_of_character) % 0x1a;
    }

    printf("\nThe key for the Caesar Cipher (the rotation) is the sum of the digits in your PIC: %d\n", PIC_length);

    if (argc > 1) {
        if (strcmp(argv[1],"crack") == 0) {
            inverse_authentication(PIC_length);
        } else {
            authenticate(PIC_length);
        }
    } else {
        authenticate(PIC_length);
    }

 
}



