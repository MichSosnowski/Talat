#include "Gracz.h"
#include "global.h"
#include <iostream>
#include <Windows.h>

HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);

//sta³e definiuj¹ce kolory
#define NIEBIESKI SetConsoleTextAttribute(hOut1, FOREGROUND_BLUE)															//kolor niebieski
#define CZERWONY SetConsoleTextAttribute(hOut1, FOREGROUND_RED)																//kolor czerwony
#define FIOLETOWY SetConsoleTextAttribute(hOut1, FOREGROUND_RED | FOREGROUND_BLUE)											//kolor fioletowy
#define BIALY SetConsoleTextAttribute(hOut1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)							//kolor bia³y

#define PRAWDA 1																											//wartoœæ prawdziwa steruj¹ca pêtl¹ while
#define POCZATEK 0																											//wartoœæ pocz¹tkowa wybranych zmiennych i pól
#define POLA 25																												//iloœæ pól na jednej planszy
#define LANCUCH "\0"																										//³añcuch zerowy s³u¿¹cy do inicjalizacji zmiennych ³añcuchowych

using namespace std;

Gracz::Gracz(string nazwa) : nick(nazwa), nazwa_pliku(nazwa), kolor("brak"), punkty(POCZATEK) {								//nazwa - przechowuje tymczasowo nick gracza,którym inicjalizowany jest obiekt
	nazwa_pliku += "-gra.txt";
}

void Gracz::wczytaj_gre(Plansza &plansza, Gracz &gracz) {																	//plansza - przechowuje wszystkie trzy plansze, gracz - przechowuje dane drugiego gracza (dane pierwszego gracza przechowuje obiekt wywo³uj¹cy metodê)
	gra.open(nazwa_pliku, ios_base::in | ios_base::out | ios_base::app);
	string tekst = LANCUCH;																									//tekst - przechowuje jedn¹ liniê wczytanego tekstu
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy
	int liczba = POCZATEK;																									//liczba - przechowuje iloœæ punktów zdobytych przez gracza wczytan¹ z pliku

	gra >> tekst;
	while (tekst != "przeciwnika:") gra >> tekst;
	gra >> tekst;
	gracz.set_nick(tekst);
	gra >> tekst;
	while (tekst != "gracza:") gra >> tekst;
	gra >> tekst;
	set_kolor(tekst);
	gra >> tekst;
	while (tekst != "przeciwnika:") gra >> tekst;
	gra >> tekst;
	gracz.set_kolor(tekst);
	gra >> tekst;
	while (tekst != "Plansza1:") gra >> tekst;
	wsk_plansza = plansza.get_plansza1();
	for (int i = POCZATEK; i < POLA; i++) {
		gra >> tekst;
		if (tekst == "***") *(wsk_plansza + i) = "   ";
		else *(wsk_plansza + i) = tekst;
	}
	while (tekst != "Plansza2:") gra >> tekst;
	wsk_plansza = plansza.get_plansza2();
	for (int i = POCZATEK; i < POLA; i++) {
		gra >> tekst;
		if (tekst == "***") *(wsk_plansza + i) = "   ";
		else *(wsk_plansza + i) = tekst;
	}
	while (tekst != "Plansza3:") gra >> tekst;
	wsk_plansza = plansza.get_plansza3();
	for (int i = POCZATEK; i < POLA; i++) {
		gra >> tekst;
		if (tekst == "***") *(wsk_plansza + i) = "   ";
		else *(wsk_plansza + i) = tekst;
	}
	gra >> tekst;
	while (tekst != "-") gra >> tekst;
	gra >> liczba;
	set_punkty(liczba);
	gra >> tekst;
	while (tekst != "-") gra >> tekst;
	gra >> liczba;
	gracz.set_punkty(liczba);
}

void Gracz::wpisz_plik(Gracz &gracz) {																						//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê)
	gra << "Tryb gry: ";
	if (gracz.nick == "komputer") gra << "1 vs 1 z komputerem" << endl << endl;
	else gra << "gracz vs gracz" << endl << endl;
	gra << "Nick gracza: " << nick << endl;
	gra << "Nick przeciwnika: " << gracz.nick << endl << endl;
}

void Gracz::zapisz_gre(Plansza &plansza, Gracz &gracz) {																	//plansza - przechowuje wszystkie trzy plansze, gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê)
	gra.close();
	gra.open(nazwa_pliku, ios_base::out | ios_base::trunc);

	wpisz_plik(gracz);
	wpisz_kolory(gracz);
	wpisz_plansze(plansza);
	wpisz_punkty(gracz);

	gra.close();
	gra.open(nazwa_pliku, ios_base::in | ios_base::out | ios_base::app);
}

void Gracz::znajdz_neutralne(Gracz &gracz) {																				//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê)
	if (kolor != "czerwony" && gracz.kolor != "czerwony") cout << "plansza gorna i plansza lewa.\n";
	else if (kolor != "niebieski" && gracz.kolor != "niebieski") cout << "plansza lewa i plansza prawa.\n";
	else cout << "plansza gorna i plansza prawa.\n";
}

void Gracz::wyswietl_faza_neutralne(Gracz *gracz, Plansza &plansza) {														//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê), plansza - przechowuje wszystkie trzy plansze
	cout << "Faza ustawiania pionkow:\n";
	cout << "Zgodnie z zasadami, ustawcie najpierw pionki gracza neutralnego.\n";
	cout << "Gracz neutralny ma swoje pola na planszach: ";
	znajdz_neutralne(*gracz);
	cout << "\nAby kontynuowac, nacisnij ENTER...";
	sprawdz_enter();
	system("cls");
	plansza.rysuj_plansze();
	cout << "Faza ustawiania pionkow:\n";
	plansza.wyswietl_legende();
	cout << "Nalezy ustawic 8 pionkow gracza neutralnego. Kazdy gracz ustawia po 4 pionki.\n";
	cout << "\nAby kontynuowac, nacisnij ENTER...";
	sprawdz_enter();
}

void Gracz::wyswietl_faza_pozostale(Gracz *gracz, Plansza &plansza) {														//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê), plansza - przechowuje wszystkie trzy plansze
	cout << "Faza ustawiania pionkow:\n";
	plansza.wyswietl_legende();
	cout << "Teraz ustawcie swoje wlasne pionki.\n";
	cout << "Kazdy gracz ustawia po 9 pionkow - na jednej z plansz 5, a na drugiej 4.\n";
	cout << "\nAby kontynuowac, nacisnij ENTER...";
	sprawdz_enter();
	system("cls");
	plansza.rysuj_plansze();
}

