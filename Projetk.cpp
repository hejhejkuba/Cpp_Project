#include <iostream>
#include <random>
#include<fstream>

using namespace std;

int main() {

	double gas_price = 0.0; // (7.20, 6.00) <=> 6.60

	//iterator
	int road_int =0; //{14.1, 15.0, 14.2, 13.9, 14.6}

	double spalanie = 0.0;

	double korki_value = 0.0;

	double road_distance[5] = {14.1, 15.0, 14.2, 13.9, 14.6};  //dystans drog

	int cross_roads[5] = {11,11,10,14,9}; //ilosc skrzyzowan na danej drodze 

	double road_time_values[5] = { 0.282, 0.256, 0.275 , 0.278,  0.292 }; //ile czasu zajmuje pokonanie tej drogi optymalnie w godzinach

	double czas = 0.0; // czas

	double swiatla = 0.0;

	ofstream zapis("dane.txt");

	mt19937 GEN(time(nullptr));
	normal_distribution<double> cena_paliwa_dzis(6.6, 0.2); // cena dzis paliwa wynosi 6.6 za litr
	normal_distribution<double> spalanie_losowanie(6.0, 0.35); // sposob jazdy czyli spalanie
	normal_distribution<double> natezenie_ruchu_dla_drogi_0_2(5.0, 0.5); // natezenie_ruchu dla drogi 0,2
	normal_distribution<double> natezenie_ruchu_dla_drogi_1_3(10.0, 2.0); // natezenie_ruchu dla drogi 0,2
	normal_distribution<double> natezenie_ruchu_dla_drogi_4(5.0, 0.5); // natezenie_ruchu dla drogi 0,2
	discrete_distribution<int> wybor_drogi{1, 0.5, 2, 1.2, 0.3}; //wybor drogi z dyskretnej 
	bernoulli_distribution czy_stoje_na_skrzyzowaniu(0.5); //czy stoje na skrzyzowaniu 

	for (int i = 0; i < 5000; i++)
	{
		czas = 0.0;

		//etap pierwszy - cena paliwa
		gas_price = cena_paliwa_dzis(GEN);
	

		//etap drugi - wybor drogi
		road_int = wybor_drogi(GEN);
		

		//etap trzeci - sposob jazdy
		spalanie = spalanie_losowanie(GEN);


		//etap czwarty - swiatla
		int ilosc_skrzyzowan = cross_roads[road_int];
		for (int i = 0; i <= ilosc_skrzyzowan; i++)
		{
			if (czy_stoje_na_skrzyzowaniu(GEN) == true)
			{
				czas = czas + (1.0 / 60.0);
			}
			else
			{
				//uffff
			};
		};


		//etap piaty
		if (road_int == 0 || road_int == 2)
		{
			czas = czas + (natezenie_ruchu_dla_drogi_0_2(GEN)/60.0);
		}
		else if (road_int == 1 || road_int == 3)
		{
			czas = czas + (natezenie_ruchu_dla_drogi_1_3(GEN)/60.0);
		}
		else
		{
			czas = czas + (natezenie_ruchu_dla_drogi_4(GEN)/60.0);
		};
		
		//PODSUMOWANIE (ETAP 6)
		//Obliczanie wartosci wyjsciowych

		//Zliczam caly czas dodany przez korki i skrzyzowania i dodaje do nich bazowy czas na pokonanie drogi
		czas = czas + road_time_values[road_int];

		//Wyliczam optymalna predkosc dla danej drogi przy optymalnym jej pokonywaniu (bez korków)
		double optymalna_predkosc = 0.0;
		optymalna_predkosc = (road_distance[road_int] / road_time_values[road_int]) * 1.0;
		
		//Wyliczam srednia predkosc dla danej drogi przy danym opoznieniu czasowym 
		double srednia_predkosc = 0.0;
		srednia_predkosc = (road_distance[road_int] / czas) * 1.0;

	
		double zmienna_1 = 0.0;
		double zmienna_2 = 0.0;

		double wynik = 0.0;
		double do_pliku = 0.0;


		zmienna_1 = (optymalna_predkosc / srednia_predkosc) * 1.0;
		zmienna_2 = (spalanie * road_distance[road_int]) / 100.0;

		wynik = zmienna_2 * zmienna_1;
		do_pliku = wynik * gas_price;

		cout <<wynik <<" "<<gas_price <<" " << do_pliku << endl;
		zapis << do_pliku << endl;
	

		
	};
	zapis.close();



}