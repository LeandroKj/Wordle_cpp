#include "util.h"
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

string elemento_casuale(vector<string> vec) {

	srand((unsigned)time(NULL)); 
    	int i = rand(); i = rand(); i = rand() % vec.size();
    	return vec[i];
}


string elemento_casuale(ABR abr) {

    return elemento_casuale(abr.toVector());

}

void pulisci() { std::system("cls"); }