void Gracz::ustaw_pionki(string *wsk_plansza, string nazwa, int nr_pola, Plansza &plansza, string kolor) {					//wsk_plansza - wskaŸnik na pierwsze pole planszy, nazwa - nazwa pionka, który jest ustawiany, nr_pola - numer pola, na którym ustawiany jest pionek, kolor - kolor pionka
	nazwa += kolor[POCZATEK];
	if (kolor == "czerwony") {
		if (wsk_plansza == plansza.get_plansza1()) {
			while (*(wsk_plansza + E * (nr_pola - A)) != "   ") {
				cout << "To pole jest juz zajete. Prosze wybrac inne pole z pol startowych tego koloru na tej planszy: ";
				nr_pola = wybierz(A, E);
			}
			if (*(wsk_plansza + E * (nr_pola - A)) == "   ") *(wsk_plansza + E * (nr_pola - A)) = nazwa;
		}
		else {
			while (*(wsk_plansza + (nr_pola - A)) != "   ") {
				cout << "To pole jest juz zajete. Prosze wybrac inne pole z pol startowych tego koloru na tej planszy: ";
				nr_pola = wybierz(A, E);
			}
			if (*(wsk_plansza + (nr_pola - A)) == "   ") *(wsk_plansza + (nr_pola - A)) = nazwa;
		}
	}
	else if (kolor == "niebieski") {
		while (*((wsk_plansza + (POLA - E)) + (nr_pola - A)) != "   ") {
			cout << "To pole jest juz zajete. Prosze wybrac inne pole z pol startowych tego koloru na tej planszy: ";
			nr_pola = wybierz(A, E);
		}
		if (*((wsk_plansza + (POLA - E)) + (nr_pola - A)) == "   ") *((wsk_plansza + (POLA - E)) + (nr_pola - A)) = nazwa;
	}
	else if (kolor == "fioletowy") {
		if (wsk_plansza == plansza.get_plansza1()) {
			while (*((wsk_plansza + D) + E * (nr_pola - A)) != "   ") {
				cout << "To pole jest juz zajete. Prosze wybrac inne pole z pol startowych tego koloru na tej planszy: ";
				nr_pola = wybierz(A, E);
			}
			if (*((wsk_plansza + D) + E * (nr_pola - A)) == "   ") *((wsk_plansza + D) + E * (nr_pola - A)) = nazwa;
		}
		else {
			while (*(wsk_plansza + (nr_pola - A)) != "   ") {
				cout << "To pole jest juz zajete. Prosze wybrac inne pole z pol startowych tego koloru na tej planszy: ";
				nr_pola = wybierz(A, E);
			}
			if (*(wsk_plansza + (nr_pola - A)) == "   ") *(wsk_plansza + (nr_pola - A)) = nazwa;
		}
	}
}

void Gracz::wpisz_plansze(Plansza &plansza) {																				//plansza - przechowuje wszystkie trzy plansze
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy

	gra << "Plansza1: ";
	wsk_plansza = plansza.get_plansza1();
	for (int i = POCZATEK; i < POLA; i++) {
		if (*(wsk_plansza + i) == "   ") gra << "*** ";
		else gra << *(wsk_plansza + i) << " ";
	}
	gra << endl << "Plansza2: ";
	wsk_plansza = plansza.get_plansza2();
	for (int i = POCZATEK; i < POLA; i++) {
		if (*(wsk_plansza + i) == "   ") gra << "*** ";
		else gra << *(wsk_plansza + i) << " ";
	}
	gra << endl << "Plansza3: ";
	wsk_plansza = plansza.get_plansza3();
	for (int i = POCZATEK; i < POLA; i++) {
		if (*(wsk_plansza + i) == "   ") gra << "*** ";
		else gra << *(wsk_plansza + i) << " ";
	}
	gra << endl;
}

void Gracz::wpisz_kolory(Gracz &gracz) {																					//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê)
	gra << "Kolor gracza: " << get_kolor() << endl;
	gra << "Kolor przeciwnika: " << gracz.get_kolor() << endl << endl;
}

void Gracz::wpisz_punkty(Gracz &gracz) {																					//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê)
	gra << "\nIlosc punktow:\n";
	gra << nick << " - " << punkty << " punktow\n";
	gra << gracz.nick << " - " << gracz.punkty << " punktow" << endl;
}

int Gracz::otworz_plik() {
	int info = sprawdz_plik(nazwa_pliku);																					//info - informuje o tym, czy plik istnieje, czy te¿ nie

	if (info) {
		cout << "\nGracz " << nick << " ma juz jedna rozpoczeta gre.\n";
		cout << "Czy chcesz rozpoczac nowa gre i usunac postep poprzedniej, czy kontynuowac poprzednia?\n";
		cout << "Wpisz 1, jesli chcesz rozpoczac nowa gre lub wpisz 2, aby kontynuowac poprzednia.\n";
		cout << "Wybrana opcja: ";
		int decyzja = wybierz(A, B);																						//decyzja - przechowuje decyzjê podjêt¹ przez gracza
		if (decyzja == A) {
			remove(nazwa_pliku.c_str());
			gra.open(nazwa_pliku, ios_base::in | ios_base::out | ios_base::trunc);
			if (!gra.is_open()) {
				cout << "Blad otwarcia pliku " << nazwa_pliku << endl << endl;
				cout << "Koniec programu.";
				cin.get();
				exit(EXIT_FAILURE);
			}
		}
		else {
			cout << "\nAby potwierdzic wczytanie gry, bedziesz proszony ponownie o podanie twojego nicku.\n";
			cout << "Aby kontynuowac, prosze nacisnac ENTER.";
			sprawdz_enter();
			return B;
		}
		return POCZATEK;
	}
	else {
		gra.open(nazwa_pliku, ios_base::in | ios_base::out | ios_base::app);
		if (!gra.is_open()) {
			cout << "Blad otwarcia pliku " << nazwa_pliku << endl << endl;
			cout << "Koniec programu.";
			cin.get();
			exit(EXIT_FAILURE);
		}
		return POCZATEK;
	}
}

int Gracz::wyszukaj_pionek(string pionek, int nr_planszy, Plansza &plansza) {												//pionek - nazwa obecnie wybranego pionka, nr_planszy - numer obecnie wybranej planszy, plansza - przechowuje wszystkie trzy plansze
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy
	if (kolor == "czerwony") pionek += "c";
	else if (kolor == "niebieski") pionek += "n";
	else pionek += "f";
	if (nr_planszy == A) wsk_plansza = plansza.get_plansza1();
	else if (nr_planszy == B) wsk_plansza = plansza.get_plansza2();
	else wsk_plansza = plansza.get_plansza3();
	for (int i = POCZATEK; i < POLA; i++) if (*(wsk_plansza + i) == pionek) return i;
	return -A;
}

int Gracz::wybierz(int liczba1, int liczba2) {																				//liczba1 - zakres dolny wyboru, liczba2 - zakres górny wyboru
	int wybor = POCZATEK;																									//wybor - przechowuje wybór gracza

	while (!(cin >> wybor) || wybor < liczba1 || wybor > liczba2 || cin.get() != '\n') {
		cout << "Nieprawidlowy numer. Prosze wybrac ponownie: ";
		cin.clear();
		wyczysc_bufor();
	}

	return wybor;
}

