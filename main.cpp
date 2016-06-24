#include <iostream>
#include "Graph.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
using namespace std;
/*
    Funzione che fornito il file ed il tipo legge il grafo da file
*/
template <class T> Graph<T> readGraph(ifstream *reader, T type)
{
    Graph<T> g;                                //Dichiaro un grafo di tipo T inizialmente vuoyo
    int vertex_num;                            //Contiene il numero di vertici del grafo
    T a, b;                                    //Variabili per leggere la coppia di vertici da collegare o aggiungere
    float weight;                              //Contiene il peso dell'arco che si sta collegando

    *reader >> vertex_num;                      //Leggo il numero di vertici del grafo
    for(int i = 0; i <vertex_num; i++){         //Leggo per ogniuno di essi l'identificativo e lo aggiungo al grafo.
        *reader >> a;
        g.addVertex(a);
    }

    while(*reader >> a >> b >> weight)          //Infine leggo le triple Verice1 vertice2 e peso e li collego
        g.link(a,b,weight);

    return g;
}

/*
    Funzione che semplicemente mostra il grafo appena letto e chiede in input da quale vertice partire
    per la ricerca del MST che avviene attraverso i metodi della classe Graph.
*/
template <class T> void trovaMST(Graph<T> &g){
    T start;
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

}

int main(int argc, char* argv[]){
    cout <<"  __  __ _      _                   ___                      _             _____                    ___     _      " <<endl;
    cout <<" |  \\/  (_)_ _ (_)_ __ _  _ _ __   / __|_ __  __ _ _ _  _ _ (_)_ _  __ _  |_   _| _ ___ ___   ___  | _ \\_ _(_)_ __ " <<endl;
    cout <<" | |\\/| | | ' \\| | '  \\ || | '  \\  \\__ \\ '_ \\/ _` | ' \\| ' \\| | ' \\/ _` |   | || '_/ -_) -_) |___| |  _/ '_| | '  \\" <<endl;
    cout <<" |_|  |_|_|_||_|_|_|_|_\\_,_|_|_|_| |___/ .__/\\__,_|_||_|_||_|_|_||_\\__, |   |_||_| \\___\\___|       |_| |_| |_|_|_|_|" <<endl;
    cout <<"                                       |_|                         |___/                                           " <<endl;

	string path;
	if(argc == 1){
        cout << "Specificare il path al file contenente il grafo: ";
        cin >> path; cout << endl;
    }else
        path = argv[1];
    ifstream reader(path);                               //Apro il file

    string type;                                         //Leggo il tipo del grafo
    reader >> type;

    if(type == "char"){                                  //Ed in base al tipo leggo e trovo l'MST
        auto g = readGraph(&reader,char());
        trovaMST(g);
    }
    if(type == "int"){
        auto g = readGraph(&reader,int());
        trovaMST(g);
    }
    if(type == "string"){
        auto g = readGraph(&reader,string());
        trovaMST(g);
    }

	return 0;
}

