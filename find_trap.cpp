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
                    
                    if(all[i][m]==all[j][r]){
                        temp.insert(i);
                        temp.insert(j);
                    }
                    
                    /*
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
                    */

                }
            }
            if(!temp.empty())
                res.insert(temp);

        }
    }
    return res;
}





int main(){
	//--------------Start Record the time----------------
    time_t  start = clock();

	//--------------get code length----------------------
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
    //sort cycle idex
    
    for(int i=0;i<idex.size();i++){
    	sort(idex[i].begin(),idex[i].end());
    }
    sort(idex.begin(),idex.end());
    
   
    //---------------find k common VN-----------------------
    
    int k;    //
    cout<<"Enter common VNs: "<<endl;
    cin>>k;
    //all_set[i] save idex[i] all subset which have k elements 
    vector<vector<vector<int>>> all_set;
    
    for(int i=0;i<cyc;i++){
        vector<vector<int>> subset;
        vector<int> temp;
        findsubset(subset,idex[i],k,temp,0);
        all_set.push_back(subset);
        
    }
    // find trapping set
    
    set<set<int>> trapset = find_trap(all_set); //return common cycle idex
    
    
    cout<<"number of common cycle idex: "<<trapset.size()<<endl;
    
   
   vector<set<int>> cycle_bit; //save all VN of common cycle
   set<set<int>> cycle_bit_no_repeat; //save VN of common cycle
   for(auto s:trapset){
        set<int> temp;
        set<int> temp2;
        for(auto e:s){
            
            for(int i=0;i<idex[e].size();i++){
                temp.insert(idex[e][i]);
                temp2.insert(idex[e][i]);
            }
                
        }
        cycle_bit.push_back(temp);
        cycle_bit_no_repeat.insert(temp2);
    }
    sort(cycle_bit.begin(),cycle_bit.end());
    cout<<"number of common VN: "<<cycle_bit_no_repeat.size()<<endl;
    
    
    //for(auto s:cycle_bit){
    //    for(auto e:s)
    //       cout<<e<<' ';
    //    cout<<endl;
    //}

   //-------------write into txt no repeat----------------------
    
	ofstream ofs1;
	ofs1.open("8 cycle common 2 VN.txt");
    if (!ofs1.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    ofs1<<cycle_bit_no_repeat.size()<<"\n";
    
    //write number of cycle bit of each VN 
    for(auto s:cycle_bit){
        for(auto e:s)
           ofs1<<e<<" ";
        ofs1<<"\n";
    }
    
	
	ofs1.close();
    

    //-------------------find repeat cycle idex VN-----------------
    set<set<int>> harm;
    vector<int> numcycle;    //number of cycle in harmful trapping set 
    int count=1;
    int max_num = 0;
    int max_idex = 0;
   for(int i=1;i<cycle_bit.size();i++){

        if(cycle_bit[i-1]==cycle_bit[i]){
            count++;
            harm.insert(cycle_bit[i]);
            if(count>max_num){
                max_num = count;
                max_idex= i;
            }

        }
        else{
            if(count>1)
                numcycle.push_back(count);
            count=1;
        }
            

    }
    cout<<"the most number of cycle: "<<max_num<<endl;
    cout<<"the most cycle: "<<endl;
    for(auto e:cycle_bit[max_idex])
        cout<<e<<" ";
    cout<<endl;
    //cout<<"Each harmful trapping set contain number of cycle: "<<numcycle.size()<<endl;
    
    
    
        
    //for(auto e:numcycle)
    //    cout<<e<<endl;
    cout<<"number of harmful trapping set: "<<harm.size()<<endl;
    //-------------------write VN within many cycles---------------
	
	ofstream ofs2;
	ofs2.open("8 cycle common 2 VN within many cycles.txt");
    if (!ofs2.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
    ofs2<<harm.size()<<"\n";
    
    //----------write the number of harmful cycle of VN-----------------
    for(auto s:harm){
        for(auto e:s)
           ofs2<<e<<" ";
        ofs2<<"\n";
    }
	ofs2.close();


    //----------------Record the end time------------------------
    time_t end = clock();
	double diff = end - start; // ms
    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second";

	return 0;
}
