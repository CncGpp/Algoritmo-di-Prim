
#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <climits>
#include <list>
#include <set>
#include <map>
#include "PriorityQueue.h"
using namespace std;

template<class T> class Graph {
	class Vertex;												//Dichiarazione della classe Vertex, definizione in seguito..
	class Edge;													//Dichiarazione della classe Edge, definizione in seguito..

	typedef typename set<Graph<T>::Vertex>::iterator VertexIt;
	typedef typename list<Graph<T>::Edge>::iterator EdgeIt;

	 /*DEFINIZIONE DELLA CLASSE INTERNA VERTEX*/
	 class Vertex{
		friend ostream& operator<<(std::ostream& os, const Vertex& obj){
			obj.printVertex();
			return os;
		}
		friend bool operator<(const Vertex& x,const Vertex& y) { return x.data<y.data; }//Funzione di confronto fra i vertici.
	 public:
		Vertex(T data, int pr=0) : data(data), priority(pr), adj() {}					//Costruttore con parametri.
		void printVertex() const;														//Stampa il vertice.
		void printAdj() const;															//Stampa gli archi per i vertici adiacenti.

		T data;																			//Contiene le "informazioni" del vertice.
		mutable int priority;															//Priorita' del vertice.
		mutable list<Graph<T>::Edge> adj;												//Lista degli archi adiacenti.
		//Mutable perche std::set restituisce const_iterator che non permettono la modifica diretta.
	};

	/*DEFINIZIONE DELLA CLASSE INTERNA EDGE*/
	class Edge{
	public:
		Edge(VertexIt link, float weight) : link(link), weight(weight){}				//Costruttore con parametri.
		void printEdge() const;															//Stampa l'arco.
		VertexIt link;																	//Iteratore al vertice che l'arco connette.
		float weight;																	//Peso dell'arco.
	};



private:
	//NB: affinche' sia possibile utilizzare il set e' necessario che gli elementi di tipo 'T' abbiano definita la relazione 'a' < 'b'
	set<Graph<T>::Vertex> graph;						 					//Set di vertici che compongono il grafo.


public:
	// COSTRUTTORE E DISTRUTTORE
	Graph(){}																//Costruttore di default.
	virtual ~Graph(){}														//Distruttore di default.
	// GETTER & SETTER
	const set<Graph<T>::Vertex>& getGraph() const {return graph;}			//Metodo getter, ritorna un riferimento costante al grafo.

	// METODI DI CLASSE
	void addVertex(T data, int priority = 0);								//Crea e aggiunge un vertice dati 'data' e 'priority'.
	void printGraph() const;												//Stampa il grafo rappresentandolo come liste di adiacenza.
	void link(T a, T b, float weight);										//Collega due vertici 'a' e 'b' con peso 'weight'.
	void link(VertexIt a, VertexIt b, float weight);
	void unlink(T a, T b);													//Scollega due vertici 'a' e 'b'.
	void unlink(VertexIt a, VertexIt b);
	void disconnect(T a);													//Disconnette un vertice dal grafo.
	void disconnect(VertexIt a);
	bool isConnected(T a) const;											//Ritorna true se il vertice e' connesso, false altrimenti.
	bool isConnected(VertexIt a) const;
	float weight() const;													//Calcola il peso del grafo (somma di tutti i pesi).

	Graph<T>& MST_PRIM(T start) const;										//Calcola e ritorna l'MST del grafo partendo da un vertice.
	Graph<T>& MST_PRIM(VertexIt start) const;
};

#endif /* GRAPH_H_ */


//			    ____        __ _       _     _                        _      _ _         __                 _             _
//			   |  _ \  ___ / _(_)_ __ (_)___(_) ___  _ __   ___    __| | ___| | | ___   / _|_   _ _ __  ___(_) ___  _ __ (_)
//			   | | | |/ _ \ |_| | '_ \| |_  / |/ _ \| '_ \ / _ \  / _` |/ _ \ | |/ _ \ | |_| | | | '_ \|_  / |/ _ \| '_ \| |
//			   | |_| |  __/  _| | | | | |/ /| | (_) | | | |  __/ | (_| |  __/ | |  __/ |  _| |_| | | | |/ /| | (_) | | | | |
//			   |____/ \___|_| |_|_| |_|_/___|_|\___/|_| |_|\___|  \__,_|\___|_|_|\___| |_|  \__,_|_| |_/___|_|\___/|_| |_|_|
//
/*
 +-----------------------------------------------------------------------------------------------------------------------------------+
 | 												   		METODI DELLA CLASSE  GRAPH													 |
 +-----------------------------------------------------------------------------------------------------------------------------------+
*/
template <class T> void Graph<T>::addVertex(T data, int priority){	//ADD_VERTEX: Aggiunge un vertice al grafo.
	Vertex v(data, priority);
	graph.insert(v);
}

