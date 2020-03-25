/**********************************************************************
Filename:				ass2.c
Version:				1.0
Author:					Joseph Trottier
Student No:				040 866 019
Course Name/Number:		Numerical Computing   CST8233
Lab Sect:				301
Assignment #:			2
Assignment name:		Moore’s Law
Due Date:				November 14 2019
Submission Date:		November 14 2019
Professor:              Abdullah Kadri
Purpose:				Fit data using linear regression 
						least-squares method for an exponential function. 
*********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EXIT '2'
void printFile(char *);
void exponentialFit(char *);
double* getXValuesFromFile(char *);
double* getYValuesFromFile(char *);




double xAxis[14], n, yAxis[14];
	/********************************************************************
	Function name:		main
	Purpose:			main function
							Reads input from the user and does math.
	In parameters:		none
	Out parameters:		1 for successful execution
	Version:			1.0
	Author:				Joseph Trottier
	**********************************************************************/
	int main() {
		system("cls");
		double xiyi, xi, yi, m, b, xii, letter, transCount, rate, tempY;
		char check = '0', string[256], name[256], checkTwo = '0';
		int i = 0, year;
		while (check != EXIT)
		{
			printf("LEAST_SQUARES LINEAR REGRESSION\n");
			printf("MENU\n");
			printf("1. Exponential Fit\n2: Quit\n");
			fflush(stdin);
			scanf(" %c", &check);
			switch (check) {
			case '1':
				system("cls");
				printf("enter the name of the file to open: ");
				fflush(stdin);
				scanf(" %s", string);
				printFile(string);

				i = 0;
				FILE *f;
				f = fopen(string, "r");
				letter = fscanf(f, "%s", name);
				letter = fscanf(f, "%s", name);
				letter = fscanf(f, "%s", name);
				while (letter != EOF) {
					letter = fscanf(f, "%lf", &xAxis[i]);
					letter = fscanf(f, "%lf", &tempY);
					yAxis[i] = log(tempY);
					letter = fscanf(f, "%s", name);
					i++;
				}
				fclose(f);
				n = sizeof(xAxis) / sizeof(double);
				/*GET xiyi*/
				xiyi = 0;
				for (i = 0; i < n; i++) {
					xiyi += (xAxis[i] * yAxis[i]);
				}
				/*GET xi*/
				xi = 0;
				for (i = 0; i < n; i++) {
					xi += xAxis[i];
				}
				xii = 0;
				for (i = 0; i < n; i++) {
					xii += xAxis[i] * xAxis[i];
				}
				/*GET yi*/
				yi = 0;
				for (i = 0; i < n; i++) {
					yi += yAxis[i];
				}

				m = (n*xiyi - xi * yi) / (n*(xii)-(xi*xi));
				b = exp((yi/1 - m * (xi-1970*n)) / n);
				printf("Linear Regression Fit:  transistor count = %E*exp(%E*(year-1970))\n", b, m);
				while (checkTwo != EXIT)
				{
					printf("MENU\n");
					printf("1. Extrapolate\n2: Main Menu\n");
					fflush(stdin);
					scanf(" %c", &checkTwo);
					switch (checkTwo) {
					case '1':
						printf("Please enter the year to extrapolate to: ");
						fflush(stdin);
						scanf(" %d", &year);
						printf("Year = %d\n", year);
						transCount = (b * exp(m*(year - 1970)));
						printf("transistor count: %E\n", transCount);
						rate = m * b*exp(m*(year - 1970));
						printf("of count increase = %E\n", rate);
					}
				}
			}

		}
		return 1;
	}
	/********************************************************************
	Function name:		printFile
	Purpose:			Print Contents of file
	In parameters:		char *: fileName - string of file name
	Out parameters:		void
	Version:			1.0
	Author:				Joseph Trottier
	**********************************************************************/
	void printFile(char *fileName) {
		FILE *f;
		char fileChar;
		/* "r"	read: Open file for input operations. The file must exist. */
		f = fopen(fileName, "r");
		while ((fileChar = fgetc(f)) != EOF) {
			printf("%c", fileChar);
		}
		fclose(f);
	}