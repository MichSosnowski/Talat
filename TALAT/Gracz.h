#ifndef GRACZ_H
#define GRACZ_H

#include <fstream>
#include <string>
#include "Plansza.h"

#define POCZATEK 0																		//wartoœæ pocz¹tkowa wybranych zmiennych i pól

using namespace std;

class Plansza;

class Gracz {																			//klasa reprezentuj¹ca gracza osobowego
protected:
	string nick;																		//przechowuje nick podany przez gracza
	string nazwa_pliku;																	//przechowuje nazwê pliku, w którym zapisywana jest obecna gra
	fstream gra;																		//strumieñ wejœcia i wyjœcia dla pliku, w którym zapisywana jest obecna gra
	string kolor;																		//przechowuje kolor gracza, którym gra w obecnej rozgrywce
	int punkty;																			//przechowuje ³¹czn¹ zdobyt¹ iloœæ punktów przez gracza
public:
	Gracz() : nick("brak"), nazwa_pliku("brak"), kolor("brak"), punkty(POCZATEK) {}		//inicjalizuje obiekt wartoœciami domyœlnymi
	Gracz(string);																		//inicjalizuje obiekt korzystaj¹c z argumentu wywo³ania konstruktora
	void set_nick(string nick) { this->nick = nick; }									//ustawia nick gracza
	void set_nazwa_pliku(string nazwa) { nazwa_pliku = nazwa; }							//ustawia nazwê pliku, do którego zapisywane bêdzie stan gry
	void set_kolor(string barwa) { kolor = barwa; }										//ustawia kolor gracza dla danej rozgrywki
	void set_punkty(int p) { punkty = p; }												//ustawia sumê punktów zdobytych przez gracza
	string get_nick() { return nick; }													//zwraca nick gracza
	string get_nazwa_pliku() { return nazwa_pliku; }									//zwraca nazwê pliku ze stanem obecnej gry
	string get_kolor() { return kolor; }												//zwraca kolor gracza
	int get_punkty() { return punkty; }													//zwraca sumê zdobytych przez gracza punktów
	void wczytaj_gre(Plansza &, Gracz &);												//wczytuje grê z podanego pliku
	void wpisz_plik(Gracz &);															//wpisuje do pliku dane pocz¹tkowe rozgrywki
	void zapisz_gre(Plansza &, Gracz &);												//zapisuje grê do pliku
	void znajdz_neutralne(Gracz &);														//znajduje plansze z polami startowymi gracza neutralnego
	void wyswietl_faza_neutralne(Gracz *, Plansza &);									//wyœwietla informacje o fazie ustawiania pionków neutralnych
	void wyswietl_faza_pozostale(Gracz *, Plansza &);									//wyœwietla informacje o fazie ustawiania pionków koloru gracza
	void ustaw_pionki(string *, string, int, Plansza &, string);						//ustawia wybrany pionek na wybranej przez gracza planszy
	void wpisz_plansze(Plansza &);														//wpisuje plansze do pliku ze stanem gry
	void wpisz_kolory(Gracz &);															//wpisuje kolory obu gracz do pliku ze stanem gry
	void wpisz_punkty(Gracz &);															//wpisuje sumy punktów zdobyte przez obu graczy do pliku ze stanem gry
	int otworz_plik();																	//otwiera plik i informuje o mo¿liwoœci wczytania istniej¹cej ju¿ gry lub utworzenia nowej dla tego gracza
	int wyszukaj_pionek(string, int, Plansza &);										//wyszukuje wybrany przez gracza pionek na wybranej planszy
	int wybierz(int, int);																//pozwala dokonaæ graczowi wyboru pomiêdzy podanymi opcjami
	int sprawdz_plansze(int, Plansza &);												//sprawdza, czy pola startowe gracza s¹ ju¿ zajête na wybranej przez niego planszy
	int znajdz_plansze(int, string);													//pozwala graczowi dokonaæ ruchu jego pionkami neutralnymi, jeœli wybierze tak¹ opcjê
	int zbij(string *, int, int, int, int);												//zbija pionek albo informuje o niemo¿noœci wykonania takiego bicia
	int rusz_sie(string *, int, int, Plansza &, int);									//dokonuje ostatecznego ruchu pionkiem
	int sprawdz_ruch1(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy górnej (dla koloru lewego planszy górnej)
	int sprawdz_ruch2(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy górnej (dla koloru prawego planszy górnej)
	int sprawdz_ruch3(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy lewej lub prawej (dla koloru górnego tej planszy)
	int sprawdz_ruch4(string *, int, int, int);											//dokonuje ostatecznego ruchu wybranym pionkiem na planszy lewej lub prawej (dla koloru dolnego tej planszy)
	string ustal_kolory(Gracz &, int);													//pozwala pierwszemu graczowi ustaliæ kolory graczy
	string zla_nazwa_pionka(string);													//sprawdza, czy gracz poda³ poprawn¹ nazwê pionka
	string * ustaw_plansze(int, Plansza &);												//ustawia wskaŸnik na pierwsze pole wybranej planszy
	string * znajdz_neutralna_gracza(string, Plansza &);								//wypisuje informacjê o planszy gracza neutralnego dla obecnego gracza
	string jest_pionek(string, string, Plansza &);										//sprawdza, czy podany pionek jest ju¿ ustawiony na wybranej planszy
	virtual ~Gracz() { gra.close(); };													//destruktor wirtualny klasy Gracz s³u¿¹cy po to, by obiekt klasy Komputer zosta³ popawnie usuniêty
	virtual int wykonaj_ruch(Plansza &, string);										//wyœwietla menu wykonania ruchu przez gracza
	virtual void ustaw_pionki_neutralne(Plansza &, string);								//ustawia pionki neutralne kontrolowane przez gracza
	virtual void ustaw_pionki_pozostale(Plansza &);										//ustawia pionki koloru kontrolowanego przez gracza
	virtual int plansze_grane(Plansza &, string);										//sprawdza, czy istniej¹ ju¿ w grze plansze zamro¿one (niegrywalne) dla obecnego gracza
	friend class Menu;
};

#endif