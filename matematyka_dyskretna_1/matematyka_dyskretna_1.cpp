#include "pch.h"
#include <iostream>
#include <string>

#define DBG 0

using namespace std;

string wejscie;

bool** tabelaprawdy;

short zw_1[8], zw_2[8], zw_3[8];
short wym_W, wym_K,przypadek, ilosc_false = -1;


void podglad_tabeli_dbg(bool** &tabelaprawdy)
{
	for (int i = 0; i < wym_W; i++)
	{
		for (int k = 0; k < wym_K; k++)
		{
			cout << tabelaprawdy[i][k] << "  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}

inline void negacja(short &a,int &przebieg,short &przy,int &litera, bool** &tabelaprawdy) //liczba wierszy,ktore dzialanie z kolei, przypadek dla 2 litera, odniesienie do litery
{
	if (a == 2) {
		tabelaprawdy[0][przebieg] = !tabelaprawdy[0][0];
		tabelaprawdy[1][przebieg] = !tabelaprawdy[1][0];
	}
	else if (a == 4) {
		if (przy == 1 || przy == 2) { // PQ , PR
			if (litera == 80 || litera == 112) {
				for (short i = 0; i < 4; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][0];
			}
			else {
				for (short i = 0; i < 4; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][1];
			}
		}
		if (przy == 3) { // QR
			if (litera == 81 || litera == 113) {
				for (short i = 0; i < 4; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][0];
			}
			else {
				for (short i = 0; i < 4; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][1];
			}
		}
	}
	else {
		if (litera == 80 || litera == 112) {//P
			for (short i = 0; i < 8; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][0];
		}
		else if (litera == 81 || litera == 113) {//Q
			for (short i = 0; i < 8; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][1];
		}
		else {//R
			for (short i = 0; i < 8; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][2];
		}
	}
	przebieg += 1;
}

bool rachunek_logiczny(void)
{
	bool neg;
	short rodz_litera = 10,litera = 0;
	int aski, aski1, askiN, askiL, askiP,dodajaca, ilosc_dzial = 0,ilosc_P = 0, ilosc_Q = 0, ilosc_R = 0;
	if (wejscie.length() < 1) { return false; }

	for (int i = (wejscie.length() - 1); i >= 0; i--)
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
	else if (ilosc_P != 0 && ilosc_Q == 0 && ilosc_R != 0) { wym_W = 4; przypadek = 2; } // PR
	else if (ilosc_P == 0 && ilosc_Q != 0 && ilosc_R != 0) { wym_W = 4; przypadek = 3; } // QR
	else { wym_W = 8; }
	wym_K = ilosc_dzial + !!ilosc_P + !!ilosc_Q + !!ilosc_R;
	int przebieg = !!ilosc_P + !!ilosc_Q + !!ilosc_R;

	if (wejscie[0] != 78 && wejscie[0] != 110) { wym_K += 1; przebieg += 1; }

	//tworzenie tablicy dynamicznej
	bool** tabelaprawdy = new bool*[wym_K];
	for (int i = 0; i < wym_W; i++) { tabelaprawdy[i] = new bool[wym_W]; }

	if (wym_W == 2) {
		tabelaprawdy[0][0] = 1; tabelaprawdy[1][0] = 0; rodz_litera = 0;
	} else if (wym_W == 4) {
		tabelaprawdy[0][0] = 0; tabelaprawdy[1][0] = 0; tabelaprawdy[2][0] = 1; tabelaprawdy[3][0] = 1;
		tabelaprawdy[0][1] = 0; tabelaprawdy[1][1] = 1; tabelaprawdy[2][1] = 0; tabelaprawdy[3][1] = 1;
	} else {
		tabelaprawdy[0][0] = 0; tabelaprawdy[1][0] = 0; tabelaprawdy[2][0] = 1; tabelaprawdy[3][0] = 1; tabelaprawdy[4][0] = 0; tabelaprawdy[5][0] = 0; tabelaprawdy[6][0] = 1; tabelaprawdy[7][0] = 1;
		tabelaprawdy[0][1] = 0; tabelaprawdy[1][1] = 1; tabelaprawdy[2][1] = 0; tabelaprawdy[3][1] = 1; tabelaprawdy[4][1] = 0; tabelaprawdy[5][1] = 1; tabelaprawdy[6][1] = 0; tabelaprawdy[7][1] = 1;
		tabelaprawdy[0][2] = 0; tabelaprawdy[1][2] = 0; tabelaprawdy[2][2] = 0; tabelaprawdy[3][2] = 0; tabelaprawdy[4][2] = 1; tabelaprawdy[5][2] = 1; tabelaprawdy[6][2] = 1; tabelaprawdy[7][2] = 1;
	}

	if (wejscie[0] != 78 && wejscie[0] != 110)
	{
		if (przypadek == 1 || przypadek == 2) {
			if (wejscie[0] == 80 || wejscie[0] == 112) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][2] = tabelaprawdy[j][0]; }
			else { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][2] = tabelaprawdy[j][1]; }
		}
		else if (przypadek == 3)
		{
			if (wejscie[0] == 81 || wejscie[0] == 113) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][2] = tabelaprawdy[j][0]; }
			else { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][2] = tabelaprawdy[j][1]; }
		}
		else
		{
			if (wejscie[0] == 820 || wejscie[0] == 112) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][3] = tabelaprawdy[j][0]; }
			else if (wejscie[0] == 81 || wejscie[0] == 113) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][3] = tabelaprawdy[j][1]; }
			else { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][3] = tabelaprawdy[j][2]; }
		}
	}

