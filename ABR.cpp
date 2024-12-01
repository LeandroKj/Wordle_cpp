#include <iostream>

#include "ABR.h"
#include "util.h"

using namespace std;

//NODO

nodo::nodo() : nodo("") {}
nodo::nodo(string k) : chiave(k), figlio_destro(NULL), figlio_sinistro(NULL), padre(NULL) {}

nodo* nodo::radice() {
    return (padre == NULL ? this : padre->radice());
}
nodo* nodo::predecessore() {

    return this;

}

void nodo::nodoInVettore(vector<nodo*>* vec) {

    vec->push_back(this);
    if (figlio_destro != NULL) {
        figlio_destro->nodoInVettore(vec); }

    if (figlio_sinistro != NULL) {
        figlio_sinistro->nodoInVettore(vec); }

}

bool nodo::foglia() {

    return (figlio_destro == NULL && figlio_sinistro == NULL);

}
int nodo::prof() {

    if (padre == NULL) {

        return 0;

    }

    return (padre->prof()) + 1;

}
int nodo::altz() {

    if (foglia()) { return 0; }

    int adx = (figlio_destro == NULL ? 0 : figlio_destro->altz());
    int asx = (figlio_sinistro == NULL ? 0 : figlio_sinistro->altz());

    return max(adx, asx) + 1;

}

void nodo::stampa() {

    cout << "\"" << chiave << "\": [this: ";
    cout << this << "; ";

    cout << "padre: ";
    cout << padre;
    if (padre != NULL) { cout << "(" << padre->chiave << ")"; }

    cout << "; dx: ";
    cout << figlio_destro;
    if (figlio_destro != NULL) { cout << "(" << figlio_destro->chiave << ")"; }

    cout << "; sx: ";
    cout << figlio_sinistro;
    if (figlio_sinistro != NULL) { cout << "(" << figlio_sinistro->chiave << ")";
    }

    cout << "]\n";

}

nodo* nodo::massimo_interno() {

    if (figlio_destro == NULL) { return this; }
    else return(figlio_destro->massimo_interno());

}
nodo* nodo::minimo_interno() {

    if (figlio_sinistro == NULL) { return this; }
    else return(figlio_sinistro->minimo_interno());

}

//ALBERO
ABR::ABR(string s) : ABR(new nodo(s)) {}
ABR::ABR() : ABR(NULL) {}
ABR::ABR(nodo* n) {

    radix = n;

}

vector<string> ABR::toVector() {

    vector<string> v;

    for (nodo* ptr : lista_nodi()) {
    
        v.push_back(ptr->chiave);
    
    }

    return v;

}

bool ABR::bilancia(nodo* n) {

    //restituisce true se riesce a inserire, ovvero non trova il nodo

    //Se l'albero è vuoto, aggiunge l'elemento senza fare nulla obv;
    if (vuoto()) {
    
        if (n != NULL) { radix = n; }
        return true;
    
    }

    srand((unsigned)time(NULL));

    vector<nodo*> vec = lista_nodi();

    if (n != NULL) {
        vec.push_back(n);
    }

    n_elem = vec.size();

    for (nodo* v : vec) {
    
        v->padre = NULL;
        v->figlio_destro = NULL;
        v->figlio_sinistro = NULL;
    
    }

    bool trovato = false;

    ABR* nuovoAlbPtr = new ABR();

    while ( !vec.empty()) {

        unsigned i = rand(); i = rand(); i = rand() % vec.size();

        //cout << "Vec size: " << vec.size() << " Rand: " << i << " Key: " << vec[i]->chiave<< endl;

        bool temp = !(nuovoAlbPtr->inserisci_interno(vec[i]));

        if (temp) {
            trovato = temp;
        }

        vec.erase(vec.begin() + i);

    }

    radix = nuovoAlbPtr->radix;


    delete nuovoAlbPtr;

    return !trovato;

}

void ABR::bilancia() {

    bilancia(NULL);

}

