#include "Plansza.h"
#include "Gracz.h"
#include "Komputer.h"
#include "global.h"
#include <iostream>
#include <Windows.h>

HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);																	//uchwyt do standardowego wyjœcia konsoli

//sta³e definiuj¹ce kolory
#define NIEBIESKI SetConsoleTextAttribute(hOut2, FOREGROUND_BLUE)												//kolor niebieski
#define CZERWONY SetConsoleTextAttribute(hOut2, FOREGROUND_RED)													//kolor czerwony
#define FIOLETOWY SetConsoleTextAttribute(hOut2, FOREGROUND_RED | FOREGROUND_BLUE)								//kolor fioletowy
#define BIALY SetConsoleTextAttribute(hOut2, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)				//kolor bia³y

#define POCZATEK 0																								//wartoœæ pocz¹tkowa wybranych zmiennych i pól
#define POLA 25																									//iloœæ pól na jednej planszy
#define LANCUCH "\0"																							//³añcuch zerowy do inicjalizacji zmiennych ³añcuchowych

using namespace std;

Plansza::Plansza() {
	for (int i = POCZATEK; i < E; i++) {
		for (int j = POCZATEK; j < E; j++) plansza1[i][j] = plansza2[i][j] = plansza3[i][j] = "   ";
	}
}

void Plansza::wybierz_kolor(int kolor) {																		//kolor - przechowuje kod koloru, który jest nastêpnie ustawiany
	if (kolor == A) CZERWONY;
	else if (kolor == B) NIEBIESKI;
	else if (kolor == C) FIOLETOWY;
	else BIALY;
}

void Plansza::wypisz_pole(string pole) {																		//pole - przechowuje zawartoœæ wybranego pola planszy
	if (pole != " " && pole[B] == 'c') {
		CZERWONY;
		cout << pole << "\b";
	}
	else if (pole != " " && pole[B] == 'n') {
		NIEBIESKI;
		cout << pole << "\b";
	}
	else if (pole != " " && pole[B] == 'f') {
		FIOLETOWY;
		cout << pole << "\b";
	}
	else cout << pole << "\b";
}

void Plansza::rysuj_wiersz(int kolor1 = POCZATEK, int kolor2 = POCZATEK, int kolor3 = POCZATEK) {				//kolor1 - kolor pierwszej linii startowej planszy górnej (czerwony), kolor2 - kolor powrotu do poprzednio ustawionego koloru (bia³y), kolor3 - kolor drugiej linii startowej planszy górnej (fioletowy)
	cout << "\t\t\t\t\t\t\t\t\t\t";
	wybierz_kolor(kolor1);
	cout << " _______ ";
	wybierz_kolor(kolor3);
	for (int i = POCZATEK; i < C; i++) cout << "_______ ";
	wybierz_kolor(kolor2);
	cout << "_______";
	wybierz_kolor(kolor3);
	for (int i = POCZATEK; i < B; i++) {
		cout << "\n\t\t\t\t\t\t\t\t\t\t";
		wybierz_kolor(kolor1);
		if (i) {
			cout << "|  ";
			wypisz_pole(plansza1[POCZATEK][POCZATEK]);
			wybierz_kolor(kolor1);
			cout << "   |";
		}
		else cout << "|\t|";
		wybierz_kolor(kolor3);
		if (i) for (int j = A; j < C; j++) {
			cout << "  ";
			wypisz_pole(plansza1[POCZATEK][j]);
			wybierz_kolor(kolor3);
			cout << "   |";
		}
		else for (int i = POCZATEK; i < B; i++) cout << "\t|";
		if (i) {
			cout << "  ";
			wypisz_pole(plansza1[POCZATEK][C]);
			wybierz_kolor(kolor3);
			cout << "   ";
			wybierz_kolor(kolor2);
			cout << "|  ";
			wypisz_pole(plansza1[POCZATEK][D]);
			wybierz_kolor(kolor2);
			cout << "   |";
		}
		else {
			wybierz_kolor(kolor2);
			cout << "\t|\t|";
		}
		wybierz_kolor(kolor3);
	}
	cout << "\n\t\t\t\t\t\t\t\t\t\t";
	wybierz_kolor(kolor1);
	cout << "|_______|";
	wybierz_kolor(kolor3);
	for (int i = POCZATEK; i < C; i++) cout << "_______|";
	wybierz_kolor(kolor2);
	cout << "\b|_______|";
	wybierz_kolor(kolor3);
}

