#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

void wyczysc_bufor();				//czy�ci bufor standardowego wej�cia
void sprawdz_enter();				//sprawdza, czy wci�ni�ty uprzednio klawisz by� enterem
std::string podaj_nick();			//pobiera od u�ytkownika nick i zapisuje go
int sprawdz_plik(std::string);		//sprawdza, czy plik o nazwie b�d�cej argumentem funkcji istnieje, czy te� nie
int zdecyduj();						//pobiera i sprawdza decyzj� o zako�czeniu gry przez u�ytkownika

#endif