int Gracz::sprawdz_plansze(int numer, Plansza &plansza) {																	//numer - numer wybranej planszy, plansza - przechowuje wszystkie trzy plansze
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy
	int info = POCZATEK;																									//info - informuje o tym, czy wszystkie pola startowe koloru obecnego gracza s¹ ju¿ zajête

	while (PRAWDA) {
		if (numer == A) {
			if (get_kolor() == "czerwony") {
				wsk_plansza = plansza.get_plansza1();
				for (int i = POCZATEK; i < E; i++) if (*(wsk_plansza + E * i) != "   ") info++;
				if (info == E) {
					cout << "Pola startowe twojego koloru na tej planszy sa juz zajete. Podaj inny numer planszy z twoim kolorem: ";
					numer = wybierz(A, C);
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "fioletowy") {
				wsk_plansza = plansza.get_plansza1();
				for (int i = POCZATEK; i < E; i++) if (*((wsk_plansza + D) + E * i) != "   ") info++;
				if (info == E) {
					cout << "Pola startowe twojego koloru na tej planszy sa juz zajete. Podaj inny numer planszy z twoim kolorem: ";
					numer = wybierz(A, C);
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "niebieski") {
				cout << "To nie jest twoja plansza. Podaj numer planszy ze swoim kolorem: ";
				numer = wybierz(A, C);
			}
		}
		else if (numer == B) {
			if (get_kolor() == "czerwony") {
				wsk_plansza = plansza.get_plansza2();
				for (int i = POCZATEK; i < E; i++) if (*(wsk_plansza + i) != "   ") info++;
				if (info == E) {
					cout << "Pola startowe twojego koloru na tej planszy sa juz zajete. Podaj inny numer planszy z twoim kolorem: ";
					numer = wybierz(A, C);
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "niebieski") {
				wsk_plansza = plansza.get_plansza2();
				for (int i = POCZATEK; i < E; i++) if (*((wsk_plansza + (POLA - E)) + i) != "   ") info++;
				if (info == E) {
					cout << "Pola startowe twojego koloru na tej planszy sa juz zajete. Podaj inny numer planszy z twoim kolorem: ";
					numer = wybierz(A, C);
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "fioletowy") {
				cout << "To nie jest twoja plansza. Podaj numer planszy ze swoim kolorem: ";
				numer = wybierz(A, C);
			}
		}
		else if (numer == C) {
			if (get_kolor() == "niebieski") {
				wsk_plansza = plansza.get_plansza3();
				for (int i = POCZATEK; i < E; i++) if (*((wsk_plansza + (POLA - E)) + i) != "   ") info++;
				if (info == E) {
					cout << "Pola startowe twojego koloru na tej planszy sa juz zajete. Podaj inny numer planszy z twoim kolorem: ";
					numer = wybierz(A, C);
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "fioletowy") {
				wsk_plansza = plansza.get_plansza3();
				for (int i = POCZATEK; i < E; i++) if (*(wsk_plansza + i) != "   ") info++;
				if (info == E) {
					cout << "Pola startowe twojego koloru na tej planszy sa juz zajete. Podaj inny numer planszy z twoim kolorem: ";
					numer = wybierz(A, C);
					info = POCZATEK;
				}
				else info = -A;
			}
			else if (get_kolor() == "czerwony") {
				cout << "To nie jest twoja plansza. Podaj numer planszy ze swoim kolorem: ";
				numer = wybierz(A, C);
			}
		}
		if (info == -A) break;
	}

	return numer;
}

int Gracz::znajdz_plansze(int numer, string neutralny) {																	//numer - numer obecnie wybranej planszy, neutralny - kolor gracza neutralnego
	if (numer == A) {
		if (get_kolor() == "niebieski") {
			set_kolor(neutralny);
			return A;
		}
		return -A;
	}
	else if (numer == B) {
		if (get_kolor() == "fioletowy") {
			set_kolor(neutralny);
			return A;
		}
		return -A;
	}
	else if (numer == C) {
		if (get_kolor() == "czerwony") {
			set_kolor(neutralny);
			return A;
		}
		return -A;
	}
	else return -A;
}

int Gracz::zbij(string *wsk_plansza, int pole, int ile, int info, int tryb = POCZATEK) {									//wsk_plansza - wskaŸnik na pierwsze pole planszy, pole - numer pola, na którym stoi pionek, ile - informuje o tym, jaki ruch jest wykonywany, info - informuje o tym, czy ju¿ zosta³y doliczone graczowi punkty, tryb - ustawia metodê tak, aby s³u¿y³a do zbijania, a innym razem to sprawdzania, czy plansza jest zamro¿ona
	string pionek_zbijajacy = *(wsk_plansza + pole);																		//pionek_zbijaj¹cy - przechowuje nazwê pionke zbijaj¹cego
	string pionek_zbijany = *(wsk_plansza + pole + ile);																	//pionek_zbijany - przechowuje nazwê pionka zbijanego

	if (pionek_zbijajacy[B] == pionek_zbijany[B]) {
		if (!tryb) {
			if (info == A) punkty -= C;
			return -B;
		}
		else return A;
	}
	if ((pionek_zbijajacy[POCZATEK] == 'm' && pionek_zbijajacy[A] == 'T') && (pionek_zbijany[POCZATEK] == 'd' && pionek_zbijany[A] == 'S')) {
		if (!tryb) {
			*(wsk_plansza + pole + ile) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
			punkty += E;
			return POCZATEK;
		}
		else return POCZATEK;
	}
	if (pionek_zbijany[POCZATEK] == 'm' && pionek_zbijajacy[POCZATEK] == 's') {
		if (!tryb) {
			*(wsk_plansza + pole + ile) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
			punkty += E;
			return POCZATEK;
		}
		else return POCZATEK;
	}
	if (pionek_zbijany[POCZATEK] == 's' && pionek_zbijajacy[POCZATEK] == 'd') {
		if (!tryb) {
			*(wsk_plansza + pole + ile) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
			punkty += E;
			return POCZATEK;
		}
		else return POCZATEK;
	}
	if (pionek_zbijany[POCZATEK] == pionek_zbijajacy[POCZATEK]) {
		if (pionek_zbijajacy[A] == 'S') {
			if (!tryb) {
				*(wsk_plansza + pole + ile) = *(wsk_plansza + pole);
				*(wsk_plansza + pole) = "   ";
				punkty += E;
				return POCZATEK;
			}
			else return POCZATEK;
		}
		if (pionek_zbijajacy[A] == 'K' && pionek_zbijany[A] == 'T') {
			if (!tryb) {
				*(wsk_plansza + pole + ile) = *(wsk_plansza + pole);
				*(wsk_plansza + pole) = "   ";
				punkty += E;
				return POCZATEK;
			}
			else return POCZATEK;
		}
	}
	if (!tryb) {
		if (info == A) punkty -= C;
		return -C;
	}
	else return A;
}

int Gracz::rusz_sie(string *wsk_plansza, int pole, int ile, Plansza &plansza, int tryb = POCZATEK) {						//wsk_plansza - wskaŸnik na pierwsze pole planszy, pole - numer pola, na którym stoi pionek, ile - informuje o tym, jaki ruch jest wykonywany, plansza - przechowuje wszystkie trzy plansze, tryb - ustawia metodê tak, aby s³u¿y³a do ruszania siê, a innym razem to sprawdzania, czy plansza jest zamro¿ona

	if (wsk_plansza == plansza.get_plansza1()) {
		if (get_kolor() == "czerwony") return sprawdz_ruch1(wsk_plansza, pole, ile, tryb);
		else if (get_kolor() == "fioletowy") return sprawdz_ruch2(wsk_plansza, pole, ile, tryb);
	}
	else if (wsk_plansza == plansza.get_plansza2()) {
		if (get_kolor() == "czerwony") return sprawdz_ruch3(wsk_plansza, pole, ile, tryb);
		else if (get_kolor() == "niebieski") return sprawdz_ruch4(wsk_plansza, pole, ile, tryb);
	}
	else {
		if (get_kolor() == "niebieski") return sprawdz_ruch4(wsk_plansza, pole, ile, tryb);
		else if (get_kolor() == "fioletowy") return sprawdz_ruch3(wsk_plansza, pole, ile, tryb);
	}

	return POCZATEK;
}

int Gracz::sprawdz_ruch1(string *wsk_plansza, int pole, int ile, int tryb) {												//wsk_plansza - wskaŸnik na pierwsze pole planszy, pole - numer pola, na którym stoi pionek, ile - informuje o tym, jaki ruch jest wykonywany, tryb - ustawia metodê tak, aby s³u¿y³a do wykonywania ruchu, a innym razem to sprawdzania, czy plansza jest zamro¿ona
	int info = POCZATEK;																									//info - informuje o tym, czy punkty zosta³y ju¿ doliczone graczowi, czy te¿ nie
	if (ile == A) {
		if (!tryb) {
			if (pole + A == E || pole + A == J || pole + A == O || pole + A == T || pole + A == Y) return -A;
			if (pole + B == E || pole + B == J || pole + B == O || pole + B == T || pole + B == Y) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole + A) != "   ") return zbij(wsk_plansza, pole, A, info, tryb);
			*(wsk_plansza + pole + A) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole + A == E || pole + A == J || pole + A == O || pole + A == T || pole + A == Y) return A;
			if (*(wsk_plansza + pole + A) != "   ") return zbij(wsk_plansza, pole, A, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == B) {
		if (!tryb) {
			if (pole - D == -D || pole - D == -C || pole - D == -B || pole - D == -A || pole - D == POCZATEK || pole - D == E || pole - D == J || pole - D == O || pole - D == T) return -A;
			if (pole - C == D || pole - C == J || pole - C == O || pole - C == T) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole - D) != "   ") return zbij(wsk_plansza, pole, -D, info, tryb);
			*(wsk_plansza + pole - D) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole - D == -D || pole - D == -C || pole - D == -B || pole - D == -A || pole - D == POCZATEK || pole - D == E || pole - D == J || pole - D == O || pole - D == T) return A;
			if (*(wsk_plansza + pole - D) != "   ") return zbij(wsk_plansza, pole, -D, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == C) {
		if (!tryb) {
			if (pole + F == J || pole + F == O || pole + F == T || pole + F == Y || pole + F == Z4 || pole + F == Z || pole + F == Z1 || pole + F == Z2 || pole + F == Z3) return -A;
			if (pole + G == J || pole + G == O || pole + G == T || pole + G == Y) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole + F) != "   ") return zbij(wsk_plansza, pole, F, info, tryb);
			*(wsk_plansza + pole + F) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole + F == J || pole + F == O || pole + F == T || pole + F == Y || pole + F == Z4 || pole + F == Z || pole + F == Z1 || pole + F == Z2 || pole + F == Z3) return A;
			if (*(wsk_plansza + pole + F) != "   ") return zbij(wsk_plansza, pole, F, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == D) {
		if (!tryb) {
			if (pole - E == -E || pole - E == -D || pole - E == -C || pole - E == -B || pole - E == -A) return -A;
			if (*(wsk_plansza + pole - E) == "   ") return -D;
			if (*(wsk_plansza + pole - E) != "   ") return zbij(wsk_plansza, pole, -E, info, tryb);
		}
		else {
			if (pole - E == -E || pole - E == -D || pole - E == -C || pole - E == -B || pole - E == -A) return A;
			if (*(wsk_plansza + pole - E) == "   ") return A;
			if (*(wsk_plansza + pole - E) != "   ") return zbij(wsk_plansza, pole, -E, info, tryb);
		}
	}
	else {
		if (!tryb) {
			if (pole + E == Y || pole + E == Z || pole + E == Z1 || pole + E == Z2 || pole + E == Z3) return -A;
			if (*(wsk_plansza + pole + E) == "   ") return -D;
			if (*(wsk_plansza + pole + E) != "   ") return zbij(wsk_plansza, pole, E, info, tryb);
		}
		else {
			if (pole + E == Y || pole + E == Z || pole + E == Z1 || pole + E == Z2 || pole + E == Z3) return A;
			if (*(wsk_plansza + pole + E) == "   ") return A;
			if (*(wsk_plansza + pole + E) != "   ") return zbij(wsk_plansza, pole, E, info, tryb);
		}
	}
	return POCZATEK;
}

int Gracz::sprawdz_ruch2(string *wsk_plansza, int pole, int ile, int tryb) {												//wsk_plansza - wskaŸnik na pierwsze pole planszy, pole - numer pola, na którym stoi pionek, ile - informuje o tym, jaki ruch jest wykonywany, tryb - ustawia metodê tak, aby s³u¿y³a do wykonywania ruchu, a innym razem to sprawdzania, czy plansza jest zamro¿ona
	int info = POCZATEK;																									//info - informuje o tym, czy punkty zosta³y ju¿ doliczone graczowi, czy te¿ nie
	if (ile == A) {
		if (!tryb) {
			if (pole - A == -A || pole - A == D || pole - A == I || pole - A == N || pole - A == S) return -A;
			if (pole - B == -A || pole - B == D || pole - B == I || pole - B == N || pole - B == S) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole - A) != "   ") return zbij(wsk_plansza, pole, -A, info, tryb);
			*(wsk_plansza + pole - A) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole - A == -A || pole - A == D || pole - A == I || pole - A == N || pole - A == S) return A;
			if (*(wsk_plansza + pole - A) != "   ") return zbij(wsk_plansza, pole, -A, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == B) {
		if (!tryb) {
			if (pole + D == D || pole + D == I || pole + D == N || pole + D == S || pole + D == X || pole + D == Y || pole + D == Z || pole + D == Z1 || pole + D == Z2) return -A;
			if (pole + C == D || pole + C == I || pole + C == N || pole + C == S) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole + D) != "   ") return zbij(wsk_plansza, pole, D, info, tryb);
			*(wsk_plansza + pole + D) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole + D == D || pole + D == I || pole + D == N || pole + D == S || pole + D == X || pole + D == Y || pole + D == Z || pole + D == Z1 || pole + D == Z2) return A;
			if (*(wsk_plansza + pole + D) != "   ") return zbij(wsk_plansza, pole, D, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == C) {
		if (!tryb) {
			if (pole - F == -B || pole - F == -C || pole - F == -D || pole - F == -E || pole - F == -F || pole - F == -A || pole - F == D || pole - F == I || pole - F == N) return -A;
			if (pole - G == -A || pole - G == D || pole - F == I || pole - F == N) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole - F) != "   ") return zbij(wsk_plansza, pole, -F, info, tryb);
			*(wsk_plansza + pole - F) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole - F == -B || pole - F == -C || pole - F == -D || pole - F == -E || pole - F == -F || pole - F == -A || pole - F == D || pole - F == I || pole - F == N) return A;
			if (*(wsk_plansza + pole - F) != "   ") return zbij(wsk_plansza, pole, -F, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == D) {
		if (!tryb) {
			if (pole + E == Y || pole + E == Z || pole + E == Z1 || pole + E == Z2 || pole + E == Z3) return -A;
			if (*(wsk_plansza + pole + E) == "   ") return -D;
			if (*(wsk_plansza + pole + E) != "   ") return zbij(wsk_plansza, pole, E, info, tryb);
		}
		else {
			if (pole + E == Y || pole + E == Z || pole + E == Z1 || pole + E == Z2 || pole + E == Z3) return A;
			if (*(wsk_plansza + pole + E) == "   ") return A;
			if (*(wsk_plansza + pole + E) != "   ") return zbij(wsk_plansza, pole, E, info, tryb);
		}
	}
	else {
		if (!tryb) {
			if (pole - E == -E || pole - E == -D || pole - E == -C || pole - E == -B || pole - E == -A) return -A;
			if (*(wsk_plansza + pole - E) == "   ") return -D;
			if (*(wsk_plansza + pole - E) != "   ") return zbij(wsk_plansza, pole, -E, info, tryb);
		}
		else {
			if (pole - E == -E || pole - E == -D || pole - E == -C || pole - E == -B || pole - E == -A) return A;
			if (*(wsk_plansza + pole - E) == "   ") return A;
			if (*(wsk_plansza + pole - E) != "   ") return zbij(wsk_plansza, pole, -E, info, tryb);
		}
	}
	return POCZATEK;
}

