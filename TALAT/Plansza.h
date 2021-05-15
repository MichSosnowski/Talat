#ifndef PLANSZA_H
#define PLANSZA_H

#include <string>
#include "Gracz.h"
using namespace std;

#define POCZATEK 0												//warto�� pocz�tkowa wybranych zmiennych i p�l

//typ enum definiuj�cy sta�e b�d�ce warto�ciami dla wybranych zmiennych
enum { A = 1, B = 2, C = 3, D = 4, E = 5, F = 6, G = 7, H = 8, I = 9, J = 10, K = 11, L = 12, M = 13, N = 14, O = 15, P = 16, Q = 17, R = 18, S = 19, T = 20, U = 21, W = 22, V = 23, X = 24, Y = 25, Z = 26, Z1 = 27, Z2 = 28, Z3 = 29, Z4 = 30 };

class Gracz;

class Plansza {													//klasa reprezentuj�ca plansze
	string plansza1[E][E];										//przechowuje zawarto�� planszy g�rnej
	string plansza2[E][E];										//przechowuje zawarto�� planszy lewej
	string plansza3[E][E];										//przechowuje zawarto�� planszy prawej
public:
	Plansza();													//inicjalizuje pola warto�ciami domy�lnymi
	void wybierz_kolor(int);									//wybiera kolor na podstawie argumentu wywo�ywanego tej metody
	void wypisz_pole(string);									//wypisuje na planszy zawarto�� wskazanego pola podanego w argumencie wywo�ania tej metody
	void rysuj_wiersz(int, int, int);							//rysuje pierwszy wiersz planszy g�rnej
	void rysuj_wiersz1(int, int, int, int);						//rysuje drugi, trzeci i pi�ty wiersz planszy g�rnej
	void rysuj_wiersz2(int, int, int, int);						//rysuje czwarty wiersz planszy g�rnej
	void rysuj_wiersz_(int);									//rysuje pierwszy wiersz planszy lewej i prawej
	void rysuj_wiersz1_(int, int);								//rysuje drugi, trzeci i pi�ty wiersz planszy lewej i prawej
	void rysuj_wiersz2_(int, int);								//rysuje czwarty wiersz planszy lewej i prawej
	void rysuj_plansze();										//rysuje wszystkie trzy plansze korzystaj�c z sze�ciu powy�szych metod
	void wyswietl_legende();									//wy�wietla legend� pionk�w
	void zapelnij_plansze(Gracz *, Gracz *, string);			//zape�nia plansze pionkami graczy
	int zamroz_plansze(int);									//sprawdza, czy plansze s� zamro�one
	string * get_plansza1() { return plansza1[POCZATEK]; }		//zwraca wska�nik na pierwsze pole planszy g�rnej
	string * get_plansza2() { return plansza2[POCZATEK]; }		//zwraca wska�nik na pierwsze pole planszy lewej
	string * get_plansza3() { return plansza3[POCZATEK]; }		//zwraca wska�nik na pierwsze pole planszy prawej
};

#endif