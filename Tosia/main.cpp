#include <iostream>
#include <set>
#include "list.h"

using namespace std;

template<class A, class B>
struct para
{
	A left;
	B right;

	para() : left(NULL), right(NULL) {}
	para(A l, B r) : left(l), right(r) {}
};

typedef para<int, int> para_t;

struct Wezel
{
	int id;
	List<para<int, int>> sasiedzi;

	Wezel(int i) : id(i), sasiedzi() {}

	int getFlowersFromNeightbour(int i)
	{
		try {
			para_t p = getPairFromNeightbour(i);

			return p.right;
		} catch(exception)
		{
			return -1;
		}
	}

	para_t & getPairFromNeightbour(int i)
	{
		for (Node<para<int, int>>* it = sasiedzi.Begin(); it != sasiedzi.End(); it = it->next)
		{
			if (it->val.left == i)
				return it->val;
		}
		throw exception("Not found");
	}

	para_t & operator [](int i)
	{
		return getPairFromNeightbour(i);
	}
};


int numCrosses = 0;
int numPaths = 0; 
const int inf = 1 << 30;

void computePaths(List<Wezel*> &paths,
	List<int>	 &minDistances,
	List<int>	 &previous)
{
	previous.reset(-1);
	previous[0] = 0;

	minDistances.reset(inf);
	minDistances[0] = 0;

	set<pair<int, int>> vertexQueue;
	vertexQueue.insert(make_pair(minDistances[0], 0));

	while (!vertexQueue.empty())
	{
		int distance = vertexQueue.begin()->first;
		int source = vertexQueue.begin()->second;
		vertexQueue.erase(vertexQueue.begin());

		Wezel* targetNode = paths[source];
		if (targetNode->sasiedzi.GetLength() > 0)
			for (Node<para_t>* it = targetNode->sasiedzi.Begin(); it != targetNode->sasiedzi.End(); it = it->next)
			{
				int target = it->val.left;
				int distanceTarget = it->val.right;
				if (distanceTarget == -1)
					continue;

				int distanceTo = distance + distanceTarget;

				if (distanceTo < minDistances[target]) {
					vertexQueue.erase(make_pair(minDistances[target], target));

					minDistances[target] = distanceTo;

					previous[target] = source;
					vertexQueue.insert(make_pair(minDistances[target], target));
				}
			}
	}
}

void addPath(int source, int target, int flowers, List<Wezel*> &paths)
{
	Wezel* sourceNode = paths[source];
	Wezel* targetNode = paths[target];

	if (sourceNode == nullptr) {
		sourceNode = new Wezel(source);
		paths[source] = sourceNode;
	}

	if (targetNode == nullptr) {
		targetNode = new Wezel(target);
		paths[target] = targetNode;
	}

	para_t p(target, flowers);
	para_t p2(source, flowers);

	sourceNode->sasiedzi.Push(p);
	targetNode->sasiedzi.Push(p2);
}

void printPaths(List<Wezel*> paths)
{
	for (Node<Wezel*>* it = paths.Begin(); it != paths.End(); it = it->next)
	{
		if (it->val == nullptr) continue;

		printf("%d:\n", it->val->id);
		if (it->val->sasiedzi.GetLength() > 0)
			for (Node<para_t>* its = it->val->sasiedzi.Begin(); its != it->val->sasiedzi.End(); its = its->next)
				printf("   %d %d\n", its->val.left, its->val.right);
		printf("\n");
	}
}

int main()
{
	scanf("%d %d", &numCrosses, &numPaths);

	List<int> minDistances(numCrosses, inf);
	List<int> previous(numCrosses, -1);

	List<Wezel*> paths(numCrosses, nullptr);
	

	int tmpSource, tmpTarget, tmpDistance;
	for (int i = 0; i < numPaths; i++)
	{
		scanf("%d %d %d", &tmpSource, &tmpTarget, &tmpDistance);

		addPath(tmpSource, tmpTarget, tmpDistance, paths);
	}

	computePaths(paths, minDistances, previous);
	int shortest = minDistances[numCrosses - 1];

	int* path = new int[numCrosses];
	int n = 0;
	for (int vertex = numCrosses - 1; vertex != 0; vertex = previous[vertex])
		path[n++] = vertex;

	path[n++] = 0;

	List<int> kpaths;

	int tmpPath1Index = -1, tmpPath2Index = -1;
	int tmpPathDistance = -1;

	int secondShortest = 99999999;

	for (int i = 0; i < n - 1; i++)
	{
		if(tmpPath1Index != -1 && tmpPath2Index != -1)
		{
			(*paths[tmpPath1Index])[tmpPath2Index].right = tmpPathDistance;
			(*paths[tmpPath2Index])[tmpPath1Index].right = tmpPathDistance;
		}

		tmpPath1Index = path[i];
		tmpPath2Index = path[i+1];

		tmpPathDistance = (*paths[tmpPath1Index])[tmpPath2Index].right;
		(*paths[tmpPath1Index])[tmpPath2Index].right = -1;
		(*paths[tmpPath2Index])[tmpPath1Index].right = -1;

		computePaths(paths, minDistances, previous);

		int dist = minDistances[numCrosses - 1];
		if (dist != -1 && dist < secondShortest)
			secondShortest = dist;
		if (shortest == secondShortest)
			break;
	}

	if (shortest < 9999999 && secondShortest < 9999999)
		printf("%d %d", shortest, secondShortest);
	else
		printf("#");

	return 0;
}