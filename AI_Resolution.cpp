#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdio.h>
#include <cstring>

using namespace std;

ifstream in_file("C:\\Users\\Giridhar A D\\Documents\\USC\\Sem1\\CSCI 561 - AI\\hw3\\test\\input.txt");
ofstream out_file("C:\\Users\\Giridhar A D\\Documents\\USC\\Sem1\\CSCI 561 - AI\\hw3\\test\\output.txt");//,std::ofstream::out | std::ofstream::app);

int alpha_n = 0;
int kb_n =0;
vector<string> alpha;
vector<string> kb;

int var_count=0;
map<string,string> t_dict;

map<string,vector<string>> index_,index_update;=

void read_input()
{
    string new_line="";
    string sent="";
    in_file>>alpha_n; getline(in_file,new_line);
    int32_t counter = alpha_n;
    while(counter>0)
    {
        getline(in_file,sent);
        alpha.push_back(sent);
        counter--;
    }

    in_file>>kb_n; getline(in_file,new_line);
    counter = kb_n;
    while(counter>0)
    {
        getline(in_file,sent);
        kb.push_back(sent);
        counter--;
    }
}


void print_input()
{
    cout<<alpha_n<<endl;
    for(auto i:alpha)
    {
        cout<<i<<endl;
    }
    cout<<kb_n<<endl;
    for(auto i:kb)
    {
        cout<<i<<endl;
    }
}

string toString(int n)
{
    char mv[6];
    sprintf(mv, "%d",n);
    string move = mv;
    return move;
}

int checkprec(char a)
{
    if(a=='~')
        return 4;
    if(a=='&')
        return 3;
    if(a=='|')
        return 2;
    if(a=='>')
        return 1;
    if(a=='(')
        return 0;
    if(a==')')
        return 0;
    return 0;
}

string prefix(string x)
{
    stack<char> s;
    string prefixexp="";
    for(int i=x.length()-1;i>=0;i--)
    {
        if(x[i]==')')
        {
            s.push(x[i]);
        }
        if(x[i]=='#')
        {
            int j=0;
            while(x[i]!='\0')
                if (x[i+j++] == '$') break;
            string x1 = x.substr(i,j);
            reverse(x1.begin(),x1.end());
            prefixexp+=x1;
        }
        if(x[i]=='&'||x[i]=='|'||x[i]=='>'||x[i]=='~')
        {

            if(s.empty())
                s.push(x[i]);
            else
            {
                int prec1=checkprec(x[i]);
                int prec2=checkprec(s.top());
                if(prec1>prec2)
                {
                    s.push(x[i]);
                }
                else
                {
                    while(prec1<prec2 && (!(s.empty())))
                    {

                        prefixexp+=s.top();
                        s.pop();
                        if(!s.empty())
                        {prec2=checkprec(s.top());}

                    }
                    s.push(x[i]);

                }

            }
        }
        if(x[i]=='(')
        {
            while(s.top()!=')')
            {
                prefixexp+=s.top();
                s.pop();
            }
            s.pop();
        }
    //cout<<x[i]<<" "<<prefixexp<<" "<<s.size()<<" "<<s.top()<<endl;
    }
    while(!s.empty()) {
        prefixexp += s.top();
        s.pop();
    }
    reverse(prefixexp.begin(),prefixexp.end());
    return prefixexp;
}

string removeimplication(string a)
{
    stack<string> s;
    for(int i=a.length()-1;i>=0;i--)
    {
        if(a[i]=='#')
        {
            int j=0;
            while(a[i]!='\0')
                if (a[i+j++] == '$') break;
            string x1 = a.substr(i,j);

            s.push(x1);
        }
        if(a[i]=='&'||a[i]=='|')
        {
            string first=s.top(); s.pop();
            string second=s.top(); s.pop();
            string third=first+a[i]+second;
            s.push(third);
        }
        if(a[i]=='~')
        {
            string newfirst="";
            string first=s.top(); s.pop();
            first="~("+first+")";
            s.push(first);
        }
        if(a[i]=='>')
        {
            string first="~("+s.top()+")";s.pop();
            string second=s.top(); s.pop();
            string third=first+"|"+second;
            s.push(third);
        }

    }
    return s.top();
}
/*
vector<string> split(string str,string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}
*/
vector<string> split(string s, string sep)
{
    char separator = sep[0];
    vector<string> output;
    string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(separator, pos)) != string::npos)
    {
        string substring( s.substr(prev_pos, pos-prev_pos) );
        output.push_back(substring);
        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word
    return output;
}

