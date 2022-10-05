#ifndef GRAPH2_H
#define GRAPH2_H
#include<unordered_map>
#include<vector>
#include<string>
using namespace std;
class graph
{
    public:
    vector<vector<bool>> g;
    unordered_map<string,int> _id;
    vector<bool> vb;

    graph()
    {

    }
    graph(int n)
    {
        init(n);
    }
    graph(vector<string> const& name_list)
    {
        init(name_list);
    }
    void init(int n)
    {
        g=vector<vector<bool>>(n,vector<bool>(n,false));
        vb.resize(n,true);
        for(int i=0;i<n;i++)
        {
            _id.insert({to_string(i),i});
        }

    }
    void init(vector<string> const& name)
    {
        int n=name.size();
        g=vector<vector<bool>>(n,vector<bool>(n,false));
        vb.resize(n,true);
        for(int i=0;i<n;i++)
        {
            _id.insert({name[i],i});
        }
    }
    private:
    inline int id(string name)
    {
        if(_id.find(name)!=_id.end())
        {
            return _id[name];
        }
        else return -1;
    }
    public:
    vector<string> get_all_node()
    {
        vector<string> res;
        for(auto& node:_id)
        {
            auto name=node.first;
            auto nid=id(name);
            if(nid>=0&&vb[nid])
            {
                res.push_back(name);
            }
        }
        return res;
    }
    bool is_edge(string from,string to)
    {
        int from_id=id(from);
        int to_id=id(to);
        if(from_id>=0&&to_id>=0&&vb[from_id]&&vb[to_id]&&g[from_id][to_id]==true)
        {
            return true;
        }
        else return false;
        
    }
    void set_edge(string from,string to)
    {
        int from_id=id(from);
        int to_id=id(to);
        if(from_id>=0&&to_id>=0&&vb[from_id]&&vb[to_id])
        {
            g[from_id][to_id]=true;
        }
    }
    void delete_edge(string from,string to)
    {
        int from_id=id(from);
        int to_id=id(to);
        if(from_id>=0&&to_id>=0&&vb[from_id]&&vb[to_id])
        {
            g[from_id][to_id]=false;
        }
    }
    int get_out_degree(string name)
    {
        int nid=id(name);
        if(nid<0&&!vb[nid]) return -1;
        int res=0;
        for(int i=0;i<g[nid].size();i++)
        {
            if((g[nid][i]==true)&&vb[i])
            {
                res++;
            }
        }
        return res;
    }
    vector<string> get_all_neibor_node(string name)
    {
        int nid=id(name);
        if(nid<0&&!vb[nid]) return vector<string>();
        vector<string> res;
        vector<string> all_node=get_all_node();
        for(int i=0;i<all_node.size();i++)
        {
            if(is_edge(name,all_node[i])||is_edge(all_node[i],name))
            {
                res.push_back(all_node[i]);
            }

        }
        return res;
    }
    void set_all_unvisiable()
    {
        for(int i=0;i<vb.size();i++)
        {
            vb[i]=false;
        }
    }
    void set_visiable(string name)
    {
        int nid=id(name);
        if(nid<0) return;
        vb[nid]=true;
    }
    void set_unvisiable(string name)
    {
        int nid=id(name);
        if(nid<0) return;
        vb[nid]=false;
    }
};
#endif