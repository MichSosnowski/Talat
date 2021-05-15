#ifndef KOMPUTER_H
#define KOMPUTER_H

#include "Gracz.h"
#include "Plansza.h"

class Komputer : public Gracz {											//klasa reprezentuj�ca gracza b�d�cego komputerem
public:
	Komputer() {}														//inicjalizuje obiekt klasy Komputer warto�ciami domy�lnymi (domy�lnie wywo�uj�c konstruktor domy�lny klasy bazowej)
	Komputer(string nazwa) { nick = nazwa; }							//inicjalizuje obiekt korzystaj�c z argumentu wywo�ania konstruktora (domy�lnie wywo�uj�c konstruktor domy�lny klasy bazowej)
	void ustaw_pionki(string *, string, int, Plansza &, string);		//ustawia wybarany pionek na wybranej planszy
	int sprawdz_plansze(int, Plansza &);								//sprawdza, czy wszystkie pola startowe gracza komputer na wybranej planszy s� ju� zape�nione pionkami
	int plansze_grane(Plansza &, string);								//sprawdza, czy istniej� ju� w grze plansze zamro�one (niegrywalne) dla gracza komputer
	string wybierz_pionek();											//dokonuje wyboru pionka
	string * znajdz_neutralna_gracza(string, Plansza &);				//znajduje plansze z pionkami gracza neutralnego kontrolowanymi przez gracza komputer
	string jest_pionek(string, string, Plansza &);						//sprawdza, czy podany pionek jest ju� ustawiony na wybranej planszy
	int wykonaj_ruch(Plansza &, string);								//wykonuje ruch wybranym pionkiem na wybranej planszy
	void ustaw_pionki_neutralne(Plansza &, string);						//ustawia pionki neutralne kontrolowane przez gracza komputer
	void ustaw_pionki_pozostale(Plansza &);								//ustawia pionki koloru kontrolowanego przez gracza komputer
};

#endif