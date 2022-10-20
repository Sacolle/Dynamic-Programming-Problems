#include <iostream>
#include <vector>

using namespace std;

int moedaFor(int i, int D, vector<int> &valor,vector<vector<int>> &mem){
	if(D == 0)
		return 1;
	if(i == valor.size())
		return 0;
	if(mem.at(i).at(D) != -1)
		return mem.at(i).at(D);

	int res = 0;
	for(int v = 0; v*valor.at(i) <= D; v++){
		res += moedaFor(i+1,D-(v*valor.at(i)),valor,mem);
	}
	mem.at(i).at(D) = res;
	return res;
}

int moedaRec(int i, int D, vector<int> &valor,vector<vector<int>> &mem){
	if(D == 0)
		return 1;
	if(i == valor.size())
		return 0;
	if(mem.at(i).at(D) != -1)
		return mem.at(i).at(D);
	//uso de expressão ternária para deixar o código mais consiso
	//caso não usando a moeda + caso usando a moeda (não incrementa o i pois pode usar de novo)
	mem.at(i).at(D) = moedaRec(i+1,D,valor,mem) + (valor.at(i) <= D ? moedaRec(i,D-valor.at(i),valor,mem) : 0);
	return mem.at(i).at(D);
}

int main(){
	int D = 50;
	vector<int> vals{50,25,15,10};
	vector<vector<int>> mem(vals.size(),vector<int>(D+1,-1));


	cout << moedaRec(0,D,vals,mem) << endl;
	return 0;
}