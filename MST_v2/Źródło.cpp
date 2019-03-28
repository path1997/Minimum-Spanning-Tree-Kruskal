#include<iostream>
#include<string>
#include<cstdlib>

class MST {
public:

	int **drogi, *kolor, pierwsza_dana, druga_dana, trzecia_dana, il_miast, il_drog, il_galezi, *dobre, *wsp,**drogi_temp;

	MST() {
		pierwsza_dana = 0;
		druga_dana = 0;
		trzecia_dana = 0;
		il_miast = 0;
		il_drog=0;
		il_galezi = 0;
	}

	void start() {
		std::cin >> il_miast;
		std::cin >> il_drog;

		kolor = new int[il_miast + 1];
		wsp = new int[3];


		drogi = new int *[il_drog];
		for (int i = 0; i < il_drog; i++) {
			drogi[i] = new int[3];
		}

		for (int i = 1; i <= il_miast; i++) {
			kolor[i] = i;
		}

		for (int i = 0; i < il_drog; i++) {
			std::cin >> pierwsza_dana;
			std::cin >> druga_dana;
			std::cin >> trzecia_dana;
			drogi[i][0] = pierwsza_dana;
			drogi[i][1] = druga_dana;
			drogi[i][2] = trzecia_dana;
		}
		sortowanie_drog();

		for (int i = 0; i < il_drog; i++) {
			if (kolor[drogi[i][0]] != kolor[drogi[i][1]]) {
				zamien(kolor[drogi[i][0]], kolor[drogi[i][1]]);
				//std::cout << drogi[i][0] << " " << drogi[i][1] << " " << drogi[i][2] << std::endl;
				drogi[il_galezi][0] = drogi[i][0];
				drogi[il_galezi][1] = drogi[i][1];
				drogi[il_galezi][2] = drogi[i][2];
				il_galezi++;
			}
		}
		dobre = new int[il_galezi];
		drogi_temp = new int *[il_galezi];
		for (int i = 0; i < il_galezi; i++) {
			drogi_temp[i] = new int[3];
		}
		

		std::cin >> pierwsza_dana;
		std::cin >> druga_dana;
		while (pierwsza_dana != 0 && druga_dana != 0) {
			std::cin >> trzecia_dana;
			for (int i = 0; i < il_galezi; i++) {
				for (int j = 0; j < 3; j++) {
					drogi_temp[i][j] = drogi[i][j];
				}
			}


			/*for (int i = 0; i < il_galezi; i++) {
				for (int j = 0; j < 3; j++) {
					std::cout << drogi_temp[i][j] << " ";
				}
				std::cout << std::endl;
			}*/
			std::cout<<analiza()<<std::endl;
			/*for (int i = 0; i < il_galezi; i++) {
				std::cout << dobre[i] << " ";
			}*/
			std::cin >> pierwsza_dana;
			std::cin >> druga_dana;
		}

		for (int i = 0; i < il_drog; i++) {
			delete[] drogi[i];
		}
		for (int i = 0; i < il_galezi; i++) {
			delete[] drogi_temp[i];
		}

		delete[] drogi_temp;
		delete[] kolor;
		delete[] drogi;
		delete[] wsp;
		delete[] dobre;
	}

	int analiza() {
		for (int i = 0; i < il_galezi; i++) {
			dobre[i] = -1;
		}
		int licznik_d = 0;
		int licznik_p = 1;
		int min = drogi[0][2];
		int poczatek = pierwsza_dana;
		int koniec = druga_dana;
		int il_osob = trzecia_dana;

		wyszukaj(poczatek);
		dobre[licznik_d] = wsp[0];

		while (wsp[2] != koniec) {
			//std::cout << "WSP0:" << wsp[0] << " WSP1:" << wsp[1] << " WSP2:" << wsp[2] << std::endl;
			if (czy_istnieje_dalej(wsp[2]) == true) {
				wyszukaj(wsp[2]);
				licznik_d++;
				dobre[licznik_d] = wsp[0];
			}
			else {
				drogi_temp[dobre[licznik_d]][0]=-1;
				drogi_temp[dobre[licznik_d]][1] = -1;
				drogi_temp[dobre[licznik_d]][2] = -1;
				//licznik_z++;
				dobre[licznik_d] = -1;
				licznik_d--;
				wsp[2] = wsp[1];
			}
			/*for (int i = 0; i < il_galezi; i++) {
				std::cout << dobre[i] << " ";
			}
			std::cout << std::endl;*/

		}
		for (int i = 0; i <= licznik_d; i++) {
			if (drogi[dobre[i]][2] < min) {
				min = drogi[dobre[i]][2];
			}
		}
		int suma = min+1;
		while (1) {
			if (suma < il_osob) {
				suma = suma + min+1;
				licznik_p++;
			}
			else {
				break;
			}
		}
		return licznik_p;

	}

	void wyszukaj(int liczba) {
		bool stan_wyszukaj = false;
		for (int c = 0; c < il_galezi; c++) {
			stan_wyszukaj = false;
			for (int v = 0; v < il_galezi; v++) {
				if (c == dobre[v]) {
					stan_wyszukaj = true;
				}
				if (stan_wyszukaj == false) {
					if (drogi_temp[c][0] == liczba) {
						wsp[0] = c;
						wsp[1] = drogi_temp[c][0];
						wsp[2] = drogi_temp[c][1];
						return;
					}
					else if (drogi_temp[c][1] == liczba) {
						wsp[0] = c;
						wsp[2] = drogi_temp[c][0];
						wsp[1] = drogi_temp[c][1];
						std::swap(drogi_temp[c][0], drogi_temp[c][1]);
						return;
					}
				}
			}
		}
	}

	bool czy_istnieje_dalej(int liczba) {
		for (int i = 0; i < il_galezi; i++) {
			bool stan = false;
			for (int j = 0; j < il_galezi; j++) {
				if (i == dobre[j]) {
					stan = true;
					break;
				}
			}
			if (stan == false) {
				if (drogi_temp[i][0] == liczba || drogi_temp[i][1] == liczba) {
					return true;
				}
			}
		}
		return false;
	}


	void sortowanie_drog()
	{
		for (int i = 0; i < il_drog; i++) {
			for (int j = 1; j < il_drog - i; j++) {
				if (drogi[j - 1][2] < drogi[j][2]) {
					std::swap(drogi[j - 1][0], drogi[j][0]);
					std::swap(drogi[j - 1][1], drogi[j][1]);
					std::swap(drogi[j - 1][2], drogi[j][2]);
				}
			}
		}
	}
	void zamien(int x, int y) {
		for (int k = 1; k <= il_miast; k++) {
			if (y == kolor[k]) {
				kolor[k] = x;
			}

		}

	}

};

int main() {
	MST m;
	m.start();
	return 0;
}