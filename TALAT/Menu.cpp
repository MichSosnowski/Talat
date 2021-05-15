#include "Menu.h"
#include "global.h"
#include "Gracz.h"
#include "Komputer.h"
#include <iostream>
#include <ctime>
#include <Windows.h>

HANDLE hOut3 = GetStdHandle(STD_OUTPUT_HANDLE);														//uchwyt do standardowego wyjœcia konsoli

#define PRAWDA 1																					//wartoœæ prawdziwa steruj¹ca pêtl¹ while
#define SZEROKOSC 90																				//szerkoœæ pola tytu³u - TALAT
#define SZEROKOSC1 114																				//szerokoœæ pola opcji Rozpocznij grê
#define SZEROKOSC2 112																				//szerokoœæ pola opcji Wczytaj grê
#define SZEROKOSC3 108																				//szerokoœæ pola opcji Opcje
#define SZEROKOSC4 132																				//szerokoœæ pola opcji Ranking
#define SZEROKOSC5 111																				//szerokoœæ pola opcji Zasady gry
#define SZEROKOSC6 113																				//szerokoœæ pola opcji WyjdŸ z gry
#define SZEROKOSC7 199																				//szerokoœæ pola pomiêdzy wersj¹ gry a napisem Copyright
#define POCZATEK 0																					//wartoœæ pocz¹tkowa wybranych zmiennych i pól
#define CZAS 10																						//czas oczekiwania na zaladowanie gry
#define TEMP 0.5																					//przerwa oczekiwania na za³adowanie gry
#define LANCUCH "\0"																				//³añcuch zerowy do inicjalizowania zmiennych ³añcuchowych

//sta³e definiuj¹ce kolory
#define NIEBIESKI SetConsoleTextAttribute(hOut3, FOREGROUND_BLUE)									//kolor niebieski
#define CZERWONY SetConsoleTextAttribute(hOut3, FOREGROUND_RED)										//kolor czerwony
#define ZIELONY SetConsoleTextAttribute(hOut3, FOREGROUND_GREEN)									//kolor zielony
#define FIOLETOWY SetConsoleTextAttribute(hOut3, FOREGROUND_RED | FOREGROUND_BLUE)					//kolor fioletowy
#define ZLOTY SetConsoleTextAttribute(hOut3, FOREGROUND_RED | FOREGROUND_GREEN)						//kolor z³oty
#define BIALY SetConsoleTextAttribute(hOut3, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)	//kolor bia³y

using namespace std;

//operacje wykonywane przez ni¿ej wymienione metody opisane s¹ w pliku nag³ówkowym menu.h
//tu zostaj¹ jedynie opisane zmienne tymczasowe u¿ywane przez te metody

void Menu::poinformuj() {
	ifstream plik("wstep.txt");																		//plik - strumieñ wejœcia dla pliku wstêp.txt
	string info = LANCUCH;																			//info - aktualnie odczytana linia tekstu z pliku wstêp.txt

	if (!plik.is_open()) {
		cout << "Blad otwarcia pliku wstep.txt.\n\n";
		cout << "Koniec programu.";
		cin.get();
		exit(EXIT_FAILURE);
	}
	while (!plik.eof()) {
		getline(plik, info);
		cout << info << endl;
	}

	plik.close();
}

void Menu::wypisz_tytul() {
	cout.width(SZEROKOSC);
	CZERWONY;
	cout << "T\t";
	NIEBIESKI;
	cout << "A\t";
	ZLOTY;
	cout << "L\t";
	ZIELONY;
	cout << "A\t";
	FIOLETOWY;
	cout << "T\n\n";
	BIALY;
}

void Menu::menu() {
	cout << "=====================================================================================================================================================================================================================\n\n";
	this->wypisz_tytul();
	cout << "=====================================================================================================================================================================================================================\n\n";
	cout.width(SZEROKOSC1);
	cout << "1. Rozpocznij gre\n";
	cout.width(SZEROKOSC2);
	cout << "2. Wczytaj gre\n";
	cout.width(SZEROKOSC3);
	cout << "3. Opcje\n";
	cout.width(SZEROKOSC4);
	cout << "4. Ranking (chwilowo niedostepna)\n";
	cout.width(SZEROKOSC5);
	cout << "5. Zasady gry\n";
	cout.width(SZEROKOSC6);
	cout << "6. Wyjdz z gry\n\n";
	cout << "Talat v 1. 0. 0";
	cout.width(SZEROKOSC7);
	cout << "Copyright Sosnowski\n\n";
	cout << "=====================================================================================================================================================================================================================\n\n";
}

