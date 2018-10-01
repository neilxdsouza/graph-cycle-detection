#ifndef nxd_graph_h
#define nxd_graph_h

#include <set>
#include <map>
#include <string>
//#include <deque>


struct Vertex {
	std::string name;
	int data;
	bool is_visited;
	bool is_being_visited;
	bool operator< (const Vertex& rhs) const;
	bool operator== (const Vertex& rhs) const;
	Vertex (const std::string & p_name, int p_data, bool is_visited=false,
			bool is_being_visited=false);
	Vertex(const Vertex & v);
	friend std::ostream& operator<< (std::ostream & os,
			const Vertex & v);
};

struct VertexPointerComparator {
	bool operator() (const Vertex * lhs, const Vertex * rhs) const;
};

struct Graph {
	Graph() ;
	std::set<Vertex*, VertexPointerComparator> vertex_set;
	std::map<Vertex *,
			std::set<Vertex*, VertexPointerComparator> *,
			VertexPointerComparator > neighbours;

	Vertex * do_vertex_exists_check(Vertex & v);
	void add_vertex(const Vertex & v);
	void add_neighbour(Vertex & v, Vertex & n);

	void dfs(Vertex * v_ptr);
	void dfsDetectCycle();
	void print_vertices_and_their_neighbours();
	void print_vertices(std::string label);
};

#endif /* nxd_graph_h */
