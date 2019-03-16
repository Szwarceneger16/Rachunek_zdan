#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>

#define DBG 0
using namespace std;

const string nazwa_pliku = "badanie_zdań_logicznych.txt";
string wejscie,tryb;
bool** tabelaprawdy;
short wym_W, wym_K=0,przypadek = 10,rodz_litera = 10,ilosc_P, ilosc_Q, ilosc_R, ilosc_dzialan = 0;
bool tryb_zaawansowany = false;
clock_t start, stop;
double czas;

bool pobierz_dane_plik(void)
{
	fstream plik(nazwa_pliku, ios::in);
	if (plik.good())
	{
		getline(plik, wejscie);
		getline(plik, tryb);
		if (!tryb.empty())
		{
			tryb = tryb[0];
			if (stoi(tryb) == 1) { tryb_zaawansowany = true; }
		}
		plik.close();
		return true;
	}
	plik.close();
	return false;
}

void utworz_plik(void)
{
	fstream plik_wejsciowy(nazwa_pliku,ios::out);
	plik_wejsciowy << "pcq" << endl << "0" <<endl;
	plik_wejsciowy << "==============================================================================================================" << endl;
	plik_wejsciowy << "Instrukcja wprowadzania danych do programu:" << endl;
	plik_wejsciowy << "   W pierwszej linijce należy wprowadzić zdanie logiczne zgodnie z konwencją zmienna-dzialanie-zmienna-dzialanie-zmienna ... itd."<< endl;
	plik_wejsciowy << "   Czyli wymagana jest konstrukcja (np. pCq) ,wielkość liter nie ma znaczenia." << endl;
	plik_wejsciowy << "   Każda zmienna może dodatkowo być poprzedzona negacją (np. NpCNq)." << endl;
	plik_wejsciowy << "   Program nie obsługuje nawiasów, wykonuje działania zgodnie z zasadami kolejności wykonywania działań,"<< endl;
	plik_wejsciowy << "   dla działań równorzednych w kolejności od lewej do prawej. " << endl;
	plik_wejsciowy << "		 LEGENDA działań: " << endl;
	plik_wejsciowy << "   N (negation - negacja)" << endl;
	plik_wejsciowy << "   D (disjunction - alternatywa) " << endl;
	plik_wejsciowy << "   C (conjunction – koniunkcja)" << endl;
	plik_wejsciowy << "   I (implication – implikacja)" << endl;
	plik_wejsciowy << "   E (equivalence – równoważnośd)" << endl << endl;
	plik_wejsciowy << "W drugiej linijce liczba decyduje o włączeniu trybu zaawansowanego, powoduje to wyświetlenie tabeli prawdy" << endl;
	plik_wejsciowy << "   0 (wyłączony tryb zaawansowany - domyślny)" << endl;
	plik_wejsciowy << "   1 (włączony tryb zaawansowany)" << endl;
	plik_wejsciowy.close();
	return;
}

