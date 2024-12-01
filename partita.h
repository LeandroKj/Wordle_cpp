#pragma once

#include <iostream>
#include <vector>
#include "ABR.h"
using namespace std;

class partita;

class guess {

private:
	string par;
	string lett_giu;
	guess(string, int);

	friend partita;

};

class diox {

	int a;

};

class partita {

private:
	vector<guess> guesses;
	int maxGuesses;
	int tentativi_rimasti;
	string parola;
	bool indov;
	bool perso;
	bool finita;
	string parola_finora;
	int numLettere;
	ABR parole;

public:
	//partita();
	partita(string, ABR);
	partita(string, ABR, int max);
	partita(string, ABR, int max, int numLet);

	int getTentativiRimasti();

	bool getFinita();

	void tentativo();

	void avvia();
	//void termina();

	void stampa();

};