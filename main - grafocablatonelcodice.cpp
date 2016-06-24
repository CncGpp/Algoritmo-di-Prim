#include <iostream>
#include "Graph.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

int main(){
    cout <<"  __  __ _      _                   ___                      _             _____                    ___     _      " <<endl;
    cout <<" |  \\/  (_)_ _ (_)_ __ _  _ _ __   / __|_ __  __ _ _ _  _ _ (_)_ _  __ _  |_   _| _ ___ ___   ___  | _ \\_ _(_)_ __ " <<endl;
    cout <<" | |\\/| | | ' \\| | '  \\ || | '  \\  \\__ \\ '_ \\/ _` | ' \\| ' \\| | ' \\/ _` |   | || '_/ -_) -_) |___| |  _/ '_| | '  \\" <<endl;
    cout <<" |_|  |_|_|_||_|_|_|_|_\\_,_|_|_|_| |___/ .__/\\__,_|_||_|_||_|_|_||_\\__, |   |_||_| \\___\\___|       |_| |_| |_|_|_|_|" <<endl;
    cout <<"                                       |_|                         |___/                                           " <<endl;


/*
	//GRAFO D'ESEMPIO USATO NEL LIBRO DI TESTO.
	Graph<string> g;
	g.addVertex("A");
	g.addVertex("B");
	g.addVertex("C");
	g.addVertex("D");
	g.addVertex("E");
	g.addVertex("F");
	g.addVertex("G");
	g.addVertex("H");
	g.addVertex("I");

	g.link("A","B",4);
	g.link("A","H",8);
	g.link("B","C",8);
	g.link("H","I",7);
	g.link("H","G",1);
	g.link("C","D",7);
	g.link("C","I",2);
	g.link("C","F",4);
	g.link("G","I",6);
	g.link("G","F",2);
	g.link("F","D",14);
	g.link("F","E",10);
	g.link("B","H",11);
	g.link("D","E",9);

	cout << "Il grafo inserito in input e' il seguente: " << endl;
	g.printGraph();
	cout << "\nL'albero di copertura minimo del grafo, partendo dal vertice < "<< "A" << " > e':" << endl;
	auto& MST = g.MST_PRIM("A");																				//Reference al MST generato
	MST.printGraph();
	cout << "\nIl peso dell'MST e': " << MST.weight();

	delete &MST;																								//Libero la memoria allocata.
	cout << "\n\n Premi un tasto per chiudere...";
	cin.ignore();
	cin.get();
*/


	//Il seguente grafo e' rappresentato nell'immagine "GRAFO.png" allegata al progetto.
	Graph<char> g;
	char start = 'C';
	g.addVertex('A'); g.addVertex('B'); g.addVertex('C'); g.addVertex('D'); g.addVertex('E');
	g.addVertex('F'); g.addVertex('G'); g.addVertex('H'); g.addVertex('I');

	g.link('A','B',22); g.link('A','C',9); 	g.link('A','D',12);
	g.link('B','C',35); g.link('B','F',36); g.link('B','H',34);
	g.link('C','D',4); 	g.link('C','F',42); g.link('C','E',65);
	g.link('D','E',33); g.link('D','I',30);
	g.link('E','G',23); g.link('E','F',18);
	g.link('F','G',39); g.link('F','H',24);
	g.link('G','H',25); g.link('G','I',21);
	g.link('H','I',19);

	cout << "Il grafo inserito in input e' il seguente: " << endl;
	g.printGraph();
	cout << "\nInserire il nodo di partenza per il calcolo dell'MST: ";  cin >> start;
	cout << "\nL'albero di copertura minimo del grafo, partendo dal vertice < "<< start << " > e':" << endl;
	auto& MST = g.MST_PRIM(start);																				//Reference al MST generato
	MST.printGraph();
	cout << "\nIl peso dell'MST e': " << MST.weight();


	delete &MST;																								//Libero la memoria allocata.
	cout << "\n\n Premi un tasto per chiudere...";
	cin.ignore();
	cin.get();

	return 0;
}