void podglad_tabeli_dbg(bool** &tabelaprawdy)
{
	cout << endl << endl;
	if (wym_W == 2) { cout << "P  "<<endl; }
	else if (wym_W == 8) { cout << "P  Q  R" << endl; }
	else
	{
		if (przypadek == 1) { cout << "P  Q" << endl; }
		else if (przypadek == 2) { cout << "P  R" << endl; }
		else if (przypadek == 3) { cout << "Q  R" << endl; }
	}
	for (int i = 0; i < wym_W; i++)
	{
		for (int k = 0; k < wym_K; k++)
		{
			cout << tabelaprawdy[i][k] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

short kolejnosc_dzialan(short start)
{
	int aski;
	for (int i = start; i < wejscie.length(); i++)
	{
		aski = wejscie[i];
		if (aski == 69 || aski == 101 || aski == 73 || aski == 105) { return i; }
	}
	return wejscie.length()-1;
}

void negacja(short &przebieg,int &litera, bool** &tabelaprawdy) //liczba wierszy,ktore dzialanie z kolei, przypadek dla 2 litera, odniesienie do litery
{
	if (wym_W == 2) {
		tabelaprawdy[0][przebieg] = !tabelaprawdy[0][0];
		tabelaprawdy[1][przebieg] = !tabelaprawdy[1][0];
	}
	else if (wym_W == 4) {
		if (przypadek == 1 || przypadek == 2) { // PQ , PR
			if (litera == 80 || litera == 112) {
				for (short i = 0; i < 4; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][0];
#if DBG == 1
				podglad_tabeli_dbg(tabelaprawdy);
#endif
			}
			else {
				for (short i = 0; i < 4; i++) tabelaprawdy[i][przebieg] = !tabelaprawdy[i][1];
#if DBG == 1
				podglad_tabeli_dbg(tabelaprawdy);
#endif
			}
		}
		if (przypadek == 3) { // QR
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

void liczba_dzialan(short a,short b)
{
	int aski=0;
	for (short i = a; i <= b; i++)
	{
		aski = wejscie[i];
		if (i == a && (aski == 78 || aski == 110)) { continue; }
		if (aski == 78 || aski == 110 || aski == 68 || aski == 100 || aski == 67 || aski == 99 || aski == 73 || aski == 105 || aski == 69 || aski == 101) { ilosc_dzialan += 1; }
	}
}

bool** utworz_tablice() //tworzy dynamiczna tablice o odpowiednym wymiarze, uzupelniona
{
	int aski;
	for (int i = (wejscie.length() - 1); i >= 0; i--)
	{
		aski = wejscie[i];
		if (aski == 80 || aski == 112) { ilosc_P += 1; }
		else if (aski == 81 || aski == 113) { ilosc_Q += 1; }
		else if (aski == 82 || aski == 114) { ilosc_R += 1; }
	}
	if (ilosc_P != 0 && ilosc_Q == 0 && ilosc_R == 0 || ilosc_P == 0 && ilosc_Q != 0 && ilosc_R == 0 || ilosc_P == 0 && ilosc_Q == 0 && ilosc_R != 0) { wym_W = 2; przypadek = 0; }
	else if (ilosc_P != 0 && ilosc_Q != 0 && ilosc_R == 0) { wym_W = 4; przypadek = 1; } // PQ
	else if (ilosc_P != 0 && ilosc_Q == 0 && ilosc_R != 0) { wym_W = 4; przypadek = 2; } // PR
	else if (ilosc_P == 0 && ilosc_Q != 0 && ilosc_R != 0) { wym_W = 4; przypadek = 3; } // QR
	else { wym_W = 8; }
	
	short a= kolejnosc_dzialan(0);
	liczba_dzialan(0, a);
	wym_K += 1;
	if (a != wejscie.length() - 1)
	{
		while (true)
		{
			wym_K += 1;
			liczba_dzialan(a+1, kolejnosc_dzialan(a+1));
			a = kolejnosc_dzialan(a+1);
			if (a == wejscie.length()-1) { break; }
		}
	}
#if DBG == 1
	cout << ilosc_dzialan << endl;
#endif
	wym_K += ilosc_dzialan + !!ilosc_P + !!ilosc_Q + !!ilosc_R;

	bool** tabelaprawdy;
	tabelaprawdy = new bool*[wym_W];
	for (int i = 0; i < wym_W; i++)  tabelaprawdy[i] = new bool[wym_K]; 

	if (wym_W == 2) {
		tabelaprawdy[0][0] = 1; tabelaprawdy[1][0] = 0; rodz_litera = 0;
	}
	else if (wym_W == 4) {
		tabelaprawdy[0][0] = 0; tabelaprawdy[1][0] = 0; tabelaprawdy[2][0] = 1; tabelaprawdy[3][0] = 1;
		tabelaprawdy[0][1] = 0; tabelaprawdy[1][1] = 1; tabelaprawdy[2][1] = 0; tabelaprawdy[3][1] = 1;
	}
	else {
		tabelaprawdy[0][0] = 0; tabelaprawdy[1][0] = 0; tabelaprawdy[2][0] = 1; tabelaprawdy[3][0] = 1; tabelaprawdy[4][0] = 0; tabelaprawdy[5][0] = 0; tabelaprawdy[6][0] = 1; tabelaprawdy[7][0] = 1;
		tabelaprawdy[0][1] = 0; tabelaprawdy[1][1] = 1; tabelaprawdy[2][1] = 0; tabelaprawdy[3][1] = 1; tabelaprawdy[4][1] = 0; tabelaprawdy[5][1] = 1; tabelaprawdy[6][1] = 0; tabelaprawdy[7][1] = 1;
		tabelaprawdy[0][2] = 0; tabelaprawdy[1][2] = 0; tabelaprawdy[2][2] = 0; tabelaprawdy[3][2] = 0; tabelaprawdy[4][2] = 1; tabelaprawdy[5][2] = 1; tabelaprawdy[6][2] = 1; tabelaprawdy[7][2] = 1;
	}
	return tabelaprawdy;
}

void wykonaj_F(bool** tabelaprawdy,bool NEG,short lewa_wspol,short prawa_wspol,short wynik,int &askiP,short przebieg,short litera)
{
	if (NEG == false)
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
				if ((tabelaprawdy[j][przebieg - 1] == lewa_wspol) && (tabelaprawdy[j][litera] == prawa_wspol)) { tabelaprawdy[j][przebieg] = wynik; }
				else { tabelaprawdy[j][przebieg] = abs(wynik - 1); }
			}
	}
	else
	{
			for (short m = 0; m < wym_W; m++)
			{
				if (tabelaprawdy[m][przebieg - 2] == lewa_wspol && tabelaprawdy[m][przebieg - 1] == prawa_wspol) { tabelaprawdy[m][przebieg] = wynik; }
				else { tabelaprawdy[m][przebieg] = abs(wynik - 1); }
			}
	}
}

void dopisywanie(bool** tabelaprawdy,short k,short i,short &przebieg)
{
	if (przypadek == 0) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][0]; }
	else if (przypadek == 1 || przypadek == 2) {
		if (wejscie[i] == 80 || wejscie[i] == 112) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][0]; }
		else { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][1]; }
	}
	else if (przypadek == 3)
	{
		if (wejscie[i] == 81 || wejscie[i] == 113) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][0]; }
		else { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][1]; }
	}
	else
	{
		if (wejscie[i] == 80 || wejscie[i] == 112) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][0]; }
		else if (wejscie[i] == 81 || wejscie[i] == 113) { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][1]; }
		else { for (short j = 0; j < wym_W; j++) tabelaprawdy[j][k] = tabelaprawdy[j][2]; }
	}
