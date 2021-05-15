#ifndef GRACZ_H
#define GRACZ_H

#include <fstream>
#include <string>
#include "Plansza.h"

#define POCZATEK 0																		//warto�� pocz�tkowa wybranych zmiennych i p�l

using namespace std;

class Plansza;

class Gracz {																			//klasa reprezentuj�ca gracza osobowego
protected:
	string nick;																		//przechowuje nick podany przez gracza
	string nazwa_pliku;																	//przechowuje nazw� pliku, w kt�rym zapisywana jest obecna gra
	fstream gra;																		//strumie� wej�cia i wyj�cia dla pliku, w kt�rym zapisywana jest obecna gra
	string kolor;																		//przechowuje kolor gracza, kt�rym gra w obecnej rozgrywce
	int punkty;																			//przechowuje ��czn� zdobyt� ilo�� punkt�w przez gracza
public:
	Gracz() : nick("brak"), nazwa_pliku("brak"), kolor("brak"), punkty(POCZATEK) {}		//inicjalizuje obiekt warto�ciami domy�lnymi
	Gracz(string);																		//inicjalizuje obiekt korzystaj�c z argumentu wywo�ania konstruktora
	void set_nick(string nick) { this->nick = nick; }									//ustawia nick gracza
	void set_nazwa_pliku(string nazwa) { nazwa_pliku = nazwa; }							//ustawia nazw� pliku, do kt�rego zapisywane b�dzie stan gry
	void set_kolor(string barwa) { kolor = barwa; }										//ustawia kolor gracza dla danej rozgrywki
	void set_punkty(int p) { punkty = p; }												//ustawia sum� punkt�w zdobytych przez gracza
	string get_nick() { return nick; }													//zwraca nick gracza
	string get_nazwa_pliku() { return nazwa_pliku; }									//zwraca nazw� pliku ze stanem obecnej gry
	string get_kolor() { return kolor; }												//zwraca kolor gracza
	int get_punkty() { return punkty; }													//zwraca sum� zdobytych przez gracza punkt�w
	void wczytaj_gre(Plansza &, Gracz &);												//wczytuje gr� z podanego pliku
	void wpisz_plik(Gracz &);															//wpisuje do pliku dane pocz�tkowe rozgrywki
	void zapisz_gre(Plansza &, Gracz &);												//zapisuje gr� do pliku
	void znajdz_neutralne(Gracz &);														//znajduje plansze z polami startowymi gracza neutralnego
	void wyswietl_faza_neutralne(Gracz *, Plansza &);									//wy�wietla informacje o fazie ustawiania pionk�w neutralnych
	void wyswietl_faza_pozostale(Gracz *, Plansza &);									//wy�wietla informacje o fazie ustawiania pionk�w koloru gracza
	void ustaw_pionki(string *, string, int, Plansza &, string);						//ustawia wybrany pionek na wybranej przez gracza planszy
	void wpisz_plansze(Plansza &);														//wpisuje plansze do pliku ze stanem gry
	void wpisz_kolory(Gracz &);															//wpisuje kolory obu gracz do pliku ze stanem gry
	void wpisz_punkty(Gracz &);															//wpisuje sumy punkt�w zdobyte przez obu graczy do pliku ze stanem gry
	int otworz_plik();																	//otwiera plik i informuje o mo�liwo�ci wczytania istniej�cej ju� gry lub utworzenia nowej dla tego gracza
	int wyszukaj_pionek(string, int, Plansza &);										//wyszukuje wybrany przez gracza pionek na wybranej planszy
	int wybierz(int, int);																//pozwala dokona� graczowi wyboru pomi�dzy podanymi opcjami
	int sprawdz_plansze(int, Plansza &);												//sprawdza, czy pola startowe gracza s� ju� zaj�te na wybranej przez niego planszy
	int znajdz_plansze(int, string);													//pozwala graczowi dokona� ruchu jego pionkami neutralnymi, je�li wybierze tak� opcj�
	int zbij(string *, int, int, int, int);												//zbija pionek albo informuje o niemo�no�ci wykonania takiego bicia
	int rusz_sie(string *, int, int, Plansza &, int);									//dokonuje ostatecznego ruchu pionkiem
	int sprawdz_ruch1(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy g�rnej (dla koloru lewego planszy g�rnej)
	int sprawdz_ruch2(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy g�rnej (dla koloru prawego planszy g�rnej)
	int sprawdz_ruch3(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy lewej lub prawej (dla koloru g�rnego tej planszy)
	int sprawdz_ruch4(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy lewej lub prawej (dla koloru dolnego tej planszy)
	string ustal_kolory(Gracz &, int);													//pozwala pierwszemu graczowi ustali� kolory graczy
	string zla_nazwa_pionka(string);													//sprawdza, czy gracz poda� poprawn� nazw� pionka
	string * ustaw_plansze(int, Plansza &);												//ustawia wska�nik na pierwsze pole wybranej planszy
	string * znajdz_neutralna_gracza(string, Plansza &);								//wypisuje informacj� o planszy gracza neutralnego dla obecnego gracza
	string jest_pionek(string, string, Plansza &);										//sprawdza, czy podany pionek jest ju� ustawiony na wybranej planszy
	virtual ~Gracz() { gra.close(); };													//destruktor wirtualny klasy Gracz s�u��cy po to, by obiekt klasy Komputer zosta� popawnie usuni�ty
	virtual int wykonaj_ruch(Plansza &, string);										//wy�wietla menu wykonania ruchu przez gracza
	virtual void ustaw_pionki_neutralne(Plansza &, string);								//ustawia pionki neutralne kontrolowane przez gracza
	virtual void ustaw_pionki_pozostale(Plansza &);										//ustawia pionki koloru kontrolowanego przez gracza
	virtual int plansze_grane(Plansza &, string);										//sprawdza, czy istniej� ju� w grze plansze zamro�one (niegrywalne) dla obecnego gracza
	friend class Menu;
};

#endif