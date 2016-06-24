
#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include <iostream>
#include <vector>
#include <map>
using namespace std;

template<class T> class PriorityQueue {
public:
	/**COSTRUTTORI E DISTRUTTORI*/
	PriorityQueue(bool (*compare)(T a,T b));			        //Costruttore con parametri.
	virtual ~PriorityQueue();									//Distruttore.

	/**FUNZIONI MEMBRO*/
	void insert(T obj);									    	//Inserisce un elemento nella coda.
	T remove();											    	//Estrae un elemento dalla coda.

	inline bool isEmpty() const;								//Restituisce true se la coda e' vuota, false altrimenti.
	int size() const {return heap.size();}						//Ritorna il numero di elementi presenti nella coda.
	inline bool inQueue(T obj) const;							//Restituisce true se l'elemento appartiene alla coda.
	void buildHeap();											//Consente di costruire l'heap interno alla coda.
	void decreasedNode(T obj);									//Ripristina l'heap sapendo che obj è stato diminuito.

private:
	vector<T> heap;												//La coda e' rappresentata internamente con un heap memorizzato in un vector.
	map<T, int> indexMap;										//map contenente le posizioni degli elementi nel vector.
	bool (*comparator)(T a,T b);								//Puntatore ad una funzione per il confronto degli elementi nella coda.

	/**FUNZIONI MEMBRO PRIVATE*/
	inline int parent(int a) const;								//Restituisce l'indice nel vector del padre dell'elemento di indice a.
	inline int left(int a) const;								//Restituisce l'indice nel vector del figlio sx dell'elemento di indice a.
	inline int right(int a) const;								//Restituisce l'indice nel vector del figlio dx dell'elemento di indice a.
	void decreaseNode(int n, T obj);							//Diminuisce il valore di un nodo tramite il suo indice.
	void heapify(int n);										//Ripristina la proprieta' dell'heap.
	void mySwap(T&,T&);											//Funzione di swap, scambia elementi sia nella map che nel vector
};

#endif /* PRIORITYQUEUE_H_ */



//		    ____        __ _       _     _                        _      _ _         __                 _             _
//		   |  _ \  ___ / _(_)_ __ (_)___(_) ___  _ __   ___    __| | ___| | | ___   / _|_   _ _ __  ___(_) ___  _ __ (_)
//		   | | | |/ _ \ |_| | '_ \| |_  / |/ _ \| '_ \ / _ \  / _` |/ _ \ | |/ _ \ | |_| | | | '_ \|_  / |/ _ \| '_ \| |
//		   | |_| |  __/  _| | | | | |/ /| | (_) | | | |  __/ | (_| |  __/ | |  __/ |  _| |_| | | | |/ /| | (_) | | | | |
//		   |____/ \___|_| |_|_| |_|_/___|_|\___/|_| |_|\___|  \__,_|\___|_|_|\___| |_|  \__,_|_| |_/___|_|\___/|_| |_|_|
//

template <class T> PriorityQueue<T>::PriorityQueue(bool (*compare)(T a,T b) ) {		//COSTRUTTORE: Riceve in input un puntatore a funzione da utilizzare per
		comparator = compare;
}
template <class T> PriorityQueue<T>::~PriorityQueue() {}							//DISTRUTTORE

template <class T> inline int PriorityQueue<T>::parent(int a) const{		//PADRE DEL NODO: Restituisce l'indice, nel vector, del padre del nodo
	if(a<=0) return -1;												        //				  memorizzato all'indice a.
		else return (a-1)/2;
}
template <class T> inline int PriorityQueue<T>::left(int a) const{			//FIGLIO SINISTRO: Restituisce l'indice, nel vector, del figlio SX del nodo
	if(a<0 or 2*a+1 > (int)heap.size() -1) return -1;				        //				   memorizzato all'indice a.
		else return 2*a+1;
}
template <class T> inline int PriorityQueue<T>::right(int a) const{			//FIGLIO DESTRO: Restituisce l'indice, nel vector, del figlio DX del nodo
	if(a<0 or 2*a+2 > (int)heap.size() -1) return -1;				         //				 memorizzato all'indice a.
		else return 2*a+2;
}

template <class T> void PriorityQueue<T>::heapify(int n){					//HEAPIFY: Ripristina la proprieta' dell'heap partendo dal nodo dell'albero
	int sx = left(n);												        //		   rappresentato con vector n.
	int dx = right(n);
	int max = n;
	if(sx != -1 and comparator(heap[sx], heap[max]) )
		max = sx;
	if(dx != -1 and comparator(heap[dx], heap[max]) )
		max = dx;

	if(max!=n)
	{
		mySwap(heap[n],heap[max]);
		heapify(max);
	}
}
template <class T> void PriorityQueue<T>::buildHeap(){						//BUILD HEAP: Costruisce un heap, partendo da un vector contenente elementi
	for(int i= parent(heap.size()-1); i>=0; i--)					        //			  che non rispettano la proprieta' dell'heap.
		heapify(i);
}

template <class T> void PriorityQueue<T>::insert(T obj){					//INSERT: Inserisce un nuovo elemento all'interno della coda.
	if(indexMap.find(obj) != indexMap.end())						        //L'elemento è gia stato inserito!
		return;

	indexMap.insert( make_pair(obj,heap.size()) );
	heap.push_back(obj);											//L'elemento viene inserito alla fine del vector ed in seguito
	decreaseNode(heap.size()-1,obj);								//chiamo la funzione changeNode che lo posizionera' correttamente.
}
template <class T> T PriorityQueue<T>::remove(){							//REMOVE: Estrae un elemento dalla coda.
	mySwap(heap[0],heap[heap.size()-1]);							//L'elemento da estrarre viene posizionato alla fine del vector,
	T temp = heap.back();											//scambiandolo con l'ultimo, quindi viene estratto dal vector
	indexMap.erase(heap[heap.size()-1]);
	heap.pop_back();
	heapify(0);														//e viene ripristinata la proprieta' dell'heap dalla cima con heapify.

	return temp;
}

template <class T> void PriorityQueue<T>::decreaseNode(int nodo, T obj){	//CHANGE NODE: Cambia il valore di un elemento ed in seguito ripristina
	if(nodo < 0) return;											        //			   la proprieta' dell'heap.

	heap[nodo] = obj;
	int padre = parent(nodo);

	while(padre>=0 and comparator(heap[nodo], heap[padre]))				//Risale l'heap dal basso verso l'alto e scambia se necessario
	{
		mySwap(heap[padre],heap[nodo]);
		nodo=padre;
		padre = parent(nodo);
	}
}

template <class T> void PriorityQueue<T>::decreasedNode(T obj){					//DECREASED_NODE: Riposiziona un elemento il cui valore e' diminuito
	if(indexMap.find(obj) == indexMap.end())							        //L'elemento obj non appartiene alla coda.
		return;
	decreaseNode(indexMap[obj],obj);
}

template <class T> inline bool PriorityQueue<T>::isEmpty() const{			//IS_EMPTY: restituisce true se la coda e' vuota, false altrimenti.
		return heap.empty();
}

template <class T> bool PriorityQueue<T>::inQueue(T obj) const{				//PRINT: Stampa in maniera molto semplice gli elementi del vector.
		return indexMap.find(obj)!=indexMap.end();
}

template <class T> void PriorityQueue<T>::mySwap(T& a, T& b) {		        //MT_SWAP: Effettua uno swap fra gli elementi dell'heap e della map
	swap(indexMap[a], indexMap[b]);
	swap(a,b);
}