void Plansza::rysuj_wiersz1(int tryb, int kolor1 = POCZATEK, int kolor2 = POCZATEK, int kolor3 = POCZATEK) {	//tryb - decyduje o rysowanym wierszu, kolor1 - kolor pierwszej linii startowej planszy górnej (czerwony), kolor2 - kolor powrotu do poprzednio ustawionego koloru (bia³y), kolor3 - kolor drugiej linii startowej planszy górnej (fioletowy)
	for (int i = POCZATEK; i < B; i++) {
		cout << "\n\t\t\t\t\t\t\t\t\t\t";
		wybierz_kolor(kolor1);
		if (i) {
			cout << "|  ";
			wypisz_pole(plansza1[tryb][POCZATEK]);
			wybierz_kolor(kolor1);
			cout << "   |";
		}
		else cout << "|\t|";
		wybierz_kolor(kolor3);
		if (i) for (int i = A; i < C; i++) {
			cout << "  ";
			wypisz_pole(plansza1[tryb][i]);
			wybierz_kolor(kolor3);
			cout << "   |";
		}
		else for (int i = POCZATEK; i < B; i++) cout << "\t|";
		if (i) {
			cout << "  ";
			wypisz_pole(plansza1[tryb][C]);
			wybierz_kolor(kolor3);
			cout << "   ";
			wybierz_kolor(kolor2);
			cout << "|  ";
			wypisz_pole(plansza1[tryb][D]);
			wybierz_kolor(kolor2);
			cout << "   |";
			wybierz_kolor(kolor2);
		}
		else {
			wybierz_kolor(kolor2);
			cout << "\t|\t|";
		}
		wybierz_kolor(kolor3);
	}
	cout << "\n\t\t\t\t\t\t\t\t\t\t";
	wybierz_kolor(kolor1);
	cout << "|_______|";
	wybierz_kolor(kolor3);
	for (int i = POCZATEK; i < C; i++) cout << "_______|";
	wybierz_kolor(kolor2);
	cout << "\b|_______|";
	wybierz_kolor(kolor3);
}

void Plansza::rysuj_wiersz2(int tryb, int kolor1 = POCZATEK, int kolor2 = POCZATEK, int kolor3 = POCZATEK) {	//tryb - decyduje o rysowanym wierszu, kolor1 - kolor pierwszej linii startowej planszy górnej (czerwony), kolor2 - kolor powrotu do poprzednio ustawionego koloru (bia³y), kolor3 - kolor drugiej linii startowej planszy górnej (fioletowy)
	for (int i = POCZATEK; i < B; i++) {
		cout << "\n\t\t\t\t\t\t\t\t\t\t";
		wybierz_kolor(kolor1);
		if (i) {
			cout << "|  ";
			wypisz_pole(plansza1[tryb][POCZATEK]);
			wybierz_kolor(kolor1);
			cout << "   |";
		}
		else cout << "|\t|";
		wybierz_kolor(kolor3);
		if (i) for (int i = A; i < C; i++) {
			cout << "  ";
			wypisz_pole(plansza1[tryb][i]);
			wybierz_kolor(kolor3);
			cout << "   |";
		}
		else for (int i = POCZATEK; i < B; i++) cout << "\t|";
		if (i) {
			cout << "  ";
			wypisz_pole(plansza1[tryb][C]);
			wybierz_kolor(kolor3);
			cout << "   ";
			wybierz_kolor(kolor2);
			cout << "|  ";
			wypisz_pole(plansza1[tryb][D]);
			wybierz_kolor(kolor2);
			cout << "   |";
		}
		else {
			wybierz_kolor(kolor2);
			cout << "\t|\t|";
		}
		wybierz_kolor(kolor3);
	}
	cout << "\n\t\t\t\t\t\t\t\t\t\t";
	wybierz_kolor(kolor1);
	cout << "|_______|";
	for (int i = POCZATEK; i < D; i++) {
		if (i == C) {
			wybierz_kolor(kolor2);
			cout << "\b|_______|";
			wybierz_kolor(kolor3);
		}
		else {
			wybierz_kolor(kolor3);
			cout << "_______|";
		}
	}
}

