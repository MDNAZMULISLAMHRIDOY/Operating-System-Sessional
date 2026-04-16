#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


void FCFS() {
    int n;
    cout<<"Enter number of process: ";
    cin >> n;
    vector<int> at(n), bt(n), id(n);
    vector<int> wt(n), tat(n);

    cout<<"Enter arrival time:\n";
    for(int i=0;i<n;i++){
        cin>>at[i];
        id[i]=i+1;
    }

    cout<<"Enter burst time:\n";
    for(int i=0;i<n;i++){
        cin>>bt[i];
    }

    vector<int> idx(n);
    for(int i=0;i<n;i++) idx[i]=i;

    sort(idx.begin(), idx.end(), [&](int a,int b){
        return at[a]<at[b];
    });

    int time=0;
    double totalWT=0,totalTAT=0;

    cout<<"\nGantt Chart:\n|";

    for(int i=0;i<n;i++){
        int k=idx[i];

        if(time<at[k]){
            cout<<" Idle |";
            time=at[k];
        }

        cout<<" P"<<id[k]<<" |";

        wt[k]=time-at[k];
        tat[k]=wt[k]+bt[k];

        time+=bt[k];

        totalWT+=wt[k];
        totalTAT+=tat[k];
    }

    cout<<"\n\nProcess AT BT WT TAT\n";
    for(int i=0;i<n;i++){
        cout<<"P"<<id[i]<<"   "<<at[i]<<"  "<<bt[i]<<"  "<<wt[i]<<"  "<<tat[i]<<endl;
    }

    cout<<"\nAvg WT: "<<totalWT/n;
    cout<<"\nAvg TAT: "<<totalTAT/n;
}

void SJF() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<int> at(n), bt(n), wt(n), tat(n), ct(n);
    vector<bool> completed(n,false);

    cout<<"Enter AT and BT:\n";
    for(int i=0;i<n;i++){
        cin>>at[i]>>bt[i];
    }

    int time=0, done=0;

    cout<<"\nGantt Chart:\n|";

    while(done<n){
        int idx=-1, minBT=1e9;

        for(int i=0;i<n;i++){
            if(at[i]<=time && !completed[i] && bt[i]<minBT){
                minBT=bt[i];
                idx=i;
            }
        }

        if(idx==-1){
            time++;
        } else {
            cout<<" P"<<idx+1<<" |";
            time+=bt[idx];
            ct[idx]=time;
            completed[idx]=true;
            done++;
        }
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }

    cout<<"\n\nProcess AT BT CT WT TAT\n";
    for(int i=0;i<n;i++){
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "<<wt[i]<<" "<<tat[i]<<endl;
    }
}

void RoundRobin() {
    int n,tq;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<int> at(n), bt(n), rem_bt(n), ct(n), wt(n), tat(n);
    vector<bool> visited(n,false);

    cout<<"Enter AT and BT:\n";
    for(int i=0;i<n;i++){
        cin>>at[i]>>bt[i];
        rem_bt[i]=bt[i];
    }

    cout<<"Enter Time Quantum: ";
    cin>>tq;

    queue<int> q;
    int time=0, done=0;

    for(int i=0;i<n;i++){
        if(at[i]==0){
            q.push(i);
            visited[i]=true;
        }
    }

    cout<<"\nGantt Chart:\n|";

    while(done<n){

        if(q.empty()){
            time++;
            for(int i=0;i<n;i++){
                if(at[i]<=time && !visited[i]){
                    q.push(i);
                    visited[i]=true;
                }
            }
            continue;
        }

        int i=q.front();
        q.pop();

        cout<<" P"<<i+1<<" |";

        if(rem_bt[i]>tq){
            time+=tq;
            rem_bt[i]-=tq;
        } else {
            time+=rem_bt[i];
            rem_bt[i]=0;
            ct[i]=time;
            done++;
        }

        for(int j=0;j<n;j++){
            if(at[j]<=time && !visited[j]){
                q.push(j);
                visited[j]=true;
            }
        }

        if(rem_bt[i]>0){
            q.push(i);
        }
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }

    cout<<"\n\nProcess AT BT CT WT TAT\n";
    for(int i=0;i<n;i++){
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "<<wt[i]<<" "<<tat[i]<<endl;
    }
}

int main() {

    cout<<"Choose Algorithm\n";
    cout<<"1. FCFS\n";
    cout<<"2. SJF\n";
    cout<<"3. Round Robin\n";

    int choice;
    cin>>choice;

    if(choice==1){
        FCFS();
    }
    else if(choice==2){
        SJF();
    }
    else if(choice==3){
        RoundRobin();
    }
    else{
        cout<<"Invalid Choice!";
    }

    return 0;
}
