#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
//#include <functional>
using namespace std;
typedef list<pair<string,int32_t>> pq_list;
ifstream in_file("input.txt");
ofstream out_file("output.txt");

string algo="";
string START="";
string GOAL="";
int32_t NO_OF_NODES=0;
int32_t NO_OF_EDGES=0;

map <string, list<pair<string,int32_t>>> Graph_tree;
map <string, int32_t> Node_g;
list<pair<string,int32_t>> sol;
void read_input();
void write_output();

bool has_edge(string);
void BFS();
void DFS();
void UCS();
void Astar();

int main()
{
read_input();

if(algo=="BFS")         BFS();
else if(algo=="DFS")    DFS();
else if(algo=="UCS")    UCS();
else if(algo=="A*")     Astar();

write_output();

	return 0;
}

void read_input()
{
string from="", to="";
int32_t cost_from_to=0;

string new_line="";
getline(in_file,algo);
cout<<algo<<" "<<endl;
getline(in_file,START);
cout<<START<<" "<<endl;
getline(in_file,GOAL);
cout<<GOAL<<" "<<endl;
in_file>>NO_OF_EDGES;
cout<<NO_OF_EDGES<<endl;

getline(in_file,new_line);
int32_t counter = NO_OF_EDGES;
while(counter>0)
	{
		getline(in_file,from,' ');
		getline(in_file,to,' ');
		//getline(in_file,w,'\n');
		in_file>>cost_from_to;
		getline(in_file,new_line);
		Graph_tree[from].push_back(make_pair(to,cost_from_to));
		cout<<from<<" "<<to<<" "<<cost_from_to<<endl;
		counter--;
	}
in_file>>NO_OF_NODES;
cout<<NO_OF_NODES<<endl;
counter = NO_OF_NODES;
getline(in_file,new_line);
while(counter>0)
{
    getline(in_file,from,' ');
    in_file>>cost_from_to;
    getline(in_file,new_line);
    Node_g[from] = cost_from_to;
    cout<<from<<" "<<cost_from_to<<endl;
    counter--;
}
in_file.close();

}
void write_output()
{
    sol.reverse();
for(auto i:sol)
    out_file<<i.first<<" "<<i.second<<endl;

    /*
for(auto i:Graph_tree)
    {
        out_file<<i.first<<":"<<endl;
        for(auto j:i.second)
        {
            out_file<<"\t"<<(j).first<<" "<<(j).second<<endl;
        }
    }
for(auto i:Node_g)
    out_file<<i.first<<": "<<i.second<<endl;
*/
out_file.close();
}
bool has_edge(string s)
{
    if(Graph_tree.count(s)>0) return true;
    else return false;
}

template<typename T> void print_queue1(T q) {
    while(!q.empty()) {
        cout<<(q.top()).first<<endl;
        for(auto i:(q.top()).second)
        std::cout << (i).first <<" "<<(i).second<<endl;
        q.pop();
        cout<<endl;
    }
    std::cout << "-----------\n";
}

bool Compare(pair<int32_t,pq_list> a, pair<int32_t,pq_list> b)
{

    //if(((a).front()).second>((b).front()).second) return true;
    if(a.first>b.first) return true;
    else return false;
}

