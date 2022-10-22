#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

/*
* Problema: https://www.spoj.com/problems/GNY07H/
*
* Este é um problema q usa DP e bitmask (representar vetores de bools em ints)
* O problema pode ser dado como tiling(coluna,mask) sendo
*	- coluna, a ith coluna da grid
*	- mask, o bitmask representando quais espaços foram preenchidos pela coluna anterior
* O caso base é: 
* ith colum + 1 == m colums
* 	se mask == 0 devolve 1   (se mask é 0, então a coluna não ocupa a proxima linha q não existe)
*  	se não devolve 0
* A recursão seria da forma
*	for n formais de tile 
*		res += tiling(i+1,forma)
*
* Deus q me tirou dessa furada: https://www.youtube.com/watch?v=lPLhmuWMRag
*/

//gerar as proximas masks tb eh chatinho, mas para um n genérico de altura para a grid eh necessário
//codigo empresentado do video
void generate_masks(int curr_mask,int i,int next,vector<int> &masks){
	//se chegou ao fim da coluna, adiciona as masks o bitmask construido
	if(i == 4){
		masks.push_back(next);
		return;
	}
	//se no bitmask o bit i != 0, ele está ocupado, então calcula-se para o prox bit
	if((curr_mask & (1 << i)) != 0)
		generate_masks(curr_mask,i+1,next,masks);

	//se não se encontra no último bit, calcula-se se pode colocar um dominó na vertical
	if(i != 3){
		if((curr_mask & (1 << i)) == 0 && (curr_mask & (1 << (i+1))) == 0)
			generate_masks(curr_mask,i+2,next,masks);
	}
	//dado que o bit mask não está ocupado, ocupas-se da próxima mask.
	//Nota-se que caso tenham dois espaços vagos, a função acima é chamada,
	//então gera-se tanto o caso com 1 vertical e 2 horizontais
	if((curr_mask & (1 << i)) == 0)
		generate_masks(curr_mask,i+1,next + (1 << i),masks);
}

int dp[1001][1<<4];
int tiling(int col,int mask,const int m){
	//caso base
	if(col == m){
		if(mask == 0){
			return 1;
		}else{
			return 0;
		}
	}
	if(dp[col][mask] != -1) return dp[col][mask];
	
	int res = 0;
	vector<int> n_masks;
	generate_masks(mask,0,0,n_masks);
	for(int n_mask: n_masks){
		res += tiling(col+1,n_mask,m); 
	}
	return dp[col][mask] = res;
}

int main(){
	int t,i = 0;
	cin >> t;
	while(t--){
		int m;
		cin >> m;
		memset(dp,-1,sizeof(dp));
		cout << ++i << ' ' << tiling(0,0,m) << endl;
	}

	return 0;
}