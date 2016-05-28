#pragma once

struct Path
{
	unsigned int source;
	unsigned int destination;
	unsigned int flowers;

	Path() : source(0), destination(0), flowers(0) {}
	Path(unsigned int s, unsigned int d, unsigned int f) : source(s), destination(d), flowers(f) {}

	void swapSrcDest()
	{
		unsigned int tmp = source;
		source = destination;
		destination = tmp;
	}

	static Path* findPathWithSource(Path** v, int source, int length) {
		for (int i = 0; i < length; i++) {
			if (v[i]->source == source)
				return v[i];
		}
		return nullptr;
	}

	static void erasePath(Path** v, int source, int destination, int &length)
	{
		for (int i = 0; i < length; i++) {
			if (v[i]->source == source && v[i]->destination == destination) {
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
			if (v[i]->destination == destination)
				return v[i];
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

	~Node()
	{
		delete path;
	}
};