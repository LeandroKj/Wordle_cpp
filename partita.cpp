#include "partita.h"
#include "util.h"
#include "ABR.h"
#include <vector>

guess::guess(string s, int n) : par(s), lett_giu(string(n, ' ')) {}

partita::partita(string w, ABR ws, int mx, int numLet) : parola(w), parole(ws),
	maxGuesses(mx), tentativi_rimasti(mx),finita(false), numLettere(numLet), indov(false), perso(false) {

	parola_finora = string(numLet, '_');

}

partita::partita(string w, ABR ws, int mx) : partita(w, ws, mx, 5) {}

partita::partita(string w, ABR ws) : partita(w, ws, 6, 5) {}

void partita::stampa() {

	//cout << endl;

	const int numSpazi = 10;

	const string intestazione = string(numSpazi, '=');
	const string spazi = string(numSpazi, ' ');

	pulisci();

	//cout << parola << " " << tentativi_rimasti << endl << endl;

	cout << intestazione << "WORDLE" << intestazione << endl << endl;

	cout << string(numSpazi-1, ' ') << "*" << parola_finora << "*" << endl << endl;

	for (auto s : guesses) {
	
		cout << spazi << s.par << endl;
		cout << spazi << s.lett_giu << endl;
	
	}

	if (!finita) {

		cout << spazi;

	}
	else {
	
		cout << intestazione << "======" << intestazione << endl << endl;

		if (indov) {
		
			cout << "Hai indovinato!!! ";
		
		}
		else {
		
			cout << "Hai perso. La parola era " << parola << ". ";
		
		}
	
	}

	//cout << maxGuesses << " " << parola << endl;

}

int partita::getTentativiRimasti() { return tentativi_rimasti; };

bool partita::getFinita() { return finita; };

void partita::avvia() {

	pulisci();

};

void partita::tentativo() {

	finita = indov || perso;

	stampa();

	if (finita) {
	
		return;
	
	}
	
	string tent;

	//pulisci();
	
	//cout << "Prossimo tentativo: ";
	cin >> tent;

	//PARTE PER CONTROLLARE CHE INSERISCA 
	//1. UNA PAROLA DEL NUMERO DI LETTERE GIUSTO
	//2. CHE ESISTA EFFETTIVAMENTE NELLA LISTA DI PAROLE
	//3. CHE NON L'ABBIA GIA USATA COME TENTATIVO

	if (tent.size() != numLettere) { return; }
	if (!parole.ricerca(tent)) { return; }
	
	for (auto s : guesses) {
	
		if (s.par == tent) { return; }
	
	}

	guess g = guess(tent, numLettere);

	--tentativi_rimasti;

	cout << tent;

	//Questa parte aggiorna "parola_finora"

	for (int i = 0; i < numLettere; ++i) {
	
		if (tent[i] == parola[i]) {
		
			parola_finora[i] = parola[i];
		
		}
	
	}

	//Questa parte aggiorna "lettere_giuste"

	for (int i = 0; i < numLettere; ++i) {

		for(int k = 0; k < numLettere; ++k) {
			
			if (tent[i]==parola[k]) {

				g.lett_giu[i] = '^';

			}

		}

	}

	//Manca cosa succede quando indovini o perdi

	if (tent == parola) {
	
		indov = true;
	
	}

	if (tentativi_rimasti == 0 && !indov) { perso = true; }

	guesses.push_back(g);

};