template<typename T,typename T1> bool find_replace1(T& q,T1 li,int32_t li_cost)
{
priority_queue<pair<int32_t,pq_list>,vector<pair<int32_t,pq_list>>,std::function<bool(pair<int32_t,pq_list>,pair<int32_t,pq_list>)>> q1(Compare);//std::greater<pair<int32_t,pq_list>>> Q;
bool flag=false;
while(!q.empty())
    {
        pair<int32_t,pq_list> top = q.top();
        if((((top.second).front()).first==(li.front()).first))
        {
            flag = true;
            cout<<"node found\n"<<top.first<<" "<<li_cost;
            if(top.first>li_cost)
            {
                q1.push(make_pair(li_cost,li));
                cout<<"node replaced\n";
            }
            else
            {
                q1.push(top);
                cout<<"node not replaced\n";
            }
        }
        else
        {
            cout<<"this is not node\n";
            q1.push(top);
        }
        q.pop();
        print_queue1(q1);
    }
    q = q1;
    //q1.clear();
    return flag;
}
void BFS()
{
cout<<endl<<"BFS"<<endl;
queue<list<pair<string,int32_t>>> open;
vector<string> closed;
list<pair<string,int32_t>> frontier,init;
init.push_back(make_pair(START,0));
open.push(init);
while(1)
    {
        if(open.empty()) {break;}
        frontier = open.front();
        open.pop();

        if((frontier.front()).first == GOAL) {sol = frontier;break;}
        if(find(closed.begin(),closed.end(),(frontier.front()).first)!=closed.end()) {cout<<"cont\n";continue;}
        for(auto i:frontier)
        cout<<i.first<<" "<<i.second<<endl;
        cout<<(frontier.front()).first<<" "<<GOAL<<endl;;
        for(auto i:Graph_tree[(frontier.front()).first])
        {
            init = frontier;

            init.push_front(make_pair(i.first,(frontier.front()).second+1));//i.second
            open.push(init);
        }
        closed.push_back(frontier.front().first);
        cout<<endl;
    }
}
void DFS()
{
cout<<endl<<"DFS"<<endl;
list<list<pair<string,int32_t>>> open;
vector<string> closed;
list<pair<string,int32_t>> frontier,init;
init.push_back(make_pair(START,0));
open.push_back(init);
while(1)
    {
        if(open.empty()) {break;}
        frontier = open.front();
        open.pop_front();
        for(auto i:frontier)
        cout<<i.first<<" "<<i.second<<endl;
        //cout<<(frontier.front()).first<<" "<<GOAL<<endl;;

        if((frontier.front()).first == GOAL) {sol = frontier;break;}

        if(find(closed.begin(),closed.end(),(frontier.front()).first)!=closed.end()) {cout<<"cont\n";continue;}

        for(list<pair<string,int32_t>>::reverse_iterator i=Graph_tree[(frontier.front()).first].rbegin(); i!=Graph_tree[(frontier.front()).first].rend();++i)
        {
            init = frontier;
            init.push_front(make_pair((*i).first,(frontier.front()).second+1));//i.second
            open.push_front(init);
        }
        closed.push_back(frontier.front().first);
        cout<<endl;
    }
}
//typedef list<pair<string,int32_t>> pq_list;
void UCS()
{
cout<<endl<<"UCS"<<endl;
priority_queue<pair<int32_t,pq_list>,vector<pair<int32_t,pq_list>>,std::function<bool(pair<int32_t,pq_list>,pair<int32_t,pq_list>)>> open(Compare);
vector<string> closed;
pair<int32_t,list<pair<string,int32_t>>> frontier,init_f;
pq_list init;
init.push_back(make_pair(START,0));
open.push(make_pair(0,init));
while(1)
    {
        if(open.empty()) {break;}
        frontier = open.top();
        open.pop();

        if(((frontier.second).front()).first == GOAL) {sol = frontier.second;break;}
        //if(find(closed.begin(),closed.end(),(frontier.front()).first)!=closed.end()) {cout<<"cont\n";continue;}
        for(auto i:frontier.second)
        cout<<i.first<<" "<<i.second<<endl;
        cout<<((frontier.second).front()).first<<" "<<GOAL<<endl;;
        for(auto i:Graph_tree[((frontier.second).front()).first])
        {
            init = frontier.second;
            int32_t init_cost = ((frontier.second).front()).second+i.second;
            init.push_front(make_pair(i.first,init_cost));//i.second
            //open.push(make_pair(init_cost,init);

            if(!find_replace1(open,init,init_cost))
                {
                    cout<<"node not found & pushed\n";
                    open.push(make_pair(init_cost,init));
                    print_queue1(open);
                }

        }
        closed.push_back((frontier.second).front().first);
        cout<<endl;
    }
}
void Astar()
{
cout<<endl<<"A*"<<endl;
priority_queue<pair<int32_t,pq_list>,vector<pair<int32_t,pq_list>>,std::function<bool(pair<int32_t,pq_list>,pair<int32_t,pq_list>)>> open(Compare);
vector<string> closed;
pair<int32_t,list<pair<string,int32_t>>> frontier,init_f;
pq_list init;
init.push_back(make_pair(START,0));
open.push(make_pair(0,init));
while(1)
    {
        if(open.empty()) {break;}
        frontier = open.top();
        open.pop();

        if(((frontier.second).front()).first == GOAL) {sol = frontier.second;break;}
        //if(find(closed.begin(),closed.end(),(frontier.front()).first)!=closed.end()) {cout<<"cont\n";continue;}
        for(auto i:frontier.second)
        cout<<i.first<<" "<<i.second<<endl;
        cout<<((frontier.second).front()).first<<" "<<GOAL<<endl;;
        for(auto i:Graph_tree[((frontier.second).front()).first])
        {
            init = frontier.second;
            int32_t init_cost = ((frontier.second).front()).second+i.second;
            init.push_front(make_pair(i.first,init_cost));//i.second
            //open.push(make_pair(init_cost,init);
            int32_t h_cost = Node_g[((frontier.second).front()).first];
            //check if the current node h(n) is only taken
            //check if it getting updated properly in the queue by printing and solving by hand
            if(!find_replace1(open,init,init_cost+h_cost))
                {
                    cout<<"node not found & pushed\n";
                    open.push(make_pair(init_cost+h_cost,init));
                    print_queue1(open);
                }

        }
        closed.push_back((frontier.second).front().first);
        cout<<endl;
    }
}
