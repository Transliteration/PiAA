#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 2147483647

using namespace std;

class WayTo{
public:
    char from,to;
    float weight;
    bool correct;
    int flow;
    WayTo(): from('\0'), to('\0'), weight(0), correct(true), flow(0){}
    WayTo(char _from, char _to, double _weight): from(_from), to(_to), weight(_weight), correct(true),flow(0){}
};

int Solution(vector<WayTo> &way, char a, int k, vector<char> &answer){
    WayTo min;
    for (int i = 0; i < way.size(); i++)
        if ((way[i].from == a) && (way[i].correct)) {min = way[i]; k = i; break;} 
           
    if (min.weight == 0.0f )
     {
        way[k].correct = false; 
        return -1;
     }

    for (int i = 0; i < way.size(); i++){
        if ((way[i].weight < min.weight) && (way[i].from == a) && (way[i].correct)) 
        {
                min = way[i]; k = i;
        }
    }
    
    if (find(answer.begin(), answer.end(), way[k].to) != answer.end()) 
    {
        way[k].correct = false; 
        return -1;
    }
    return k;
}

int main(){
    int edges;
    cin>>edges;
    char a, b;
    cin >> a; 
    cin >> b;
    vector<WayTo> way;
    char tmp,tmp2;
    
    float weight;
    for (int k=0;k<edges;k++){
        cin >> tmp >> tmp2 >> weight;
        WayTo currway(tmp, tmp2, weight);
        way.push_back(currway);
    }
    char curr = a;
    int i = 0;
    vector<char> sequence;
    
    vector<WayTo> go;
    double minway=MAX;
    int indexMin=0,maxFlow=0;
    bool breakFrom=true;
    
   while(true){
        //
        breakFrom=true;
        for(int y=0;y<way.size();y++){
            if(way[y].from==a) {
               if(way[y].correct){
               breakFrom=false;
               }
            }
        }
        
        if(breakFrom) break;
                    
        sequence.push_back(curr);
        i = Solution(way, curr, i, sequence);
        
        if (i == -1) {
                i = 0;
                curr = a;
                sequence.clear();
                go.clear();
                minway=MAX;

        }
        else {
        if(minway>=way[i].weight) {minway=way[i].weight;
        indexMin=i;
        
        }
        go.push_back(way[i]);
        curr = way[i].to;
        }
        
        if (way[i].to == b) {
        way[indexMin].correct=false;
        maxFlow+=way[indexMin].weight;
        sequence.push_back(b);
                      
        int w=0,l=0;
        
        while(l<way.size() && w<go.size()){
        if(way[l].from==go[w].from && way[l].to==go[w].to)
        {
         way[l].flow+=way[indexMin].weight; 
         w++;
         l=0;
        }
        l++;
        }      
        curr = a;
        
        go.clear();
        sequence.clear();
        minway=MAX;
        }
    }
    cout << maxFlow<<endl;
            
    for (int i = 0; i<way.size(); i++){
    cout << way[i].from<<" "<<way[i].to<<" "<<way[i].flow<<endl;
    }
   
}