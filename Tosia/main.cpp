#include <vector>
#include <list>
#include <set>
#include <iostream>

using namespace std;

struct Path
{
	int source;
	int target;
	int numFlowers;
	bool collected;

	Path(int s, int t, int f) : source(s), target(t), numFlowers(f), collected(false) {}
};

typedef vector<Path*> path_t;
typedef vector<path_t> paths_t;

void computePaths(paths_t		 &paths, 
				  vector<int>	 &maxFlowers,
				  vector<int>	 &distanceFromHome)
{
	int n = paths.size();

	maxFlowers.clear();
	maxFlowers.resize(n + 1, 0);
	maxFlowers[1] = 0;

	distanceFromHome.clear();
	distanceFromHome.resize(n + 1, -1);

	set<pair<int, int>> vertexQueue;
	vertexQueue.insert(make_pair(maxFlowers[1], 1));

	distanceFromHome[1] = 0;

	while(!vertexQueue.empty())
	{
		int flowers = vertexQueue.begin()->first;
		int source = vertexQueue.begin()->second;
		vertexQueue.erase(vertexQueue.begin());

		path_t &targetPaths = paths[source];
		for (path_t::iterator it = targetPaths.begin(); it != targetPaths.end(); ++it)
		{
			if ((*it)->collected) continue;

			int target = ((*it)->target == source) ? (*it)->source : (*it)->target;

			int flowersTarget = (*it)->numFlowers;
			int distanceTo = flowers + flowersTarget;

			(*it)->collected = true;
			vertexQueue.erase(make_pair(maxFlowers[target], target));

			maxFlowers[target] = distanceTo;

			distanceFromHome[target] = distanceFromHome[source] + 1;
			vertexQueue.insert(make_pair(maxFlowers[target], target));
		}
	}
}

void addPath(int source, int target, int flowers, paths_t &paths)
{
	path_t &sourcePaths = paths[source];
	path_t &targetPaths = paths[target];

	Path* p = new Path(source, target, flowers);

	sourcePaths.push_back(p);
	targetPaths.push_back(p);
}

int main()
{
	int numPaths = 0;
	int maxPaths = 0;

	scanf("%d %d", &numPaths, &maxPaths);

	vector<int> maxFlowers;
	vector<int> distanceFromHome;
	paths_t paths;

	int* readSource = new int[numPaths];
	int* readTarget = new int[numPaths];
	int* readFlowers = new int[numPaths];
	
	int maxVertex = 0;

	for (int i = 0; i < numPaths; i++)
	{
		scanf("%d %d %d", &readSource[i], &readTarget[i], &readFlowers[i]);

		if (readSource[i] > maxVertex)
			maxVertex = readSource[i];

		if (readTarget[i] > maxVertex)
			maxVertex = readTarget[i];
	}

	paths.resize(maxVertex + 1, path_t());

	for (int i = 0; i < numPaths; i++)
	{
		addPath(readSource[i], readTarget[i], readFlowers[i], paths);
	}

	computePaths(paths, maxFlowers, distanceFromHome);

	int result = 0;
	int key = 0;
	for (vector<int>::const_iterator it = distanceFromHome.begin(); it != distanceFromHome.end(); ++it, key++) {
		if (*it == maxPaths && maxFlowers[key] > result)
			result = maxFlowers[key];
	}

	printf("%d", result);

	delete readSource;
	delete readTarget;
	delete readFlowers;
	return 0;
}