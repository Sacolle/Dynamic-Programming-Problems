#include <iostream>
#include <vector>

using namespace std;

int mochila(int i, int n, int peso, vector<int>& volume,vector<int>& valor,vector<vector<int>> &mem){
	if(i == n){
		return 0;
	}
	if(volume[i] == -1){
		return mochila(i+1, n, peso, volume, valor, mem);
	}
	if(mem.at(i).at(peso/10) != -1){
		return mem.at(i).at(peso/10);
	}

	int r1 = -1, r2 = -1;
	
	if(volume[i] <= peso){
		r1 = valor[i]*volume[i] + mochila(i+1, n, peso-volume[i], volume, valor, mem);
	}
	if(i % 4 == 0){
		r2 = mochila(i+4, n, peso, volume, valor, mem);
	}else{
		r2 = mochila(i+1, n, peso, volume, valor, mem);
	}
	int res = r1 > r2 ? r1 : r2;
	mem.at(i).at(peso/10) = res;
	return res;
}


int main(){
	int tests;
	cin >> tests;
	while(tests--){
		int peso, n;
		cin >> peso >> n;

		vector<int> volume(n*4,-1);
		vector<int> valor(n*4,-1);
		vector<vector<int>> mem(n*4,vector<int>(peso/10 + 1,-1));

		for(int i = 0; i < n; i++){
			int vol, imp, dep;			
			cin >> vol >> imp >> dep;
			if(dep == 0){
				volume[i*4] = vol;
				valor[i*4]  = imp; 
			}else{
				int j = (dep - 1)*4 + 1;
				while(volume[j] != -1){ j++; }
				volume[j] = vol;
				valor[j] = imp;
			}
		}
		cout << mochila(0,n*4,peso,volume,valor,mem) << endl;
	}

	return 0;
}