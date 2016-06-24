#include <iostream>
#include "Graph.h"
#include <math.h>
using namespace std;

const double PI = 3.1415926;
class City{
	friend bool operator<(const City& a, const City& b) {return a.nome < b.nome;}
	friend ostream& operator<<(std::ostream& os, const City& obj){
			cout<< " " << obj.nome << " ";
			return os;
		}
public:
	City(const string Nome, double Lat, double Long) : nome(Nome), latitudine(Lat), longitudine(Long){}
	static double distance(const City& a, const City& b) {
		//Calcolo della distanza geodetica tra due punti della superficie terrestre
		auto a_lat = PI*a.latitudine/180;
		auto a_lon = PI*a.longitudine/180;
		auto b_lat = PI*b.latitudine/180;
		auto b_lon = PI*b.longitudine/180;
		return acos( sin(a_lat)*sin(b_lat) + cos(a_lat)*cos(b_lat)*cos(a_lon-b_lon) ) * 6371;
	}

	string nome;
	double latitudine;
	double longitudine;
};

int main(){
	cout <<"    __  __ _      _              ___                     _             _____                    ___     _       " <<endl;
	cout <<"   |  \\/  (_)_ _ (_)_  _ _ __   / __|_ __  ___ _ _  _ _ (_)_ _  __ _  |_   _| _ ___ ___   ___  | _ \\_ _(_)_ __  " <<endl;
	cout <<"   | |\\/| | | ' \\| | || | '  \\  \\__ \\ '_ \\/ -_) ' \\| ' \\| | ' \\/ _` |   | || '_/ -_) -_) |___| |  _/ '_| | '  \\ " <<endl;
	cout <<"   |_|  |_|_|_||_|_|\\_,_|_|_|_| |___/ .__/\\___|_||_|_||_|_|_||_\\__, |   |_||_| \\___\\___|       |_| |_| |_|_|_|_|" <<endl;
	cout <<"                                    |_|                        |___/ " <<endl;


	vector<City> destinazioni;
	destinazioni.push_back( City("Roma", 41.799799, 12.245927) );
	destinazioni.push_back( City("Sidney", -33.940083, 151.175373) );
	destinazioni.push_back( City("Dubai", 25.252951, 55.365673) );
	destinazioni.push_back( City("Parigi", 49.009641, 2.547699) );
	destinazioni.push_back( City("Londra", 51.493008, 0.065300) );
	destinazioni.push_back( City("Mosca", 55.973558, 37.412503) );
	destinazioni.push_back( City("Atlanta", 33.640585, -84.427679) );
	destinazioni.push_back( City("Pechino", 40.079726, 116.603091) );
	destinazioni.push_back( City("Tokyo", 35.771856, 140.392807) );
	destinazioni.push_back( City("New York", 40.641189, -73.778161) );
	destinazioni.push_back( City("Madrid", 40.483806, -3.567984) );
	destinazioni.push_back( City("Istanbul", 40.982835, 28.810335) );
	destinazioni.push_back( City("Monaco di Baviera", 48.353534, 11.775082) );

	Graph<City> voli;
	for(auto x : destinazioni) voli.addVertex(x);


	for(unsigned int i = 0; i<destinazioni.size(); i++ )
		for(unsigned int j = i+1; j<destinazioni.size(); j++ )
				voli.link(destinazioni[i], destinazioni[j], City::distance(destinazioni[i],destinazioni[j]));


	cout << "Il grafo inserito in input e' il seguente: " << endl;
	voli.printGraph();
	cout << "\nL'albero di copertura minimo del grafo, partendo dal vertice < "<< destinazioni[0] << " > e':" << endl;
	auto& MST = voli.MST_PRIM(destinazioni[0]);																				//Reference al MST generato
	MST.printGraph();
	cout << "\nIl peso dell'MST e': " << MST.weight() << "km";

	delete &MST;																								//Libero la memoria allocata.
	cout << "\n\n Premi un tasto per chiudere...";
	cin.ignore();
	cin.get();

	return 0;
}



