#include <vector>
#include <set>
#include <list>

using namespace std;

struct Path
{
	int target;
	int distance;

	Path(int t, int f) : target(t), distance(f) {}
};

typedef vector<Path> path_t;
typedef vector<path_t> paths_t;

void computePaths(paths_t		 &paths, 
				  vector<int>	 &minDistances,
				  vector<int>	 &previous,
				  int start)
{
	int n = paths.size();

	minDistances.clear();
	minDistances.resize(n, 2000000000);
	minDistances[start] = 0;

	previous.clear();
	previous.resize(n, -1);

	set<pair<int, int>> vertexQueue;
	vertexQueue.insert(make_pair(minDistances[start], start));

	previous[start] = 0;

	while(!vertexQueue.empty())
	{
		int distance = vertexQueue.begin()->first;
		int source = vertexQueue.begin()->second;
		vertexQueue.erase(vertexQueue.begin());

		path_t &targetPaths = paths[source];
		for (path_t::iterator it = targetPaths.begin(); it != targetPaths.end(); ++it)
		{
			int target = it->target;
			int distanceTarget = it->distance;
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

void addPath(int source, int target, int flowers, paths_t &paths)
{
	path_t &sourcePaths = paths[source];
	path_t &targetPaths = paths[target];

	Path p(target, flowers);

	sourcePaths.push_back(p);
	Path p2(source, flowers);
	targetPaths.push_back(p2);
}

int main()
{
	int numCrosses = 0;
	int numPaths = 0;

	scanf("%d %d", &numCrosses, &numPaths);

	vector<int> minDistances;
	vector<int> previous;
	paths_t paths;
	paths.resize(numCrosses, path_t());


	int tmpSource, tmpTarget, tmpDistance;
	for (int i = 0; i < numPaths; i++)
	{
		scanf("%d %d %d", &tmpSource, &tmpTarget, &tmpDistance);

		addPath(tmpSource, tmpTarget, tmpDistance, paths);
	}

	list<int> path;
	for (int vertex = numCrosses - 1; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);


	vector<int> kpaths;

	for (int i = 1; i < path.size() - 2; i++)
	{
		computePaths(paths, minDistances, previous, i);
		kpaths.push_back(minDistances[0] + minDistances[numCrosses - 1]);
	}

	int shortest		= 99999998;
	int secondShortest	= 99999999;

	for (vector<int>::const_iterator it = kpaths.begin(); it != kpaths.end(); ++it)
	{

		if (*it < shortest) {
			secondShortest = shortest;
			shortest = *it;
		}
		else if (*it < secondShortest && *it != shortest)
			secondShortest = *it;
	}

	if (kpaths.size() > 1)
		printf("%d %d", shortest, secondShortest);
	else
		printf("#");

	return 0;
}