#if DBG == 1
	cout << "robione " << endl;
	podglad_tabeli_dbg(tabelaprawdy);
#endif
	przebieg += 1;
}

bool sprawdz_F(bool** tabelaprawdy,short a,short b,short &przebieg,short &litera)
{
	int askiP,askiPP;
	bool czy_dzialano = false;
	short i,prze = przebieg;
	if (a == 0 && (wejscie[0] != 78 && wejscie[0] != 110)) { dopisywanie(tabelaprawdy, przebieg, 0, przebieg); }
	else if (b - a == 1) { dopisywanie(tabelaprawdy, przebieg, a, przebieg); return false; }
	//else if (){ dopisywanie(tabelaprawdy, przebieg, a, przebieg); }
	for (i = a; i <= b; i++)
	{
		int aski1 = wejscie[i];

		switch (aski1)
		{
		case 78:
		case 110: //N ,~ - negacja
			askiP = wejscie[i + 1];
			negacja(przebieg, askiP, tabelaprawdy);
			czy_dzialano = true;
			break;
		case 68:
		case 100: //D ,v - alternatywa
			askiP = wejscie[i + 1];
			if (prze == przebieg) { dopisywanie(tabelaprawdy, przebieg, i-1, przebieg); }
			if (askiP == 78 || askiP == 110) {
				askiPP = wejscie[i + 2];
				negacja(przebieg, askiPP, tabelaprawdy);
				wykonaj_F(tabelaprawdy, true, 0, 0, 0, askiP, przebieg, litera);
				i++;
			}
			else
			{
				wykonaj_F(tabelaprawdy, false, 0, 0, 0, askiP, przebieg, litera);
			}
			czy_dzialano = true;
			przebieg += 1;
			break;
		case 67:
		case 99: //C ,^ - koniukcja
			askiP = wejscie[i + 1];
			if (prze == przebieg) { dopisywanie(tabelaprawdy, przebieg, i-1, przebieg); }
			if (askiP == 78 || askiP == 110) {
				askiPP = wejscie[i + 2];
				negacja(przebieg, askiPP, tabelaprawdy);
				wykonaj_F(tabelaprawdy, true, 1, 1, 1, askiP, przebieg, litera);
				i++;
			}
			else
			{
				wykonaj_F(tabelaprawdy, false, 1, 1, 1, askiP, przebieg, litera);
			}
			czy_dzialano = true;
			przebieg += 1;
			break;
		default:
			break;
		}

#if DBG==1 
		podglad_tabeli_dbg(tabelaprawdy);
#endif
	}
	if (czy_dzialano == false && prze == przebieg) { dopisywanie(tabelaprawdy, przebieg, a+1, przebieg); }
	return true;
}