string removenegation(string a)
{
    stack<string> s;
    for(int i=a.length()-1;i>=0;i--)
    {
        if(a[i]=='#')
        {
            int j=0;
            while(a[i]!='\0')
                if (a[i+j++] == '$') break;
            string x1 = a.substr(i,j);
            s.push(x1);
        }
        if(a[i]=='&'||a[i]=='|')
        {
            string first=s.top(); s.pop();
            string second=s.top(); s.pop();
            string third=first+a[i]+second;
            s.push(third);
        }

        if(a[i]=='~')
        {
            string newfirst="";
            string first = s.top();  s.pop();
            for (int j = 0; j < first.length(); j++)
            {
                if (j == 0 && first[j] == '#')
                {
                    newfirst += "~";
                    int j_ = 0;
                    while (first[j] != '\0')
                        if (first[j + j_++] == '$') break;
                    newfirst += first.substr(j, j_);
                }
                else if (first[j] == '|')
                {
                    newfirst += "&";
                }
                else if (first[j] == '&')
                {
                    newfirst += "|";
                }
                else if (first[j] == '#')
                {
                    if (first[j - 1] == '~')
                    {
                        int j_ = 0;
                        while (first[j] != '\0')
                            if (first[j + j_++] == '$') break;
                        newfirst += first.substr(j, j_);
                    }
                    else
                    {
                        int j_ = 0;
                        while (first[j] != '\0')
                            if (first[j + j_++] == '$') break;
                        newfirst += '~'+first.substr(j, j_);
                    }
                }
            }
            if (newfirst.find("&") != string::npos) {
                list <string> a1;
                for (string a111:split(newfirst, "&"))
                {
                    a111 = "(" + a111 + ")";
                    a1.push_back(a111);
                }
                string tempnewfirst = "";
                for (string temper:a1) {
                    tempnewfirst += temper + "&";
                }
                tempnewfirst = tempnewfirst.substr(0, tempnewfirst.length() - 1);
                tempnewfirst = "(" + tempnewfirst + ")";
                newfirst = tempnewfirst;

            }

            s.push(newfirst);
        }
    //cout<<a[i]<<" "<<s.size()<<" "<<(!s.empty()?s.top():"")<<endl;
    }
    return s.top();
}

string distributivity(string a)
{
    stack<string> s;

    for(int i=a.length()-1;i>=0;i--)
    {
        // System.out.println(s);
        if(a[i]=='#')
        {
            int j_ = 0;
            while (a[i] != '\0')
                if (a[i + j_++] == '$') break;
            s.push(a.substr(i,j_));
        }
        if(a[i]=='&')
        {
            string first=s.top(); s.pop();
            string second=s.top(); s.pop();
            string third=first+a[i]+second;
            s.push(third);
        }
        if(a[i]=='~')
        {
            string newfirst="";
            string first=s.top(); s.pop();
            newfirst="~"+first;

            s.push(newfirst);
        }
        if(a[i]=='|')
        {
            string first=s.top(); s.pop();
            string second=s.top(); s.pop();
            string third="";
            list<string> one;
            list<string> two;
            if(first.find("&") != string::npos)
            {

                for(string d:split(first,"&"))
                    one.push_back(d);
            }
            if(second.find("&")!=string::npos)
            {
                for(string d:split(second,"&"))
                    two.push_back(d);
            }

            if(one.empty() && two.empty())
            {
                third+=first+"|"+second;
            }
            if(one.empty() && !two.empty())
            {
                for(string ee:two)
                {
                    third+=first+"|"+ee;
                    third+="&";
                }
            }
            if(!one.empty() && two.empty())
            {
                for(string ee:one)
                {
                    third+=second+"|"+ee;
                    third+="&";
                }
            }
            if(!one.empty() && !two.empty())
            {
                for(string ee:one)
                {
                    for(string ee2:two)
                    {
                        third+=ee+"|"+ee2;
                        third+="&";
                    }
                }
            }
            if(third[third.length()-1]=='&')
                third=third.substr(0,third.length()-1);
            s.push(third);
        }


    }
    return s.top();
}

