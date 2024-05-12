#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> //strcmp
#include "cs50.h" 

// defining the node structure data type (DOUBLE DEFINED IN TWO FILES)
typedef struct node {
    char value;
} node;

// Prompt for each rotorposition
void prompt_rposition(int pos1, int pos2, int pos3, const int N, const int A)
{
    char cpos1;
    char cpos2;
    char cpos3;
    
    while (true)
    {        
        printf("ROTOR POSITIONS: \n");
        cpos1 = toupper(get_char("\n    Enter first rotor position: A-Z \n"));
        cpos2 = toupper(get_char("    Enter second rotor position: A-Z \n"));
        cpos3 = toupper(get_char("    Enter third rotor position: A-Z \n"));
        
        pos1 = (int)((cpos1)) + A; 
        pos2 = (int)((cpos2)) + A; 
        pos3 = (int)((cpos3)) + A; 

        if      (pos1 < 0 || pos1 > N) {printf("ERROR: Invalid rotor position 1 \n\n\n"); continue;}
        else if (pos2 < 0 || pos2 > N) {printf("ERROR: Invalid rotor position 2 \n\n\n"); continue;}
        else if (pos3 < 0 || pos3 > N) {printf("ERROR: Invalid rotor position 3 \n\n\n"); continue;}

        break;
    }
        printf("         ___________ \n");
        printf("        |   |   |   |\n");
        printf("        | %c | %c | %c |\n", cpos1, cpos2, cpos3);
        printf("        |   |   |   |\n");
        printf("         ‾‾‾‾‾‾‾‾‾‾‾ \n");

    return;
}

