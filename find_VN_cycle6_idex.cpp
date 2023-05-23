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
	//將有cycle idex 的 txt 檔
	//轉換成 每一個 VN 有產生 cycle 的 cycle idex 
	
	
	
	cout<<"Code length: "<<endl;
	int L; 
	
	cin>>L;
	
	//read txt
	 
	ifstream ifs("6 cycle idex H_96_48.txt");
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
	int cycle6,c;
	
	ifs>>cycle6>>c;
	//cout<<"number of cycle"<<endl;
	//cout<<cycle4<<' '<<cycle6<<' '<<cycle8<<endl;
	
    int i1,i2,i3;
    
    
    //calculate cycle6 
    
    vector<vector<int>> idex(cycle6,vector<int>(3,0));
    int i=0;
    while (ifs >>i1>>i2>>i3) {
        
        idex[i][0] = i1-1;
        idex[i][1] = i2-1;
        idex[i][2] = i3-1;
        i++; 	
        
    }

    ifs.close();
    //*******************************************************************
    //將每個 cycle 6 idex sorting
    
	//write into txt
	ofstream ofs1;
	ofs1.open("6 cycle idex sorting.txt");
    if (!ofs1.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    ofs1<<cycle6<<" "<<c<<"\n";
    //sorting
    for(int i=0;i<idex.size();i++){
    	sort(idex[i].begin(),idex[i].end());
    }
    sort(idex.begin(),idex.end());
    //write number of cycle bit of each VN 
    
    for(int i=0;i<idex.size();i++){
    	
    	ofs1<<idex[i][0]<<" "<<idex[i][1]<<" "<<idex[i][2]<<"\n";
	}
	
	ofs1.close();
	//******************************************************************
	
	
	//整理出 每個 VN 有相關的 bit 
	
	
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
	//write cycle 6 idex of each VN 
	for(int i=0;i<idex.size();i++){
		
		for(int j=0;j<idex[i].size();j++){
			for(int k=0;k<idex[i].size();k++){
				res[idex[i][j]].insert(idex[i][k]);
			}
			
		}
		
	}
	//Largest number of cycle bit
	int max_L = 0;
	for(int i=0;i<res.size();i++){
		if(max_L<res[i].size())
			max_L = res[i].size();
	}
	//cout<<"max_L: "<<max_L<<endl;
	
	
	/*
	//印出 cycle 6 
	for(int i=0;i<L;i++){
		if(!res[i].empty()){
			cout<<"VN: "<<i<<" size: "<<res[i].size()<<endl;
			for(auto e:res[i])
				cout<<e<<' ';
			cout<<endl;
		}
		
	}
	*/
	
	
	//write into txt
	ofstream ofs;
	ofs.open("6 cycle bit H_96_48.txt");
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    
    //write max number of cycle bit
    ofs <<max_L<< "\n";
    
    //write number of cycle bit of each VN 
    for(int i=0;i<res.size();i++){
    	ofs<<res[i].size()<<"\n";
		
	}
    //write cycle idex
    for(int i=0;i<res.size();i++){
			
	
		for(auto e:res[i]){
			ofs<<e<<" ";
		}
		
		
		ofs<<"\n";
		
	}
    /*
    vector<vector<int>> all_idex;
    
    for(int i=0;i<L;i++){
    	vector<int> temp(res[i].begin(),res[i].end());
    	all_idex.push_back(temp);
	}
    
    
    for(int i=0;i<res.size();i++){
			
	
		for(int j=0;j<max_L;j++){
			if(j<all_idex[i].size())
				ofs<<all_idex[i][j]<<" ";
			else
				ofs<<-1<<" ";
		}
		ofs<<"\n";
		
	}
    */
	
	
    ofs.close();
    

	return 0;
}