#if DBG==1 
	podglad_tabeli_dbg(tabelaprawdy);
#endif

	for (int i = 0; i < wejscie.length(); i++)
	{
		aski1 = wejscie[i];

		switch (aski1)
		{
		case 78:
		case 110: //N ,~ - negacja
			askiP = wejscie[i + 1];
			negacja(wym_W,przebieg,przypadek, askiP,tabelaprawdy);
			break;
		case 68:
		case 100: //D ,v - alternatywa
			if (i == 0) { askiL = wejscie[i - 1]; }
			else { askiL = 0; }
			askiP = wejscie[i + 1];
			
			if (askiP == 78 || askiP == 110) {
				negacja(wym_W,przebieg,przypadek, askiP,tabelaprawdy);
				for (short m = 0; m < wym_W; m++)
				{
					if ((tabelaprawdy[m][przebieg - 2] == 0) && (tabelaprawdy[m][przebieg - 1] == 0)) { tabelaprawdy[m][przebieg] = 0; }
					else { tabelaprawdy[m][przebieg] = 1; }
				}
				i++;
			}
			else
			{
				if (rodz_litera != 0) 
				{
					if (przypadek == 1 || przypadek == 2) {
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else { litera = 1; }
					}
					else if (przypadek == 3)
					{
						if (askiP == 81 || askiP == 113) { litera = 0; }
						else { litera = 1; }
					}
					else 
					{
						if (askiP == 820 || askiP == 112) { litera = 0; }
						else if (askiP == 81 || askiP == 113) { litera = 1; }
						else { litera = 2; }
					}
				}
				for (short j = 0; j < wym_W; j++)
				{
					if ((tabelaprawdy[j][przebieg - 1] == 0) && (tabelaprawdy[j][litera] == 0)) { tabelaprawdy[j][przebieg] = 0; }
					else { tabelaprawdy[j][przebieg] = 1; }
				}
			}
			
			przebieg += 1;
			break;
		case 67:
		case 99: //C ,^ - koniukcja
			if (i == 0) { askiL = wejscie[i - 1]; }
			else { askiL = 0; }
			askiP = wejscie[i + 1];

			if (askiP == 78 || askiP == 110) {
				negacja(wym_W, przebieg, przypadek, askiP, tabelaprawdy);
				for (short m = 0; m < wym_W; m++)
				{
					if (tabelaprawdy[m][przebieg - 2] == 1 && tabelaprawdy[m][przebieg - 1] == 1) { tabelaprawdy[m][przebieg] = 1; }
					else { tabelaprawdy[m][przebieg] = 0; }
				}
				i++;
			}
			else
			{
				if (rodz_litera != 0) {
					if (przypadek == 1 || przypadek == 2) {
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else { litera = 1; }
					}
					else if (przypadek == 3)
					{
						if (askiP == 81 || askiP == 113) { litera = 0; }
						else { litera = 1; }
					}
					else
					{
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else if (askiP == 81 || askiP == 113) { litera = 1; }
						else { litera = 2; }
					}
				}
				for (short j = 0; j < wym_W; j++)
				{
					if (tabelaprawdy[j][przebieg - 1] == 1 && tabelaprawdy[j][litera] == 1) { tabelaprawdy[j][przebieg] = 1; }
					else { tabelaprawdy[j][przebieg] = 0; }
				}
			}
			break;
		case 73:
		case 105: //I ,=> - implikacja
			if (i == 0) { askiL = wejscie[i - 1]; }
			else { askiL = 0; }
			askiP = wejscie[i + 1];


			if (askiP == 78 || askiP == 110) {
				negacja(wym_W, przebieg, przypadek, askiP, tabelaprawdy);
				for (short m = 0; m < wym_W; m++)
				{
					if (tabelaprawdy[m][przebieg - 2] == 1 && tabelaprawdy[m][przebieg - 1] == 0) { tabelaprawdy[m][przebieg] = 0; }
					else { tabelaprawdy[m][przebieg] = 1; }
				}
				i++;
			}
			else
			{
				if (rodz_litera != 0)

				{
					if (przypadek == 1 || przypadek == 2) {
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else { litera = 1; }
					}
					else if (przypadek == 3)
					{
						if (askiP == 81 || askiP == 113) { litera = 0; }
						else { litera = 1; }
					}
					else
					{
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else if (askiP == 81 || askiP == 113) { litera = 1; }
						else { litera = 2; }
					}
				}
				for (short j = 0; j < wym_W; j++)
				{
					if (tabelaprawdy[j][przebieg - 1] == 1 && tabelaprawdy[j][litera] == 0) { tabelaprawdy[j][przebieg] = 0; }
					else { tabelaprawdy[j][przebieg] = 1; }
				}
			}

			przebieg += 1;
			break;
		case 69:
		case 101: //E, <=> - równoważnosc
			if (i == 0) { askiL = wejscie[i - 1]; }
			else { askiL = 0; }
			askiP = wejscie[i + 1];

			if (askiP == 78 || askiP == 110) {
				negacja(wym_W, przebieg, przypadek, askiP, tabelaprawdy);
				for (short m = 0; m < wym_W; m++)
				{
					if ((tabelaprawdy[m][przebieg - 2] == 1 && tabelaprawdy[m][przebieg - 1] == 1) || (tabelaprawdy[m][przebieg - 2] == 0 && tabelaprawdy[m][przebieg - 1] == 0)) { tabelaprawdy[m][przebieg] = 1; }
					else { tabelaprawdy[m][przebieg] = 0; }
				}
				i++;
			}
			else
			{
				if (rodz_litera != 0) {
					if (przypadek == 1 || przypadek == 2) {
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else { litera = 1; }
					}
					else if (przypadek == 3)
					{
						if (askiP == 81 || askiP == 113) { litera = 0; }
						else { litera = 1; }
					}
					else
					{
						if (askiP == 80 || askiP == 112) { litera = 0; }
						else if (askiP == 81 || askiP == 113) { litera = 1; }
						else { litera = 2; }
					}
				}
				for (short j = 0; j < wym_W; j++)
				{
					if ((tabelaprawdy[j][przebieg - 1] == 0 && tabelaprawdy[j][litera] == 0) || (tabelaprawdy[j][przebieg - 1] == 1 && tabelaprawdy[j][litera] == 1)) { tabelaprawdy[j][przebieg] = 1; }
					else { tabelaprawdy[j][przebieg] = 0; }
				}
			}
			break;
		default:
			break;
		}
#if DBG==1 
		podglad_tabeli_dbg(tabelaprawdy);
#endif
	}

	podglad_tabeli_dbg(tabelaprawdy);

	short ilosc_zmiennych = !!ilosc_P + !!ilosc_Q + !!ilosc_R;
	for (short j = 0; j < wym_W; j++)
	{
		if (tabelaprawdy[j][wym_K - 1] == 0) { break; }
		if (j == wym_W - 1) { return true; }
	}
	//wykonuje sie jesli false
	for (short j = 0; j < wym_W; j++)
	{
		if (tabelaprawdy[j][wym_K - 1] == 0) 
		{
			ilosc_false += 1;
			if (ilosc_zmiennych == 1) { zw_1[ilosc_false] = tabelaprawdy[j][0]; }
			else if (ilosc_zmiennych == 2) {
				zw_1[ilosc_false] = tabelaprawdy[j][0];
				zw_2[ilosc_false] = tabelaprawdy[j][1];
			} else {
				zw_1[ilosc_false] = tabelaprawdy[j][0];
				zw_2[ilosc_false] = tabelaprawdy[j][1];
				zw_3[ilosc_false] = tabelaprawdy[j][2];
			}
		}
	}
	return false;
}

