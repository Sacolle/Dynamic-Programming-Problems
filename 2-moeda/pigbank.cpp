#include <iostream>
#include <vector>

/*
* Dado um peso e um set de moedas, determinar o valor mínimo q o container pode ter
* https://www.spoj.com/problems/PIGBANK/
*/

using namespace std;

int moedaRec(int i, int D, vector<int> &valor, vector<int> &peso,vector<vector<int>> &mem){
	//a sacada é q se termina quando size == i, a sequencia é inválida
	if(D == 0)
		return 0;
	if(i == peso.size())
		return -1;
	if(mem.at(i).at(D) != -2)
		return mem.at(i).at(D);
	//pensando na estrutura de árvore, se o valor de todos os filhos é -1, então esse nodo faz parte de um caminho inváildo,
	//assim seu valor deve ser -1 e isso se repete recursivamente ao topo 
	int m1 = -1,m2 = -1,res = -1, parcial;
	if(peso.at(i) <= D){
		parcial = moedaRec(i, D - peso.at(i), valor, peso ,mem);
		if(parcial != -1){
			m1 = valor.at(i) + parcial;
		}
	}
	m2 = moedaRec(i+1,D,valor,peso,mem);

	//se m2 chegou ao fim da lista, retorna m1, que pode ser -1
	if(m2 == -1){
		res = m1;
	}else if(m1 == -1){
		res = m2;
	}else{
		res = m1 < m2 ? m1 : m2;
	}
	mem.at(i).at(D) = res;
	return mem.at(i).at(D);
}

int main(){
	int tests;
	cin >> tests;
	while(tests--){
		int min, max, n, cap;
		cin >> min >> max >> n;
		cap = max - min;
		vector<int> valor(n,0);
		vector<int> peso(n,0);
		vector<vector<int>> mem(n,vector<int>(cap + 1,-2));

		for(int i = 0; i < n; i++){
			cin >> valor[i] >> peso[i];
		}
		int res = moedaRec(0,cap,valor,peso,mem); 
		if(res == -1){
			cout << "This is impossible." << endl;
		}else{
			cout << "The minimum amount of money in the piggy-bank is " << res << "." << endl;
		}
	}

	return 0;
}