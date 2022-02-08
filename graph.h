#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;



//edits to this are likely not needed
template <class T>
struct Vertex {
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree; // Part 2: number of nodes pointing in
  int top_num; // Part 2: topological sorting number
  Vertex(T l) : label(l) {top_num = 0;} //Part 1
  // You may include default constructor optionally.
};

// optional, but probably helpful
 template <class T>
 ostream& operator<<(ostream &o, Vertex<T> v)
 {
     for(int i = 0; i<v.adj_list.size(); i++)
     {
     	o<<v.adj_list[i]<<" ";
     }
     return o;
 };



// std::priority_queue may take takes three template parameters: <Type, ContainerType, Functor>
// syntax for custom compare functor
// Refer the instructions PDF last section for more information

 template<class T>
 class VertexCompare
 {
 public:
   bool operator()(Vertex<T> v1, Vertex<T> v2)
   {
   	   if(v1.top_num > v2.top_num)
   	   {
   	   	 return true;
   	   }
//     //todo - implement here
     return false;
   }
 };

template <class T>
class Graph {
private:
  //c++ stl hash table

  unordered_map<T, Vertex<T>> node_set;
  //Use other data fields if needed
public:
  Graph() {};  //No modification needed to default constructor. Can be used optionally if needed.
  ~Graph() {}; //No modification needed to destructor. Can be used optionally if needed.

  // build a graph - refer the instructions PDF for more information.
  void buildGraph(istream &input)
  {
  	  while(!input.eof())
  	  {
  	  	string line;
  	  	getline(input, line);
  	  	if(line == "")
  	  	{
  	  		break;
  	  	}
  	  	istringstream sin(line);
  	  	T label;
  	  	T value;
  	  	sin>>label;
  	  	Vertex<T>v{label};
  	  	while(sin>>value)
  	  	{
            v.adj_list.push_back(value);
  	  	}
  	  	node_set.insert(make_pair(label, v));
  	  }
  }

  // display the graph into o - refer the instructions PDF for more information.
  void displayGraph(ostream& o)
  {
     for(pair<T, Vertex<T>>element: node_set)
     {
     	o<<element.first<<":"<<element.second<<endl;
     }
     
  }

  //return the vertex at label, else throw any exception  - refer the instructions PDF for more information.
  Vertex<T> at(T label)
  {
       return node_set.at(label);
  }

  //return the graph size (number of verticies)
  int size()
  {
       return node_set.size();
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  
  bool topological_sort()
  {
      queue<Vertex<T>>q;
      int counter = 0;
      //make Empty
      while(q.size() != 0)
      {
      	q.pop();
      }

      for(pair<T, Vertex<T>>element: node_set)
      {
      	if(element.second.indegree == 0)
      	{
             q.push(element.second);
      	}
     	
      }
      while(!q.empty())
      {
      	Vertex<T>v = q.front();
      	q.pop();
      	node_set.at(v.label).top_num = ++counter;

      	for(T val: v.adj_list)
      	{
      		Vertex<T>&vert = node_set.at(val);
      		if(--vert.indegree == 0)
      		{
      			q.push(vert);
      		}
      	}

      }
      if(counter != node_set.size())
      {
      	//cout<<"Counter: "<<counter<<endl;
      	//cout<<"node Size"<<node_set.size()<<endl;
      	return false;
      }
      return true;


  }; // Part 2
  
  // find indegree
  void compute_indegree()
  {
  	  for(auto& element: node_set)
      {
      	element.second.indegree = 0;
     	
      }

      for(pair<T, Vertex<T>>element: node_set)
      {
      	for(T elem: element.second.adj_list)
      	{
      		Vertex<T>&vect = node_set.at(elem);
      		vect.indegree++;
      	}
     	
      }

  }; // Part 2


  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream& o, bool addNewline=true)
  { 
    //TODO - implement things here
    priority_queue<Vertex<T>, vector<Vertex<T>>, VertexCompare<T>>pq;
    for(pair<T, Vertex<T>>element: node_set)
    {
      	pq.push(element.second);
     	
    }

    while(!pq.empty())
    {
    	Vertex<T>v = pq.top();
    	o<<v.label<<" ";
    	pq.pop();
    }

    
    if(addNewline){o << '\n';};
  }; // Part 2*/
};

#endif