int Menu::wybierz(int liczba1, int liczba2) {														//liczba1 - zakres dolny wyboru, liczba2 - zakres górny wyboru umo¿liwionego graczowi
	int wybor = POCZATEK;																			//wybor - przechowuje wybór dokonany przez u¿ytkownika

	cout << "Wybierz jedna z powyzszych opcji: ";
	while (!(cin >> wybor) || wybor < liczba1 || wybor > liczba2 || cin.get() != '\n') {
		cout << "Nieznana komenda. Prosze wybrac ponownie: ";
		cin.clear();
		wyczysc_bufor();
	}

	return wybor;
}

void Menu::zaladuj() {
	clock_t czas = clock();																			//czas - przechowuje informacjê o czasie rozpoczêcia dzia³ania tej metody

	system("cls");
	while ((clock() - czas) < CZAS * CLOCKS_PER_SEC) {
		clock_t temp;																				//temp - przechowuje aktualny czas potrzebny do dzia³ania pêtli oczekuj¹cych
		cout << "Prosze czekac. Trwa ladowanie gry.";
		temp = clock();
		while ((clock() - temp) < TEMP * CLOCKS_PER_SEC);
		cout << ".";
		temp = clock();
		while ((clock() - temp) < TEMP * CLOCKS_PER_SEC);
		cout << ".";
		temp = clock();
		while ((clock() - temp) < TEMP * CLOCKS_PER_SEC);
		system("cls");
	}

	cout << "Gra zaladowana. Aby rozpoczac gre, nacisnij ENTER...";
	sprawdz_enter();
	system("cls");
}

int Menu::rozpocznij_gre() {
	string neutralny = LANCUCH;																		//neutralny - przechowuje kolor gracza neutralnego
	int decyzja = POCZATEK;																			//decyzja - przechowuje decyzjê gracza o rozpoczêciu nowej gry lub wczytaniu zapisanej
	int zwrot = POCZATEK;																			//zwrot - informacja zwrotna decyduj¹ca o zakoñczeniu gry spowodowanym koñcem gry
	int wola = POCZATEK;																			//wola - informacja zwrotna decyduj¹ca o zakoñczeniu gry spowodowanym wol¹ graczy
	Plansza plansza;																				//plansza - obiekt przechowuj¹cy plansze
	Gracz *gracz1 = NULL;																			//gracz1 - wskaŸnik na pierwszego gracza
	Gracz *gracz2 = NULL;																			//gracz2 - wskaŸnik na drugiego gracza

	system("cls");
	if (info == A) {
		cout << "Tryb gry: gracz vs gracz\n\n";
		cout << "Podaj nick pierwszego gracza: ";
		gracz1 = new Gracz(podaj_nick());															//ustawienie pierwszego gracza jako gracza osobowego
		decyzja = gracz1->otworz_plik();
		if (decyzja == B) {
			delete gracz1;
			return decyzja;
		}
		cout << "Podaj nick drugiego gracza: ";
		gracz2 = new Gracz(podaj_nick());															//ustawienie drugiego gracza jako gracza osobowego
	}
	else {
		cout << "Tryb gry: gracz vs komputer\n\n";
		cout << "Podaj swoj nick: ";
		gracz1 = new Gracz(podaj_nick());															//ustawienie pierwszego gracza jako gracza osobowego
		decyzja = gracz1->otworz_plik();
		if (decyzja == B) {
			delete gracz1;
			return decyzja;
		}
		gracz2 = new Komputer("komputer");															//ustawienie drugiego gracza jako komputer
	}
	neutralny = gracz1->ustal_kolory(*gracz2, info);
	zaladuj();
	cout << "Uwaga!!! Dopoki plansze nie zostana cale wypelnione pionkami graczy, stan gry nie zostanie zapisany.\n";
	cout << "Aby kontynuowac, wcisnij ENTER...";
	sprawdz_enter();
	system("cls");
	plansza.zapelnij_plansze(gracz1, gracz2, neutralny);
	wyczysc_bufor();
	cout << "Po wcisnieciu ENTER, zacznie sie rozgrywka. Milej gry!!!\n";
	cout << "P. S. Za kazdym razem po wykonaniu przez obu graczy ruchow bedzie mozliwosc przerwania gry.";
	sprawdz_enter();
	system("cls");
	while (PRAWDA) {
		plansza.rysuj_plansze();
		zwrot = gracz2->wykonaj_ruch(plansza, neutralny);
		zwrot = gracz1->wykonaj_ruch(plansza, neutralny);
		if (!zwrot) break;
		gracz1->zapisz_gre(plansza, *gracz2);
		system("cls");
		plansza.rysuj_plansze();
		cout << "Suma punktow po tej rundzie:\n";
		cout << gracz1->get_nick() << " - " << gracz1->get_punkty() << " punktow.\n";
		cout << gracz2->get_nick() << " - " << gracz2->get_punkty() << " punktow.\n\n";
		cout << "Czy chcesz przerwac gre?\n";
		cout << "Tak, chce przerwac gre - wpisz T\n";
		cout << "Nie, nie chce jej przerywac - wpisz N\n\n";
		wola = zdecyduj();
		system("cls");
		if (wola == A) break;
	}
	if (wola == A) {
		cout << "Aby powrocic do menu, prosze nacisnac ENTER...";
		delete gracz1;
		delete gracz2;
		return POCZATEK;
	}
	system("cls");
	plansza.rysuj_plansze();
	cout << "Koniec gry!!!.\n";
	cout << "Dwie z trzech plansz zostaly zamrozone.\n";
	cout << "Zdobyte punkty:\n";
	cout << gracz1->get_nick() << " - " << gracz1->get_punkty() << " punktow.\n";
	cout << gracz2->get_nick() << " - " << gracz2->get_punkty() << " punktow.\n\n";
	if (gracz1->get_punkty() > gracz2->get_punkty()) cout << "Wygrywa gracz: " << gracz1->get_nick() << endl << endl;
	else if (gracz1->get_punkty() < gracz2->get_punkty()) cout << "Wygrywa gracz: " << gracz2->get_nick() << endl << endl;
	else cout << "REMIS!!!\n\n";
	
	cout << "Aby powrocic do menu, prosze nacisnac ENTER...";
	string nazwa_pliku = gracz1->get_nazwa_pliku();													//nazwa_pliku - przechowuje nazwê pliku z zapisem gry
	wyczysc_bufor();
	delete gracz1;
	delete gracz2;
	remove(nazwa_pliku.c_str());
	return POCZATEK;
}

