#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<utility>
#include<map>

using namespace std;

void dfs_l(const int i,long int leftmost,long int rightmost, priority_queue<long int,vector<long int>> & q, const int & size,const vector<pair<vector<long int>,vector<long int>>> & I,vector<bool> & indicator){
    indicator[i]=true;  int flag=1;
    //cout<<"function check: "<<leftmost<<" "<<rightmost<<'\n';
    for(int k=0;k<size;k++){
        if(!indicator[k]){
            if(I[k].first[1]==leftmost){
                flag=0;
                dfs_l(k,I[k].first[0],rightmost,q,size,I,indicator);
            }
            if(I[k].second[1]==leftmost){
                flag=0;
                dfs_l(k,I[k].second[0],rightmost,q,size,I,indicator);
            }
            if(I[k].first[0]==rightmost){
                flag=0;
                dfs_l(k,leftmost,I[k].first[1],q,size,I,indicator);
            }
            if(I[k].second[0]==rightmost){
                flag=0;
                dfs_l(k,leftmost,I[k].first[1],q,size,I,indicator);
            }
        }
    }
    if(flag){
        int tmp=rightmost-leftmost;
        if(tmp>q.top()) {
            q.pop();
            q.push(tmp);
        }
    }
}

long int FindInterval(const int & size,const vector<pair<vector<long int>,vector<long int>>> & I){
    priority_queue<long int,vector<long int>> q;
    q.push((I[0].first)[1]-(I[0].first)[0]);
    for(int i=0;i<size;i++){
        //cout<<"loop "<<i<<" first half\n";
        vector<bool> ind(size,false);
        dfs_l(i,(I[i].first)[0],(I[i].first)[1],q,size,I,ind);
        //cout<<"loop "<<i<<" second half\n";
        vector<bool> ind2(size,false);
        dfs_l(i,(I[i].second)[0],(I[i].second)[1],q,size,I,ind2);
    }
    /*
    while(!q.empty()){
        cout<<q.top()<<'\n';
        q.pop();
    }*/
    return q.top();
}

int main(){
    ifstream data("timber_validation_input.txt");
    int cases,i=1;
    data>>cases;
    ofstream output("timber_validation_output2.txt");
    int max_length;
    while(i<=cases){
        output<<"Case #"<<i<<": ";
        int size;   data>>size;
        //cout<<i<<" eme cases\n";
        vector<pair<vector<long int>,vector<long int>>> Intervals(size);
        for(int i=0;i<size;i++){
            int t1; data>>t1;
            int t2; data>>t2;
            //cout<<"data check "<<t1<<" "<<t2<<'\n';
            vector<long int> i1={t1-t2,t1};  vector<long int> i2={t1,t1+t2};
            Intervals[i]=make_pair(i1,i2);
        }
        max_length=FindInterval(size,Intervals);
        output<<max_length<<'\n';
        i++;
    }
    data.close();
    output.close();
    return 0;
}
