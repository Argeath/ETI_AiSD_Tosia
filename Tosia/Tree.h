#pragma once

struct Path
{
	int source;
	int destination;
	int flowers;

	Path() : source(0), destination(0), flowers(0) {}
	Path(int s, int d, int f) : source(s), destination(d), flowers(f) {}

	void swapSrcDest()
	{
		int tmp = source;
		source = destination;
		destination = tmp;
	}

	static Path* findPathWithSource(std::vector<Path*> &v, int f)
	{
		for (std::vector<Path*>::const_iterator it = v.begin(); it != v.end(); ++it)
		{
			if ((*it)->source == f)
				return *it;
		}
		return nullptr;
	}

	static void erasePath(std::vector<Path*> &v, int source, int destination)
	{
		for (std::vector<Path*>::const_iterator it = v.begin(); it != v.end(); ++it)
		{
			if ((*it)->source == source && (*it)->destination == destination) {
				v.erase(it);
				break;
			}
		}
	}

	static Path* findPathWithDestination(std::vector<Path*> &v, int f)
	{
		for (std::vector<Path*>::const_iterator it = v.begin(); it != v.end(); ++it)
		{
			if ((*it)->destination == f)
				return *it;
		}
		return nullptr;
	}
};

struct Node
{
	Node* left;
	Node* right;
	Path* path;

	int distancesIndex;

	Node() : left(nullptr), right(nullptr), path(nullptr), distancesIndex(-1) {}
	Node(Path* p) : left(nullptr), right(nullptr), path(p), distancesIndex(-1) {}

	static Node* findNodeWithDestination(std::vector<Node*> tree, int dest)
	{
		for (std::vector<Node*>::const_iterator it = tree.begin(); it != tree.end(); ++it) {
			if ((*it)->path->destination == dest)
				return *it;
		}
		return nullptr;
	}
};


typedef std::vector<Path*> vpath_t;
typedef std::vector<Node*> vnode_t;