int Menu::wczytaj_gre() {
	string neutralny = LANCUCH;																		//neutralny - przechowuje kolor gracza neutralnego
	int decyzja = POCZATEK;																			//decyzja - przechowuje decyzjê gracza o rozpoczêciu nowej gry lub wczytaniu zapisanej
	int zwrot = POCZATEK;																			//zwrot - informacja zwrotna decyduj¹ca o zakoñczeniu gry spowodowanym koñcem gry
	int wola = POCZATEK;																			//wola - informacja zwrotna decyduj¹ca o zakoñczeniu gry spowodowanym wol¹ graczy
	Plansza plansza;																				//plansza - obiekt przechowuj¹cy plansze

	system("cls");
	cout << "Podaj swoj nick, aby wczytac gre: ";
	Gracz *wsk1 = new Gracz(podaj_nick());															//wsk1 - wskaŸnik na pierwszego gracza
	wsk1->set_nazwa_pliku(wsk1->get_nick() + "-gra.txt");
	zwrot = sprawdz(*wsk1);
	if (zwrot) {
		decyzja = POCZATEK;
		return decyzja;
	}
	wczytaj_info(*wsk1);
	Gracz *wsk2 = NULL;																				//wsk2 - wskaŸnik na drugiego gracza
	if (info == A) wsk2 = new Gracz();																//ustawienie drugiego gracza jako gracza osobowego
	else wsk2 = new Komputer();																		//ustawienie drugiego gracza jako komputer
	wyczysc_bufor();
	zaladuj();
	wsk1->wczytaj_gre(plansza, *wsk2);

	if (wsk1->get_kolor() != "czerwony" && wsk2->get_kolor() != "czerwony") neutralny = "czerwony";
	else if (wsk1->get_kolor() != "niebieski" && wsk2->get_kolor() != "niebieski") neutralny = "niebieski";
	else neutralny = "fioletowy";

	while (PRAWDA) {
		plansza.rysuj_plansze();
		zwrot = wsk2->wykonaj_ruch(plansza, neutralny);
		zwrot = wsk1->wykonaj_ruch(plansza, neutralny);
		if (!zwrot) break;
		wsk1->zapisz_gre(plansza, *(wsk2));
		plansza.zamroz_plansze(A);
		plansza.zamroz_plansze(B);
		plansza.zamroz_plansze(C);
		system("cls");
		plansza.rysuj_plansze();
		cout << "Suma punktow po tej rundzie:\n";
		cout << wsk1->get_nick() << " - " << wsk1->get_punkty() << " punktow.\n";
		cout << wsk2->get_nick() << " - " << wsk2->get_punkty() << " punktow.\n\n";
		cout << "Czy chcesz przerwac gre?\n";
		cout << "Tak, chce przerwac gre - wpisz T\n";
		cout << "Nie, nie chce jej przerywac - wpisz N\n\n";
		wola = zdecyduj();
		system("cls");
		if (wola == A) break;
	}
	if (wola == A) {
		cout << "Aby powrocic do menu, prosze nacisnac ENTER...";
		decyzja = POCZATEK;
		delete wsk1;
		delete wsk2;
		return POCZATEK;
	}
	system("cls");
	plansza.rysuj_plansze();
	cout << "Koniec gry!!!.\n";
	cout << "Dwie z trzech plansz zostaly zamrozone.\n";
	cout << "Zdobyte punkty:\n";
	cout << wsk1->get_nick() << " - " << wsk1->get_punkty() << " punktow.\n";
	cout << wsk2->get_nick() << " - " << wsk2->get_punkty() << " punktow.\n\n";
	if (wsk1->get_punkty() > wsk2->get_punkty()) cout << "Wygrywa gracz: " << wsk1->get_nick() << endl << endl;
	else if (wsk1->get_punkty() < wsk2->get_punkty()) cout << "Wygrywa gracz: " << wsk2->get_nick() << endl << endl;
	else cout << "REMIS!!!\n\n";
	
	cout << "Aby powrocic do menu, prosze nacisnac ENTER...";
	string nazwa_pliku = wsk1->get_nazwa_pliku();													//nazwa_pliku - przechowuje nazwê pliku z zapisem gry
	decyzja = POCZATEK;
	delete wsk1;
	delete wsk2;
	remove(nazwa_pliku.c_str());
	return decyzja;
}