void Plansza::rysuj_wiersz_(int kolor = POCZATEK) {																//kolor - kolor pierwszego wiersza planszy lewej
	cout << "\t\t\t\t";
	for (int i = POCZATEK; i < B; i++) {
		if (!i) wybierz_kolor(kolor);
		else wybierz_kolor(C);
		cout << " _______ ";
		for (int i = POCZATEK; i < C; i++) cout << "_______ ";
		cout << "_______";
		if (!i) cout << "\t\t\t\t\t\t\t";
	}
	for (int i = POCZATEK; i < B; i++) {
		cout << "\n\t\t\t\t";
		for (int j = POCZATEK; j < B; j++) {
			if (!j) wybierz_kolor(kolor);
			else wybierz_kolor(C);
			if (i) {
				cout << "|  ";
				if (!j) wypisz_pole(plansza2[POCZATEK][POCZATEK]);
				else wypisz_pole(plansza3[POCZATEK][POCZATEK]);
				if (!j) wybierz_kolor(kolor);
				else wybierz_kolor(C);
				cout << "   |";
			}
			else cout << "|\t|";
			if (i) {
				for (int i = A; i < E; i++) {
					cout << "  ";
					if (!j) wypisz_pole(plansza2[POCZATEK][i]);
					else wypisz_pole(plansza3[POCZATEK][i]);
					if (!j) wybierz_kolor(kolor);
					else wybierz_kolor(C);
					cout << "   |";
				}
			}
			else for (int i = POCZATEK; i < D; i++) cout << "\t|";
			if (!j) cout << "\t\t\t\t\t\t\t";
		}
	}
	cout << "\n\t\t\t\t";
	for (int i = POCZATEK; i < B; i++) {
		if (!i) wybierz_kolor(kolor);
		else wybierz_kolor(C);
		cout << "|_______|";
		for (int i = POCZATEK; i < C; i++) cout << "_______|";
		cout << "\b|_______|";
		if (!i) cout << "\t\t\t\t\t\t\t";
	}
}

void Plansza::rysuj_wiersz1_(int tryb, int kolor = POCZATEK) {													//tryb - decyduje o rysowanym wierszu, kolor - kolor rysowanego wiersza
	for (int i = POCZATEK; i < B; i++) {
		cout << "\n\t\t\t\t";
		wybierz_kolor(kolor);
		for (int j = POCZATEK; j < B; j++) {
			if (i) {
				cout << "|  ";
				if (j) wypisz_pole(plansza3[tryb][POCZATEK]);
				else wypisz_pole(plansza2[tryb][POCZATEK]);
				wybierz_kolor(kolor);
				cout << "   |";
			}
			else cout << "|\t|";
			if (i) for (int i = A; i < E; i++) {
				cout << "  ";
				if (j) wypisz_pole(plansza3[tryb][i]);
				else wypisz_pole(plansza2[tryb][i]);
				wybierz_kolor(kolor);
				cout << "   |";
			}
			else for (int i = POCZATEK; i < D; i++) cout << "\t|";
			if (!j) cout << "\t\t\t\t\t\t\t";
		}
	}
	cout << "\n\t\t\t\t";
	for (int i = POCZATEK; i < B; i++) {
		cout << "|_______|";
		for (int i = POCZATEK; i < C; i++) cout << "_______|";
		cout << "\b|_______|";
		if (!i) cout << "\t\t\t\t\t\t\t";
	}
}