string clean_clause(string clause)
{
    clause.erase (std::remove (clause.begin(), clause.end(), ' '), clause.end());
    //cout<<clause<<endl;
    int i=0;
    while((i = clause.find("=")) != string::npos)    clause.replace(i,2,">");
    return clause;
}

map<string,string> map_pred(string &clause)
{
    map<string, string> Pred_map;
    int count=0;
    for (int i=0;i<clause.length(); i++)
    {
        //cout<<clause<<" "<<clause.length()<<" "<<clause[i]<<endl;
        char ch = clause[i];
        if((ch>='A') && (ch<='Z'))
        {
            int j=0;
            while(clause[i]!='\0')
                if (clause[i+j++] == ')') break;
            //cout<<clause.substr(i,j)<<endl;
            string p_map = "#"+toString(count)+"$";
            Pred_map[p_map] = clause.substr(i,j);
            clause.replace(i,j,p_map);
            count++;
        }
    }
    return Pred_map;
}

vector<string> to_cnf(string clause)
{
    clause = clean_clause(clause);
    map<string, string> Pred_map;
    Pred_map = map_pred(clause);

    cout<<"Clause:"<<clause<<endl;
    clause = prefix(clause);
    cout<<"Prefix:"<<clause<<endl;
    clause = removeimplication(clause);
    cout<<"Remove Impl:"<<clause<<endl;
    clause = prefix(clause);
    cout<<"Prefix:"<<clause<<endl;
    clause = removenegation(clause);
    cout<<"Remove neg:"<<clause<<endl;
    clause = prefix(clause);
    cout<<"Prefix:"<<clause<<endl;
    clause = distributivity(clause);
    cout<<"Distribution:"<<clause<<endl;

    string final_clause="";
    for (int i=0;i<clause.length();)
    {
        if(clause[i]=='#')
        {
            int j=0;
            while(clause[i]!='\0')
                if (clause[i+j++] == '$') break;
            final_clause+=Pred_map[clause.substr(i,j)];
            //cout<<i<<" "<<j<<endl;
            i=i+j;
        }
        else
        {
            final_clause+=clause[i];
            i++;
        }
    }

    return split(final_clause,"&");
}

int literals_(string clause)
{
    if(clause.find('(') != string::npos)
        return (split(clause,"|")).size();
    return 0;
}

string op(string clause)
{
    if((clause[0]>='a' && clause[0]<='z') || clause[0]=='#')
    {
        return clause;
        return "None";
    }
    if(literals_(clause)==1)
    {
        if(clause[0]=='~') return string(1,'~');
        int j=0;
        while(clause[j]!='\0')
            if (clause[j++] == '(') break;
        //cout<<"lit not~ "<<clause<<" "<<j<<endl;
        if(clause.find("(")==string::npos) j++;
        //cout<<clause.substr(0,j-1)<<endl;
        return clause.substr(0,j-1);
    }
    return string(1,'|');
}

