#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdint.h>

#define u64 unsigned long long int
#define MAX 0xffffffffffffffffLL

using namespace std;

/*
* problema: https://www.spoj.com/problems/LISA/
*/

int min(u64 a,u64 b){
	return a < b ? a : b;
}

int max(u64 a,u64 b){
	return a > b ? a : b;
}

u64 maximize(int i, int j,string &exp,vector<vector<u64>> &mem){
	if(i == j)
		return exp.at(i) - '0';
	if(mem.at(i).at(j) != MAX)
		return mem.at(i).at(j);
	u64 res = 0;
	for(int k = i; k < j; k+=2){
		if(exp.at(k+1) == '+'){
			res = max(res, maximize(i,k,exp,mem) + maximize(k+2,j,exp,mem));
		}else if(exp.at(k+1) == '*'){
			res = max(res, maximize(i,k,exp,mem) * maximize(k+2,j,exp,mem));
		}else{
			cout << "character inválido, índice: " << k+1 << " é " << exp.at(k+1) << endl;
			exit(1);
		}
	}
	mem.at(i).at(j) = res;
	return res;
}

u64 minimize(int i, int j,string &exp,vector<vector<u64>> &mem){
	if(i == j)
		return exp.at(i) - '0';
	if(mem.at(i).at(j) != MAX)
		return mem.at(i).at(j);
	u64 res = MAX;
	for(int k = i; k < j; k+=2){
		if(exp.at(k+1) == '+'){
			res = min(res, minimize(i,k,exp,mem) + minimize(k+2,j,exp,mem));
		}else if(exp.at(k+1) == '*'){
			res = min(res, minimize(i,k,exp,mem) * minimize(k+2,j,exp,mem));
		}else{
			cout << "character inválido, índice: " << k+1 << " é " << exp.at(k+1) << endl;
			exit(1);
		}
	}
	mem.at(i).at(j) = res;
	return res;
}

int main(){
	int tests;
	cin >> tests;
	while(tests--){
		string inp;
		cin >> inp;
		vector<vector<u64>> memmax(inp.size(),vector<u64>(inp.size(),MAX));
		vector<vector<u64>> memmin(inp.size(),vector<u64>(inp.size(),MAX));
		cout << maximize(0,inp.size() - 1,inp,memmax);
		cout << ' ' << minimize(0,inp.size() - 1,inp,memmin) << endl;
	}
	return 0;
}