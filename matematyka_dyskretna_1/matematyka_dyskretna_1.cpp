#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

string wejscie;

bool p, q, r;

const bool kon_c[4][3] = { {0,0,0},{0,1,0},{1,0,0},{1,1,1} };
const bool alt_c[4][3] = { {0,0,0},{0,1,1},{1,0,1},{1,1,1} };
const bool imp_c[4][3] = { {0,0,1},{0,1,1},{1,0,0},{1,1,1} };
const bool row_c[4][3] = { {0,0,1},{0,1,0},{1,0,0},{1,1,1} };

bool kon[4][3] = { {0,0,0},{0,1,0},{1,0,0},{1,1,1} };
bool alt[4][3] = { {0,0,0},{0,1,1},{1,0,1},{1,1,1} };
bool imp[4][3] = { {0,0,1},{0,1,1},{1,0,0},{1,1,1} };
bool row[4][3] = { {0,0,1},{0,1,0},{1,0,0},{1,1,1} };

//void copytab(int z) //ta metoda zajmuje wiele linijek kodu ale jest najszybszą z mozliwych
//{ 
//	switch (z)
//	{
//	case 0:
//		kon[0][0] = kon_c[0][0];
//		kon[0][1] = kon_c[0][1];
//		kon[0][2] = kon_c[0][2];
//		kon[1][0] = kon_c[1][0];
//		kon[1][1] = kon_c[1][1];
//		kon[1][2] = kon_c[1][0];
//		kon[2][0] = kon_c[2][0];
//		kon[2][1] = kon_c[2][1];
//		kon[2][2] = kon_c[2][2];
//		kon[3][0] = kon_c[3][0];
//		kon[3][1] = kon_c[3][1];
//		kon[3][2] = kon_c[3][2];
//		break;
//	case 1:
//		alt[0][0] = alt_c[0][0];
//		alt[0][1] = alt_c[0][1];
//		alt[0][2] = alt_c[0][2];
//		alt[1][0] = alt_c[1][0];
//		alt[1][1] = alt_c[1][1];
//		alt[1][2] = alt_c[1][0];
//		alt[2][0] = alt_c[2][0];
//		alt[2][1] = alt_c[2][1];
//		alt[2][2] = alt_c[2][2];
//		alt[3][0] = alt_c[3][0];
//		alt[3][1] = alt_c[3][1];
//		alt[3][2] = alt_c[3][2];
//		break;
//	case 2:
//		imp[0][0] = imp_c[0][0];
//		imp[0][1] = imp_c[0][1];
//		imp[0][2] = imp_c[0][2];
//		imp[1][0] = imp_c[1][0];
//		imp[1][1] = imp_c[1][1];
//		imp[1][2] = imp_c[1][0];
//		imp[2][0] = imp_c[2][0];
//		imp[2][1] = imp_c[2][1];
//		imp[2][2] = imp_c[2][2];
//		imp[3][0] = imp_c[3][0];
//		imp[3][1] = imp_c[3][1];
//		imp[3][2] = imp_c[3][2];
//		break;
//	case 3:
//
//		row[0][0] = row_c[0][0];
//		row[0][1] = row_c[0][1];
//		row[0][2] = row_c[0][2];
//		row[1][0] = row_c[1][0];
//		row[1][1] = row_c[1][1];
//		row[1][2] = row_c[1][0];
//		row[2][0] = row_c[2][0];
//		row[2][1] = row_c[2][1];
//		row[2][2] = row_c[2][2];
//		row[3][0] = row_c[3][0];
//		row[3][1] = row_c[3][1];
//		row[3][2] = row_c[3][2];
//		break;
//	default:
//		break;
//	}
//}