int Gracz::sprawdz_ruch3(string *wsk_plansza, int pole, int ile, int tryb) {												//wsk_plansza - wskaŸnik na pierwsze pole planszy, pole - numer pola, na którym stoi pionek, ile - informuje o tym, jaki ruch jest wykonywany, tryb - ustawia metodê tak, aby s³u¿y³a do wykonywania ruchu, a innym razem to sprawdzania, czy plansza jest zamro¿ona
	int info = POCZATEK;																									//info - informuje o tym, czy punkty zosta³y ju¿ doliczone graczowi, czy te¿ nie
	if (ile == A) {
		if (!tryb) {
			if (pole + E == Y || pole + E == Z || pole + E == Z1 || pole + E == Z2 || pole + E == Z3) return -A;
			if (pole + J == Y || pole + J == Z || pole + J == Z1 || pole + J == Z2 || pole + J == Z3) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole + E) != "   ") return zbij(wsk_plansza, pole, E, info, tryb);
			*(wsk_plansza + pole + E) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole + E == Y || pole + E == Z || pole + E == Z1 || pole + E == Z2 || pole + E == Z3) return A;
			if (*(wsk_plansza + pole + E) != "   ") return zbij(wsk_plansza, pole, E, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == B) {
		if (!tryb) {
			if (pole + F == J || pole + F == O || pole + F == T || pole + F == Y || pole + F == Z4 || pole + F == Z || pole + F == Z1 || pole + F == Z2 || pole + F == Z3) return -A;
			if (pole + K == Z || pole + K == Z1 || pole + K == Z2 || pole + K == Z3) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole + F) != "   ") return zbij(wsk_plansza, pole, F, info, tryb);
			*(wsk_plansza + pole + F) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole + F == J || pole + F == O || pole + F == T || pole + F == Y || pole + F == Z4 || pole + F == Z || pole + F == Z1 || pole + F == Z2 || pole + F == Z3) return A;
			if (*(wsk_plansza + pole + F) != "   ") return zbij(wsk_plansza, pole, F, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == C) {
		if (!tryb) {
			if (pole + D == D || pole + D == I || pole + D == N || pole + D == S || pole + D == X || pole + D == Y || pole + D == Z || pole + D == Z1 || pole + D == Z2) return -A;
			if (pole + I == Y || pole + I == Z || pole + I == Z1 || pole + I == Z2) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole + D) != "   ") return zbij(wsk_plansza, pole, D, info, tryb);
			*(wsk_plansza + pole + D) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole + D == D || pole + D == I || pole + D == N || pole + D == S || pole + D == X || pole + D == Y || pole + D == Z || pole + D == Z1 || pole + D == Z2) return A;
			if (*(wsk_plansza + pole + D) != "   ") return zbij(wsk_plansza, pole, D, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == D) {
		if (!tryb) {
			if (pole + A == E || pole + A == J || pole + A == O || pole + A == T || pole + A == Y) return -A;
			if (*(wsk_plansza + pole + A) == "   ") return -D;
			if (*(wsk_plansza + pole + A) != "   ") return zbij(wsk_plansza, pole, A, info, tryb);
		}
		else {
			if (pole + A == E || pole + A == J || pole + A == O || pole + A == T || pole + A == Y) return A;
			if (*(wsk_plansza + pole + A) == "   ") return A;
			if (*(wsk_plansza + pole + A) != "   ") return zbij(wsk_plansza, pole, A, info, tryb);
		}
	}
	else {
		if (!tryb) {
			if (pole - A == -A || pole - A == D || pole - A == I || pole - A == N || pole - A == S) return -A;
			if (*(wsk_plansza + pole - A) == "   ") return -D;
			if (*(wsk_plansza + pole - A) != "   ") return zbij(wsk_plansza, pole, -A, info, tryb);
		}
		else {
			if (pole - A == -A || pole - A == D || pole - A == I || pole - A == N || pole - A == S) return A;
			if (*(wsk_plansza + pole - A) == "   ") return A;
			if (*(wsk_plansza + pole - A) != "   ") return zbij(wsk_plansza, pole, -A, info, tryb);
		}
	}
	return POCZATEK;
}

