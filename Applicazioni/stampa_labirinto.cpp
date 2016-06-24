template <class T> void Graph<T>::printMAZE(int ALTEZZA, int LARGHEZZA) {
	bool maze[ALTEZZA*2+1][LARGHEZZA*2+1];
	for(int i = 0; i < ALTEZZA*2+1; i++)
		for(int j = 0; j < LARGHEZZA*2+1; j++)
			maze[i][j]=false;

	for(auto vertex : graph){								//Per ogni vertice del grafo...
		int x = vertex.data.x * 2 +1;						//Ogni vertice è distanziato di 1 spazio dagli altri
		int y = vertex.data.y * 2 +1;
		maze[x][y] = true;									//Metto in tutte le coordinate dei vertici.
		for(auto edge : vertex.adj){
			int x2 = edge.link->data.x *2 +1;				//Per ogni adiacente
			int y2 = edge.link->data.y *2 +1;
															//Setto a 1 il collegamento i vertice
			if(x < x2 and y == y2) maze[x+1][y] = true;
			if(x > x2 and y == y2) maze[x-1][y] = true;
			if(x == x2 and y < y2) maze[x][y+1] = true;
			if(x == x2 and y > y2) maze[x][y-1] = true;
		}
	}

	for(int i = 0; i <ALTEZZA*2+1; i++){					//Stampo
		cout << endl;
		for(int j = LARGHEZZA*2; j >=0; j--)
			cout << " " << maze[j][i];}
}
