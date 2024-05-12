#include "enigma_func.c"

// Prompt for each rotorposition
void prompt_rposition(int pos1, int pos2, int pos3, const int N, const int A);

// prompt user for specific plugboard connections
void prompt_plug(char plug[][2], int check[], const int P, const 
int A, const int N); //without bool answer

// Prompt cleartext
string prompt_clear(string cleartext, const int N, const int A);

// Permutate through plugboard
void plugboard(bool b, char plug[][2], const int P, string cleartext, int i);

// Permutate through entire rotor system
void rotorsys(string cleartext, node *table[], node *n[], 
node *m[], node *l[], node *reflecter[], int i, const int A, const int N);

// Readjust rotor M and L if turnover conditions are met
void turn_ML(const int N, int i, int a, int b, int pos1, int pos2, int notch1, 
int notch2, node *table[], node *n[], node *m[], node *l[]);
