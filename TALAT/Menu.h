#ifndef MENU_H
#define MENU_H

#include "Plansza.h"
#include "Gracz.h"

class Menu {										//klasa reprezentuj�ca menu gry
	int info;										//przechowuje informacj� o aktualnie wybranym trybie gry
public:
	Menu() : info(A) {}								//inicjalizuje pole info warto�ci� domy�ln�
	void set_info(int i) { info = i; }				//ustawia warto�� info po zmianie trybu gry
	int get_info() { return info; };				//zwraca informacj� o aktualnie wybranym trybie
	void poinformuj();								//wy�wietla ekran powitalny gry (plik wstep.txt)
	void wypisz_tytul();							//wypisuje tytu� gry w menu
	void menu();									//wy�wietla menu z wyborem opcji
	int wybierz(int, int);							//pozwala dokona� wyboru u�ytkownikowi spo�r�d mo�liwych opcji
	void zaladuj();									//"oszukuje" gracza wy�wietlaj�c mu informacj� o �adowaniu gry
	int rozpocznij_gre();							//uruchamia proces tworzenia nowej gry
	int wczytaj_gre();								//uruchamia proces wczytywania gry
	int sprawdz(Gracz &);							//korzysta z funkcji globalnej sprawdz_plik() i informuje o tym gracza
	void opcje();									//wy�wietla wyb�r trybu gry
	void wyswietl_ranking();						//wy�wietla ranking (opcja chwilowo niedost�pna)
	void podaj_zasady();							//wy�wietla zasady zapisane w pliku zasady.txt
	void wczytaj_info(Gracz &);						//ustawia pole info na podstawie informacji zawartej w zapisanej grze
};

#endif