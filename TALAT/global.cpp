#include "global.h"
#include "Gracz.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>

#define POCZATEK 0															//warto�� pocz�tkowa wybranych zmiennych i p�l
#define ZNAK '\0'															//znak '\0' do inicjalizowania zmiennych znakowych
#define LANCUCH "\0"														//�a�cuch zerowy do inicjalizowania zmiennych �a�cuchowych
#define ENTER '\n'															//znak nowej linii
#define TAK 'T'																//odpowied� pozytywna gracza w metodzie zdecyduj()
#define NIE 'N'																//odpowied� negatywna gracza w metodzie zdecyduj()

using namespace std;

//operacje wykonywane przez ni�ej wymienione funkcje globalne opisane s� w pliku nag��wkowym global.h
//tu zostaj� jedynie opisane argumenty wywo�ania i zmienne tymczasowe u�ywane przez te funkcje

void wyczysc_bufor() {
	while (cin.get() != ENTER)
	{
	}
}

void sprawdz_enter() {
	while (cin.get() != ENTER) {
		cout << "Nieznana komenda. Prosze nacisnac tylko klawisz ENTER.";
		wyczysc_bufor();
	}
}

string podaj_nick() {
	string nick = LANCUCH;													//nick - przechowuje podany przez u�ytkownika nick
	cin >> nick;
	return nick;
}

int sprawdz_plik(string nazwa_pliku) {										//nazwa_pliku - przechowuje nazw� pliku z zapisem gry (je�li istnieje)
	fstream plik;															//plik - strumie� wej�cia dla pliku o nazwie podanej w argumencie wywo�ania
	plik.open(nazwa_pliku, ios_base::in);
	if (errno == ENOENT) {
		plik.close();
		return POCZATEK;
	}
	else {
		char znak = ZNAK;													//znak - przechowuje jeden wczytany znak z pliku
		int ile = POCZATEK;													//ile - zlicza ilo�� znak�w w pliku
		while (!plik.eof()) {
			plik >> znak;
			ile++;
		}
		plik.close();
		if (ile == A) return POCZATEK;
		return A;
	}
}

int zdecyduj() {
	char decyzja = ZNAK;													//decyzja - przechowuje wybran� przez u�ytkownika opcj� dotycz�c� zako�czenia gry w obecnej chwili
	cout << "Decyzja: ";
	cin >> decyzja;
	while ((decyzja != TAK && decyzja != NIE) || cin.get() != ENTER) {
		wyczysc_bufor();
		cout << "Nie znam takiej opcji. Podaj poprawna opcje: ";
		cin >> decyzja;
	}
	if (decyzja == TAK) return A;
	else return B;
}