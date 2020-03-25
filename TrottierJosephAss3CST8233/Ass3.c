/**********************************************************************
Filename:				Ass3.c
Version:				1.0
Author:					Joseph Trottier
Student No:				040 866 019
Course Name/Number:		Numerical Computing   CST8233
Lab Sect:				301
Assignment #:			3
Assignment name:		Transient-Response Analysis of 1st Order Systems 
Due Date:				December 06  2019
Submission Date:		December 05 2019
Professor:              Abdullah Kadri
Purpose:				Find the solution of 1st order Ordinary 
						Differential Equations (ODE) using well
						known  methods; namely, Euler’s and 
						Runge-Kutta 2nd Order Methods.
*********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double diff(double, double);
void eulersMethod(double);
void rungeKutta(double);


/********************************************************************
Function name:		main
Purpose:			main function
						Reads input from the user and calls functions to do math.
In parameters:		none
Out parameters:		1 for successful execution
Version:			1.0
Author:				Joseph Trottier
**********************************************************************/
int main() {
	system("cls");
	int method = 0;
	double stepSize = 0;
	while (method != 3) {
		printf("\n");
		printf("Choose the method for solving the ODE:\n");
		do {
			printf("1. Euler's Method\n2. Runge - Kutta 4th Order Method\n3. Quit\n");
			fflush(stdin);
			scanf(" %d", &method);
			if (method == 3)return;
		} while (method != 1 && method != 2);
		do {
			printf("Choose step size \"h\" (0.8, 0.2, 0.05)\n");
			fflush(stdin);
			scanf(" %lf", &stepSize);
		} while (stepSize != 0.8 && stepSize != 0.2 && stepSize != 0.05);
		if (method == 1) {
			eulersMethod(stepSize);
		}
		else {
			rungeKutta(stepSize);
		}
	}

}
/********************************************************************
Function name:		eulersMethod
Purpose:			do math and print results
In parameters:		double h
Out parameters:		void
Version:			1.0
Author:				Joseph Trottier
**********************************************************************/
void eulersMethod(double h) {
	double y = 3, x = 0, exact, error=100;
	int loops = (int)(2.0 / h), i;

	printf("Time(s)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%%)\n");

	for (i = 0; i < loops; i++) {
		y += (h*(cos(4 * x) - 2 * y));
		x += h;
		exact = 0.1 * cos(4.0 * x) + 0.2 * sin(4.0 * x) + 2.9 * exp(-2.0 * x);
		error *= fabs((y - exact) / exact);
		printf("%0.1lf\t%0.3lf\t\t%0.3lf\t\t\t%0.2lf\n", x, exact, y, error);
		
		//reset values for next loop
		error = 100;
	}
}

/********************************************************************
Function name:		rungeKutta
Purpose:			do math for Runge-Kutta and print results
In parameters:		double h
Out parameters:		void
Version:			1.0
Author:				Joseph Trottier
**********************************************************************/
void rungeKutta(double h) {
	double runge1 = h, runge2 = h, runge3 = h, runge4 = h, error = 100, y = 3, t = 0, exact;
	int loops = (int)(2.0 / h);

	printf("Time(s)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%%)\n");

	for (int i = 0; i < loops; i++) {

		runge1 *= diff(t, y);
		runge2 *= diff(t + 0.5 * h, y + 0.5 * runge1);
		runge3 *= diff(t + 0.5 * h, y + 0.5 * runge2);
		runge4 *= diff(t + h, y + runge3);

		y = y + (1.0 / 6.0) * (runge1 + 2 * runge2 + 2 * runge3 + runge4);
		t += h;
		exact = 0.1 * cos(4 * t) + 0.2 * sin(4 * t) + 2.9 * exp(-2 * t);
		error *= fabs((y - exact) / exact);
		printf("%0.1lf\t%0.3lf\t\t%0.3lf\t\t\t%0.2lf\n", t, exact, y, error);
		
		//reset values for next loop
		error = 100;
		runge1 = h;
		runge2 = h;
		runge3 = h;
		runge4 = h;
	}
}

double diff(double x, double y) {
	double math = cos(4 * x) - 2 * y;
	return math;
}