ABR ABR::figlioDx() { 
    
    if (radix->figlio_destro == NULL) { return *new ABR(); }
    
    return *new ABR(radix->figlio_destro);

}

ABR ABR::figlioSx() {

    if (radix->figlio_sinistro == NULL) { return *new ABR(); }

    return *new ABR(radix->figlio_sinistro);
}

ABR ABR::genitore() {

    if (radix->padre == NULL) { return *new ABR(); }

    return *new ABR(radix->padre);
}
string ABR::get_key() { return radix->chiave; }

int ABR::get_altezza() {

    return radix->altz();

}

inline bool ABR::vuoto() { return (this->radix == NULL); }

bool ABR::ricerca(string s) {

    return (ricerca_interna(s)[0] != NULL);

}

vector<nodo*> ABR::ricerca_interna(string s) {

    //Restituisce
    //ptr1: NULL se non trova nulla, altrimenti punta al nodo trovato
    //ptr2: ultimo nodo prima di trovare NULL o s -> ptr2 è NULL solo se l'albero è vuoto;

    nodo* ptr1 = radix;
    nodo* ptr2 = NULL;

    while (ptr1 != NULL) {

        ptr2 = ptr1;

        if (s == ptr1->chiave) {
            break; 
        }

        ptr1 = (s < ptr2->chiave ? ptr2->figlio_sinistro : ptr2->figlio_destro);

    }

    return { ptr1, ptr2 };

}

bool ABR::inserisci(string s) {

    //MANCA:    implementa un sistema per cui l'albero si bilancia
    //          solo dopo che un tot di elementi (questo tot
    //          dipende da quanti elementi sono già presenti)
    //          vengono inseriti normalmente. Così l'albero ha un
    //          "margine di tolleranza" riguardo a quanto sbilanciato può essere.
    //          Evitando così di doversi bilanciare ogni volta, magari inutilmente.

    //restituisce true se riesce a inserire, ovvero non trova il nodo

    if (ricerca(s)) { return false; }

    nodo* n = new nodo(s);

    bool ins = bilancia(n);

    return ins;

}

bool ABR::inserisci_interno(nodo* nuovoPtr) {

    //restituisce true se riesce a inserire, ovvero non trova il nodo

    string s = nuovoPtr->chiave;
    vector<nodo*> ptrA = ricerca_interna(s);

    if (ptrA[0] == NULL) {

        //nodo* nuovoPtr = new nodo(s);
        nuovoPtr->padre = ptrA[1];

        if (ptrA[1] == NULL) {

            radix = nuovoPtr;

        }
        else if (s < ptrA[1]->chiave) {

            ptrA[1]->figlio_sinistro = nuovoPtr;

        }
        else { ptrA[1]->figlio_destro = nuovoPtr; }

        //bilancia();

        return true;

    }
    else { return false; }

}

void ABR::stampa_interna(nodo* n) {

    cout << n->chiave;

    cout << "\t";

    if (n->figlio_destro != NULL) {

        stampa_interna(n->figlio_destro);

    }
    else { cout << "[ ]"; }

    cout << "\n";

    for (int i = 0; i < n->prof() + 1; ++i) {

        cout << "\t";

    }

    if (n->figlio_sinistro != NULL) {

        stampa_interna(n->figlio_sinistro);

    }
    else { cout << "[ ]"; }

    cout << "\n";

}

vector<nodo*> ABR::lista_nodi() {

    vector<nodo*> v;

    radix->nodoInVettore(&v);

    /*for (auto k : v) {
    
        cout << k->chiave << endl;
    
    }*/

    return v;

}

void ABR::stampa() {

    /*for (nodo* ptr : lista_nodi()) {
    
        ptr->stampa();
    
    }*/

    //return;

    stampa_interna(radix);

}

string ABR::massimo() {

    return radix->massimo_interno()->chiave;

}

string ABR::minimo() {

    return radix->minimo_interno()->chiave;

}

int ABR::nElem() {

    return n_elem;

}
