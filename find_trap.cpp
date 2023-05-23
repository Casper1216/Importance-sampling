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

void findsubset(vector<vector<int>>& ans,vector<int>& v,int k,vector<int>& temp,int idex){   
    //Each subset have k elements

    if(temp.size()>=k){
        ans.push_back(temp);
        return ;
    }
        
    int n = v.size();
    for(int i=idex;i<n;i++){
        temp.push_back(v[i]);
        findsubset(ans,v,k,temp,i+1);
        temp.pop_back();
    }
}
set<set<int>> find_trap(vector<vector<vector<int>>>& all){
    set<set<int>> res;
    int cyc = all.size();
    int numset = all[0].size();
    int k = all[0][0].size();

    for(int i=0;i<cyc-1;i++){
        for(int j=i+1;j<cyc;j++){
            set<int> temp;
            for(int m=0;m<numset;m++){
                
                for(int r=0;r<numset;r++){
                    bool flag = true;
                    for(int d=0;d<k;d++){
                        
                        if(all[i][m][d]!=all[j][r][d]){
                            flag = false;
                            break;
                        }
                    }
                    if(flag){
                        
                        temp.insert(i);
                        temp.insert(j);
                        
                    }

                }
            }
            if(!temp.empty())
                res.insert(temp);

        }
    }
    return res;
}













int main(){
	
	
	
	
	cout<<"Code length: "<<endl;
	int L; 
	cin>>L;
	//--------------read cycle idex----------------------
    FILE *fp1 = fopen("6 cycle idex H_96_48.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    
    int cyc,c;      //have cyc  2*c  cycles
                    // c VNs
                
    fscanf(fp1,"%d ",&cyc);
    fscanf(fp1,"%d ",&c);	// H ªº row ¼Æ¶q 

    vector<vector<int>> idex(cyc,vector<int>(c,0));
    
    for(int i=0;i<cyc;i++){
        for(int j=0;j<c;j++){
            fscanf(fp1,"%d ",&idex[i][j]);
            idex[i][j]--;
        }
	}
    fclose(fp1);
    


    
    //---------------sort cycle 2c idex-----------------
    //sort cycle 6 idex
    
    for(int i=0;i<idex.size();i++){
    	sort(idex[i].begin(),idex[i].end());
    }
    sort(idex.begin(),idex.end());
    /*
    for(int i=0;i<cyc;i++){
        for(int j=0;j<c;j++){
            fscanf(fp1,"%d ",&idex[i][j]);
            cout<<idex[i][j]<<' ';
        }
        cout<<endl;
	}
    */
   
    //---------------find k common VN-----------------------
    
    int k=2;    //

    
    //all_set[i] save idex[i] all subset which have k elements 
    vector<vector<vector<int>>> all_set;
    
    for(int i=0;i<cyc;i++){
        vector<vector<int>> subset;
        vector<int> temp;
        findsubset(subset,idex[i],k,temp,0);
        all_set.push_back(subset);
        /*
        for(int j=0;j<subset.size();j++){
           for(auto e:subset[j])
                cout<<e<<' ';
            cout<<endl;
        }
        cout<<endl;
        */
    }
    // find trapping set
    
    set<set<int>> trapset = find_trap(all_set); //return common cycle idex
    
    /*
    cout<<"number of common VN: "<<trapset.size()<<endl;
    for(auto s:trapset){
        for(auto e:s)
           cout<<e<<' ';
        cout<<endl;
    }
    */
   set<set<int>> cycle_bit; //save VN of common cycle
   for(auto s:trapset){
        set<int> temp;
        for(auto e:s){
            
            for(int i=0;i<idex[e].size();i++)
                temp.insert(idex[e][i]);
        }
        cycle_bit.insert(temp);
    }
    /*
    for(auto s:cycle_bit){
        for(auto e:s)
           cout<<e<<' ';
        cout<<endl;
    }
    */



    //-------------------write into txt-------------
	
	ofstream ofs1;
	ofs1.open("6 cycle common 2 VN.txt");
    if (!ofs1.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    ofs1<<cyc<<"\n";
    
    //write number of cycle bit of each VN 
    for(auto s:cycle_bit){
        for(auto e:s)
           ofs1<<e<<" ";
        ofs1<<"\n";
    }
    
	
	ofs1.close();
	

	return 0;
}
