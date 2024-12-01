#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>

#include "partita.h"
#include "util.h"
#include "ABR.h"

const int NUMEROLETTERE = 5;

const string wordBankUrl;

using namespace std;

int getMaxGuesses() {

	int max = 6;
	cout << "Numero di tentativi massimi? ";
	
	while (!(cin >> max) || max < 1) {
	
		cout << "Riprova con un numero intero maggiore di 0: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	}

	return max;

}

ABR load_words() {

	ifstream input;
	ABR parole;
	//vector<string> vec;
	string s;
	string filename;

	//S_OK == URLDownloadToFile(NULL, SourceURL.c_str(), DestinationFile.c_str(), 0, NULL)

	cout << "Nome del file da cui prendere le parole? ";
	cin >> filename;
	//filename = "words.txt";

	input.open(filename);

	while (!input) {

		cout << "Non riesco ad aprire il file. Riprova: ";

		cin >> filename;
		input.open(filename);

	}

	bool good;

	while (input >> s) { 

		//debug
		//if (parole.nElem() == 30) { break; }
		
		//1. PAROLE DI 5 LETTERE
		//2. CON LETTERE SOLO INGLESI

		good = true;

		if (s.size() > NUMEROLETTERE) {
			//cout << s << ": not ok" << endl;
			continue;
		}

		for (int i = 0; i < NUMEROLETTERE; ++i) {

			char c = s[i];

			if (c < 97 || c > 122) {
			
				if (c < 65 || c > 90) {
				
					good = false;
					//cout << s << ": not ok" << endl;
					break;
				
				}
				else {
				
					s[i] = c + 32;
				
				}
			
			}

		}

		if (good) { 
			parole.inserisci(s);
			//cout << s << ": ok" << endl;

			//string k; cin >> k;

		}
	
	}

	return parole;
}

/*void test3() {

	bool cont = true;

	while (cont) {

		for (int i = 0; i < 100000; ++i) {

			//nodo* ptr = test2();
			//ptr->stampa_nodo();
			//delete ptr;

		}

		cout << "Fatto. Continuare? (y/n)" << endl;

		string s; cin >> s; cont = (s == "y");

	}

}

void test4() {

	ABR albero1 = ABR("50");
	//albero1.stampa();

	albero1.inserisci("42");
	albero1.inserisci("56");
	albero1.inserisci("42");
	albero1.inserisci("56");
	albero1.inserisci("72");
	albero1.inserisci("10");
	albero1.inserisci("60");

	albero1.stampa();

	cout << albero1.ricerca("32") << endl;
	cout << albero1.ricerca("50") << endl;
	cout << albero1.ricerca("60") << endl;

	//nodo* r = albero1.radix; r->stampa();
	//nodo* dx = r->figlio_destro; dx->stampa();
	//nodo* sx = r->figlio_sinistro; sx->stampa();

}

void controlla(ABR albe) {

	cout << "1: " << (albe.ricerca("1") ? "trovato" : "non trovato") << endl;
	cout << "2: " << (albe.ricerca("2") ? "trovato" : "non trovato") << endl;
	cout << "3: " << (albe.ricerca("3") ? "trovato" : "non trovato") << endl;
	cout << "4: " << (albe.ricerca("4") ? "trovato" : "non trovato") << endl;

}

void test5() {

	ABR alb = ABR("1");

	controlla(alb);

	alb.inserisci("2");
	alb.stampa();

	controlla(alb);

	alb.inserisci("3");
	alb.stampa();

	controlla(alb);

	alb.inserisci("4");
	alb.stampa();

	controlla(alb);

	alb.bilancia();
	alb.stampa();

	controlla(alb);

	cout << "h di alb: " << alb.get_altezza() << endl;

	ABR alb2 = alb.figlioDx();
	alb2.stampa();

	cout << "h di alb2: " << alb2.get_altezza() << endl;

	/*cout << alb.get_key();

	cout << endl;
	ABR alb2 = alb.figlioDx();
	alb2.stampa();
	cout << alb2.get_key();

}*/

void main() {

	//test5();

	//return;

	pulisci();

	cout << endl << "Ciao! Stai per giocare a una versione di wordle per C++.\n\n";
	
	ABR parole = load_words();

	/*/parole.stampa();

	cout << parole.massimo() << endl;
	cout << parole.minimo() << endl;

	ABR subPar = parole.figlioDx();

	cout << subPar.massimo() << endl;
	cout << subPar.minimo() << endl;

	int n = parole.nElem();
	cout << "h : " << parole.get_altezza() << endl;
	cout << "n : " << n << endl;
	cout << "log2(n) : " << log2(float(n)) << endl;*/

	bool cont = true;

	while (cont) {

		string PAROLA = elemento_casuale(parole);

		int MASSIMO = getMaxGuesses();

		partita parti = partita(PAROLA, parole, MASSIMO, NUMEROLETTERE);
		
		while (!parti.getFinita()) {

			parti.tentativo();

		}

		cout << "Vuoi giocare di nuovo? (y/n) ";
		
		string b; cin >> b;

		cont = b == "y";

	}

	//pulisci();

}