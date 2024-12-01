#pragma once

#include <vector>
#include <string>

//#include "util.h"

using namespace std;

class ABR;

class nodo {

private:
	nodo* figlio_destro;
	nodo* figlio_sinistro;
	nodo* padre;
	string chiave;

	nodo();
	nodo(string);

	//MANCANO PREDECESSORE E SUCCESSORE
	//nodo* successore();
	nodo* predecessore();
	nodo* massimo_interno();
	nodo* minimo_interno();
	nodo* radice();

	bool foglia();
	int prof();
	int altz();

	void nodoInVettore(vector<nodo*>* );

	void stampa();

	friend ABR;

};

class ABR {

private:
	nodo* radix;
	vector<nodo*> ricerca_interna(string);
	void stampa_interna(nodo*);
	vector<nodo*> lista_nodi();
	bool inserisci_interno(nodo*);
	bool bilancia(nodo*);
	ABR(nodo*);
	int n_elem;
	//int altezza;
	

public:
	ABR(string);
	ABR();
	bool inserisci(string);
	//bool rimuovi(string);

	bool ricerca(string);

	vector<string> toVector();

	//La distribuzione casuale usata per bilanciare l'albero
	// ha un po di bias e quindi non bilancia bene.
	// h è sempre > log2(n) di tanto.
	void bilancia();

	ABR figlioDx();
	ABR figlioSx();
	ABR genitore();
	string get_key();
	int get_altezza();
	bool vuoto();
	int nElem();
	
	void stampa();

	string minimo();
	string massimo();
	
};

