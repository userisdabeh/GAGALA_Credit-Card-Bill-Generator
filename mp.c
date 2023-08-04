/***************************************************************************************
This is to certify that this project is my own work, based on my personal efforts
in studying and applying the concepts learned. I have constructed the
functions and their respective algorithms and corresponding code by myself.
The program was run, tested, and debugged by my own efforts. I further
certify that I have not copied in part or whole or otherwise plagiarized the
work of other students and/or persons.
                                              Dave Anthony P. Gagala, DLSU ID# 12207314
***************************************************************************************/


/*
	Description: This program
	Programmed by: Dave Anthony Gagala, S16
	Last modified: July 31, 2023
	Version: 3.7
	Acknowledgements:
		[1] https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a (ANSI Color Codes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void displayMenu (float);

void AddPurchase (float limit, int * points, float * purchase)
{
	float amt;
	char choi;
	
	system("cls");
	
	do
	{
		printf ("\e[0;37m""Input amount of purchase: ");
		scanf (" %f", &amt);
		
		if (amt < 0 || amt >= (limit * 2))
		{
			printf ("\e[0;31m""\tInvalid Input. Please try again.\n");
		}
		else
		{
			*purchase += amt;
			*points += (int)(amt / 30);
			printf ("\e[0;32m""\tSuccess! Purchase Added. ");
			printf ("\e[0;37m""Total points: %d Would you like to add another purchase (y/n)? ", *points);
			scanf (" %c", &choi);
			
			if (choi == 'N' || choi == 'n')
				displayMenu(limit);
		}
	} while (amt < 0 || amt >= (limit * 2) || choi == 'Y' || choi == 'y');
}

void viewPrevious(float limit, float prevdue, float prevbal)
{
	char choiceko;
	
	system("cls");
		
	do
	{
		printf ("\e[0;37m""Your previous balance is:\t.2%f\n", prevbal);
		printf ("\e[0;37m""Your previous minimum amount due is:\t.2%f\n\n", prevdue);
	
		printf ("Go back to main menu (y): ");
		scanf (" %c", &choiceko);
	
		if (choiceko == 'y' || choiceko == 'Y')
			displayMenu(limit);
	} while (choiceko != 'y' && choiceko != 'Y');
}

void makePayment (float limit, float * payments)
{
	float pay = 0;
	char cho;
	
	system("cls");
	
	do
	{
		printf ("\e[0;37m""Input amount of payment: ");
		scanf ("%f", &pay);
		
		if (pay < 0)
			printf ("\e[0;31m""\tInvalid Input. Please try again.\n ");
		else
		{
			*payments += pay;
			printf ("\e[0;32m""\tSuccess! Payment Added. ");
			printf ("\e[0;37m""Would you like to add another payment (y/n)? ");
			scanf (" %c", &cho);
			
			if (cho == 'n' || cho == 'N')
				displayMenu(limit);
		}
	} while (pay < 0 || cho == 'y' || cho == 'Y');
}

void viewRewards (float limit, int points)
{
	char choicerewards;
	
	system ("cls");
	
	do
	{
		printf ("\e[0;37m""Your total rewards points is:\t%d\n", points);
		Sleep(3000);
		printf ("\e[0;37m""Would you like to go back to main menu (y/n)? ");
		scanf (" %c", &choicerewards);
		
		if (choicerewards == 'y' || choicerewards == 'Y')
			displayMenu(limit);
		else
			printf ("\n");
	} while (choicerewards == 'n' || choicerewards ==  'N');
}

void useRewards (float limit, int * used, int * points)
{
	int opt;
	
	system ("cls");
	
	do
	{
		if (*points >= 1000)
		{
			printf ("\e[0;37m""[1] Php 100 eGift Voucher (1000 points)\n");
			printf ("\e[0;37m""[2] Php 100 credits (1000 points)\n");
			printf ("\e[0;37m""[3] Cancel\n\n");
			printf ("\e[0;37m""Input option: ");
			scanf (" %d", &opt);
			
			switch (opt)
			{
				case 1:
				case 2:
					*used += 1000;
					*points -= 1000;
					printf ("\e[0;37m""Processing request. Please wait for confirmation message\n");
					Sleep(3000);
					printf ("\e[0;32m""\tSuccess!\n");
					printf ("\e[0;37m""\tYou have used %d points. Your remaining balance is %d points\n", *used, *points);
					Sleep(3000);
				case 3:
					displayMenu(limit);
					break;
				default:
					printf ("\e[0;31m""Warning! ");
					printf ("\e[0;37m""You have entered an invalid option.");
			}
		}
		else
		{
			printf ("\e[0;31m""Warning! ");
			printf ("\e[0;37m""There is not enough points to claim anything at the moment. You only have %d points. \n\tPlease come back at a later time\n", *points);
			printf ("You will now be redirected back to the main menu.");
			Sleep(3000);
			displayMenu(limit);
		}
	} while (opt != 1 && opt != 2);
}

void endCycle(float limit, float * prevbal, float * payments, float * purchase, float fin_charge, float out_bal, float min_due, float late_charge, float total_due, int * prevbal_points, int * points, int * used, int * total_points, int * cycle)
{
	char newchoice;
	
	system("cls");
	
	printf ("Previous Balance:\t\t%15.2f\n", *prevbal);
	printf ("Payments/Credits:\t\t%15.2f\n", *payments);
	printf ("Purchases:\t\t\t%15.2f\n", *purchase);
	
	if (out_bal > limit)
		fin_charge += 500;
	
	if (*payments < *prevbal)
		fin_charge += (*prevbal - *payments) * 0.03;
	
	printf ("Finance Charges:\t\t%15.2f\n", fin_charge);
	
	if (min_due > *payments)
		late_charge += *prevbal - *payments;
		
	printf ("Late Payment Charges:\t\t%15.2f\n", late_charge);
	
	total_due = out_bal + fin_charge + late_charge;
	
	printf ("Total Amount Due:\t\t%15.2f\n", total_due);
	
	if (total_due <= 850)
		min_due = total_due;
	else
		min_due = total_due * 0.0357;
		
	printf ("Minimum Amount Due:\t\t%15.2f\n", min_due);
	
	printf ("Previous Cards Points Balance:\t\t   %d\n", *prevbal_points);
	printf ("Current Points Earned:\t\t\t   %d\n", *points);
	printf ("Points Used:\t\t\t\t   %d\n", *used);
	printf ("Total Credit Points:\t\t\t   %d", *total_points);
	
	printf ("\n\nWould you like to start a new billing cycle (y/n)? ");
	scanf (" %c", &newchoice);
	
	if (newchoice == 'Y' || newchoice == 'y')
	{
		*prevbal = total_due;
		*prevbal_points = *total_points;
		*points = 0;
		*used = 0;
		*purchase = 0;
		*payments = 0;
		*cycle += 1;
		displayMenu(limit);
	}
}

void getCreditLimit(float * limit)
{
	do
	{
		printf ("Input Credit Limit in Php: ");
		scanf ("%f", limit);
	} while (*limit < 0);
}

void displayMenu (float limit)
{
	int choice;
	static int used, points, cycle, total_points = 0, prevbal_points;
	static float payments, mindue, prev_bal, purchase, fin_charge, out_bal, late_charge, total_due, min_due, prev_mindue;
	
	do
	{
		system("cls");
		printf ("\e[0;37m""[1] Add Purchase\n");
		printf ("\e[0;37m""[2] View Previous Statement\n");
		printf ("\e[0;37m""[3] Make Payment\n");
		printf ("\e[0;37m""[4] View Rewards Points\n");
		printf ("\e[0;37m""[5] Use Rewards Points\n");
		printf ("\e[0;37m""[6] End Billing Cycle\n");
		printf ("\e[0;37m""[7] Exit\n");
		printf("\n");
		printf ("\e[0;37m""Input option: ");
		scanf (" %d", &choice);	
		
		if (choice < 1 || choice > 7)
		{
			printf ("\e[0;31m""Warning! You have inputted an invalid option. You will be redirected to the home page in 3 secconds.");
			Sleep(3000);
		}
		else
		{
			switch (choice)
			{
				case 1:
					AddPurchase(limit, &points, &purchase);
					break;
				case 2:
					viewPrevious(limit, mindue, prev_bal);
					break;
				case 3:
					makePayment(limit, &payments);
					break;
				case 4:
					viewRewards(limit, points);
					break;
				case 5:
					useRewards(limit, &used, &points);
					break;
				case 6:
					endCycle(limit, &prev_bal, &payments, &purchase, fin_charge, out_bal, mindue, late_charge, total_due, &prevbal_points, &points, &used, &total_points, &cycle);
					break;
				case 7:
					break;
			}
		}
	} while (choice < 1 || choice > 7);
}

int main ()
{
	float limit;
	
	getCreditLimit(&limit);
	displayMenu(limit);
	
	return 0;
}
