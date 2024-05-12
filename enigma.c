#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cs50.h"
#include "enigma_func.h"

// declare global variables
const int N = 26;       // amount of letters in the english alphabet
const int R = 5;        // amount of rotors to pick from
const int A = -65;      // ASCII arithmetics, from ASCII alphabet number to regular alphabet number
const int P = 6;        // max plugboard connections


// declaring alphabet string
char alphabet[N + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// initialize array of strings to contain rotor wiring types
string rot_type[R] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",   // ENIGMA I 1930
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",   // ENIGMA I 1930
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",   // ENIGMA I 1930
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",   // M3 ARMY ENIGMA 1938 
    "VZBRGITYUPSDNHLXAWMJQOFECK"    // M3 ARMY ENIGMA 1938 
};

// initiating string array of reflector types
char reflect_type[N + 1] = {
    "ZYXWVUTSRQPONMLKJIHGFEDCBA"   // BETA : MODEL M4 1941  
};


int main (void)
{   
    // declare hash table
    node *table[N];

    // allocate memory for entire rotor system (26 nodes * 3 rotors)
    node *n[N]; 
    node *m[N];
    node *l[N]; 
    node *reflecter[N];
    
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node)*N);
        n[i] = malloc(sizeof(node)*N);
        m[i] = malloc(sizeof(node)*N);
        l[i] = malloc(sizeof(node)*N);
        reflecter[i] = malloc(sizeof(node)*N);
    
        // malloc check
        if (*n == NULL || *m == NULL || *l == NULL || *reflecter == NULL || *table == NULL)
        {
            printf("Error handling: Memory allocation failed.");
            return 1;
        }
    }

    // initialize specific rotor models' turnover notch positions
    int notch1, notch2;
    int notch_type1 = 16;           // TNP = Q-R
    int notch_type2 = 4;            // TNP = E-F
    int notch_type3 = 21;           // TNP = V-W
    int notch_type4 = 9;            // TNP = J-K
    int notch_type5 = 25;           // TNP = Z-A

    // ROTOR ORDER: prompt user for rotor order (a-b-c)
    int a = 0; int b = 0; int c = 0;

    // notch(R, a, b, c, notch1, notch2, notch_type1, notch_type2, notch_type3, notch_type4, notch_type5);
    while (true)
    {
        printf("\nROTOR ORDER: \n\n");
        a = get_int("   Enter first roter model: 1-%d\n", R) - 1; printf("\n");
        b = get_int("   Enter second roter model: 1-%d\n", R) - 1; printf("\n");
        c = get_int("   Enter third roter model: 1-%d\n", R) - 1; printf("\n\n");

        // check for invalid prompt
        if (a < 0 || a >= R || b < 0 || b >= R || c < 0 || c >= R)
        {
            printf("ERROR: Invalid rotor model was entered. Try again.\n\n\n");
            continue;
        }
        else
        {
            break;
        }
    }

    // set notch positions for specific rotor model
    if      (a == 0) {notch1 = notch_type1;}
    else if (a == 1) {notch1 = notch_type2;}
    else if (a == 2) {notch1 = notch_type3;}
    else if (a == 3) {notch1 = notch_type4;}
    else if (a == 4) {notch1 = notch_type5;}

    if      (b == 0) {notch2 = notch_type1;}
    else if (b == 1) {notch2 = notch_type2;}
    else if (b == 2) {notch2 = notch_type3;}
    else if (b == 3) {notch2 = notch_type4;}
    else if (b == 4) {notch2 = notch_type5;}

    printf("         ___________\n");
    printf("        |   |   |   |\n");
    printf("        | %d | %d | %d |\n", a+1, b+1, c+1);
    printf("        |   |   |   |\n");
    printf("         ‾‾‾‾‾‾‾‾‾‾‾\n");
    
    printf("\n---------------------------------------------\n\n\n");

    // ROTOR POSITIONS: prompting for string, then converting and storing it as int where A = 0 and Z = 25
    int pos1; int pos2; int pos3;
    prompt_rposition(pos1, pos2, pos3, N, A);

    // initializing reflecter pointer connections
    for (int i = 0; i < N; i++)
    {
        reflecter[i]->value = reflect_type[i];
    }
    
    // set rotor cryptoalphabets from specific rotor types
    for(int i = 0; i < N; i++)
    {
        n[i]->value = rot_type[a][i]; 
        m[i]->value = rot_type[b][i]; 
        l[i]->value = rot_type[c][i]; 
    } 

    // set table values to alphabet
    for (int i = 0; i < N; i++)
    {
        table[i]->value = alphabet[i];
    }

    // ensuring that one letter is used maximum one time (will be used in the following prompting section)
    int check[N];           // ensuring that any letter is used maximum once
    for (int i = 0; i < N; i++)
    {
        check[i] = 0;
    }


    // prompt user for specific plugboard connections
    char plug[P][2];        // declare arrays to contain letter substitutions
    printf("\n---------------------------------------------\n\n");
    prompt_plug(plug, check, P, A, N);
    printf("\n---------------------------------------------\n\n");


    // Prompt cleartext
    string cleartext = prompt_clear(cleartext, N, A);

    // ENCRYPTION: encrypt each letter iteratively
    for (int i = 0; i < strlen(cleartext); i++)
    {
        // Permutate through plugboard
        plugboard(b, plug, P, cleartext, i);

        // permutate through entire rotor system
        rotorsys(cleartext, table, n, m, l, reflecter, i, A, N);

        // Inverse Permutate through plugboard
        plugboard(b, plug, P, cleartext, i);


        // turn rotor N 1/26 after each key press
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                if (n[j]->value == rot_type[a][k])
                {

                    n[j]->value = rot_type[a][(k + 1) % N];
                    break;
                }
            }
        }

        // turn M if N has crossed it's turnover point
        if (n[(i + 25) % N]->value + A == notch1)
        {
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    if (m[j]->value == rot_type[b][k])
                    {

                        m[j]->value = rot_type[b][(k + 1) % N];
                        break;
                    }
                }
            }
        }
                
        // turn L if M has crossed it's turnover point
        if (m[(i + 25) % N]->value + A == notch2)
        {
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    if (l[j]->value == rot_type[c][k])
                    {
                        l[j]->value = rot_type[c][(k + 1) % N];
                        break;
                    }
                }
            }
        }
    }

    // printf the encrypted cleartext
    printf("\n---------------------------------------------\n\n");
    printf("Cryptotext: \n    %s\n", cleartext);
    printf("\n---------------------------------------------\n\n");

    // free allocated memory
    for (int i = 0; i < N; i++)
    {
        free(table[i]);
        free(n[i]);
        free(m[i]);
        free(l[i]);
        free(reflecter[i]);
    }

    return 0;
}