//prompt user for plugboard connections
void prompt_plug(char plug[][2], int check[], const int P, const int A, 
    const int N)
{
    printf("PLUGBOARD: \n\n");
    while (true)
    {
        // reset checker and max (expressions used to check for invalid input)
        for(int i = 0; i < N; i++)
        {
            check[i] = 0;
        }
        bool b = false;

        printf("Plugboard system requires %d substitution pairs.    \n\n", P);
        for (int i = 0; i < P; i++)
        {                
            plug[i][0] = toupper(get_char("    Select two letters for pair no. %d: \n", i + 1));
            plug[i][1] = toupper(get_char(""));
        
            for (int j = 0; j < 2; j++)
            {
                if (plug[i][j] < 65 || plug[i][j] > 122)
                {
                    b = true;
                    break;
                }
                if (plug[i][j] >= 91 && plug[i][j] <= 96)
                {
                    b = true;
                    break;
                }
                for (int k = 0; k < N; k++)
                {
                    if ((plug[i][j]) + A == k)
                    {    
                        check[k]++;          // check[N] represents all letters in the alphabet, and the value = times used in plugboard
                    }                        // used to track which letters were plugged and if any was chosen multiple times
                }
            }
            if (b == true)
            {
                break;
            }
        }
        if (b == true)
        {
            printf("ERROR: Non alphabetic letter was entered. Retry\n");
            continue;
        }

        // turning bool max false if a letter is entered more than once
        for (int i = 0; i < N; i++)
        {
            if (check[i] > 1)   
            {
                b = true;    
            }
        }
        if (b == true)        
        {
            printf("ERROR: One letter was entered multiple times. Retry \n\n\n");
            continue;
        }
        else
        {
            break;
        }
    }

    //print box to highlight the prompted plugboard pairs

        printf("         _______________________ \n");
        printf("        |   |   |   |   |   |   |\n");
        printf("        | %c | %c | %c | %c | %c | %c |\n", plug[0][0], plug[1][0], plug[2][0], plug[3][0], plug[4][0], plug[5][0]);
        printf("        | %c | %c | %c | %c | %c | %c |\n", plug[0][1], plug[1][1], plug[2][1], plug[3][1], plug[4][1], plug[5][1]);
        printf("        |   |   |   |   |   |   |\n");
        printf("         ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
    return;
}

// Prompt cleartext
string prompt_clear(string cleartext, const int N, const int A)
{
   
    printf("CLEARTEXT:\n    ");
    while (true)
    {    
        bool check = false;
        cleartext = get_string("");

        //check if every character is a letter in the alphabet
        for (int i = 0; i < strlen(cleartext); i++)
        {
            // reprompt if a non alphabetic letter was entered
            if (cleartext[i] < 65 || cleartext[i]>122)
            {
                check = true;
                break;
            }
            if (cleartext[i] >= 91 && cleartext[i] <= 96)
            {
                check = true;
                break;
            }
        }
        if (check == true)
        {
            printf("Error: Non alphabetic character was entered. Try again.\n\n");
            printf("CLEARTEXT:\n    ");
            continue;
        }
        else
        {
            break;
        }
    }

    // capitalize the characters cleartext
    for (int i = 0; i < strlen(cleartext); i++)
    {
        cleartext[i] = toupper(cleartext[i]);
    }

    return cleartext;
}


// Permutate through plugboard
void plugboard(bool b, char plug[][2], const int P, string cleartext, int i)
{

        // PLUGBOARD: checking if the cleartext letter should be permutated
        for (int j = 0; j < P; j++)
        {

                // permutate if letter is connected to another in plugboard
                if (cleartext[i] == plug[j][0])
                {
                    cleartext[i] = plug[j][1];
                }
                else if (cleartext[i] == plug[j][1])
                {
                    cleartext[i] = plug[j][0];
                }
        }
    return;
}

// Permutate through entire rotor system
void rotorsys(string cleartext, node *table[], node *n[], node *m[], 
    node *l[], node *reflecter[], int i, const int A, const int N)
{
    // Uncomment the print functions to track each permuation through the rotorsystem
        // printf("    S: %c\n", cleartext[i]); 
    // N
    cleartext[i] = n[((int)(cleartext[i] + A) % N)]->value;
        // printf("    N: %c\n", cleartext[i]);   

    // M
    cleartext[i] = m[(int)((cleartext[i] + A) % N)]->value;
        // printf("    M: %c\n", cleartext[i]);   
    // L  
    cleartext[i] = l[((int)(cleartext[i] + A) % N)]->value;
        // printf("    L: %c\n", cleartext[i]);   

    // Reflecter
    cleartext[i] = reflecter[((int)(cleartext[i]) + A) % N]->value;
        // printf("    R: %c\n", cleartext[i]);

    cleartext[i] = reflecter[((int)(cleartext[i]) + A) % N]->value;
        // printf("    R: %c\n", cleartext[i]);
    

    int index;
    // R inverse: find specific spot in the array where the permutated letter is stored
    for (int n = 0; n < N; n++)
    {
        if (cleartext[i] == reflecter[n]->value)
        {
            index = n;
        }
    }
    // locate the following permutation (inverse)
    for (int n = 0; n < N; n++)
    {
        if (l[n]->value + A == index)
        {
            cleartext[i] = l[n]->value;
        }
    }

    // L inverse: repeat the previous step for the following inverse permutations
    for (int n = 0; n < N; n++)
    {
        if (cleartext[i] == l[n]->value)
        {
            index = n;
        }
    }
    // locate the following permutation
    for (int n = 0; n < N; n++)
    {
        if (m[n]->value + A == index)
        {
            cleartext[i] = m[n]->value;
        }
    }
   
    // M inverse:
    for (int h = 0; h < N; h++)
    {
        if (cleartext[i] == m[h]->value)
        {
            index = h;
        }
    }
    // locate the following permutation
    for (int h = 0; h < N; h++)
    {
        if (n[h]->value + A == index)
        {
            cleartext[i] = n[h]->value;
        }
    }

    // N inverse:
    for (int h = 0; h < N; h++)
    {
        if (cleartext[i] == n[h]->value)
        {
            index = h;
        }
    }
    // locate the following permutation
    for (int h = 0; h < N; h++)
    {
        if (table[h]->value + A == index)
        {
            cleartext[i] = table[h]->value;
        }
    }

    return;
}
