#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

void wyczysc_bufor();				//czyœci bufor standardowego wejœcia
void sprawdz_enter();				//sprawdza, czy wciœniêty uprzednio klawisz by³ enterem
std::string podaj_nick();			//pobiera od u¿ytkownika nick i zapisuje go
int sprawdz_plik(std::string);		//sprawdza, czy plik o nazwie bêd¹cej argumentem funkcji istnieje, czy te¿ nie
int zdecyduj();						//pobiera i sprawdza decyzjê o zakoñczeniu gry przez u¿ytkownika

#endif