int Gracz::sprawdz_ruch4(string *wsk_plansza, int pole, int ile, int tryb) {												//wsk_plansza - wskaŸnik na pierwsze pole planszy, pole - numer pola, na którym stoi pionek, ile - informuje o tym, jaki ruch jest wykonywany, tryb - ustawia metodê tak, aby s³u¿y³a do wykonywania ruchu, a innym razem to sprawdzania, czy plansza jest zamro¿ona
	int info = POCZATEK;																									//info - informuje o tym, czy punkty zosta³y ju¿ doliczone graczowi, czy te¿ nie
	if (ile == A) {
		if (!tryb) {
			if (pole - E == -E || pole - E == -D || pole - E == -C || pole - E == -B || pole - E == -A) return -A;
			if (pole - J == -E || pole - J == -D || pole - J == -C || pole - J == -B || pole - J == -A) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole - E) != "   ") return zbij(wsk_plansza, pole, -E, info, tryb);
			*(wsk_plansza + pole - E) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole - E == -E || pole - E == -D || pole - E == -C || pole - E == -B || pole - E == -A) return A;
			if (*(wsk_plansza + pole - E) != "   ") return zbij(wsk_plansza, pole, -E, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == B) {
		if (!tryb) {
			if (pole - F == -F || pole - F == -E || pole - F == -D || pole - F == -C || pole - F == -B || pole - F == -A || pole - F == D || pole - F == I || pole - F == N) return -A;
			if (pole - K == -E || pole - K == -D || pole - K == -C || pole - K == -B) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole - F) != "   ") return zbij(wsk_plansza, pole, -F, info, tryb);
			*(wsk_plansza + pole - F) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole - F == -F || pole - F == -E || pole - F == -D || pole - F == -C || pole - F == -B || pole - F == -A || pole - F == D || pole - F == I || pole - F == N) return A;
			if (*(wsk_plansza + pole - F) != "   ") return zbij(wsk_plansza, pole, -F, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == C) {
		if (!tryb) {
			if (pole - D == -D || pole - D == -C || pole - D == -B || pole - D == -A || pole - D == POCZATEK || pole - D == D || pole - D == J || pole - D == O || pole - D == T) return -A;
			if (pole - I == -D || pole - I == -C || pole - I == -B || pole - I == -A) {
				punkty += C;
				info = A;
			}
			if (*(wsk_plansza + pole - D) != "   ") return zbij(wsk_plansza, pole, -D, info, tryb);
			*(wsk_plansza + pole - D) = *(wsk_plansza + pole);
			*(wsk_plansza + pole) = "   ";
		}
		else {
			if (pole - D == -D || pole - D == -C || pole - D == -B || pole - D == -A || pole - D == POCZATEK || pole - D == D || pole - D == J || pole - D == O || pole - D == T) return A;
			if (*(wsk_plansza + pole - D) != "   ") return zbij(wsk_plansza, pole, -D, info, tryb);
		}
		return POCZATEK;
	}
	else if (ile == D) {
		if (!tryb) {
			if (pole - A == -A || pole - A == D || pole - A == I || pole - A == N || pole - A == S) return -A;
			if (*(wsk_plansza + pole - A) == "   ") return -D;
			if (*(wsk_plansza + pole - A) != "   ") return zbij(wsk_plansza, pole, -A, info, tryb);
		}
		else {
			if (pole - A == -A || pole - A == D || pole - A == I || pole - A == N || pole - A == S) return A;
			if (*(wsk_plansza + pole - A) == "   ") return A;
			if (*(wsk_plansza + pole - A) != "   ") return zbij(wsk_plansza, pole, -A, info, tryb);
		}
	}
	else {
		if (!tryb) {
			if (pole + A == E || pole + A == J || pole + A == O || pole + A == T || pole + A == Y) return -A;
			if (*(wsk_plansza + pole + A) == "   ") return -D;
			if (*(wsk_plansza + pole + A) != "   ") return zbij(wsk_plansza, pole, A, info, tryb);
		}
		else {
			if (pole + A == E || pole + A == J || pole + A == O || pole + A == T || pole + A == Y) return A;
			if (*(wsk_plansza + pole + A) == "   ") return A;
			if (*(wsk_plansza + pole + A) != "   ") return zbij(wsk_plansza, pole, A, info, tryb);
		}
	}
	return POCZATEK;
}

