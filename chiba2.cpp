#include"graph2.h"
#include<set>
#include<algorithm>
#include<iostream>
#define DEBUG false

using namespace std;
static void _chiba(graph& g,int k,set<string> &c,set<set<string>> &res);
vector<vector<string>> chiba(graph g,int k)
{
    set<string> c;
    set<set<string>> res;
    _chiba(g,k,c,res);
    vector<vector<string>> real_res;
    
    for(auto& s:res)
    {
        real_res.emplace_back(vector<string>(s.begin(),s.end()));
    }
    return real_res;
}
static void _chiba(graph& g,int k,set<string> &c,set<set<string>> &res)
{
    if(k==2)
    {
        vector<string> all_node=g.get_all_node();
        if(DEBUG)
        {
            cout<<"k==2:[";
            for(int i=0;i<all_node.size();i++)
            {
                cout<<"{"<<all_node[i]<<"}";
            }
            cout<<"]"<<endl;
        }
        for(int i=0;i<all_node.size();i++)
        {
            for(int j=i+1;j<all_node.size();j++)
            {
                if(g.is_edge(all_node[i],all_node[j]))
                {
                    set<string> c2=c;
                    c2.insert(all_node[i]);
                    c2.insert(all_node[j]);
                    res.insert(c2);
                }
            }
        }
    }
    else
    {
        vector<string> all_node=g.get_all_node();
        if(DEBUG)
        {
            cout<<"k="<<k<<"all_node"<<"[";
            for(int i=0;i<all_node.size();i++)
            {
                cout<<"{"<<all_node[i]<<"}";
            }
            cout<<"]"<<endl;
        } 
        vector<pair<int,string>> node_degree;
        for(int i=0;i<all_node.size();i++)
        {
            node_degree.push_back({g.get_out_degree(all_node[i]),all_node[i]});
        }
        sort(node_degree.begin(),node_degree.end());
        reverse(node_degree.begin(),node_degree.end());
        if(DEBUG)
        {
            cout<<"k="<<k<<"[";
            for(int i=0;i<node_degree.size();i++)
            {
                cout<<"{"<<node_degree[i].first<<","<<node_degree[i].second<<"}";
            }
            cout<<"]"<<endl;
        } 
        for(int i=0;i<node_degree.size();i++)
        {
            vector<string> all_neibor_node=g.get_all_neibor_node(node_degree[i].second);
            if(DEBUG)
            {
                cout<<"k="<<k<<"neibor"<<"[";
                for(int i=0;i<all_neibor_node.size();i++)
                {
                    cout<<"{"<<all_neibor_node[i]<<"}";
                }
                cout<<"]"<<endl;
            } 
            g.set_all_unvisiable();
            for(int j=0;j<all_neibor_node.size();j++)
            {
                g.set_visiable(all_neibor_node[j]);
            }
            set<string> c2=c;
            c2.insert(node_degree[i].second);
            _chiba(g,k-1,c2,res);


            g.set_all_unvisiable();
            for(int j=0;j<all_node.size();j++)
            {
                g.set_visiable(all_node[j]);
            }
            
            for(int j=0;j<=i;j++)
            {
                g.set_unvisiable(node_degree[j].second);
            }
        }

    }
}