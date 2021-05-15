#include "global.h"
#include "Gracz.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>

#define POCZATEK 0															//wartoœæ pocz¹tkowa wybranych zmiennych i pól
#define ZNAK '\0'															//znak '\0' do inicjalizowania zmiennych znakowych
#define LANCUCH "\0"														//³añcuch zerowy do inicjalizowania zmiennych ³añcuchowych
#define ENTER '\n'															//znak nowej linii
#define TAK 'T'																//odpowiedŸ pozytywna gracza w metodzie zdecyduj()
#define NIE 'N'																//odpowiedŸ negatywna gracza w metodzie zdecyduj()

using namespace std;

//operacje wykonywane przez ni¿ej wymienione funkcje globalne opisane s¹ w pliku nag³ówkowym global.h
//tu zostaj¹ jedynie opisane argumenty wywo³ania i zmienne tymczasowe u¿ywane przez te funkcje

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
	string nick = LANCUCH;													//nick - przechowuje podany przez u¿ytkownika nick
	cin >> nick;
	return nick;
}

int sprawdz_plik(string nazwa_pliku) {										//nazwa_pliku - przechowuje nazwê pliku z zapisem gry (jeœli istnieje)
	fstream plik;															//plik - strumieñ wejœcia dla pliku o nazwie podanej w argumencie wywo³ania
	plik.open(nazwa_pliku, ios_base::in);
	if (errno == ENOENT) {
		plik.close();
		return POCZATEK;
	}
	else {
		char znak = ZNAK;													//znak - przechowuje jeden wczytany znak z pliku
		int ile = POCZATEK;													//ile - zlicza iloœæ znaków w pliku
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
	char decyzja = ZNAK;													//decyzja - przechowuje wybran¹ przez u¿ytkownika opcjê dotycz¹c¹ zakoñczenia gry w obecnej chwili
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