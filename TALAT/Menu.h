#ifndef MENU_H
#define MENU_H

#include "Plansza.h"
#include "Gracz.h"

class Menu {										//klasa reprezentuj¹ca menu gry
	int info;										//przechowuje informacjê o aktualnie wybranym trybie gry
public:
	Menu() : info(A) {}								//inicjalizuje pole info wartoœci¹ domyœln¹
	void set_info(int i) { info = i; }				//ustawia wartoœæ info po zmianie trybu gry
	int get_info() { return info; };				//zwraca informacjê o aktualnie wybranym trybie
	void poinformuj();								//wyœwietla ekran powitalny gry (plik wstep.txt)
	void wypisz_tytul();							//wypisuje tytu³ gry w menu
	void menu();									//wyœwietla menu z wyborem opcji
	int wybierz(int, int);							//pozwala dokonaæ wyboru u¿ytkownikowi spoœród mo¿liwych opcji
	void zaladuj();									//"oszukuje" gracza wyœwietlaj¹c mu informacjê o ³adowaniu gry
	int rozpocznij_gre();							//uruchamia proces tworzenia nowej gry
	int wczytaj_gre();								//uruchamia proces wczytywania gry
	int sprawdz(Gracz &);							//korzysta z funkcji globalnej sprawdz_plik() i informuje o tym gracza
	void opcje();									//wyœwietla wybór trybu gry
	void wyswietl_ranking();						//wyœwietla ranking (opcja chwilowo niedostêpna)
	void podaj_zasady();							//wyœwietla zasady zapisane w pliku zasady.txt
	void wczytaj_info(Gracz &);						//ustawia pole info na podstawie informacji zawartej w zapisanej grze
};

#endif