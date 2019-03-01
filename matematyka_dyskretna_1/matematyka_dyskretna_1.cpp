#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

string wejscie;

const bool kon_c[4][3] = { {0,0,0},{0,1,0},{1,0,0},{1,1,1} };
const bool alt_c[4][3] = { {0,0,0},{0,1,1},{1,0,1},{1,1,1} };
const bool imp_c[4][3] = { {0,0,1},{0,1,1},{1,0,0},{1,1,1} };
const bool row_c[4][3] = { {0,0,1},{0,1,0},{1,0,0},{1,1,1} };

bool kon[4][3] = { {0,0,0},{0,1,0},{1,0,0},{1,1,1} };
bool alt[4][3] = { {0,0,0},{0,1,1},{1,0,1},{1,1,1} };
bool imp[4][3] = { {0,0,1},{0,1,1},{1,0,0},{1,1,1} };
bool row[4][3] = { {0,0,1},{0,1,0},{1,0,0},{1,1,1} };

void copytab(int z) //ta metoda zajmuje wiele linijek kodu ale jest najszybszą z mozliwych
{ 
	switch (z)
	{
	case 0:
		kon[0][0] = kon_c[0][0];
		kon[0][1] = kon_c[0][1];


		kon[0][2] = kon_c[0][2];
		kon[1][0] = kon_c[1][0];
		kon[1][1] = kon_c[1][1];
		kon[1][2] = kon_c[1][0];
		kon[2][0] = kon_c[2][0];
		kon[2][1] = kon_c[2][1];
		kon[2][2] = kon_c[2][2];
		kon[3][0] = kon_c[3][0];
		kon[3][1] = kon_c[3][1];
		kon[3][2] = kon_c[3][2];
		break;
	case 1:
		alt[0][0] = alt_c[0][0];
		alt[0][1] = alt_c[0][1];
		alt[0][2] = alt_c[0][2];
		alt[1][0] = alt_c[1][0];
		alt[1][1] = alt_c[1][1];
		alt[1][2] = alt_c[1][0];
		alt[2][0] = alt_c[2][0];
		alt[2][1] = alt_c[2][1];
		alt[2][2] = alt_c[2][2];
		alt[3][0] = alt_c[3][0];
		alt[3][1] = alt_c[3][1];
		alt[3][2] = alt_c[3][2];
		break;
	case 2:
		imp[0][0] = imp_c[0][0];
		imp[0][1] = imp_c[0][1];
		imp[0][2] = imp_c[0][2];
		imp[1][0] = imp_c[1][0];
		imp[1][1] = imp_c[1][1];
		imp[1][2] = imp_c[1][0];
		imp[2][0] = imp_c[2][0];
		imp[2][1] = imp_c[2][1];
		imp[2][2] = imp_c[2][2];
		imp[3][0] = imp_c[3][0];
		imp[3][1] = imp_c[3][1];
		imp[3][2] = imp_c[3][2];
		break;
	case 3:

		row[0][0] = row_c[0][0];
		row[0][1] = row_c[0][1];
		row[0][2] = row_c[0][2];
		row[1][0] = row_c[1][0];
		row[1][1] = row_c[1][1];
		row[1][2] = row_c[1][0];
		row[2][0] = row_c[2][0];
		row[2][1] = row_c[2][1];
		row[2][2] = row_c[2][2];
		row[3][0] = row_c[3][0];
		row[3][1] = row_c[3][1];
		row[3][2] = row_c[3][2];
		break;
	default:
		break;
	}
}

void operatory(void)
{
	bool neg;
	int aski,askiN,askiL,askiP;
	for (int i = 0; i < wejscie.length(); i++)
	{
		aski = wejscie[i];

		switch (aski)
		{
		case 78:
		case 110: //N - negacja
			//askiN = wejscie[i+1];
			//if (!(askiN == 80 || askiN == 112 || askiN == 81 || askiN == 113 || askiN == 82 || askiN == 114)) { exit(EXIT_FAILURE); }
			neg = true;
			break;
		case 68:
		case 100: //D - alternatywa
			askiL = wejscie[i - 1];
			askiP = wejscie[i + 1];
			if (neg == true) {
				alt[0][0] = !alt[0][0];
				alt[1][0] = !alt[1][0];
				alt[2][0] = !alt[2][0];
				alt[3][0] = !alt[3][0];
			}
			if (askiP == 78 || askiP == 110) {
				alt[0][1] = !alt[0][1];
				alt[1][1] = !alt[1][1];
				alt[2][1] = !alt[2][1];
				alt[3][1] = !alt[3][1];
				askiP = wejscie[i + 2];
			}
			


			break;
		case 67:
		case 99: //C - koniukcja
			askiL = wejscie[i - 1];
			askiP = wejscie[i + 1];
			if (neg == true) {
				kon[0][0] = !kon[0][0];
				kon[1][0] = !kon[1][0];
				kon[2][0] = !kon[2][0];
				kon[3][0] = !kon[3][0];
			}
			if (askiP == 78 || askiP == 110) {
				kon[0][1] = !kon[0][1];
				kon[1][1] = !kon[1][1];
				kon[2][1] = !kon[2][1];
				kon[3][1] = !kon[3][1];
				askiP = wejscie[i + 2];
			}



			break;
		case 73:
		case 105: //I - implikacja
			cout << "I - implikacja" << endl;


			break;
		case 69:
		case 101: //E - równoważnosc
			break;
		default:

			break;
		}
	}
}

int main()
{
	
	cin >> wejscie;
	
	operatory();

	cout << "Program autorstwa Grzegorz Szwarc" << endl;
}
