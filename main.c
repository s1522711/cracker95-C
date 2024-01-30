#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG false

enum menuChoice { CD=1, OEM, VERIF, EXIT};

int randr(int min, int max);
void genCdKey();
void genOemKey();
void verifKey();

int main() {
    srand(time(NULL));
    enum menuChoice menuCh = CD;
    while (menuCh != EXIT) {
        printf("Welcome to cracker95 in C!!!!\n");
        printf("MENU:\n1. Generate CD Key\n2. Generate OEM Key\n3. Verify Key\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &menuCh);
        switch (menuCh) {
            case CD:
                printf("CD Key: ");
                genCdKey();
                break;
            case OEM:
                printf("OEM Key: ");
                genOemKey();
                break;
            case VERIF:
                verifKey();
                break;
            case EXIT:
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}

int randr(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void genCdKey()
{
    char cdKey[12] = {0};
    int box1 = 000;
    int box2[7] = {0 , 0 , 0 , 0 , 0 , 0, 0};

    do
    {
        box1 = randr(100, 999);
    } while (box1 == 333 || box1 == 444 || box1 == 555 || box1 == 666 || box1 == 777 || box1 == 888 || box1 == 999);

    do {
        for (int i = 0; i < 7; i++) {
            box2[i] = randr(0, 9);
        }
    } while ((box2[0] + box2[1] + box2[2] + box2[3] + box2[4] + box2[5] + box2[6]) % 7 != 0 || box2[6] > 7 || box2[6] == 0);

    printf("%d-%d%d%d%d%d%d%d\n", box1, box2[0], box2[1], box2[2], box2[3], box2[4], box2[5], box2[6]);
}

void genOemKey()
{
    int box1P1 = 000;
    int box1P2 = 00;
    int box3[7] = {0, 0, 0, 0, 0, 0, 0};
    int box4[5] = {0, 0, 0, 0, 0};

    box1P1 = randr(100, 366);
    box1P2 = randr(95, 99);

    box3[0] = 0;
    do {
        for (int i = 1; i < 7; i++) {
            box3[i] = randr(0, 9);
        }
    } while ((box3[0] + box3[1] + box3[2] + box3[3] + box3[4] + box3[5] + box3[6]) % 7 != 0 || box3[6] > 7 || box3[6] == 0);

    for (int i = 0; i < 5; i++) {
        box4[i] = randr(0, 9);
    }

    printf("%d%d-OEM-%d%d%d%d%d%d%d-%d%d%d%d%d\n", box1P1, box1P2, box3[0], box3[1], box3[2], box3[3], box3[4], box3[5], box3[6], box4[0], box4[1], box4[2], box4[3], box4[4]);
}

void verifKey()
{
    char key[23] = {0};

    getchar(); // Clear buffer
    printf("Enter key: ");
    fgets(key, 25, stdin);
    key[strcspn(key, "\n")] = 0;

    if ((key[6] == 'O' && key[7] == 'E' && key[8] == 'M') || (key[6] == 'o' && key[7] == 'e' && key[8] == 'm'))
    {
        int box1P1 = ((int)key[0] - '0') * 100 + ((int)key[1] - '0') * 10 + ((int)key[2] - '0');
        int box1P2 = ((int)key[3] - '0') * 10 + ((int)key[4] - '0');
        char box3[8] = {key[10], key[11], key[12], key[13], key[14], key[15], key[16], 0};
        int box3Sum = 0;
        int box1P1Verif = 0;
        int box1P2Verif = 0;
        int box3Verif = 0;

        if (box1P1 >=1 && box1P1 <= 366)
        {
            box1P1Verif = 1;
        }

        if (box1P2 >= 95 && box1P2 <= 99 || box1P2 >= 00 && box1P2 <= 02)
        {
            box1P2Verif = 1;
        }

        for (int i = 0; i < 7; i++)
        {
            box3Sum += (int)box3[i] - '0';
        }
        if (box3Sum % 7 == 0 && box3[6] != '0' && box3[6] != '8' && box3[6] != '9' && box3[0] == '0')
        {
            box3Verif = 1;
        }

        if (DEBUG)
        {
            printf("Box 1 Part 1: %d\n", box1P1);
            printf("Box 1 Part 2: %d\n", box1P2);
            printf("Box 3: %s\n", box3);
            printf("Box 1 Part 1 Verif: %d\n", box1P1Verif);
            printf("Box 1 Part 2 Verif: %d\n", box1P2Verif);
            printf("Box 3 Verif: %d\n", box3Verif);
        }

        if (box1P1Verif == 1 && box1P2Verif == 1 && box3Verif == 1) {
            printf("Valid key\n\n");
        } else {
            printf("Invalid key\n\n");
        }
    }
    else
    {
        char box1[4] = {key[0], key[1], key[2], 0};
        char box2[8] = {key[4], key[5], key[6], key[7], key[8], key[9], key[10], 0};
        int box2Sum = 0;
        int box1Verif = 0;
        int box2Verif = 0;

        if (strcmp(box1, "333") != 0 && strcmp(box1, "444") != 0 && strcmp(box1, "555") != 0 && strcmp(box1, "666") != 0 && strcmp(box1, "777") != 0 && strcmp(box1, "888") != 0 && strcmp(box1, "999") != 0)
        {
            box1Verif = 1;
        }

        for (int i = 0; i < 7; i++)
        {
            box2Sum += (int)box2[i] - '0';
        }
        if (box2Sum % 7 == 0 && box2[6] != '8' && box2[6] != '9')
        {
            box2Verif = 1;
        }

        if (DEBUG)
        {
            printf("Box 1: %s\n", box1);
            printf("Box 2: %s\n", box2);
            printf("Box 1 Verif: %d\n", box1Verif);
            printf("Box 2 Verif: %d\n", box2Verif);
        }

        if (box1Verif == 1 && box2Verif == 1) {
            printf("Valid key\n\n");
        } else {
            printf("Invalid key\n\n");
        }
    }
}