vector<string> args(string clause)
{
    clause = clean_clause(clause);
    vector<string> arg;
    if((clause[0]>='a' && clause[0]<='z') || clause[0]=='#')
    {
        //cout<<"args var\n";
        return arg;
    }
    if(literals_(clause)==1)
    {
        //cout<<"args 1 lit\n";
        if(clause[0]=='~')
        {
            arg.push_back(clause.substr(1, clause.length() - 1));
            return arg;
        }
        if(clause.find('(') != string::npos)
            return split((clause.substr(clause.find('(')+1, clause.length() - (clause.find('(')+1) -1)),",");
        {
            //arg.push_back("None");
            return arg;
        }
    }
    //cout<<"args >1 lit\n";
    if(clause.find('|') == string::npos) {arg.push_back(clause); return arg;}
    reverse(clause.begin(),clause.end());
    int index_c = clause.length() - clause.find('|');
    reverse(clause.begin(),clause.end());
    arg.push_back(clause.substr(0,index_c-1));
    arg.push_back(clause.substr(index_c));
    return arg;
}

bool is_var(string s)
{
    if((s[0]>='a' && s[0]<='z') || s[0]=='#') return true;
    return false;
}

string repr(string op_, vector<string> arg)
{
    if (arg.size() == 0)
    {
        //cout<<"1"<<op_<<endl;
        return op(op_);
    }
    else if(!is_var(op_) && (op_[0]>='A' && op_[0]<='Z'))
    {
        //cout<<"2"<<endl;
        string s="";
        int i=0;
        for(i=0; i<arg.size()-1; i++) s+=(arg[i]+",");
        s+=arg[i];
        return op_+"("+s+")";
    }
    else if(arg.size() == 1)
    {
        //cout<<"3"<<endl;
        return (op_ + arg[0]);
    }
    else
    {
        //cout<<"4"<<endl;
        string s="";
        int i=0;
        for(i=0; i<arg.size()-1; i++) s+=(arg[i]+op_);
        s+=arg[i];
        return s;
        //return '(%s)' % (' ' + self.op + ' ').join(map(repr, self.args))
    }
}

string std_clause(string clause)
{
    string temp;
    if(is_var(clause))
    {
        //cout << "is var symbol " << clause << " " <<op(clause)<<endl;
        if (t_dict.count(clause)>0)
        {
            //cout<<"in dict: "<<t_dict[clause]<<endl;
            temp = t_dict[clause];
            return temp;
        }
        else
        {
            var_count += 1;
            t_dict[clause] = ("#" + toString(var_count));
            temp = t_dict[clause];
            //cout<<"not in dict: "<<t_dict[clause]<<endl;
            return temp;
        }
    }
    else if(!is_var(clause) && (literals_(clause)==0))
        return clause;
    else
    {
        //cout<<"before return"<<endl;
        vector<string> ar;
        for(auto i:args(clause))
        {
            //cout<<"args: "<<i<<endl;
            ar.push_back(std_clause(i));
        }
        return repr(op(clause),ar);
        //return Expr(sentence.op, *[standardize_apart(a, dic) for a  in   sentence.args])
    }
}

string std_clause_(string clause)
{
    vector<string> disjuncts = split(clause,"|");
    vector<string> std;
    for(auto dis:disjuncts)
    {
        string p=dis.substr(0,dis.find('('));
        p+="(";
        vector<string> ar = (dis[0]=='~'?args(dis.substr(1)):args(dis));
        for(int i=0; i<ar.size(); i++)
        {
            if(is_var(ar[i]))
            {
                if (t_dict.count(ar[i])>0)
                {
                    ar[i] = t_dict[ar[i]];
                }
                else
                {
                    var_count += 1;
                    t_dict[ar[i]] = ("#" + toString(var_count));
                    ar[i] = t_dict[ar[i]];
                }
            }
        }
        int i=0;
        for(i=0;i<ar.size()-1;i++) p+=ar[i]+",";
        p+=ar[i]+")";
        std.push_back(p);
    }
    string ans="";
    int i=0;
    for(i=0;i<std.size()-1;i++)
        ans+=std[i]+"|";
    ans+=std[i];
    return ans;
}

