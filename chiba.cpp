#include"graph.h"
class chiba
{
    vector<vector<string>> res;
    //此函数会修改图g，请注意传入图的副本。
    void listing(int l,graph* g)
    {
        if(l==2)
        {
            for(auto& node:g->get_all_node())
            {
                for(auto& neibor:node->pointing_list)
                {
                    for(auto& c:res)
                    {
                        c.push_back(node->node_name);
                        c.push_back(neibor->node_name);
                    }
                    node->pointed_list->erase(ff)
                }

            }
        }
    }
};