string Gracz::ustal_kolory(Gracz &gracz, int ilosc) {																		//gracz - przechowuje dane drugiego gracza (dane pierwszego gracza - obiekt wywo³uj¹cy metodê), ilosc - ustala sposób wyœwietlania zdania wprowadzaj¹cego do wyboru kolorów
	string barwa;																											//barwa - przechowuje aktaulnie wybrany kolor
	if (ilosc == A) cout << "\nGracz " << nick << " ustala kolory pozostalych graczy.\n";
	else cout << "\nZdecyduj o kolorach pozostalych graczy.\n";
	cout << "Kolory do wyboru:\n- niebieski,\n- czerwony,\n- fioletowy.\n";
	cout << "Prosze podac przy przypisywaniu pelne nazwy kolorow.\n\n";
	cout << "Czas wyboru:\n";
	cout << "Twoj kolor: ";
	cin >> kolor;
	while (kolor != "czerwony" && kolor != "niebieski" && kolor != "fioletowy") {
		cout << "\nNie znam takiego koloru. Podaj kolor ponownie: ";
		kolor = "\0";
		cin >> kolor;
	}
	wyczysc_bufor();
	cout << "\nKolor twojego przeciwnika: ";
	cin >> gracz.kolor;
	while (gracz.kolor == kolor || (gracz.kolor != "czerwony" && gracz.kolor != "niebieski" && gracz.kolor != "fioletowy")) {
		if (gracz.kolor == kolor) cout << "\nTen kolor zostal juz zajety. Podaj inny kolor z listy wymienionej wyzej: ";
		else cout << "\nNie znam takiego koloru. Podaj inny kolor z listy wymienionej wyzej: ";
		gracz.kolor = "\0";
		cin >> gracz.kolor;
	}
	wyczysc_bufor();
	cout << "\nGracz neutralny otrzymuje kolor ";
	if (kolor != "czerwony" && gracz.kolor != "czerwony") barwa = "czerwony";
	else if (kolor != "niebieski" && gracz.kolor != "niebieski") barwa = "niebieski";
	else barwa = "fioletowy";
	cout << barwa << ".\n\n";
	cout << "Aby kontynuowac, nacisnij ENTER...";
	sprawdz_enter();
	return barwa;
}

string Gracz::zla_nazwa_pionka(string nazwa) {																				//nazwa - przechowuje nazwê obecnie wybranego pionka
	while (nazwa != "mT" && nazwa != "sT" && nazwa != "dT" && nazwa != "mK" && nazwa != "sK" && nazwa != "dK" && nazwa != "mS" && nazwa != "sS" && nazwa != "dS") {
		cout << "Niepoprawna nazwa pionka. Podaj poprawna nazwe pionka: ";
		cin >> nazwa;
	}
	return nazwa;
}

string * Gracz::ustaw_plansze(int numer, Plansza &plansza) {																//numer - numer obecnie wybranej planszy, plansza - przechowuje wszystkie trzy plansze
	if (numer == A) return plansza.get_plansza1();
	else if (numer == B) return plansza.get_plansza2();
	else return plansza.get_plansza3();
}

string * Gracz::znajdz_neutralna_gracza(string neutralny, Plansza &plansza) {												//neutralny - przechowuje kolor gracza neutralnego, plansza - przechowuje wszystkie trzy plansze
	string * wsk_plansza = NULL;																							//wsk_plansza - wskaŸnik na pierwsze pole planszy
	if (get_kolor() == "czerwony" && (neutralny == "niebieski" || neutralny == "fioletowy")) {
		wsk_plansza = plansza.get_plansza3();
		cout << "plansza prawa (gracz neutralny - " << neutralny << ")\n";
	}
	else if (get_kolor() == "niebieski" && (neutralny == "czerwony" || neutralny == "fioletowy")) {
		wsk_plansza = plansza.get_plansza1();
		cout << "plansza gorna (gracz neutralny - " << neutralny << ")\n";
	}
	else if (get_kolor() == "fioletowy" && (neutralny == "czerwony" || neutralny == "niebieski")) {
		wsk_plansza = plansza.get_plansza2();
		cout << "plansza lewa (gracz neutralny - " << neutralny << ")\n";
	}
	return wsk_plansza;
}

