#include <iostream>
#include <vector>

using namespace std;

int min(int a,int b){
	return a < b ? a : b;
}

/*
* problema: https://www.spoj.com/problems/MIXTURES/
* A sacada do problema é gerar uma matriz bidimensional com todos os possíveis valores acumulados das poções.
* ou seja, para 3 poções de valor 40 60 e 20 gera-se
* [40 100 120;
*   0  60  80;
*   0   0  20]
* com isso pode-se calcula qualquer valor de fumaça, quando a recursão gerar a expressão mix(0,0) + mix(1,2)
* sabe-se que é o valor do range (0,0) 40 % 100, ou seja, o index 0,0 da matriz, vezes o range (1,2) 80 % 100.  
* Pois o index i j da matriz é o valor da soma de i a j.
*/

int mix(int i, int j,vector<int> &pot,vector<vector<int>> &acc,vector<vector<int>> &mem){
	if(i == j)
		return 0;
	if(mem.at(i).at(j) != -1)
		return mem.at(i).at(j);
	int res = 100000000; // era pra ser INT_MAX mas isso dah tb
	for(int k = i; k < j; k++){
		res = min(res, mix(i,k,pot,acc,mem) + mix(k+1,j,pot,acc,mem) + (acc.at(i).at(k)%100)*(acc.at(k+1).at(j)%100));
	}
	mem.at(i).at(j) = res;
	return res;
}

int main(){
	int n;
	while(cin >> n){
		vector<int> pot(n,0);
		for(int i =0; i < n; i++){
			cin >> pot[i];
		}
		vector<vector<int>> acc(n,vector<int>(n,0));

		for(int i = 0; i < n; i++){
			for(int j = i; j < n; j++){
				if(j != 0){
					acc[i][j] = acc[i][j] + acc[i][j-1] + pot[j];
				}else{
					acc[i][j] = pot[j];
				}
			}
		}
		vector<vector<int>> mem(n,vector<int>(n,-1));

		cout << mix(0,n - 1,pot,acc,mem) << endl;
	}
	return 0;
}