bool rachunek_logiczny(void)
{
	bool neg;
	short przypadek;
	int ilosc_P = 0, ilosc_Q = 0, ilosc_R = 0,ilosc_dzial = 0;
	int aski,aski1,askiN,askiL,askiP,wym_W,wym_K;
	if (wejscie.length() < 1) { return false; }

	for (int i = wejscie.length() - 1; i >= 0; i--)
	{
		aski = wejscie[i];

		if (aski == 80 || aski == 112) { ilosc_P += 1; }
		else if (aski == 81 || aski == 113) { ilosc_Q += 1; }
		else if (aski == 82 || aski == 114) { ilosc_R += 1; }
		else if (aski == 78 || aski == 110 || aski == 68 || aski == 100 || aski == 67 || aski == 99 || aski == 73 || aski == 105 || aski == 69 || aski == 101) { ilosc_dzial += 1; }
	}
	if (ilosc_dzial == 0) { return false; }

	if (ilosc_P != 0 && ilosc_Q == 0 && ilosc_R == 0 || ilosc_P == 0 && ilosc_Q != 0 && ilosc_R == 0 || ilosc_P == 0 && ilosc_Q == 0 && ilosc_R != 0) { wym_W = 2; przypadek = 1; }
	else if (ilosc_P != 0 && ilosc_Q != 0 && ilosc_R == 0) { wym_W = 4; przypadek = 1; } // PQ
	else if (ilosc_P != 0 && ilosc_Q == 0 && ilosc_R != 0) { wym_W = 4; przypadek = 1; } // PR
	else if (ilosc_P == 0 && ilosc_Q != 0 && ilosc_R != 0) { wym_W = 4; przypadek = 3; } // QR
	else { wym_W = 8; }
	wym_K = ilosc_dzial + !!ilosc_P + !!ilosc_Q + !!ilosc_R;

	bool** tabelaprawdy = new bool*[wym_W];
	for (int i = 0; i < wym_W; i++) { tabelaprawdy[i] = new bool[wym_K]; }
	if (wym_W == 2) {
		tabelaprawdy[0][0] = 1; tabelaprawdy[1][0] = 0;
	} else if (wym_W == 4) {
		tabelaprawdy[0][0] = 0; tabelaprawdy[1][0] = 0; tabelaprawdy[2][0] = 1; tabelaprawdy[3][0] = 1;
		tabelaprawdy[0][1] = 0; tabelaprawdy[1][1] = 1; tabelaprawdy[2][1] = 0; tabelaprawdy[3][1] = 1;
	} else {
		tabelaprawdy[0][0] = 0; tabelaprawdy[1][0] = 0; tabelaprawdy[2][0] = 1; tabelaprawdy[3][0] = 1; tabelaprawdy[4][0] = 0; tabelaprawdy[5][0] = 0; tabelaprawdy[6][0] = 1; tabelaprawdy[7][0] = 1;
		tabelaprawdy[0][1] = 0; tabelaprawdy[1][1] = 1; tabelaprawdy[2][1] = 0; tabelaprawdy[3][1] = 1; tabelaprawdy[4][1] = 0; tabelaprawdy[5][1] = 1; tabelaprawdy[6][1] = 0; tabelaprawdy[7][1] = 1;
		tabelaprawdy[0][2] = 0; tabelaprawdy[1][2] = 0; tabelaprawdy[2][2] = 0; tabelaprawdy[3][2] = 0; tabelaprawdy[4][2] = 1; tabelaprawdy[5][2] = 1; tabelaprawdy[6][2] = 1; tabelaprawdy[7][2] = 1;
	}



	for (int i = 0; i < wejscie.length(); i++)
	{
		aski1 = wejscie[i];

		switch (aski1)
		{
		case 78:
		case 110: //N ,~ - negacja
			int dodajaca;
			askiP = wejscie[i + 1];
			if (wym_W == 2) {
				tabelaprawdy[0][i + 1] = !tabelaprawdy[0][0];
				tabelaprawdy[1][i + 1] = !tabelaprawdy[1][0];
			}
			else if (wym_W == 4) {
				if (przypadek == 1) { // PQ , PR
					if (askiP == 80 || askiP == 112) {
						for (short i = 0; i < 4; i++) tabelaprawdy[i][i + 2] = !tabelaprawdy[i][0];
					} else {
						for (short i = 0; i < 4; i++) tabelaprawdy[i][i + 2] = !tabelaprawdy[i][1];
					}
				}
				if (przypadek == 3) { // QR
					if (askiP == 81 || askiP == 113) {
						for (short i = 0; i < 4; i++) tabelaprawdy[i][i + 2] = !tabelaprawdy[i][0];
					} else {
						for (short i = 0; i < 4; i++) tabelaprawdy[i][i + 2] = !tabelaprawdy[i][1];
					}
				}
			}
			else {
				if (askiP == 80 || askiP == 112) {//P
					for (short i = 0; i < 8; i++) tabelaprawdy[i][i + 3] = !tabelaprawdy[i][0];
				} else if (askiP == 81 || askiP == 113){//Q
					for (short i = 0; i < 8; i++) tabelaprawdy[i][i + 3] = !tabelaprawdy[i][1];
				} else {//R
					for (short i = 0; i < 8; i++) tabelaprawdy[i][i + 3] = !tabelaprawdy[i][2];
				}

			}
			break;
		case 68:
		case 100: //D ,v - alternatywa
			askiL = wejscie[i - 1];
			askiP = wejscie[i + 1];
			if (askiP == 78 || askiP == 110) {
				alt[0][i + 4] = !alt[0][0];
				alt[1][0] = !alt[1][0];
				alt[2][0] = !alt[2][0];
				alt[3][0] = !alt[3][0];
				askiP = wejscie[i + 2];
				i += 1;
			}

			for (short i = 0; i < 4; i++)
			{
				if (alt[i][0] == 0 && alt[i][1] == 0) { alt[i][2] = 0; }
				else { alt[i][2] = 1; }
			}

			if (askiP != askiL)
			{

			}

			break;
		case 67:
		case 99: //C ,^ - koniukcja
			askiL = wejscie[i - 1];
			askiP = wejscie[i + 1];
			



			break;
		case 73:
		case 105: //I ,=> - implikacja
			cout << "I - implikacja" << endl;


			break;
		case 69:
		case 101: //E, <=> - równoważnosc
			break;
		default:
			break;
		}
	}


	return true;
}

int main()
{
	
	cin >> wejscie;
	
	rachunek_logiczny();

	cout << "Program autorstwa Grzegorz Szwarc" << endl;
}