void Plansza::rysuj_wiersz2_(int kolor1 = POCZATEK, int kolor2 = POCZATEK) {									//kolor1 - decyduje o kolorze rysowanego wiersza, kolor2 - kolor powrotu do koloru uprzedniego (bia³y)
	for (int i = POCZATEK; i < B; i++) {
		cout << endl;
		for (int j = POCZATEK; j < B; j++) {
			if (!j) cout << "\t\t\t\t";
			else cout << "\t\t\t\t\t\t\t";
			wybierz_kolor(kolor2);
			if (i) {
				cout << "|  ";
				if (j) wypisz_pole(plansza3[C][POCZATEK]);
				else wypisz_pole(plansza2[C][POCZATEK]);
				wybierz_kolor(kolor2);
				cout << "   |";
			}
			else cout << "|\t|";
			if (i) for (int i = A; i < E; i++) {
				cout << "  ";
				if (j) wypisz_pole(plansza3[C][i]);
				else wypisz_pole(plansza2[C][i]);
				wybierz_kolor(kolor2);
				cout << "   |";
			}
			else for (int i = POCZATEK; i < D; i++) cout << "\t|";
		}
	}
	cout << "\n\t\t\t\t";
	for (int i = POCZATEK; i < B; i++) {
		cout.put('|');
		for (int i = POCZATEK; i < E; i++) {
			wybierz_kolor(kolor1);
			cout << "_______";
			wybierz_kolor(kolor2);
			cout.put('|');
			if (i == D) cout << "\b|";
		}
		if (!i) cout << "\t\t\t\t\t\t\t";
	}
}

void Plansza::rysuj_plansze() {
	rysuj_wiersz(A, C);
	for (int i = A; i < C; i++) rysuj_wiersz1(i, A, C);
	rysuj_wiersz2(C, A, C);
	rysuj_wiersz1(D, A, C);
	cout << endl << endl << endl;
	rysuj_wiersz_(A);
	for (int i = A; i < C; i++) rysuj_wiersz1_(i);
	rysuj_wiersz2_(B);
	rysuj_wiersz1_(D, B);
	cout << endl << endl;
	BIALY;
}

void Plansza::wyswietl_legende() {
	cout << "Legenda pionkow:\n";
	cout << "mT - maly trojkat,\n";
	cout << "sT - sredni trojkat,\n";
	cout << "dT - duzy trojkat,\n";
	cout << "mK - maly kwadrat,\n";
	cout << "sK - sredni kwadrat,\n";
	cout << "dK - duzy kwadrat,\n";
	cout << "mS - maly szesciokat,\n";
	cout << "sS - sredni szesciokat,\n";
	cout << "dS - duzy szesciokat.\n\n";
}

void Plansza::zapelnij_plansze(Gracz *gracz1, Gracz *gracz2, string neutralny) {								//gracz1 - przechowuje dane pierwszego gracza, gracz2 - przechowuje dane drugiego gracza, neutralny - przechowuje kolor gracza neutralnego
	rysuj_plansze();
	gracz1->wyswietl_faza_neutralne(gracz2, *this);
	for (int i = POCZATEK; i < D; i++) {
		system("cls");
		rysuj_plansze();
		gracz1->ustaw_pionki_neutralne(*this, neutralny);
		gracz2->ustaw_pionki_neutralne(*this, neutralny);
	}
	wyczysc_bufor();
	gracz1->wyswietl_faza_pozostale(gracz2, *this);
	for (int i = POCZATEK; i < I; i++) {
		system("cls");
		rysuj_plansze();
		gracz1->ustaw_pionki_pozostale(*this);
		gracz2->ustaw_pionki_pozostale(*this);
	}
	gracz1->wpisz_plik(*(gracz2));
	gracz1->wpisz_kolory(*(gracz2));
	gracz1->wpisz_plansze(*this);
	gracz1->wpisz_punkty(*(gracz2));
}

