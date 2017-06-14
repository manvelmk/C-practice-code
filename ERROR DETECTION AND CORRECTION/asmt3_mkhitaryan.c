//Manvel Mkhitaryan
//COMP 222
//Assignment 3

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Declare global vars */
int max_length = 0;
int parity = 0;
int actual_length = 0;
/* define hamming string as a dynamic array of characters */
char* hamming=NULL;

void paramInput()
{
	/* prompt for maximum hamming code length and for even/odd parity */
	printf("\nEnter the maximum length: ");
	scanf("%d", &max_length);
	printf("Enter the parity (0=even, 1=odd): ");
	scanf("%d", &parity);
	/* allocate memory for hamming string based on maximum length and size of a character element*/
	
	return;
}

void checkHamm()
{
	/* declare local vars */
	int i, j, k = 0;
	int error_location = 0;
	int local_parity = 0;

	/* prompt for hamming code as a "string"*/
	hamming = (char*)malloc(sizeof(char)* max_length);
	printf("\nEnter the Hamming code: ");
	scanf("%s", hamming);

	//set actual length as lenth of hamming string
	actual_length = strlen(hamming);

	/* OUTER LOOP: for each parity bit in the Hamming code*/
	/* BEGIN OF OUTER LOOP */
	for (i = 1; i <= actual_length; i *= 2)
	{
		/* initialize appropriate local variables */
		local_parity = parity;
		/* MIDDLE LOOP: for each starting bit of a sequence */
		for (j = i; j <= actual_length; j += i * 2)
		{
			/* INNER LOOP: for each bit to be checked, check value and update parity information for current parity bit*/
			for (k = j; k < i + j && k <= actual_length; k++)
			{
				//XOR
				local_parity = local_parity ^ (hamming[actual_length - k] - '0');
			}
		}
		/* update parity checking by including result for parity bit checked in total */
		error_location = error_location + local_parity * i;
	}

	/* report error in hamming code based on result from parity bits or report no error if none */
	if (error_location == 0)
	{
		printf("There is no bit error \n");
	}
	else
	{
		printf("There is an error in bit: %d", error_location);
		//correct hamming string with known location by substracting the wrong bit from 1
		hamming[actual_length - error_location] = (char)(('1' - hamming[actual_length - error_location]) + '0');
		printf("\nThe corrected Hamming code is: %s \n", hamming);
	}
	return;
}

int main()
{
	int menu = 0;
	/* print out menu, prompt for choice, and call appropriate procedure until user quits */
	while (menu <= 3)
	{
		printf("\nError detection/correction:\n");
		printf("---------------------------\n");
		printf("1) Enter parameters\n");
		printf("2) Check Hamming Code \n");
		printf("3) Quit\n");
		printf("\nEnter selection: ");

		scanf("%d", &menu);
		switch (menu)
		{
		case 1: paramInput();
			break;
		case 2: checkHamm();
			break;
		case 3:
			return;
		default:
			printf("\nPlease choose options 1-3\n");
			menu = 0; //reset menu choice
			break;
		}
	}
	return 1;
}
