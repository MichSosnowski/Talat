#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Menu.h"
#include "Plansza.h"
#include "Gracz.h"
#include "Komputer.h"
#include "global.h"
#include "szablon.h"

using namespace std;

#define POCZATEK 0										//wartoœæ pocz¹tkowa wybranych zmiennych i pól
#define PRAWDA 1										//wartoœæ prawdziwa steruj¹ca pêtl¹ while
#define OKNO1 120										//ustala rozmiar bufora konsoli w celu zmiany rozmiaru jej okna
#define OKNO2 30										//ustala rozmiar bufora konsoli w celu zmiany rozmiaru jej okna
#define LICZBA1 4										//pierwszy argument wywo³ania funkcji sumuj() dla typu int;
#define LICZBA2 8										//drugi argument wywo³ania funkcji sumuj() dla typu int;
#define LICZBA3 15.25									//pierwszy argument wywo³ania funkcji sumuj() dla typu double;
#define LICZBA4 13.25									//drugi argument wywo³ania funkcji sumuj() dla typu double;

int main() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//uchwyt do standardowego wyjœcia konsoli
	HWND konsola = GetConsoleWindow();					//uchwyt okna konsoli
	COORD rozmiar = { OKNO1, OKNO2 };					//rozmiar bufora ekranu do otwierania okna konsoli w ¿¹danym rozmiarze
	SetConsoleScreenBufferSize(hOut, rozmiar);			//ustawia rozmiar bufora ekranu
	ShowWindow(konsola, SW_MAXIMIZE);					//otwiera konsolê w pe³nym ekranie

	srand(time(NULL));

	Menu start;											//obiekt klasy Menu steruj¹cy dzia³aniem menu gry
	int decyzja = POCZATEK;								//przechowuje decyzjê o wybranej przez u¿ytkownika opcji menu

	start.poinformuj();
	sprawdz_enter();
	system("cls");

	while (PRAWDA) {
		if (decyzja != B) {
			start.menu();
			decyzja = start.wybierz(A, F);
		}
		if (decyzja == A) {
			decyzja = start.rozpocznij_gre();
			if (decyzja == B) continue;
		}
		else if (decyzja == B) decyzja = start.wczytaj_gre();
		else if (decyzja == C) {
			start.opcje();
			continue;
		}
		else if (decyzja == D) start.wyswietl_ranking();
		else if (decyzja == E) start.podaj_zasady();
		else break;
		sprawdz_enter();
		system("cls");
	}

	system("cls");
	cout << "Czy wiedziales, ze 4 + 8 = " << sumuj(LICZBA1, LICZBA2) << ", a 15.25 + 13.25 = " << sumuj(LICZBA3, LICZBA4) << "?\n\n";
	cout << "Dziekuje za gre. Do widzenia.\n\n";
	cout << "Koniec programu.";
	cin.get();
	return 0;
}