int Menu::sprawdz(Gracz &gracz1) {																	//gracz1 - przekazuje dane gracza pierwszego
	string nazwa = gracz1.get_nazwa_pliku();														//nazwa - przechowuje nazwê pliku z zapisem gry
	int info = sprawdz_plik(nazwa);																	//info - przechowje informacjê o istnieniu pliku
	if (!info) {
		cout << "\nNie znaleziono zadnego zapisu stanu gry zwiazanego z tym graczem.\n";
		cout << "Powrot do menu - prosze nacisnac ENTER.";
		remove(nazwa.c_str());
		wyczysc_bufor();
		return A;
	}
	else return POCZATEK;
}

void Menu::opcje() {
	system("cls");
	cout << "Tryby gry:\n";
	cout << "1. Gra dla dwoch osob\n";
	cout << "2. Gra 1 vs 1 z komputerem\n";
	cout << "0. Powrot do menu\n\n";
	cout << "Obecny tryb: ";
	if (info == A) cout << "gra dla dwoch osob\n\n";
	else cout << "gra 1 vs 1 z komputerem\n\n";
	int tryb = wybierz(POCZATEK, B);																//tryb - przechowuje informacjê o wybranym przez gracza trybie gry
	if (tryb != info && tryb) {
		info = tryb;
		cout << "\nTryb zostal pomyslnie zmieniony.\n";
	}
	else if (tryb == info) cout << "\nNie dokonano zmiany trybu gry.\n";
	else {
		system("cls");
		return;
	}
	cout << "Aby powrocic do menu, prosze nacisnac ENTER...";
	sprawdz_enter();
	system("cls");
}

void Menu::wyswietl_ranking() {
	system("cls");
	cout << "Opcja chwilowo niedostepna.\n";
	cout << "Aby powrocic do menu, wcisnij ENTER...";
}

void Menu::podaj_zasady() {
	ifstream plik("zasady.txt");																	//plik - strumieñ wejœcia dla pliku zasady.txt
	string temp = LANCUCH;																			//temp - przechowuje liniê tekstu wczytan¹ z pliku

	if (!plik.is_open()) {
		cout << "Blad otwarcia pliku zasady.txt.\n\n";
		cout << "Koniec programu.";
		cin.get();
		exit(EXIT_FAILURE);
	}
	system("cls");
	while (!plik.eof()) {
		getline(plik, temp);
		cout << temp << endl;
	}

	plik.close();
}

void Menu::wczytaj_info(Gracz &gracz) {																//gracz - przekazuje dane gracza pierwszego bêd¹cego podmiotem zapisu gry
	gracz.gra.open(gracz.get_nazwa_pliku(), ios_base::in | ios_base::out | ios_base::app);
	string tekst;																					//temp - przechowuje informacjê o trybie gry wczytan¹ z pliku

	gracz.gra >> tekst;
	while (tekst != "komputerem" && tekst != "gracz") gracz.gra >> tekst;
	if (tekst == "komputerem") set_info(B);
	else set_info(A);

	gracz.gra.seekg(POCZATEK, ios_base::beg);
	gracz.gra.close();
}