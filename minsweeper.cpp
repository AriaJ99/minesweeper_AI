#include<bits/stdc++.h>
#include<conio.h>
void make_game(int a[][50],int n);
void show_board(int a[][50],int n,int time,int bomb);
void lose(int x,int y,int a[][50],int n);
void zero(int x,int y,int a[][50],int n);
bool win(int a[][50],int n);
void add_knowledge(int x,int y,int cnt);
bool AI_aid(int a[][50],int n);
void process_knowledge();
void sentence_prone();
void evaluate_vars();
void subset_reduction();
bool subset_check( std::set<std::pair<int,int>> s1,std::set<std::pair<int,int>> s2);
void bomb_expand(int a[][50],int n);
void add_again(int a[][50],int n);
int bomb;
using namespace std;
vector<vector<int>> know;//0 unknown 1 non bomb 2 bomb
map<set<pair<int,int>>,int> log_sent;
int main(){
    int n,m,x,y,ai_cnt=0;
cout<<"choose your game mode:"<<endl<<"1-easy"<<endl<<"2-medium"<<endl<<"3-hard"<<endl<<"4-custom"<<endl;
cin>>n;

int a[50][50]={0},time;
time=clock();
system("cls");

    if(n==1)n=9;
    if(n==2)n=16;
    if(n==3)n=30;

make_game(a,n);
know=vector<vector<int>> (n,vector<int>(n,0));
//cout<<"f";
while(1){
        system("cls");
show_board(a,n,time,bomb);
cout<<"1-show the x-y"<<endl<<"2-flag the x-y"<<endl<<"3-get a help from AI (AI aids so far : "<<ai_cnt<<')'<<endl<<"press zero if you choose wrong"<<endl;
cin>>m;
system("cls");
if(m==3){
    bool help=AI_aid(a,n);
    ai_cnt+=help;
    if(win(a,n)){cout<<"you won"<<endl<<"your time is : "<<(clock()-time)/1000<<endl<<"AI aids : "<<ai_cnt;break;}
    continue;
    }
show_board(a,n,time,bomb);
cout<<"enter the x:"<<endl;
cin>>y;
if(y==0)continue;
system("cls");
show_board(a,n,time,bomb);
cout<<"enter the y:"<<endl;
cin>>x;
if(x==0)continue;
x=n-x+1;
if(m==2){
    if(a[x-1][y-1]<20)a[x-1][y-1]+=20;
else a[x-1][y-1]-=20;
if(a[x-1][y-1]==9)bomb--;
if(a[x-1][y-1]==29)bomb++;
}
if(x>n || y>n)continue;
if(m==1){
    int cnt=0;
    if(a[x-1][y-1]==9 || a[x-1][y-1]==29){system("cls");cout<<"GAME OVER"<<endl;lose(x-1,y-1,a,n);return 0;}
    else if(a[x-1][y-1]<10)cnt=a[x-1][y-1],a[x-1][y-1]+=10,add_knowledge(x-1,y-1,cnt);
    else if(a[x-1][y-1]>=20)a[x-1][y-1]-=10,cnt=a[x-1][y-1]-10,add_knowledge(x-1,y-1,cnt);
    if(a[x-1][y-1]==10){
            know[x-1][y-1]=1;
            zero(x-1,y-1,a,n);

    }
    //add_knowledge(x-1,y-1,cnt);

}
//cout<<"f";
if(win(a,n)){cout<<"you won"<<endl<<"your time is : "<<(clock()-time)/1000;break;}
}
return 0;
}
void make_game(int a[][50],int n){
int x,y;
if(n==9)bomb=10;
if(n==16)bomb=40;
if(n==30)bomb=99;
srand(time(NULL));

if(n==4){
    cout<<"please enter the n : ";
    cin>>n;
    system("cls");
    FILE * ptr;
    ptr=fopen("mine.txt","r");
    if(ptr==NULL)cout<<"error in opening file\n";
    bomb=0;
    char c[100];
    for(int i=0;i<n;i++){
            fscanf(ptr,"%s\n",c);
        for(int j=0;j<n;j++){


            if(c[j]=='*'){
                a[i][j]=9;
                bomb++;
            }
            else a[i][j]=0;
        }
    }
    for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(a[i][j]==9)for(int ii=i-1;ii<i+2;ii++)
for(int jj=j-1;jj<j+2;jj++)if(a[ii][jj]!=9)a[ii][jj]++;

        }
    }
    fclose(ptr);


}
else {
for(int i=0;i<bomb;i++){
    x=rand()%n;
    y=rand()%n;
    if(a[x][y]!=9)a[x][y]=9;
   else i--;
}
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(a[i][j]==9)for(int ii=i-1;ii<i+2;ii++)
for(int jj=j-1;jj<j+2;jj++)if(a[ii][jj]!=9)a[ii][jj]++;

        }
    }
}

}
void show_board(int a[][50],int n,int time,int bomb){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j]<10)cout<<"#"<<" ";
            if(a[i][j]>=10 && a[i][j]<=18)cout<<a[i][j]-10<<" ";
            if(a[i][j]>=20)cout<<"@"<<" ";
        }

        cout<<endl;
    }
    cout<<"time : "<<(clock()-time)/1000<<endl<<"bomb : "<<bomb<<endl<<"press zero if you choose wrong"<<endl;

}
void lose(int x,int y,int a[][50],int n){
for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
                if(i==x && j==y){cout<<"& ";continue;}
                if(a[i][j]==29 || a[i][j]==9)cout<<"* ";
                else{
            if(a[i][j]<8)cout<<a[i][j]<<" ";
            if(a[i][j]>=10 && a[i][j]<=18)cout<<a[i][j]-10<<" ";
            if(a[i][j]>=20)cout<<a[i][j]-20<<" ";
        }
        }
        cout<<endl;
}
}
bool win(int a[][50],int n){
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(a[i][j]<10 || (a[i][j]>20 && a[i][j]!=29))return 0;
    }

}
  return 1;
}
void zero(int x,int y,int a[][50],int n){

//cout<<x<<" "<<y<<endl;
for(int i=x-1;i<=x+1;i++){if(i<0 || i>=n)continue;
for(int j=y-1;j<=y+1;j++){if(j<0 || j>=n ||(x==i && y==j))continue;
       if(a[i][j]==0 ){a[i][j]+=10;
       know[i][j]=1;
       zero(i,j,a,n);}
        if(a[i][j]<9 )a[i][j]+=10,add_knowledge(i,j,a[i][j]-10);
if(a[i][j]>=20 && a[i][j]!=29)a[i][j]-=10,add_knowledge(i,j,a[i][j]-10);

}}

}
void add_knowledge(int x,int y,int cnt){
    int n=know.size();
    know[x][y]=1;//set as non bomb
    set<pair<int,int>> temp;
    for(int i=x-1;i<=x+1;i++)
        for(int j=y-1;j<=y+1;j++)
            if(!(x==i && y==j) && i<n && j<n && i>=0 && j>=0){
            if(know[i][j]==0)
            temp.insert({i,j});
            if(know[i][j]==2)
                cnt--;
            }
    //cerr<<"er\n";
    log_sent[temp]=cnt;
}
bool AI_aid(int a[][50],int n){

 //bomb_expand(a,n);
 process_knowledge();
 //bomb_expand(a,n);
    add_again(a,n);
 process_knowledge();
 for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        if(a[i][j]<10 ){
        if(know[i][j]>0){
            if(know[i][j]==1){
                a[i][j]+=10;
                if(a[i][j]==10)
                    zero(i,j,a,n);
                }
            else
                a[i][j]+=20;
            return 1;
        }}
        else if(a[i][j]>=20){
            if(know[i][j]==1){
                a[i][j]-=10;
                if(a[i][j]==10)
                    zero(i,j,a,n);
                return 1;}
        }
    system("cls");
    cout<<"AI couldn't help\npress any key to continue";
    getchar();
    getchar();
    return 0;
};
void process_knowledge(){
    sentence_prone();
    evaluate_vars();
    sentence_prone();
    //eliminate zero counts
    vector<set<pair<int,int>>> del;
    for(map<set<pair<int,int>>,int>::iterator it=log_sent.begin();it!=log_sent.end();++it)
        if(it->second==0){
            for(set<pair<int,int>>::iterator it1=(it->first).begin();it1!=(it->first).end();++it1)
                know[it1->first][it1->second]=1;
            del.push_back(it->first);
        }
    for(int i=0;i<del.size();i++)
        log_sent.erase(del[i]);
    //bomb_expand();
    sentence_prone();
    evaluate_vars();
    //bomb_expand();
}
void sentence_prone(){
    for(int t=0;t<20;t++){
            vector<set<pair<int,int>>> del;
            vector<pair<set<pair<int,int>>,int>> add;
    for(map<set<pair<int,int>>,int>::iterator it=log_sent.begin();it!=log_sent.end();++it){
        //eliminate valued variablaes
        set<pair<int,int>> temp;
        bool dif=0;
        int cnt=it->second;
        for(set<pair<int,int>>::iterator itt=it->first.begin();itt!=it->first.end();++itt){
            if(know[itt->first][itt->second]>0){
                dif=1;
                if(know[itt->first][itt->second]==2)
                    cnt--;
                continue;}
            temp.insert(pair<int,int>(itt->first,itt->second));

        }
        if(dif)
            del.push_back(it->first),
            add.push_back(pair<set<pair<int,int>>,int>(temp,cnt));
    }
    for(int i=0;i<del.size();i++)
        log_sent.erase(del[i]),
        log_sent[add[i].first]=add[i].second;

    }
    subset_reduction();


}
void evaluate_vars(){
    vector<set<pair<int,int>>> del;
    for(map<set<pair<int,int>>,int>::iterator it=log_sent.begin();it!=log_sent.end();++it){
        if((it->first).size()==it->second){
            del.push_back(it->first);
            for(set<pair<int,int>>::iterator itt=(it->first).begin();itt!=(it->first).end();++itt)
                know[itt->first][itt->second]=2;
        }


    }
    for(int i=0;i<del.size();i++)
        log_sent.erase(del[i]);


}

