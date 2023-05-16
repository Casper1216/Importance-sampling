#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<unordered_set>
#include<time.h>
#include <fstream>

using namespace std;

int main(){
	cout<<"code length: "<<endl;
	int L; 
	
	cin>>L;
	
	//讀取 txt
	 
	ifstream ifs("6 cycle idex.txt");
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
	int cycle4,cycle6,cycle8;
	
	ifs >>cycle4>>cycle6>>cycle8;
	cout<<"number of cycle"<<endl;
	cout<<cycle4<<' '<<cycle6<<' '<<cycle8<<endl;
	
    int i1,i2,i3;
    
    vector<vector<int>> idex(cycle6,vector<int>(3,0));
    int i=0;
    while (ifs >>i1>>i2>>i3) {
        
        idex[i][0] = i1-1;
        idex[i][1] = i2-1;
        idex[i][2] = i3-1;
        i++; 	
        
    }

    ifs.close();
	
	
	sort(idex.begin(),idex.end());
	/*
	for(int i=0;i<idex.size();i++){
		
		for(int j=0;j<idex[i].size();j++){
			cout<<idex[i][j]<<' ';
		}
		cout<<endl;
	}
	*/
	
	vector<set<int>> res(L);
	
	for(int i=0;i<idex.size();i++){
		int vn = idex[i][0];
		res[vn].insert(idex[i][0]);
		for(int j=1;j<idex[i].size();j++){
			res[vn].insert(idex[i][j]);
		}
		
	}
	/*
	for(int i=0;i<res.size();i++){
		if(!res[i].empty()){
			cout<<"VN: "<<i<<endl;
			for(auto e:res[i])
				cout<<e<<' ';
			cout<<endl;
		}
		
	}
	*/
	
	
	//寫入檔案 text
	ofstream ofs;
	ofs.open("cycle 6 bit.txt");
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    
    //寫入 cycle6 數目 
    ofs <<cycle6<< "\n";
    
    

    
    for(int i=0;i<res.size();i++){
			
		for(auto e:res[i])
			ofs<<e<<" ";
		ofs<<"\n";
		
	}
    
	
	
    ofs.close();
    

	return 0;
}
