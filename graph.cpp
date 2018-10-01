#include "graph.h"

#include <iostream>

using std::map;
using std::set;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
// using std::deque;

bool Vertex::operator< (const Vertex& rhs) const {
	return name < rhs.name;
}

bool Vertex::operator== (const Vertex& rhs) const {
	return name == rhs.name;
}

Vertex::Vertex (const string & p_name, int p_data, bool is_visited,
		bool is_being_visited)
	: name(p_name), data(p_data), is_visited(false), is_being_visited(false)
{ }

Vertex::Vertex(const Vertex & v)
	: name(v.name), data(v.data), is_visited(v.is_visited),
	  is_being_visited(v.is_being_visited)
{ }

std::ostream & operator<< (std::ostream & os, const Vertex & v)
{
	os << " Vertex:[ name:" << v.name
		<< ", data: " << v.data << "]";
	return os;
}


bool VertexPointerComparator::operator() (const Vertex * lhs, const Vertex * rhs)
	const
{
	// cout << "Pointer comparison used" << endl;
	return lhs->name < rhs->name;
}

Vertex * Graph::do_vertex_exists_check(Vertex & v)
{
	auto it = vertex_set.find(&v);
	if ( it == vertex_set.end() ) {
		cerr << "did not find vertex: " << v 
			<< " exiting instead of throwing exception"
			<< endl;
		exit(1);
	}
	return *it;
}

Graph::Graph() : vertex_set(), neighbours()
{ }

void Graph::add_vertex(const Vertex & v)
{
	cout << "ENTER " << __PRETTY_FUNCTION__ << " v: " << v << endl;
	print_vertices(string("before"));
	cout << "before vertex_set.size(): " << vertex_set.size() << endl;
	vertex_set.insert(new Vertex(v));
	cout << "after vertex_set.size(): " << vertex_set.size() << endl;
	print_vertices(string("after"));
	cout << "EXIT " << __PRETTY_FUNCTION__ << " v: " << v << endl;
}

void Graph::add_neighbour(Vertex & v, Vertex & n)
{
	Vertex * v_ptr = do_vertex_exists_check(v);
	Vertex * v_s_neigbhour = do_vertex_exists_check(n);
	auto it = neighbours.find(&v);
	if (it == neighbours.end() ) {
		// this is the first time we're adding a neighbour of v
		auto new_set = new set<Vertex *, VertexPointerComparator>();
		new_set->insert(&n);
		auto neighbours_iter_begin = neighbours.begin();
		//std::pair<Vertex*, set<Vertex*, VertexPointerComparator> *> p =
		//	std::pair<Vertex*, set<Vertex*, VertexPointerComparator> *>
		//		(&v, new_set);
		neighbours.insert(neighbours_iter_begin, 
			std::pair<Vertex*,
				set<Vertex*, VertexPointerComparator>* >
					(&v, new_set));
		//cout << decltype(neighbours_iter_begin) << endl;
		// neighbours.insert(neighbours_iter_begin,  p);
	} else {
		// some neighbours of v were already added
		set<Vertex*, VertexPointerComparator> & s = *(it->second);
		s.insert(&n);
	}
}

void Graph::dfs(Vertex * v_ptr)
{
	v_ptr->is_being_visited = true;


	auto v_s_neigbhours = neighbours.find(v_ptr);

	if (v_s_neigbhours != neighbours.end()) {
		set<Vertex*, VertexPointerComparator>
			& neighbours = *(v_s_neigbhours->second);
		for (auto v_ptr : neighbours) {
			if (v_ptr->is_being_visited) {
				cout << "cycle detected at node : " << *v_ptr;
				return;
			} else {
				if (!v_ptr->is_visited) {
					dfs(v_ptr);
				}
			}
		}
	} else {
		v_ptr->is_being_visited = false;
		v_ptr->is_visited = true;
	}

}

void Graph::dfsDetectCycle()
{
	for (auto v_ptr : vertex_set) {
		Vertex &v = *v_ptr;
		if (v.is_visited == false) {
			dfs(v_ptr);
		}
	}


}

void Graph::print_vertices(string label)
{
	cout << "ENTER " << __PRETTY_FUNCTION__ <<  " " << label << endl;
	for (auto it: vertex_set) {
		auto a_vertex = *it;
		cout <<  a_vertex << endl;
	}
	cout << "EXIT " << __PRETTY_FUNCTION__ <<  " " << label << endl;
}

void Graph::print_vertices_and_their_neighbours()
{
	cout << "ENTER " << __PRETTY_FUNCTION__ << endl;

	for (auto it: vertex_set) {
		auto a_vertex = *it;
		cout <<  a_vertex << endl;
	}
	for (auto it: neighbours) {
		auto a_vertex = it.first;
		cout << * a_vertex << " : " ;
		//auto its_neighbours = it.second;
		set<Vertex*, VertexPointerComparator> & its_neighbours = *(it.second);
		for (auto a_neighbour: its_neighbours) {
			cout << *a_neighbour;
		}
		cout << endl;
	}
	cout << endl;
	cout << "EXIT " << __PRETTY_FUNCTION__ << endl;
}

int main()
{
	cout << "Hello" << endl;
	Graph g;
	{
		string v_name("a");
		Vertex  v_a(v_name, 101);
		g.add_vertex(v_a);
		g.print_vertices("After a");
		cout << "Hello 2" << endl;

		string v_name_b("b");
		Vertex  v_b(v_name_b, 102);
		g.add_vertex(v_b);
		g.print_vertices("After b");
		//g.print_vertices_and_their_neighbours();

		cout << "Hello 3" << endl;

		string v_name_c("c");
		Vertex  v_c(v_name_c, 103);
		g.add_vertex(v_c);
		g.print_vertices("After c");

		string v_name_d("d");
		Vertex  v_d(v_name_d, 104);
		g.add_vertex(v_d);

		string v_name_e("e");
		Vertex  v_e(v_name_e, 105);
		g.add_vertex(v_e);

		string v_name_f("f");
		Vertex  v_f(v_name_f, 106);
		g.add_vertex(v_f);


		cout << "Hello 6" << endl;
		g.print_vertices_and_their_neighbours();

		//g.add_neighbour(v_a, v_b);
		g.add_neighbour(v_b, v_c);
		g.add_neighbour(v_b, v_d);
		g.add_neighbour(v_d, v_e);
		g.add_neighbour(v_d, v_f);
		g.add_neighbour(v_c, v_f);
		g.add_neighbour(v_f, v_b);
		cout << "Hello 7" << endl;
		//cout << "Topological order is: " << endl;
		//deque<Vertex*> topological_order
		//	= g.get_topological_order();
		//for (auto v: topological_order) {
		//	cout << " " << *v ;
		//}
		g.dfsDetectCycle();
		/*
		*/
		cout << endl;
	}

}