string Gracz::jest_pionek(string pionek, string kolor, Plansza &plansza) {													//pionek - nazwa obecnie wybranego pionka, kolor - kolor pionka, plansza - przechowuje wszystkie trzy plansze
	Gracz temp;																												//obiekt tymczasowy Gracz
	int nr_planszy = POCZATEK;																								//nr_planszy - numer planszy
	int info1 = POCZATEK;																									//info1 - informuje o tym, czy na danej planszy jest pionek
	int info2 = POCZATEK;																									//info2 - informuje o tym, czy na danej planszy jest pionek
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

		if (info1 != -1 || info2 != -1) cout << "Ten pionek juz jest ustawiony. Wybierz inny pionek: ";
		else break;
		cin >> pionek;
	}

	return pionek;
}

int Gracz::wykonaj_ruch(Plansza &plansza, string neutralny) {																//plansza - przechowuje wszystkie trzy plansze, neutralny - przechowuje kolor gracza neutralnego
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy
	string nazwa = LANCUCH;																									//nazwa - nazwa pionka, którym rusza siê gracz
	string kolor_gracza = get_kolor();																						//kolor_gracza - kolor gracza obecnie wykonuj¹cego ruch
	int pole = -A;																											//pole - informuje o tym, czy pole jest puste, czy nie
	int zwrot = -A;																											//zwrot - informuje, czy uda³o siê wykonaæ ruch, czy te¿ nie
	int nr_planszy = POCZATEK;																								//nr_planszy - numer planszy, która nie jest zamro¿ona

	while (zwrot) {
		system("cls");
		plansza.rysuj_plansze();
		cout << "Ruchu dokonuje gracz ";
		if (get_kolor() == "czerwony") CZERWONY;
		else if (get_kolor() == "niebieski") NIEBIESKI;
		else FIOLETOWY;
		cout << get_nick() << endl;
		BIALY;
		nr_planszy = plansze_grane(plansza, neutralny);
		if (!nr_planszy) break;
		int info = znajdz_plansze(nr_planszy, neutralny);																	//info - jeœli jest pozytywne, tzn. ¿e nast¹pi³a zmiana koloru
		if (info == A) cout << "Gracz zdecydowal ruszyc sie pionkiem gracza neutralnego.\n";
		wsk_plansza = ustaw_plansze(nr_planszy, plansza);
		cout << "Podaj nazwe pionka, ktorym chcesz sie poruszyc: ";
		cin >> nazwa;
		nazwa = zla_nazwa_pionka(nazwa);
		while (pole == -A) {
			pole = wyszukaj_pionek(nazwa, nr_planszy, plansza);
			if (pole == -A) {
				cout << "Nie ma takiego pionka twojego koloru na tej planszy.\n";
				cout << "Podaj inny pionek twojego koloru z tej planszy: ";
				cin >> nazwa;
				nazwa = zla_nazwa_pionka(nazwa);
			}
			else break;
		}
		system("cls");
		plansza.rysuj_plansze();
		cout << "Ruchu dokonuje gracz ";
		if (get_kolor() == "czerwony") CZERWONY;
		else if (get_kolor() == "niebieski") NIEBIESKI;
		else FIOLETOWY;
		cout << get_nick() << endl;
		BIALY;
		cout << "W jaki sposob chcesz sie poruszyc tym pionkiem?\n";
		cout << "1. O jedno pole do przodu\n";
		cout << "2. O jedno pole na ukos w lewo\n";
		cout << "3. O jedno pole na ukos w prawo\n";
		cout << "4. O jedno pole w lewo w przypadku bicia\n";
		cout << "5. O jedno pole w prawo w przypadku bicia\n\n";
		cout << "Wpisz numer z wybranej opcji: ";
		int decyzja = wybierz(A, E);																						//decyzja - przechowuje sposób poruszenia siê pionkiem
		zwrot = rusz_sie(wsk_plansza, pole, decyzja, plansza, POCZATEK);
		if (info == A) set_kolor(kolor_gracza);
		if (zwrot == -A) {
			cout << "Nie wolno wychodzic pionkami poza plansze!!!\n";
			cout << "Po wcisnieciu ENTER, bedziesz mogl wykonac swoj ruch ponownie.\n";
			sprawdz_enter();
			pole = -A;
		}
		else if (zwrot == -B) {
			cout << "Nie mozesz zbic swoich wlasnych pionkow.\n";
			cout << "Po wcisnieciu ENTER, bedziesz mogl wykonac swoj ruch ponownie.\n";
			sprawdz_enter();
			pole = -A;
		}
		else if (zwrot == -C) {
			cout << "Brak mozliwosci wykonania takiego zbicia.\n";
			cout << "Po wcisnieciu ENTER, bedziesz mogl wykonac swoj ruch ponownie.\n";
			sprawdz_enter();
			pole = -A;
		}
		else if (zwrot == -D) {
			cout << "Nie mozesz wykonac tego ruchu jesli nie zbijasz pionka przeciwnika.\n";
			cout << "Po wcisnieciu ENTER, bedziesz mogl wykonac swoj ruch ponownie.\n";
			sprawdz_enter();
			pole = -A;
		}
	}

	return nr_planszy;
}

void Gracz::ustaw_pionki_neutralne(Plansza &plansza, string neutralny) {													//plansza - przechowuje wszystkie trzy plansze, neutralny - przechowuje kolor gracza neutralnego
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy
	cout << "Faza ustawiania pionkow:\n";
	plansza.wyswietl_legende();
	cout << "Ustawia gracz ";
	if (get_kolor() == "czerwony") CZERWONY;
	else if (get_kolor() == "niebieski") NIEBIESKI;
	else FIOLETOWY;
	cout << get_nick();
	BIALY;
	cout << " - plansza gracza neutralnego dla tego gracza to ";
	wsk_plansza = znajdz_neutralna_gracza(neutralny, plansza);
	if (wsk_plansza == plansza.get_plansza1()) cout << "Pola startowe dla kazdego koloru sa liczone z gory na dol liczbami od 1 do 5.\n";
	else cout << "Pola startowe dla kazdego koloru sa liczone od lewej do prawej liczbami od 1 do 5.\n";
	cout << "Podaj numer pola startowego, na ktorym chcesz postawic pionek: ";
	int numer = wybierz(A, E);																								//numer - przechowuje numer pola startowego, na którym gracz chce postawiæ pionek
	cout << "Wpisz nazwe pionka, ktory chcesz postawic: ";
	string nazwa;																											//nazwa - przechowuje nazwê pionka, którym gracz chce siê ruszyæ
	cin >> nazwa;
	nazwa = zla_nazwa_pionka(nazwa);
	nazwa = jest_pionek(nazwa, neutralny, plansza);
	ustaw_pionki(wsk_plansza, nazwa, numer, plansza, neutralny);
	system("cls");
	plansza.rysuj_plansze();
}