string subst(string clause, map<string,string> theta)
{
    if(is_var(clause))
    {
        if (theta.count(clause)>0)
            return theta[clause];
        else
        return clause;
    }
    else if(!is_var(clause) && (literals_(clause)==0))
        return clause;
    else
    {
        vector<string> ar;
        for(auto i:args(clause))
            ar.push_back(subst(i,theta));
        return repr(op(clause),ar);
    }
}
int no_pred=0;
map<string,vector<string>> index_KB(vector<string> kb)
{
    map<string,vector<string>> m;
    for(auto clause:kb)
    {
        vector<string> disjuncts = split(clause,"|");
        for(auto pred:disjuncts)
        {
            no_pred++;
            int j = pred.find('(');
            m[pred.substr(0,j)].push_back(clause);
        }
    }
    return m;
}

bool can_unify(vector<string> args1, vector<string> args2)
{
    int count=0;
    for(int i=0; i<args1.size(); i++)
    {
        if(is_var(args1[i]) && is_var(args2[i])) count++;
        else if(is_var(args1[i]) && !is_var(args2[i])) count++;
        else if(!is_var(args1[i]) && is_var(args2[i])) count++;
        else if(args1[i] == args2[i]) count++;
        //cout<<args1[i]<<" " << args2[i]<<endl;
    }
    if(count == args1.size()) return true;
    return false;
}
string resolution(stack<string> query, int infy_count)
{
    cout<<query.size()<<" "<<infy_count;
    while(!query.empty())
    {
        cout<<"\t Top:"<<query.top()<<endl;
        string lit = query.top(); query.pop();

        if(lit[0]=='~') lit = lit.substr(1);
        else lit = "~" + lit;
        string query_pred = lit.substr(0,lit.find('('));
        vector<string> query_args = (lit[0]=='~')?args(lit.substr(1)):args(lit);

        //cout<<"\n\t"<<lit<<"\n\t"<<lit_pred<<"\n\t"<<lit_args[0]<<"\n\t"<<lit_args[1]<<endl;
        if(index_update.count(query_pred)>0)
        {
            vector<string> clauses = index_update[query_pred];
            stack<string> new_query;
            for(auto clause:clauses)
            {
                if(infy_count > (2*index_update.size() +1))
                {
                    //cout<<"bcoz of count\n";
                    return "FALSE";
                }
                vector<string> disjuncts = split(clause,"|");
                string found_pred;
                int m_1=0, match=0;
                for(auto p:disjuncts) {m_1++;if(p.substr(0,p.find('(')) == query_pred) {found_pred = p; match=m_1;}}
                vector<string> found_args = (found_pred[0]=='~')?args(found_pred.substr(1)):args(found_pred);
                if(can_unify(query_args,found_args))
                {
                    map<string, string> theta;
                    for(int i=0; i<query_args.size(); i++)
                        theta[found_args[i]] = query_args[i];
                    //for(auto i:theta)
                    //    cout<<i.first<<" "<<i.second<<endl;
                    //t_dict = theta;

                    new_query=query;
                    m_1=0;
                    for(auto resolvent:disjuncts)
                    {
                        //cout<<"\t"<<subst(resolvent,theta);
                        m_1++;
                        resolvent = subst(resolvent,theta);
                        lit = subst(lit,theta);
                        string resolvent_pred = resolvent.substr(0,resolvent.find("("));
                        if(resolvent_pred!=query_pred || ((resolvent_pred==query_pred) && m_1!=match))//if(resolvent != lit)
                        {
                            cout<<"\t Pushed:"<<resolvent<<endl;
                            new_query.push(resolvent);
                        }
                    }

                    if(resolution(new_query,infy_count+1) == "TRUE")
                        return "TRUE";
                }
            }
            //return resolution(new_query,infy_count+1);

            //cout<<"bcoz not resolved\n";
            return "FALSE";
        }
        else
        {
            //cout << "bcoz not found on index\n";
            return "FALSE";
        }
    }
    return "TRUE";
}

