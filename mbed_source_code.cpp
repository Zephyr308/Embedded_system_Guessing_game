/* Name: Syed Zain Hasan
Code for ARM Mbed
*/



#include "mbed.h"
#include "TextLCD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 31
#define SIZE 100
#define NUMS_TO_GENERATE 1

TextLCD lcd(p15, p16, p17, p18, p19, p20); // LCD display

int random_no();
int within(int value, int goal, int n); // Function initialisation
int Scoring(int trials);

Serial pc(USBTX, USBRX); // tx, rx
char str1[] = "Hi host PC!"; // message for the pc terminal
BusOut rows(p26,p25,p24);
BusIn cols(p14,p13,p12,p11);

char Keytable[] = { 'F', 'E', 'D', 'C',
                    '3', '6', '9', 'B',
                    '2', '5', '8', '0',
                    '1', '4', '7', 'A'
                    };
char error_check[] = {'F', 'D', 'C', 'B', 'A'}; // list of invalid input

char getKey(){
    int i,j;
    char ch=' ';
    for (i = 0; i <= 3; i++) {
        rows = i;
        for (j = 0; j <= 3; j++) {
            if (((cols ^ 0x00FF) & (0x0001<<j)) != 0) { // function which recognise keypad presses
                ch = Keytable[(i * 4) + j];
            }
        }
    }
    return ch;
}


// Main code


int main()
{
    int RANDOM_VALUE, check, ret;
    int tally = 0;
    int buffer = 0;
    char strings[2][30] = {"y", "n"};
    int range = 2;

    // Welcoming Message
    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("Welcome to the");
    lcd.locate(0,1);
    lcd.printf("Guessing Game");
    wait(2.0);

    while(1){ // Kept in infinite loop to maintain the serial communication

        char playagain[256] = ""; // user input from PC
        pc.printf("%s", str1);
        pc.gets(playagain, 256);
        ret = strcmp(playagain, strings[0]);

        if(strstr(playagain, strings[0]) != NULL){

            while(ret == 0){ // First while loop keep the game going until user decided not to

                // Generate random number
                RANDOM_VALUE = random_no();
                lcd.cls();
                lcd.locate(0,0);
                lcd.printf("Secret no. ##");

                pc.printf("Please enter a number between 0 to 30\n");
                pc.printf("Please enter you guess, using keypad and press E to enter the value\n");
                pc.printf("Value: ");

                // User input from keypad
                char key1[] = "";
                char key = ' ';
                while(1){
                    key  = getKey();
                    if(key != ' '){
                        if(key == 'E'){
                            break;
                        }
                        for(int i = 0; i < 5; i++){

                            if(key == error_check[i]){
                                pc.printf("\r\nSorry, incorrect input\r\n");
                                break;
                            }
                        }
                        strncat(key1, &key, 1);
                        pc.printf("%s\r\n", key1);
                        wait(0.3);
                    }
                }


                // Data type conversion for user input
                char reference_no[20];
                int input_guess;
                strcpy(reference_no, key1);
                input_guess = atoi(reference_no);

                // Check proximity
                while(input_guess != RANDOM_VALUE){   // Nested while loop will prompt the user to keep guessing until correct guess have been made
                    check = within(input_guess, RANDOM_VALUE, range);

                    if(check == 0){
                        pc.printf("Not close enough");
                        tally++;

                        // User input from keypad
                        char key1[] = "";
                        char key = ' ';
                        while(1){
                            key  = getKey();
                            if(key != ' '){
                                if(key == 'E'){
                                    break;
                                }
                                for(int i = 0; i < 5; i++){

                                    if(key == error_check[i]){
                                        pc.printf("\r\nSorry, incorrect input\r\n");
                                        break;
                                    }
                                }
                                strncat(key1, &key, 1);
                                pc.printf("%s\r\n", key1);
                                wait(0.3);
                            }
                        }
                        // Data type conversion for user input
                        char reference_no[20];
                        strcpy(reference_no, key1);
                        input_guess = atoi(reference_no);
                        continue;
                    }
                    else if(check == 1){
                        pc.printf("Getting close");
                        tally++;

                        // User input from keypad
                        char key1[] = "";
                        char key = ' ';
                        while(1){
                            key  = getKey();
                            if(key != ' '){
                                if(key == 'E'){
                                    break;
                                }
                                for(int i = 0; i < 5; i++){

                                    if(key == error_check[i]){
                                        pc.printf("\r\nSorry, incorrect input\r\n");
                                        break;
                                    }
                                }
                                strncat(key1, &key, 1);
                                pc.printf("%s\r\n", key1);
                                wait(0.3);
                            }
                        }
                        // Data type conversion for user input
                        char reference_no[20];
                        strcpy(reference_no, key1);
                        input_guess = atoi(reference_no);
                        continue;
                    }
                }

                buffer = Scoring(tally); // Calculate the score based on number of trial until user guess correctly
                pc.printf("\r\nCongratulation!\r\n");
                lcd.cls();
                lcd.locate(0,0);
                lcd.printf("Secret no. %d", RANDOM_VALUE);
                lcd.locate(0,1);
                lcd.printf("Score: %d", buffer);

                pc.printf("\r\nWould you like to play (y or n)?\r\n");
                char playagain[256] = ""; // user input from pc
                pc.gets(playagain, 256);
                ret = strcmp(playagain, strings[0]);
                continue;
            }
        }
    }
}




/* Function */

int random_no(){
    int rand_no;
    srand(time(NULL));
    for (int i = 0; i < NUMS_TO_GENERATE; i++){
        rand_no = rand() % MAX;
    }
    return rand_no;
}

int within(int value, int goal, int n){
  int check = goal - value;
  int range;

  if(check > 0)
  {
    range = goal - value;
    if(range > n)
    {
      return 0;
    }
    else if(range < n || range == n)
    {
      return 1;
    }
  }

  else if(check < 0)
  {
    range = value - goal;
    if(range > n)
    {
      return 0;
    }
    else if(range < n || range == n)
    {
      return 1;
    }
  }
}

int Scoring(int trials)
{
    float highest_score = 100;
    float multiplier = 0.01;
    float calculate;
    float no_of_trials = (float)trials;

    calculate = highest_score - highest_score*(no_of_trials*multiplier);
    int final_score = (int)(calculate < 0 ? (calculate - 0.5) : (calculate + 0.5));

    return final_score;
}