int main()
{
	short h = 0;
	
	cin >> wejscie;
	
	if (rachunek_logiczny() == true) 
	{
		cout << endl;
		cout << " Podane zdanie logiczne jest tautologią !" << endl;
		cout << endl;
	}
	else
	{
		cout << "Podane zdanie logiczne nie jest tatuologią dla: " << endl;
		if (wym_W == 2) { for (short i = 0; i < ilosc_false; i++) cout << "P= " << zw_1[i] << endl; }
		else if (wym_W == 4)
		{
			if (przypadek == 1) { for (short i = 0; i < ilosc_false; i++) cout << "P= " << zw_1[i] << ", Q= " << zw_2[i] << endl; }
			else if (przypadek == 2) { for (short i = 0; i < ilosc_false; i++) cout << "P= " << zw_1[i] << ", R= " << zw_2[i] << endl; }
			else { for (short i = 0; i < ilosc_false; i++) cout << "Q= " << zw_1[i] << ", R= " << zw_2[i] << endl; }
		}
		else
		{
			for (short i = 0; i < ilosc_false; i++)
			{
				cout << "P= " << zw_1[i] << ", Q= " << zw_2[i] << ", R= " << zw_3[i];
			}
	}

	}

	cout << "Program autorstwa Grzegorz Szwarc" << endl;
	system("pause");
}
