#include <iostream>
#include <vector>


using namespace std;

int min(int a,int b){
	return a < b ? a : b;
}

int MM(int i, int j,vector<int> &l,vector<int> &c,vector<vector<int>> &mem){
	if(i == j)
		return 0;
	if(mem.at(i).at(j) != -1)
		return mem.at(i).at(j);
	int res = 1000000; // era pra ser INT_MAX mas isso dah tb
	for(int k = i; k < j; k++){
		res = min(res, MM(i,k,l,c,mem) + MM(k+1,j,l,c,mem) + l.at(i)*c.at(k)*c.at(j));
	}
	mem.at(i).at(j) = res;
	return res;
}

int main(){
	vector<int> l{10,100,5};
	vector<int> c{100,5,50};

	vector<vector<int>> mem(l.size(),vector<int>(c.size(),-1));

	
	cout << MM(0,l.size() - 1,l,c,mem) << endl;

	return 0;
}