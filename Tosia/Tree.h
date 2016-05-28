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

	static Path* findPathWithSource(Path** v, int source, int length)
	{
		for (int i = 0; i < length; i++) {
			Path* it = v[i];
			if (it->source == source)
				return it;
		}
		return nullptr;
	}

	static void erasePath(Path** v, int source, int destination, int &length)
	{
		for (int i = 0; i < length; i++) {
			Path* it = v[i];
			if (it->source == source && it->destination == destination) {
				v[i] = v[length - 1];
				v[length - 1] = nullptr;
				length--;
				break;
			}
		}
	}

	static Path* findPathWithDestination(Path** v, int destination, int length)
	{
		for (int i = 0; i < length; i++) {
			Path* it = v[i];
			if (it->destination == destination)
				return it;
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

	static Node* findNodeWithDestination(Node** tree, int dest, int length)
	{
		for (int i = 0; i < length; i++) {
			Node* it = tree[i];
			if (it->path->destination == dest)
				return it;
		}
		return nullptr;
	}
};