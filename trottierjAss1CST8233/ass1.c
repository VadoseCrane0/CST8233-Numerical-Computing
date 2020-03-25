/**********************************************************************
Filename:				ass1.c 
Version:				1.0                                          
Author:					Joseph Trottier                                               
Student No:				040 866 019                                               
Course Name/Number:		Numerical Computing   CST8233                               
Lab Sect:				301                                                       
Assignment #:			1 
Assignment name:		Building Motion Simulation  
Due Date:				September 29 2019                                            
Submission Date:		September 28 2019
Professor:              Abdullah Kadri                            
Purpose:				Investigate a less accurate but faster Maclaurin Series approximation.
						Until the user decides to quit. Do the maclaurin series
*********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT '2'
void mclaurinSeries(int, double);


/******************************************************************** 
Function name:		main 
Purpose:			main function     
						Reads input from the user.  
In parameters:		none 
Out parameters:		1 for successful execution 
Version:			1.0 
Author:				Joseph Trottier 
**********************************************************************/
int main() {
	system("cls");
	int terms;
	double range;
	char check = '0';
	while (check != EXIT)
	{
		printf("Evaluate the Maclaurin Series approximation to exp(-t)*cos(t)\n");
		printf("1: Evaluate the series\n2: quit\n");
		fflush(stdin);
		scanf(" %c", &check);
		switch (check) {
		case '1':
			system("cls");
			printf("Evaluating the series\n");
			do {
				printf("Please enter the number of terms in the series(max 5 terms): ");
				fflush(stdin);
				scanf(" %d", &terms);
			} while (terms < 0 || terms > 5);
			do {
				printf("Please enter the range of t to evaluate in 10 increments (0.0 < t < +2.0): ");
				fflush(stdin);
				scanf(" %lf", &range);
			} while (range < 0 || range > 2);
			range = range / 10.0;
			mclaurinSeries(terms, range);
			break;
		}

	}
	return 1;
}
/********************************************************************
Function name:		mclaurinSeries
Purpose:			Calculate the result of mclaurin series 
					and print the results
In parameters:		int: terms - how many terms to approximate the mclaurin series
					double: range - the range of the mclaurin series
Out parameters:		none
Version:			1.0
Author:				Joseph Trottier
**********************************************************************/
void mclaurinSeries(int terms, double range) {
	double series;
	double exact;
	double exactError;
	double truncError;
	double trunc;
	double t = range;
	int i;

	printf("MACLAURIN SERIES\n\n");
	printf("  t         Series        Exact           Exact %% Error  Trunc. %% Error \n");
	printf("%.3e   %.5e   %.5e     %.5e    %.5e \n", 0.0, 1.0, 1.0, 0.0, 0.0);

	for (i = 0; i < 10; i++) {
		exact = exp(-t)*cos(t);
		switch (terms) {
		case 1:
			series = 1.0;
			trunc = -t;
			break;
		case 2:
			series = 1.0 - t;
			trunc = (t*t*t) / 3.0;
			break;
		case 3:
			series = 1.0 - t + (t*t*t) / 3.0;
			trunc = -(t*t*t*t) / 6.0;
			break;
		case 4:
			series = 1.0 - t + (t*t*t) / 3.0 - (t*t*t*t) / 6.0;
			trunc = (t*t*t*t*t) / 30.0;
			break;
		case 5:
			series = 1.0 - t + (t*t*t) / 3.0 - (t*t*t*t) / 6.0 + (t*t*t*t*t) / 30.0;
			trunc = -(t*t*t*t*t*t*t) / 630;
			break;
		}
		exactError = 100*(exact-series)/exact;
		truncError = 100 * trunc / series;
		printf("%.3e   %.5e   %.5e     %.5e    %.5e \n", t, series, exact, exactError, truncError);
		t += range;
	}
}