int main()
{
    //cout<<std_clause_("~A(x,Char)|B(y,Bob)|~C(y,x)")<<endl;
    //t_dict.clear();
    read_input();
    //print_input();
    //cout<<removenegation("~&#0$#1$");

    //Main block
    vector<string> kb_;
    for(auto clause:kb)
    {
        vector<string> conjuncts = to_cnf(clause);
        for (auto i:conjuncts)
        {
            cout << i << endl;
            kb_.push_back(i);
        }
    }
    cout<<endl;

    kb=kb_; kb_.clear();
    for(auto i:kb)
    {
        t_dict.clear();
        kb_.push_back(std_clause_(i));
        //cout << i << endl;
    }
    //cout<<endl;

    t_dict.clear();
    kb=kb_; kb_.clear();
    //cout<<endl;

    for(auto i:kb)
        cout<<i<<endl;

    cout<<endl<<index_.size()<<endl;

    index_ = index_KB(kb);

    cout<<endl<<index_.size()<<endl;

    for(auto i:index_)
    {
        cout<<i.first;
        for(auto j:i.second)
            cout<<"\t"<<j<<endl;
    }
    cout<<endl;
    map<string,string> query_ans;

    for(auto query: alpha)
    {
        query = clean_clause(query);//
        string s;//
        if(query[0]=='~') s = query.substr(1);//
        else s = "~" + query;//
        cout<<query<<" "<<s<<" "<<query_ans.count(s)<<endl;//
        if(query_ans.count(s)>0)//
        {
            cout<<"in IF\n";
            if(query_ans[s]=="TRUE")
            {
                out_file<<"FALSE"<<endl;
                cout<<"FALSE"<<endl;
            }
            else if(query_ans[s]=="FALSE")
            {
                out_file<<"TRUE"<<endl;
                cout<<"TRUE"<<endl;
            }
            continue;
        }

        index_update = index_;

        stack<string> alpha_stack;
        query = clean_clause(query);

        if(query[0]=='~') query = query.substr(1);
        else query = "~" + query;

        index_update[query.substr(0,query.find('('))].push_back(query);

        alpha_stack.push(query);
        //if(query[0]=='~') alpha_stack.push(query.substr(1));
        //else alpha_stack.push("~"+query);

        //cout<<alpha_stack.top()<<endl;
        string ans = resolution(alpha_stack,0);



        out_file<<ans<<endl;
        cout<<ans<<endl;

        if(query[0]=='~') query = query.substr(1);//
        else query = "~" + query;//
        query_ans[query] = ans;//
        //for(auto i:query_ans)
        //    cout<<i.first<<" "<<i.second<<endl<<endl;
    }
    out_file<<endl;
    out_file.close();

    for(auto i:to_cnf(clean_clause("Buy(x) => ~(~Owns(x,y) | ~Rabbit(y) & ~Grocery(y))")))
        cout<<i<<endl;

    cout<<distributivity("&|#0$#1$|#2$#3$");
    /*
    string s = "~A(x,y) | B(x,Bob) | C(y,z)";
    cout<<op(s);
    for(auto i:args(s))
        cout<<"\t"<<i<<endl;
    cout<<repr(op(s),args(s));
    cout<<endl<<std_clause(s);
    t_dict.clear();
    s = "B(x,y) | C(y,z)";
    cout<<endl<<std_clause(s);

    string s = "~A(x,y) | B(x,Boobs) | C(y,z)";
    s = "~Owns(#15,#16)";//|~Hates(#17,#16)|~Date(#17,#15)";
    //t_dict["#17"] = "Mary";
    //t_dict["#15"] = "John";
    cout<<t_dict.size()<<endl;
    cout<<endl<<subst(s,t_dict);
    //cout<<endl<<std_clause(s);
    */
    //string check = "A(x)>H(x)";
    //map<string,string> chk = map_pred(check);
    cout<<no_pred;
    return 0;
}
