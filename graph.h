#include<vector>
#include<string>
#include<unordered_map>
#include<set>
#include<algorithm>
using namespace std;
class graph;
class graph_node
{
    public:
    string node_name;
    set<graph_node*> pointing_list;
    set<graph_node*> pointed_list;
    graph* g;
    int Degree()
    {
        
    }
    graph_node(graph* g)
    {
        this->g=g;
    }
};
class graph
{
    public:
    unordered_map<string,graph_node> node_book;
    bool direct;
    //默认为无向图。
    void init_graph(vector<string> node_name_list,bool direct=false)
    {
        for(auto name:node_name_list)
        {
            node_book[name]=graph_node(this);

        }
        this->direct=direct;
    }
    void set_edge(string from_node,string to_node)
    {
        auto from=get_node_pointer_by_name(from_node);
        auto to=get_node_pointer_by_name(to_node);
        if(from!=nullptr&&to!=nullptr)
        {
            from->pointing_list.insert(to);
            to->pointed_list.insert(from);
            if(!direct)
            {
                to->pointing_list.insert(from);
                from->pointed_list.insert(to);
            }
        }
    }
    graph_node* get_node_pointer_by_name(string node_name)
    {
        if(node_book.find(node_name)!=node_book.end())
        {
            return &node_book[node_name];
        }
        else return nullptr;
    }
    vector<graph_node*> get_all_node()
    {
        vector<graph_node*> res;
        for(auto& p:node_book)
        {
            res.push_back(&node_book[p.first]);
        }
        return res;
    }
    graph delete_node(string node_name)
    {
        auto node_p=get_node_pointer_by_name(node_name);
        for(auto neibor:node_p->pointing_list)
        {
            neibor->pointed_list.erase(node_p);
        }
        for(auto neibor:node_p->pointed_list)
        {
            neibor->pointing_list.erase(node_p);
        }
        node_book.erase(node_name);

    }
    // 返回的子图是函数内new出来的，请注意delete。
    graph* create_subgraph(vector<string> node_name_list)
    {
        auto _new_g=new graph();
        auto& new_g=*_new_g;
        new_g.init_graph(node_name_list);
        for(const auto& node_name:node_name_list)
        {
            //获取原图的某个节点的邻居节点，如果邻居节点是子图的节点之一，就在子图上作一条边。
            // 获取原图的节点。
            auto origin_node_p=get_node_pointer_by_name(node_name);
            auto sub_node_p=new_g.get_node_pointer_by_name(node_name);
            // 遍历node_p的所有邻居节点
            for(const auto& origin_neibor:origin_node_p->pointing_list)
            {
                auto name=origin_neibor->node_name;
                if(new_g.node_book.find(name)!=new_g.node_book.end())
                {
                    sub_node_p->pointing_list.insert(&(new_g.node_book[name]));
                }
            }
            for(const auto& origin_neibor:origin_node_p->pointed_list)
            {
                auto name=origin_neibor->node_name;
                if(new_g.node_book.find(name)!=new_g.node_book.end())
                {
                    sub_node_p->pointed_list.insert(&(new_g.node_book[name]));
                }
            }
        }
        return _new_g;
    }
};