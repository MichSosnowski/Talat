#include "Komputer.h"
#include <iostream>
#include <ctime>

#define PRAWDA 1																									//wartoœæ prawdziwa steruj¹ca pêtl¹ while
#define POCZATEK 0																									//wartoœæ pocz¹tkowa wybranych zmiennych i pól
#define POLA 25																										//iloœæ pól na jednej planszy
#define RUCH 5																										//czas oczekiwania na ruch komputera
#define LANCUCH "\0"

using std::cout;

void Komputer::ustaw_pionki(string *wsk_plansza, string nazwa, int nr_pola, Plansza &plansza, string kolor) {		//wsk_plansza - wskaŸnik na pierwsze pole planszy, nazwa - nazwa pionka, który jest ustawiany, nr_pola - numer pola, na którym ustawiany jest pionek, kolor - kolor pionka
	nazwa += kolor[POCZATEK];
	if (kolor == "czerwony") {
		if (wsk_plansza == plansza.get_plansza1()) {
			while (*(wsk_plansza + E * nr_pola) != "   ") nr_pola = rand() % E;
			if (*(wsk_plansza + E * nr_pola) == "   ") *(wsk_plansza + E * nr_pola) = nazwa;
		}
		else {
			while (*(wsk_plansza + nr_pola) != "   ") nr_pola = rand() % E;
			if (*(wsk_plansza + nr_pola) == "   ") *(wsk_plansza + nr_pola) = nazwa;
		}
	}
	else if (kolor == "niebieski") {
		while (*((wsk_plansza + (POLA - E)) + nr_pola) != "   ") nr_pola = rand() % E;
		if (*((wsk_plansza + (POLA - E)) + nr_pola) == "   ") *((wsk_plansza + (POLA - E)) + nr_pola) = nazwa;
	}
	else if (kolor == "fioletowy") {
		if (wsk_plansza == plansza.get_plansza1()) {
			while (*((wsk_plansza + D) + E * nr_pola) != "   ") nr_pola = rand() % E;
			if (*((wsk_plansza + D) + E * nr_pola) == "   ") *((wsk_plansza + D) + E * nr_pola) = nazwa;
		}
		else {
			while (*(wsk_plansza + nr_pola) != "   ") nr_pola = rand() % E;
			if (*(wsk_plansza + nr_pola) == "   ") *(wsk_plansza + nr_pola) = nazwa;
		}
	}
}