template <class T> void Graph<T>::printGraph() const{				//PRINT_GRAPH: Stampa il grafo sottoforma di liste di adiacenza
	for(auto it : graph){	//Per ogni vertice del grafo..
		it.printVertex();	//Stampo prima il vertice e
		it.printAdj();		//poi la lista degli adiacenti.
		cout << endl;
	}
}

template <class T> void Graph<T>::link(T a, T b, float weight) {	//LINK:	Connette due vertici 'a' e 'b' in input mediante valore
	VertexIt vertice1 = graph.find(a);								//		con un arco avente peso pari a 'weight'.
	VertexIt vertice2 = graph.find(b);								//I vertici sono ricercati nel set tramite il loro valore
																	//e collegati dalla funzione che opera con gli iteratori.
	link(vertice1, vertice2, weight);
}
template <class T> void Graph<T>::link(VertexIt a, VertexIt b, float weight) {
	if(a == graph.end() or b == graph.end())			//Se uno dei due nodi non e' presente nel grafo ritorno
		return;

	(a->adj).push_back(Edge(b,weight));					//Inserisco 'b' nella lista di adiacenza di 'a'
	(b->adj).push_back(Edge(a,weight));					//Inserisco 'a' nella lista di adiacenza di 'b'
}

template <class T> void Graph<T>::unlink(T a, T b) {				//UNLINK: Disconnette i vertici 'a' e 'b' in input mediante valore.
	VertexIt vertice1 = graph.find(a);
	VertexIt vertice2 = graph.find(b);

	unlink(vertice1, vertice2);										//Trovate le occorrenze, chiama la funzione con gli iteratori.
}
template <class T> void Graph<T>::unlink(VertexIt a, VertexIt b) {
	if(a == graph.end() or b == graph.end())						//Se uno dei due nodi non e' presente nel grafo ritorno
		return;

	for(EdgeIt it = a->adj.begin(); it!=a->adj.end(); it++){	//Ricerco tra gli adiacenti di 'a' l'arco che porta a 'b' e lo elimino.
		if(it->link == b){
			a->adj.erase(it);
			break;
		}
	}

	for(EdgeIt it = b->adj.begin(); it!=b->adj.end(); it++){	//Ricerco tra gli adiacenti di 'b' l'arco che porta a 'a' e lo elimino.
		if(it->link == a){
			b->adj.erase(it);
			break;
		}
	}

}

template <class T> void Graph<T>::disconnect(T a) {					//DISCONNECT: Disconnette un vertice da tutti i suoi adiacenti.
	VertexIt vertice = graph.find(a);

	disconnect(vertice);
}
template <class T> void Graph<T>::disconnect(VertexIt a) {
	if(a == graph.end())											//Se il vertice non e' presente nel grafo ritorna.
		return;

	for(EdgeIt it = a->adj.begin(); it!=a->adj.end();)			//Poiche' non e' possibile eliminare l'elemento corrente di
		unlink((it++)->link, a);								//un iterator ementre sta scorrendo la lista e' necessario farlo
																//puntare all'elemento successivo prima della cancellazione.
}

template <class T> bool Graph<T>::isConnected(T a) const{			//IS_CONNECTED: Ritorna true se il vertice in input e' un
	VertexIt vertice = graph.find(a);								//				vertice connesso altrimenti ritorna false.

	return isConnected(vertice);
}
template <class T> bool Graph<T>::isConnected(VertexIt a) const{
	if(a == graph.end())												//Se il vertice non e' presente nel grafo ritorna false.
		return false;
	return !a->adj.empty();												//Controlla se la lista di adiacenza di 'a' e' vuota o meno.
}

