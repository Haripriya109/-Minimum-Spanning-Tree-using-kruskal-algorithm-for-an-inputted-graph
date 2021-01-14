#include <iostream>
#include<vector>
#include<list>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;

const int inf=999;

//This function returns the total number of nodes in the graph.
int getTotalNodes()
{
    //Load the file to get the number of nodes.
    ifstream fin;
    fin.open("graphData.txt");
    string line;
    getline(fin,line);
    stringstream len (line);
    int num_of_nodes=0;
    //num_of_nodes has the total number of nodes in the graph
    len >> num_of_nodes;
    fin.close();
    return num_of_nodes;
}
//The total number of nodes is stored in const variable len
const int len= getTotalNodes();

int getIndex(vector<int> myVector, int val) {
    for (int i = 0; i < myVector.size(); i++) {
        if (myVector[i] == val) {
            return i;
        }
    }
    return -1;
}
//Class to implement the graph
class Graph
{
public:
    Graph();
    void getGraphValues (string line);
    void print_graph();
    void read_file();
    void addInf();
    vector<int> reachable_nodes(int node);
    //int adj_matrix[20][20];
    vector<vector<int>>adj_matrix;
};

Graph::Graph()
{
    for (int i=0; i<len; i++)
    {
        vector<int> mat;
        for(int j=0; j<len; j++)
        {
            if(i==j)
            {
                mat.push_back(inf);
            }
            else
            {
                mat.push_back(0);
            }

        }
        adj_matrix.push_back(mat);
    }
}

void Graph::getGraphValues (string line)
{
    int arr [3];
    string T;
    int j=0;
    stringstream X(line);
    while(getline(X,T,' ') && j!=3)
    {
        stringstream t(T);
        int val=0;
        t>>val;
        arr[j]=val;
        j++;
    }
    adj_matrix[arr[0]][arr[1]]=arr[2];

}

void Graph::read_file()
{
    //cout<<"file_read"<<endl;
    ifstream fin;
    fin.open("graphData.txt");
    string line,T;
    getline(fin, line);
    while (fin)
    {
        getline(fin, line);
        getGraphValues(line);
    }
    fin.close();
}

void Graph::addInf()
{
        for(int i=0; i<len;i++)
        {
            for(int j=0;j<len;j++)
            {
                if(adj_matrix[i][j]==0)
                    adj_matrix[i][j]=inf;
            }
        }
}

void Graph:: print_graph()
{
    cout<< "The inputted graph is----------------------------------------------------------------------------\n"<<endl;
    for(int z=0; z<len; z++)
                  cout<<"   "<< z;
    cout<<"\n";

    for(int z=0; z<len; z++)
    {
        cout<<z;
        for (int y=0; y<len; y++)
        {
            cout<< "   "<<adj_matrix[z][y];
        }
        cout<<"\n";
    }
    cout << "\n-----------------------------------------------------------------------------------------------\n" <<endl;
}

vector<int> Graph:: reachable_nodes(int node)
{
    vector<int>reachable;
    for(int i=0; i<len;i++)
    {
        if(adj_matrix[node][i]!=inf)
        {
            reachable.push_back(i);
        }
    }
    return reachable;
}

class MinSpanTree
{
public:
    void get_MinSpanTree();
    int cost;

};

bool isExists (vector<vector<int>> myVector, int key)
{
    for (auto i:myVector){for(auto j: i)  {if(j==key) { return true;} } }
    return false;
}


void MinSpanTree:: get_MinSpanTree()
{
    cost=0;
    const int length=len;
    vector <vector <int>> spanning_tree(length, vector<int>(length));

    Graph g;
    g.read_file();
    g.addInf();
    g.print_graph();

    vector<int> reachable_node_weight, reachable_node,node_list;
    int node=0,trial=1;

    cout<<"\n----------------------------------------------------------------"<<endl;
    cout << "The Minimum Spanning Tree Found is:"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;

    while(trial!=len)
    {
        for(auto i:g.reachable_nodes(node))
        {
            if (!isExists(spanning_tree, i))
            {
                reachable_node.push_back(i);
                reachable_node_weight.push_back(g.adj_matrix[node][i]);
                node_list.push_back(node);
            }
        }
        auto minima=*min_element(reachable_node_weight.begin(),reachable_node_weight.end());
        cost+=minima;
        int x=getIndex(reachable_node_weight,minima);
        int y=reachable_node[x];
        cout<<"("<<node_list[x]<<"->"<<y<< " Weight: "<<minima<<"),"<<endl;
        spanning_tree[node_list[x]][y]=y;
        spanning_tree[y][node_list[x]]=node_list[x];

        node=reachable_node[x];
        for (auto i: reachable_node) {
            if (isExists(spanning_tree,i)) {
                int j = getIndex (reachable_node, i);
                reachable_node.erase(reachable_node.begin()+j);
                reachable_node_weight.erase(reachable_node_weight.begin()+j);
                node_list.erase(node_list.begin()+j);
            }
        }
        trial++;
    }
    cout << "end" << endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"\nThe cost found for the tree is : "<<cost<<endl;
}




int main()
{
    MinSpanTree myTree;
    myTree.get_MinSpanTree();
}
