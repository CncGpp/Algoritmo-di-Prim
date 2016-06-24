#include <iostream>
#include "Graph.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;


class Punto{
	//I punti vengono ordinati prima rispetto alla coordinata Y e poi rispetto X
	friend bool operator<(const Punto& a,const Punto& b) {
		if(a.x == b.x)
			return a.y < b.y;
		else return a.x < b.x;
	}
	friend ostream& operator<<(std::ostream& os, const Punto& obj){
		cout<< "[" << obj.x << "," << obj.y << "]";
		return os;
	}
public:
	Punto(float a, float b) : x(a), y(b) {}
	float x;
	float y;
private:
	static float dist(Punto a, Punto b) {return sqrtf( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );}
};


const int ALTEZZA = 9;
const int LARGHEZZA = 9;

int main(){
	cout <<"    __  __ _      _              ___                     _             _____                    ___     _       " <<endl;
	cout <<"   |  \\/  (_)_ _ (_)_  _ _ __   / __|_ __  ___ _ _  _ _ (_)_ _  __ _  |_   _| _ ___ ___   ___  | _ \\_ _(_)_ __  " <<endl;
	cout <<"   | |\\/| | | ' \\| | || | '  \\  \\__ \\ '_ \\/ -_) ' \\| ' \\| | ' \\/ _` |   | || '_/ -_) -_) |___| |  _/ '_| | '  \\ " <<endl;
	cout <<"   |_|  |_|_|_||_|_|\\_,_|_|_|_| |___/ .__/\\___|_||_|_||_|_|_||_\\__, |   |_||_| \\___\\___|       |_| |_| |_|_|_|_|" <<endl;
	cout <<"                                    |_|                        |___/ " <<endl;

	//srand(time(0));

	//Aggiungo tutti i vertici all'interno del grafo
	Graph<Punto> maze;
	for(int i = 0; i < ALTEZZA;i++)
		for(int j = 0; j < LARGHEZZA;j++)
			maze.addVertex(Punto(i,j));

    //E per ognino di essi creo un collegamento con peso casuale con quello sopra e quello a destra.
	for(int i = 0; i < ALTEZZA;i++)     //Nel caso i vertici non esistano non viene eseguita alcuna operazione.
		for(int j = 0; j < LARGHEZZA;j++){
			Punto a(i,j);               //Vertice corrente
			Punto b(i+1,j);             //Vertice in altro
			Punto c(i,j+1);             //Vertice a destra
			maze.link(a,b,rand());      //Effettuo i collegamenti
			maze.link(a,c,rand());
		}

	cout << "Il grafo inserito in input e' il seguente: " << endl;
	maze.printGraph();
	cout << "\nL'albero di copertura minimo del grafo, partendo dal vertice < "<< Punto(0,0) << " > e':" << endl;
	auto& MST = maze.MST_PRIM(Punto(0,0));																		//Reference al MST generato
	MST.printGraph();
	cout << "\nIl peso dell'MST e': " << MST.weight();


	delete &MST;																								//Libero la memoria allocata.
	cout << "\n\n Premi un tasto per chiudere...";
	cin.ignore();
	cin.get();

	return 0;
}