int Plansza::zamroz_plansze(int nr_planszy) {																	//nr_planszy - przechowuje numer planszy
	Komputer temp;																								//temp - obiekt tymczasowy komputer
	string pionek = LANCUCH;																					//pionek - przechowuje ustalony pionek
	string *wsk_plansza = NULL;																					//wsk_plansza - wskaŸnik na planszê o podanym numerze

	if (nr_planszy == A) {
		int pionekc = POCZATEK;																					//pionekc - iloœæ wszystkich pionków koloru czerwonego na tej planszy
		int pionekf = POCZATEK;																					//pionekf - iloœæ wszystkich pionków koloru fioletowego na tej planszy
		int infoc = POCZATEK;																					//infoc - suma wszystkich niemo¿liwych ruchów wszystkich pionków koloru czerwonego na tej planszy
		int infof = POCZATEK;																					//infof - suma wszystkich niemo¿liwych ruchów wszystkich pionków koloru fioletowego na tej planszy
		wsk_plansza = get_plansza1();
		for (int i = POCZATEK; i < POLA; i++) {
			if (*(wsk_plansza + i) != "   ") {
				pionek = *(wsk_plansza + i);
				if (pionek[B] == 'c') pionekc++;
				else pionekf++;
			}
		}
		for (int i = POCZATEK; i < POLA; i++) {
			if (*(wsk_plansza + i) != "   ") {
				pionek = *(wsk_plansza + i);
				if (pionek[B] == 'c') {
					temp.set_kolor("czerwony");
					for (int j = A; j < F; j++) infoc += temp.rusz_sie(wsk_plansza, i, j, *this, A);
				}
				else {
					temp.set_kolor("fioletowy");
					for (int j = A; j < F; j++) infof += temp.rusz_sie(wsk_plansza, i, j, *this, A);
				}
			}
		}
		if (infoc == E * pionekc && infof == E * pionekf) return A;
		else if (infoc == E * pionekc) return B;
		else if (infof == E * pionekf) return C;
		else return POCZATEK;
	}
	else if (nr_planszy == B) {
		int pionekc = POCZATEK;																					//pionekc - iloœæ wszystkich pionków koloru czerwonego na tej planszy
		int pionekn = POCZATEK;																					//pionekn - iloœæ wszystkich pionków koloru niebieskiego na tej planszy
		int infoc = POCZATEK;																					//infoc - suma wszystkich niemo¿liwych ruchów wszystkich pionków koloru czerwonego na tej planszy
		int infon = POCZATEK;																					//infon - suma wszystkich niemo¿liwych ruchów wszystkich pionków koloru niebieskiego na tej planszy
		wsk_plansza = get_plansza2();
		for (int i = POCZATEK; i < POLA; i++) {
			if (*(wsk_plansza + i) != "   ") {
				pionek = *(wsk_plansza + i);
				if (pionek[B] == 'c') pionekc++;
				else pionekn++;
			}
		}
		for (int i = POCZATEK; i < POLA; i++) {
			if (*(wsk_plansza + i) != "   ") {
				pionek = *(wsk_plansza + i);
				if (pionek[B] == 'c') {
					temp.set_kolor("czerwony");
					for (int j = A; j < F; j++) infoc += temp.rusz_sie(wsk_plansza, i, j, *this, A);
				}
				else {
					temp.set_kolor("niebieski");
					for (int j = A; j < F; j++) infon += temp.rusz_sie(wsk_plansza, i, j, *this, A);
				}
			}
		}
		if (infoc == E * pionekc && infon == E * pionekn) return A;
		else if (infoc == E * pionekc) return B;
		else if (infon == E * pionekn) return C;
		else return POCZATEK;
	}
	else {
		int pionekf = POCZATEK;																					//pionekf - iloœæ wszystkich pionków koloru fioletowego na tej planszy
		int pionekn = POCZATEK;																					//pionekn - iloœæ wszystkich pionków koloru niebieskiego na tej planszy
		int infof = POCZATEK;																					//infof - suma wszystkich niemo¿liwych ruchów wszystkich pionków koloru fioletowego na tej planszy
		int infon = POCZATEK;																					//infon - suma wszystkich niemo¿liwych ruchów wszystkich pionków koloru niebieskiego na tej planszy
		wsk_plansza = get_plansza3();
		for (int i = POCZATEK; i < POLA; i++) {
			if (*(wsk_plansza + i) != "   ") {
				pionek = *(wsk_plansza + i);
				if (pionek[B] == 'f') pionekf++;
				else pionekn++;
			}
		}
		for (int i = POCZATEK; i < POLA; i++) {
			if (*(wsk_plansza + i) != "   ") {
				pionek = *(wsk_plansza + i);
				if (pionek[B] == 'f') {
					temp.set_kolor("fioletowy");
					for (int j = A; j < F; j++) infof += temp.rusz_sie(wsk_plansza, i, j, *this, A);
				}
				else {
					temp.set_kolor("niebieski");
					for (int j = A; j < F; j++) infon += temp.rusz_sie(wsk_plansza, i, j, *this, A);
				}
			}
		}
		if (infof == E * pionekf && infon == E * pionekn) return A;
		else if (infof == E * pionekf) return B;
		else if (infon == E * pionekn) return C;
		else return POCZATEK;
	}
}