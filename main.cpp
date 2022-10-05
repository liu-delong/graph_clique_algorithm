#include"chiba2.h"
#include"graph2.h"
#include<iostream>
using namespace std;
int main()
{
    vector<string> node_name={"A","B","C","D","E","F","G","H","I","J"};
    graph g(node_name);
    g.set_edge("H","I");
    g.set_edge("I","H");

    g.set_edge("A","B");
    g.set_edge("B","A");
    g.set_edge("A","C");
    g.set_edge("C","A");
    g.set_edge("A","D");
    g.set_edge("D","A");
    g.set_edge("A","E");
    g.set_edge("E","A");

    g.set_edge("B","C");
    g.set_edge("C","B");
    g.set_edge("B","D");
    g.set_edge("D","B");
    g.set_edge("B","E");
    g.set_edge("E","B");

    g.set_edge("C","D");
    g.set_edge("D","C");

    g.set_edge("D","F");
    g.set_edge("F","D");

    g.set_edge("E","G");
    g.set_edge("G","E");

    vector<vector<string>> res=chiba(g,3);
    cout<<"{"<<endl;
    for(int i=0;i<res.size();i++)
    {
        cout<<"  {";
        for(int j=0;j<res[i].size();j++)
        {
            if(j!=res[i].size()-1)
            {
                cout<<res[i][j]<<",";
            }
            else
            {
                cout<<res[i][j]<<"}"<<endl;
            }
        }
    }
    cout<<"}"<<endl;


}