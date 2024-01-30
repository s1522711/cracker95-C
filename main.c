#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG false // enable debug mode

enum menuChoice { CD=1, OEM, VERIF, EXIT}; // menu choices

int randr(int min, int max);
void genCdKey();
void genOemKey();
void verifKey();

int main()
{
    srand(time(NULL)); // seed random number generator
    enum menuChoice menuCh = CD;
    while (menuCh != EXIT) // loop until user chooses to exit
    {
        printf("Welcome to cracker95 in C!!!!\n");
        printf("MENU:\n1. Generate CD Key\n2. Generate OEM Key\n3. Verify Key\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &menuCh);
        switch (menuCh) // switch statement for menu choices
        {
            case CD: // generate cd key
                printf("CD Key: ");
                genCdKey();
                break;
            case OEM: // generate oem key
                printf("OEM Key: ");
                genOemKey();
                break;
            case VERIF: // verify key
                verifKey();
                break;
            case EXIT: // exit
                break;
            default: // invalid choice
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}

/*
 * randr - returns a random number between min and max
 * input: min - minimum number, max - maximum number
 * output: random number between min and max
 */
int randr(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

/*
 * genCdKey - generates a cd key
 * input: none
 * output: none
 */
void genCdKey()
{
    int box1 = 000; // box 1
    int box2[7] = {0 , 0 , 0 , 0 , 0 , 0, 0}; // box 2

    do // generate box 1, windows 95 checks if its not 333, 444, 555, 666, 777, 888, or 999, it can even be text!!!!
    {
        box1 = randr(100, 999);
    } while (box1 == 333 || box1 == 444 || box1 == 555 || box1 == 666 || box1 == 777 || box1 == 888 || box1 == 999);

    do // generate box 2, windows 95 checks if the sum of box 2 is divisible by 7 and if box 2 part 7 is not 0, 8 or 9
    {
        for (int i = 0; i < 7; i++) // generate box 2 part 1-7
        {
            box2[i] = randr(0, 9);
        }
    } while ((box2[0] + box2[1] + box2[2] + box2[3] + box2[4] + box2[5] + box2[6]) % 7 != 0 || box2[6] > 7 || box2[6] == 0);

    printf("%d-%d%d%d%d%d%d%d\n", box1, box2[0], box2[1], box2[2], box2[3], box2[4], box2[5], box2[6]);
}

/*
 * genOemKey - generates an oem key
 * input: none
 * output: none
 */
void genOemKey()
{
    int box1P1 = 000; // box 1 part 1
    int box1P2 = 00; // box 1 part 2
    int box3[7] = {0, 0, 0, 0, 0, 0, 0}; // box 3
    int box4[5] = {0, 0, 0, 0, 0}; // box 4

    box1P1 = randr(100, 366); // generate box 1 part 1 windows 95 checks if its between 001 and 366
    box1P2 = randr(95, 99); // generate box 1 part 2 windows 95 checks if its between 95 and 99 or 00 between and 02

    box3[0] = 0; // box 3 part 1 is always 0
    do // generate box 3 part 2-7
    {
        for (int i = 1; i < 7; i++)
        {
            box3[i] = randr(0, 9);
        }
    } while ((box3[0] + box3[1] + box3[2] + box3[3] + box3[4] + box3[5] + box3[6]) % 7 != 0 || box3[6] > 7 || box3[6] == 0); // windows 95 checks if the sum of box 3 part 1-7 is divisible by 7 and if box 3 part 7 is not 0, 8, or 9, and if box 3 part 1 is 0

    for (int i = 0; i < 5; i++) // generate box 4, its just random
    {
        box4[i] = randr(0, 9);
    }

    printf("%d%d-OEM-%d%d%d%d%d%d%d-%d%d%d%d%d\n", box1P1, box1P2, box3[0], box3[1], box3[2], box3[3], box3[4], box3[5], box3[6], box4[0], box4[1], box4[2], box4[3], box4[4]);
}

/*
 * verifKey - verifies a key
 * input: none
 * output: none
 */
void verifKey()
{
    char key[23] = {0}; // key input

    getchar(); // Clear buffer
    printf("Enter key: ");
    fgets(key, 25, stdin); // get key input
    key[strcspn(key, "\n")] = 0; // remove newline from key

    if ((key[6] == 'O' && key[7] == 'E' && key[8] == 'M') || (key[6] == 'o' && key[7] == 'e' && key[8] == 'm')) // check if oem key
    {
        int box1P1 = ((int)key[0] - '0') * 100 + ((int)key[1] - '0') * 10 + ((int)key[2] - '0'); // convert box 1 part 1 to int
        int box1P2 = ((int)key[3] - '0') * 10 + ((int)key[4] - '0'); // convert box 1 part 2 to int
        char box3[8] = {key[10], key[11], key[12], key[13], key[14], key[15], key[16], 0}; // box 3
        int box3Sum = 0; // box 3 sum
        // verification variables
        bool box1P1Verif = false;
        bool box1P2Verif = false;
        bool box3Verif = false;

        if (box1P1 >=1 && box1P1 <= 366) // check if box 1 part 1 is valid
        {
            box1P1Verif = true;
        }

        if (box1P2 >= 95 && box1P2 <= 99 || box1P2 >= 00 && box1P2 <= 02) // check if box 1 part 2 is valid
        {
            box1P2Verif = true;
        }

        for (int i = 0; i < 7; i++) // calculate box 3 sum
        {
            box3Sum += (int)box3[i] - '0';
        }
        if (box3Sum % 7 == 0 && box3[6] != '0' && box3[6] != '8' && box3[6] != '9' && box3[0] == '0') // check if box 3 is valid
        {
            box3Verif = true;
        }

        if (DEBUG) // debug output
        {
            printf("Box 1 Part 1: %d\n", box1P1);
            printf("Box 1 Part 2: %d\n", box1P2);
            printf("Box 3: %s\n", box3);
            printf("Box 1 Part 1 Verif: %d\n", box1P1Verif);
            printf("Box 1 Part 2 Verif: %d\n", box1P2Verif);
            printf("Box 3 Verif: %d\n", box3Verif);
        }

        if (box1P1Verif == 1 && box1P2Verif == 1 && box3Verif == 1) // check if key is valid
        {
            printf("Valid key\n\n");
        }
        else
        {
            printf("Invalid key\n\n");
        }
    }
    else // cd key
    {
        char box1[4] = {key[0], key[1], key[2], 0}; // box 1
        char box2[8] = {key[4], key[5], key[6], key[7], key[8], key[9], key[10], 0}; // box 2
        int box2Sum = 0; // box 2 sum
        // verification variables
        bool box1Verif = false;
        bool box2Verif = false;

        // check if box 1 is valid
        if (strcmp(box1, "333") != 0 && strcmp(box1, "444") != 0 && strcmp(box1, "555") != 0 && strcmp(box1, "666") != 0 && strcmp(box1, "777") != 0 && strcmp(box1, "888") != 0 && strcmp(box1, "999") != 0)
        {
            box1Verif = true;
        }

        for (int i = 0; i < 7; i++) // calculate box 2 sum
        {
            box2Sum += (int)box2[i] - '0';
        }
        if (box2Sum % 7 == 0 && box2[6] != '8' && box2[6] != '9') // check if box 2 is valid
        {
            box2Verif = true;
        }

        if (DEBUG) // debug output
        {
            printf("Box 1: %s\n", box1);
            printf("Box 2: %s\n", box2);
            printf("Box 1 Verif: %d\n", box1Verif);
            printf("Box 2 Verif: %d\n", box2Verif);
        }

        if (box1Verif == 1 && box2Verif == 1) // check if key is valid
        {
            printf("Valid key\n\n");
        }
        else
        {
            printf("Invalid key\n\n");
        }
    }
}

