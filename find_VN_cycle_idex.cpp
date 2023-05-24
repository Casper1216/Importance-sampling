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
	//--------------read cycle idex----------------------
    FILE *fp1 = fopen("8 cycle idex H_96_48.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    int cyc,c;      //have cyc  2*c  cycles
                    // c VNs
                
    fscanf(fp1,"%d ",&cyc);
    fscanf(fp1,"%d ",&c);	// H 的 row 數量 

    vector<vector<int>> idex(cyc,vector<int>(c,0));
    
    for(int i=0;i<cyc;i++){
        for(int j=0;j<c;j++){
            fscanf(fp1,"%d ",&idex[i][j]);
            idex[i][j]--;
        }
	}
    fclose(fp1);
    //*******************************************************************
    //將每個 cycle 6 idex sorting
    
	//write into txt
	ofstream ofs1;
	ofs1.open("8 cycle idex sorting.txt");
    if (!ofs1.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    ofs1<<cyc<<" "<<c<<"\n";
    //sorting
    for(int i=0;i<idex.size();i++){
    	sort(idex[i].begin(),idex[i].end());
    }
    sort(idex.begin(),idex.end());
    //write number of cycle bit of each VN 
    
    for(int i=0;i<cyc;i++){
    	for(int j=0;j<c;j++){
			ofs1<<idex[i][j]<<" ";
		}
    	ofs1<<"\n";
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
	//write cycle 2*c idex of each VN 
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
	ofs.open("8 cycle bit H_96_48.txt");
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