void subset_reduction(){
    vector<set<pair<int,int>>> del;
    vector<pair<set<pair<int,int>>,int>> add;
    for(map<set<pair<int,int>>,int>::iterator it=log_sent.begin();it!=log_sent.end();++it)
    for(map<set<pair<int,int>>,int>::iterator itp=log_sent.begin();itp!=log_sent.end();++itp){
        if(it==itp)
            continue;
        bool sub=0;
        if(it->first.size()>itp->first.size())
            sub=subset_check(it->first,itp->first);
        if(!sub)
            continue;
        int cnt=it->second-itp->second;
        set<pair<int,int>> temp;
        for(set<pair<int,int>>::iterator it1=(it->first).begin();it1!=(it->first).end();++it1)
            if((itp->first).find(*it1)==(itp->first).end())
                temp.insert(*it1);
        add.push_back({temp,cnt});
        del.push_back(it->first);

    }
    for(int i=0;i<del.size();i++)
        log_sent.erase(del[i]);
    for(int i=0;i<add.size();i++)
        log_sent[add[i].first]=add[i].second;

}
bool subset_check(set<pair<int,int>> s1,set<pair<int,int>> s2){

    for(set<pair<int,int>>::iterator it=s2.begin();it!=s2.end();++it){
        if(s1.find(*it)==s1.end())
            return 0;

    }
    return 1;

}
void bomb_expand(int a[][50],int n){
    //int n=know.size();
    for(int x=0;x<n;x++)
        for(int y=0;y<n;y++)
            if(know[x][y]==1 && (a[x][y]>=10 && a[x][y]<20)){
                int cnt=0;
                for(int i=x-1;i<=x+1;i++)
                    for(int j=y-1;j<=y+1;j++)
                        if(!(x==i && y==j) && i>=0 && i<n && j>=0 && j<n && know[i][j]==2)
                            cnt++;
            if(cnt==a[x][y]-10)
                            for(int i=x-1;i<=x+1;i++)
                                for(int j=y-1;j<=y+1;j++)
                                    if(!(x==i && y==j) && i>=0 && i<n && j>=0 && j<n && know[i][j]==0)
                                        know[i][j]=1;

                        }


}
void add_again(int a[][50],int n){
for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        if(a[i][j]>10 && a[i][j]<20)
            add_knowledge(i,j,a[i][j]-10);


}