template <class T> Graph<T>& Graph<T>::MST_PRIM(T start) const{		//MTS_PRIM: Ritorna un sottografo che partendo dal vertice
	VertexIt vertice = graph.find(start);							//			'start' fornito, risulta essere un MST.

	return MST_PRIM(vertice);
}

template <class T> Graph<T>& Graph<T>::MST_PRIM(VertexIt start) const{
	Graph<T>& MST = *new Graph();								//Alloco memoria per memorizzare l'MST, inizialmente un grafo vuoto.

	if(start == graph.end())									//Se il vertice di partenza 'start' non e' presente nel grafo ritorno MST.
		return MST;
	//Creo una coda di min-priorita' contenente i vertici.
	PriorityQueue<Vertex*> queue( [](Vertex* a, Vertex* b){return a->priority < b->priority;} );

	//INSERISCO I NODI NELL'MST MA SENZA ANCORA CREARE CONNESSIONI, MST=(V,0).
	for(auto it : graph) MST.addVertex(it.data);

	//INSERISC NELLA CODA TUTTI I VERTICI DEL GRAFO TRAMITE I LORO PUNTATORI
	for(VertexIt it = graph.begin(); it!=graph.end(); it++){
		it->priority = INT_MAX;											//Setto la priorita' del vertice a +infinito (Massimo int rapp)
		Vertex* ptr = (Vertex*)&(*it);									//ottengo il puntatore al vertice del grafo.
		queue.insert(ptr);												//infine inserisco il puntatore nella coda.
	}

	graph.find(start->data)->priority = 0;								//Setto la priorita' del vertice start a 0, in modo da estrarlo
	queue.buildHeap();													//per primo dalla coda e costruisco l'heap.

	while(!queue.isEmpty()){											//Fin che la coda non e' vuota...
		Vertex* u = queue.remove();							    		//Estraggo il nodo con minore priorita' memorizzandolo in 'u'
		for(auto x : u->adj){
			Vertex* v = (Vertex*)&(*x.link);							//Per ogni vertice 'v' adiacente al vertice 'u'
			if( queue.inQueue(v) and v->priority > x.weight ){			//Se 'v' si trova nella coda e la sua priorita' e' > del peso
				v->priority = x.weight;									//dell'arco.. aggiorna la priorita' di 'v'
				queue.decreasedNode(v);
				if(MST.isConnected(v->data))							//Se il corrispettivo di 'v' nell'MST e' connesso, con
					MST.disconnect(v->data);							//qualche altro vertice allora lo disconnetto.
				MST.link(v->data,u->data, x.weight);					//E lo riconnetto quindi con il vertice 'u' dell'MST.
			}
		}
	}

	return MST;
} //FINE


template <class T> float Graph<T>::weight() const{					//WEIGHT: Ritorna il peso del grafo (somma dei pesi degli archi)
	float weight = 0;
	for(const auto vertex : graph)						//Scorro i vertici
		for(const auto edge : vertex.adj)				//Scorro gli adiacenti
			weight += edge.weight;						//Sommo i pesi
	//Alla fine divido per due in quanto per ogni coppia di vertici collegati ho due archi con stesso peso.
	return weight/2;
}


/*
 +-----------------------------------------------------------------------------------------------------------------------------------+
 | 												   		METODI DELLA CLASSE  VERTEX													 |
 +-----------------------------------------------------------------------------------------------------------------------------------+
*/
template <class T> void Graph<T>::Vertex::printVertex() const{		//PRINT_VERTEX: Stampa il vertice corrente.
	cout << "[" << data << "]";										//NB: Richiede che il tipo 'T' possa essere stampato.
}
template <class T> void Graph<T>::Vertex::printAdj() const{			//PRINT_ADJ: Stampa gli archi ai nodi adiacenti.
	for(auto it : adj)
		it.printEdge();				//Stampa l'arco

	cout << "--x";					//Stampa simbolo che indica la fine nella lista.
}


/*
 +-----------------------------------------------------------------------------------------------------------------------------------+
 | 												   		METODI DELLA CLASSE  EDGE													 |
 +-----------------------------------------------------------------------------------------------------------------------------------+
*/
template <class T> void Graph<T>::Edge::printEdge() const{			//PRINT_EDGE: Stampa l'arco corrente, con peso e vertice.
	cout << "-->(" << weight << ")";		//Stampa il peso
	link->printVertex();					//E poi il vertice con cui c'e' il collegamento.
}
