#include <iostream>
#include <vector>

using namespace std;

float formiga(int v,int t, vector<vector<float>> &mem){
	if(t == 0){
		if(v == 3)return 1;
		else return 0;
	}
	if(mem.at(v).at(t) != -1) return mem.at(v).at(t);
	
	float res = 0;
	for(int i = 0; i < 4;i++){
		if(i != v){
			res += formiga(i,t-1,mem)/3; 
		}
	}
	mem.at(v).at(t) = res;
	return res;
}

int main(){
	int t,v = 3;
	vector<vector<float>> mem(v+1,vector<float>(t+1,-1));
	
	cin >> t;
	
	cout << formiga(v,t,mem) << endl;

	return 0;
}