bool rachunek_logiczny(bool** &tabelaprawdy)
{
	short litera = 0, startowa = 0,koncowa = 0,ostatni = 0;
	int askiL, askiP;
	if (wejscie.length() < 1) { return false; }

	short przebieg = !!ilosc_P + !!ilosc_Q + !!ilosc_R;

#if DBG==1 
	podglad_tabeli_dbg(tabelaprawdy);
#endif

	startowa = kolejnosc_dzialan(startowa);
	sprawdz_F(tabelaprawdy,0,startowa, przebieg, litera);
	if (startowa < wejscie.length()-1) 
	{
		while (true)
		{
			ostatni = przebieg - 1;
			koncowa = kolejnosc_dzialan(startowa+1);
			sprawdz_F(tabelaprawdy, startowa, koncowa, przebieg, litera);
#if DBG == 1
			podglad_tabeli_dbg(tabelaprawdy);
#endif
			if (wejscie[startowa] == 73 || wejscie[startowa] == 105)// I
			{
				for (short j = 0; j < wym_W; j++)
				{
					if ((tabelaprawdy[j][ostatni] == 1) && (tabelaprawdy[j][przebieg-1] == 0)) { tabelaprawdy[j][przebieg] = 0; }
					else { tabelaprawdy[j][przebieg] = 1; }
				}
			}
			else if (wejscie[startowa] == 69 || wejscie[startowa] == 101)// E
			{
				for (short j = 0; j < wym_W; j++)
				{
					if ((tabelaprawdy[j][ostatni] == 1 && tabelaprawdy[j][przebieg-1] == 1) || (tabelaprawdy[j][ostatni] == 0 && tabelaprawdy[j][przebieg-1] == 0)) { tabelaprawdy[j][przebieg] = 1; }
					else { tabelaprawdy[j][przebieg] = 0; }
				}
			}
			if (koncowa == wejscie.length()-1) { break; }
			przebieg += 1;
			startowa = koncowa;
		}
	}

#if DBG==1 
	podglad_tabeli_dbg(tabelaprawdy);
#endif

	short ilosc_zmiennych = !!ilosc_P + !!ilosc_Q + !!ilosc_R;
	for (short j = 0; j < wym_W; j++)
	{
		if (tabelaprawdy[j][wym_K - 1] == 0) { break; }
		if (j == wym_W - 1) { return true; }
	}
	return false;
}

int main()
{
	start = clock();
	setlocale(LC_CTYPE, ".1250");

	if (pobierz_dane_plik() == false) 
	{ 
		utworz_plik();
		return 0;
	}

#if DBG 1
	cout << wejscie << endl;
#endif

	bool** temp = utworz_tablice();

	if (rachunek_logiczny(temp) == true) 
	{
		cout << endl << " Podane zdanie logiczne jest tautologią !" << endl<< endl;;
	}
	else
	{
		cout << "Podane zdanie logiczne nie jest tautologią dla: " << endl;
		for (short j = 0; j < wym_W; j++)
		{
			if (temp[j][wym_K - 1] == 0)
			{
				if (wym_W == 2) { cout << "P= " << temp[j][0] << endl; }
				else if (wym_W == 4) 
				{ 
					if (przypadek == 1) { cout << "P= " << temp[j][0] << ", Q= " << temp[j][1] << endl; }
					else if (przypadek == 2) { cout << "P= " << temp[j][0] << ", R= " << temp[j][1] << endl; }
					else { cout << "Q= " << temp[j][0] << ", R= " << temp[j][1] << endl; }
				}
				else { cout << "P= " << temp[j][0] << ", Q= " << temp[j][1] << ", R= " << temp[j][2] << endl; }
			}
		}
	}

	if (tryb_zaawansowany) { podglad_tabeli_dbg(temp); }

	for (int i = 0; i < wym_W; i++) delete[] temp[i];
	delete[] temp;

	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	if (tryb_zaawansowany) { cout << "Wykonanie programu trwało: " << czas << endl << endl; }

	cout << "Program autorstwa Grzegorz Szwarc" << endl;
	system("pause");
	return 0;
}