void Gracz::ustaw_pionki_pozostale(Plansza &plansza) {																		//plansza - przechowuje wszystkie trzy plansze
	string *wsk_plansza = NULL;																								//wsk_plansza - wskaŸnik na pierwsze pole planszy
	cout << "Faza ustawiania pionkow:\n";
	plansza.wyswietl_legende();
	cout << "Ustawia gracz ";
	if (get_kolor() == "czerwony") CZERWONY;
	else if (get_kolor() == "niebieski") NIEBIESKI;
	else FIOLETOWY;
	cout << get_nick();
	BIALY;
	cout << "\nPlansza gorna ma numer 1, plansza lewa ma numer 2, a plansza prawa - numer 3.\n";
	cout << "Podaj numer planszy, na ktorej chcesz postawic swoj pionek: ";
	int nr_planszy = wybierz(A, C);																							//nr_planszy - przechowuje numer wybranej planszy
	nr_planszy = sprawdz_plansze(nr_planszy, plansza);
	wsk_plansza = ustaw_plansze(nr_planszy, plansza);
	if (wsk_plansza == plansza.get_plansza1()) cout << "Pola startowe dla kazdego koloru sa liczone z gory na dol liczbami od 1 do 5.\n";
	else cout << "Pola startowe dla kazdego koloru sa liczone od lewej do prawej liczbami od 1 do 5.\n";
	cout << "Podaj numer pola startowego, na ktorym chcesz postawic pionek: ";
	int numer = wybierz(A, E);																								//numer - przechowuje numer pola startowego, na którym gracz chce postawiæ pionek
	cout << "Wpisz nazwe pionka, ktory chcesz postawic: ";
	string nazwa;
	cin >> nazwa;
	nazwa = zla_nazwa_pionka(nazwa);
	string barwa = get_kolor();
	nazwa = jest_pionek(nazwa, barwa, plansza);
	ustaw_pionki(wsk_plansza, nazwa, numer, plansza, barwa);
	system("cls");
	plansza.rysuj_plansze();
}

int Gracz::plansze_grane(Plansza &plansza, string neutralny) {																//plansza - przechowuje wszystkie trzy plansze, neutralny - kolor gracza neutralnego
	int info1 = POCZATEK, info2 = POCZATEK, info3 = POCZATEK;																//info1, info2, info3 - przechowuj¹ informacje o tym, czy dana plansza jest zamro¿ona
	int nr_planszy = POCZATEK;																								//nr_planszy - numer wybranej obecnie planszy
	string kolor = get_kolor();																								//kolor - kolor obecnego gracza
	info1 = plansza.zamroz_plansze(A);
	info2 = plansza.zamroz_plansze(B);
	info3 = plansza.zamroz_plansze(C);
	int gorna = POCZATEK, lewa = POCZATEK, prawa = POCZATEK;																//gorna, lewa, prawa - przetrzymuj¹ informacje o tym, czy te plansze s¹ zamro¿one

	if ((info1 == A && info2 == A) || (info2 == A && info3 == A) || (info1 == A && info3 == A)) return POCZATEK;
	if (get_kolor() == "czerwony") {
		if (info1 == A || info1 == B) {
			cout << "Plansza gorna dla tego gracza zostala zamrozona.\n";
			gorna++;
		}
		if (info2 == A || info2 == B) {
			cout << "Plansza lewa dla tego gracza zostala zamrozona.\n";
			lewa++;
		}
	}
	else if (get_kolor() == "niebieski") {
		if (info2 == A || info2 == C) {
			cout << "Plansza lewa dla tego gracza zostala zamrozona.\n";
			lewa++;
		}
		if (info3 == A || info3 == C) {
			cout << "Plansza prawa dla tego gracza zostala zamrozona.\n";
			prawa++;
		}
	}
	else {
		if (info1 == A || info1 == C) {
			cout << "Plansza gorna dla tego gracza zostala zamrozona.\n";
			gorna++;
		}
		if (info3 == A || info3 == B) {
			cout << "Plansza prawa dla tego gracza zostala zamrozona.\n";
			prawa++;
		}
	}

	if (neutralny == "czerwony") {
		if ((info1 == A || info1 == B) && get_kolor() == "niebieski") {
			cout << "Plansza gorna dla tego gracza zostala zamrozona.\n\n";
			gorna++;
		}
		if ((info2 == A || info2 == B) && get_kolor() == "fioletowy") {
			cout << "Plansza lewa dla tego gracza zostala zamrozona.\n\n";
			lewa++;
		}
	}
	else if (neutralny == "niebieski") {
		if ((info2 == A || info2 == C) && get_kolor() == "fioletowy") {
			cout << "Plansza lewa dla tego gracza zostala zamrozona.\n";
			lewa++;
		}
		if ((info3 == A || info3 == C) && get_kolor() == "czerwony") {
			cout << "Plansza prawa dla tego gracza zostala zamrozona.\n";
			prawa++;
		}
	}
	else {
		if ((info1 == A || info1 == C) && get_kolor() == "niebieski") {
			cout << "Plansza gorna dla tego gracza zostala zamrozona.\n";
			gorna++;
		}
		if ((info3 == A || info3 == B) && get_kolor() == "czerwony") {
			cout << "Plansza prawa dla tego gracza zostala zamrozona.\n";
			prawa++;
		}
	}

	if (gorna && lewa) {
		cout << "\nAutomatycznie zostala ustawiona plansza prawa dla ruchu tego gracza.\n";
		nr_planszy = C;
	}
	else if (gorna && prawa) {
		cout << "\nAutomatycznie zostala ustawiona plansza lewa dla ruchu tego gracza.\n";
		nr_planszy = B;
	}
	else if (lewa && prawa) {
		cout << "\nAutomatycznie zostala ustawiona plansza gorna dla ruchu tego gracza.\n";
		nr_planszy = A;
	}
	else if (gorna) {
		cout << "\nPlansza lewa ma numer 2, a plansza prawa - numer 3.\n";
		cout << "Podaj numer planszy, na ktorej chcesz wykonac ruch pionkiem: ";
		nr_planszy = wybierz(A, C);
		while (nr_planszy == A) {
			cout << "\nNie ma mozliwosci wybrania planszy gornej - jest zamrozona.\n";
			cout << "Podaj numer innej planszy, na ktorej chcesz wykonac ruch pionkiem: ";
			nr_planszy = wybierz(A, C);
		}
	}
	else if (lewa) {
		cout << "\nPlansza gorna ma numer 1, a plansza prawa - numer 3.\n";
		cout << "Podaj numer planszy, na ktorej chcesz wykonac ruch pionkiem: ";
		nr_planszy = wybierz(A, C);
		while (nr_planszy == B) {
			cout << "\nNie ma mozliwosci wybrania planszy lewej - jest zamrozona.\n";
			cout << "Podaj numer innej planszy, na ktorej chcesz wykonac ruch pionkiem: ";
			nr_planszy = wybierz(A, C);
		}
	}
	else if (prawa) {
		cout << "\nPlansza gorna ma numer 1, a plansza lewa - numer 2.\n";
		cout << "Podaj numer planszy, na ktorej chcesz wykonac ruch pionkiem: ";
		nr_planszy = wybierz(A, C);
		while (nr_planszy == C) {
			cout << "\nNie ma mozliwosci wybrania planszy prawej - jest zamrozona.\n";
			cout << "Podaj numer innej planszy, na ktorej chcesz wykonac ruch pionkiem: ";
			nr_planszy = wybierz(A, C);
		}
	}
	else {
		cout << "\nPlansza gorna ma numer 1, plansza lewa ma numer 2, a plansza prawa - numer 3.\n";
		cout << "Podaj numer planszy, na ktorej chcesz wykonac ruch pionkiem: ";
		nr_planszy = wybierz(A, C);
	}
	cout << endl;

	return nr_planszy;
}