int Komputer::sprawdz_plansze(int numer, Plansza &plansza) {														//numer - numer planszy, plansza - przechowuje wszystkie trzy plansze
	string *wsk_plansza = NULL;																						//wsk_plansza - wskaŸnik na pierwsze pole planszy
	int info = POCZATEK;																							//info - przechowuje iloœæ zajêtych pól startowych na tej planszy

	while (PRAWDA) {
		if (numer == A) {
			if (get_kolor() == "czerwony") {
				wsk_plansza = plansza.get_plansza1();
				for (int i = POCZATEK; i < E; i++) if (*(wsk_plansza + E * i) != "   ") info++;
				if (info == E) {
					numer = rand() % C + A;
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "fioletowy") {
				wsk_plansza = plansza.get_plansza1();
				for (int i = POCZATEK; i < E; i++) if (*((wsk_plansza + D) + E * i) != "   ") info++;
				if (info == E) {
					numer = rand() % C + A;
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "niebieski") numer = rand() % C + A;
		}
		else if (numer == B) {
			if (get_kolor() == "czerwony") {
				wsk_plansza = plansza.get_plansza2();
				for (int i = POCZATEK; i < E; i++) if (*(wsk_plansza + i) != "   ") info++;
				if (info == E) {
					numer = rand() % C + A;
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "niebieski") {
				wsk_plansza = plansza.get_plansza2();
				for (int i = POCZATEK; i < E; i++) if (*((wsk_plansza + (POLA - E)) + i) != "   ") info++;
				if (info == E) {
					numer = rand() % C + A;
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "fioletowy") numer = rand() % C + A;
		}
		else if (numer == C) {
			if (get_kolor() == "niebieski") {
				wsk_plansza = plansza.get_plansza3();
				for (int i = POCZATEK; i < E; i++) if (*((wsk_plansza + (POLA - E)) + i) != "   ") info++;
				if (info == E) {
					numer = rand() % C + A;
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "fioletowy") {
				wsk_plansza = plansza.get_plansza3();
				for (int i = POCZATEK; i < E; i++) if (*(wsk_plansza + i) != "   ") info++;
				if (info == E) {
					numer = rand() % C + A;
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "czerwony") numer = rand() % C + A;
		}
		if (info == -A) break;
	}

	return numer;
}

int Komputer::plansze_grane(Plansza &plansza, string neutralny) {													//plansza - przechowuje wszystkie trzy plansze, neutralny - kolor gracza neutralnego
	int info1 = POCZATEK, info2 = POCZATEK, info3 = POCZATEK;														//info1, info2, info3 - przechowuj¹ informacje o tym, czy dana plansza jest zamro¿ona
	int nr_planszy = POCZATEK;																						//nr_planszy - numer wybranej obecnie planszy
	info1 = plansza.zamroz_plansze(A);
	info2 = plansza.zamroz_plansze(B);
	info3 = plansza.zamroz_plansze(C);
	int gorna = POCZATEK, lewa = POCZATEK, prawa = POCZATEK;														//gorna, lewa, prawa - przetrzymuj¹ informacje o tym, czy te plansze s¹ zamro¿one

	if ((info1 == A && info2 == A) || (info2 == A && info3 == A) || (info1 == A && info3 == A)) return POCZATEK;
	if (get_kolor() == "czerwony") {
		if (info1 == A || info1 == B) gorna++;
		if (info2 == A || info2 == B) lewa++;
	}
	else if (get_kolor() == "niebieski") {
		if (info2 == A || info2 == C) lewa++;
		if (info3 == A || info3 == C) prawa++;
	}
	else {
		if (info1 == A || info1 == C) gorna++;
		if (info3 == A || info3 == B) prawa++;
	}

	if (neutralny == "czerwony") {
		if ((info1 == A || info1 == B) && get_kolor() == "niebieski") gorna++;
		if ((info2 == A || info2 == B) && get_kolor() == "fioletowy") lewa++;
	}
	else if (neutralny == "niebieski") {
		if ((info2 == A || info2 == C) && get_kolor() == "fioletowy") lewa++;
		if ((info3 == A || info3 == C) && get_kolor() == "czerwony") prawa++;
	}
	else {
		if ((info1 == A || info1 == C) && get_kolor() == "niebieski") gorna++;
		if ((info3 == A || info3 == B) && get_kolor() == "czerwony") prawa++;
	}

	if (gorna && lewa) nr_planszy = C;
	else if (gorna && prawa) nr_planszy = B;
	else if (lewa && prawa) nr_planszy = A;
	else if (gorna) nr_planszy = rand() % B + B;
	else if (lewa) {
		nr_planszy = rand() % C + A;
		while(nr_planszy == B) nr_planszy = rand() % C + A;
	}
	else if (prawa) nr_planszy = rand() % B + A;
	else nr_planszy = rand() % C + A;

	return nr_planszy;
}

string Komputer::wybierz_pionek() {
	int los = rand() % I + A;																						//los - dokonany przez komputer wybór

	if (los == A) return "mT";
	else if (los == B) return "sT";
	else if (los == C) return "dT";
	else if (los == D) return "mK";
	else if (los == E) return "sK";
	else if (los == F) return "dK";
	else if (los == G) return "mS";
	else if (los == H) return "sS";
	else return "dS";
}

string * Komputer::znajdz_neutralna_gracza(string neutralny, Plansza &plansza) {									//neutralny - przechowuje kolor gracza neutralnego, plansza - przechowuje wszystkie trzy plansze
	string * wsk_plansza = NULL;																					//wsk_plansza - wskaŸnik na pierwsze pole planszy
	if (get_kolor() == "czerwony" && (neutralny == "niebieski" || neutralny == "fioletowy")) wsk_plansza = plansza.get_plansza3();
	else if (get_kolor() == "niebieski" && (neutralny == "czerwony" || neutralny == "fioletowy")) wsk_plansza = plansza.get_plansza1();
	else if (get_kolor() == "fioletowy" && (neutralny == "czerwony" || neutralny == "niebieski")) wsk_plansza = plansza.get_plansza2();
	return wsk_plansza;
}

string Komputer::jest_pionek(string pionek, string kolor, Plansza &plansza) {										//pionek - nazwa obecnie wybranego pionka, kolor - kolor pionka, plansza - przechowuje wszystkie trzy plansze
	Gracz temp;																										//obiekt tymczasowy Gracz
	int nr_planszy = POCZATEK;																						//nr_planszy - numer planszy
	int info1 = POCZATEK;																							//info1 - informuje o tym, czy na danej planszy jest pionek
	int info2 = POCZATEK;																							//info2 - informuje o tym, czy na danej planszy jest pionek
	temp.set_kolor(kolor);

	while (PRAWDA) {
		if (kolor == "czerwony") nr_planszy = A;
		else if (kolor == "niebieski") nr_planszy = B;
		else if (kolor == "fioletowy") nr_planszy = C;
		info1 = temp.wyszukaj_pionek(pionek, nr_planszy, plansza);
		if (kolor == "czerwony") nr_planszy = B;
		else if (kolor == "niebieski") nr_planszy = C;
		else if (kolor == "fioletowy") nr_planszy = A;
		info2 = temp.wyszukaj_pionek(pionek, nr_planszy, plansza);

		if (info1 != -1 || info2 != -1) pionek = wybierz_pionek();
		else break;
	}

	return pionek;
}

int Komputer::wykonaj_ruch(Plansza &plansza, string neutralny) {													//plansza - przechowuje wszystkie trzy plansze, neutralny - przechowuje kolor gracza neutralnego
	string *wsk_plansza = NULL;																						//wsk_plansza - wskaŸnik na pierwsze pole planszy
	string nazwa = LANCUCH;																							//nazwa - nazwa pionka, którym rusza siê gracz
	string kolor_gracza = get_kolor();																				//kolor_gracza - kolor gracza obecnie wykonuj¹cego ruch
	int pole = -A;																									//pole - informuje o tym, czy pole jest puste, czy nie
	int zwrot = -A;																									//zwrot - informuje, czy uda³o siê wykonaæ ruch, czy te¿ nie
	int wybor = POCZATEK;																							//wybor - numer planszy, która nie jest zamro¿ona

	system("cls");
	plansza.rysuj_plansze();
	cout << "Komputer dokonuje ruchu.";
	while (zwrot) {
		clock_t czas = clock();																						//czas - umo¿liwia dzia³anie pêtli oczekuj¹cej
		while (clock() - czas < RUCH * CLOCKS_PER_SEC);
		wybor = plansze_grane(plansza, neutralny);
		if (!wybor) break;
		int info = Gracz::znajdz_plansze(wybor, neutralny);															//info - jeœli jest pozytywne, tzn. ¿e nast¹pi³a zmiana koloru
		wsk_plansza = ustaw_plansze(wybor, plansza);
		nazwa = wybierz_pionek();
		while (pole == -A) {
			pole = wyszukaj_pionek(nazwa, wybor, plansza);
			if (pole == -A) nazwa = wybierz_pionek();
			else break;
		}
		int decyzja = rand() % E + A;																				//decyzja - przechowuje sposób poruszenia siê pionkiem
		zwrot = rusz_sie(wsk_plansza, pole, decyzja, plansza, POCZATEK);
		if (info == A) set_kolor(kolor_gracza);
		if (zwrot == -A) {
			pole = -A;
			continue;
		}
		else if (zwrot == -B) {
			pole = -A;
			continue;
		}
		else if (zwrot == -C) {
			pole = -A;
			continue;
		}
		else if (zwrot == -D) {
			pole = -A;
			continue;
		}
	}

	return wybor;
}

void Komputer::ustaw_pionki_neutralne(Plansza &plansza, string neutralny) {											//plansza - przechowuje wszystkie trzy plansze, neutralny - przechowuje kolor gracza neutralnego
	string *wsk_plansza = NULL;																						//wsk_plansza - wskaŸnik na pierwsze pole planszy
	string nazwa = LANCUCH;																							//nazwa - nazwa pionka, którym rusza siê gracz
	int numer = rand() % E;																							//numer - numer pola, na którym ustawiany jest pionek

	clock_t czas = clock();																							//czas - umo¿liwia dzia³anie pêtli oczekuj¹cej
	cout << "Komputer ustawia pionek gracza neutralnego.";
	while (clock() - czas < RUCH * CLOCKS_PER_SEC);
	wsk_plansza = znajdz_neutralna_gracza(neutralny, plansza);
	nazwa = wybierz_pionek();
	nazwa = jest_pionek(nazwa, neutralny, plansza);
	ustaw_pionki(wsk_plansza, nazwa, numer, plansza, neutralny);
	system("cls");
	plansza.rysuj_plansze();
}

void Komputer::ustaw_pionki_pozostale(Plansza &plansza) {															//plansza - przechowuje wszystkie trzy plansze
	string *wsk_plansza = NULL;																						//wsk_plansza - wskaŸnik na pierwsze pole planszy
	string nazwa = LANCUCH;																							//nazwa - nazwa pionka, którym rusza siê gracz
	int nr_planszy = rand() % C + A;																				//nr_planszy - numer wybranej obecnie planszy
	int numer = rand() % E;																							//numer - numer pola, na którym ustawiany jest pionek

	clock_t czas = clock();																							//czas - umo¿liwia dzia³anie pêtli oczekuj¹cej
	cout << "Komputer ustawia swoj pionek.";
	while (clock() - czas < RUCH * CLOCKS_PER_SEC);
	nr_planszy = sprawdz_plansze(nr_planszy, plansza);
	wsk_plansza = ustaw_plansze(nr_planszy, plansza);
	nazwa = wybierz_pionek();
	nazwa = jest_pionek(nazwa, kolor, plansza);
	ustaw_pionki(wsk_plansza, nazwa, numer, plansza, kolor);
	system("cls");
	plansza.rysuj_plansze();
}