#include <vector>
#include <queue>

using namespace std;

typedef int* path_t;
typedef path_t* paths_t;

int numCrosses = 0;
int numPaths = 0;

/*void computePaths(paths_t		 &paths, 
				  vector<int>	 &minDistances,
				  vector<int>	 &previous,
				  short start)
{
	minDistances.clear();
	minDistances.resize(numCrosses, 2000000000);
	minDistances[start] = 0;

	previous.clear();
	previous.resize(numCrosses, -1);

	vector<pair<int, short>> vertexQueue;
	vertexQueue.push_back(make_pair(minDistances[start], start));

	previous[start] = 0;

	while(!vertexQueue.empty())
	{
		int distance = vertexQueue.begin()->first;
		short source = vertexQueue.begin()->second;
		vertexQueue.erase(vertexQueue.begin());

		path_t &targetPaths = paths[source];
		for (int i = 0; i < numCrosses; i++)
		{
			if (targetPaths[i] == -1)
				continue;

			int distanceTarget = targetPaths[i];
			int distanceTo = distance + distanceTarget;

			if (distanceTo < minDistances[i]) {
				vertexQueue.erase(make_pair(minDistances[i], i));

				minDistances[i] = distanceTo;

				previous[i] = source;
				vertexQueue.insert(make_pair(minDistances[i], i));
			}
		}
	}
}*/

const int INF = 1 << 30;

class prioritize { public: bool operator ()(pair<int, int>&p1, pair<int, int>&p2) { return p1.second>p2.second; } };

void Dijkstra(int source,
	paths_t a,
	vector<int>	 &dis,
	vector<int>	 &previous)
{
	dis.clear();
	dis.resize(numCrosses, 2000000000);
	dis[source] = 0;

	previous.clear();
	previous.resize(numCrosses, -1);


	bool* vis = new bool[numCrosses];
	for (int i = 0; i < numCrosses; i++)
		vis[i] = false;

	for (int i = 0; i<numCrosses; i++)
		dis[i] = INF;

	priority_queue<pair<int, int>, vector<pair<int, int> >, prioritize> pq;
	pq.push(make_pair(source, dis[source] = 0));
	while (!pq.empty())
	{
		pair<int, int> curr = pq.top();
		pq.pop();
		int cv = curr.first, cw = curr.second;
		if (vis[cv])
			continue;
		vis[cv] = true;
		for (int i = 0; i < numCrosses; i++) {
			if (a[cv][i] == -1)
				continue;

			if (!vis[i] && a[cv][i] + cw < dis[i]) {
				pq.push(make_pair(i, (dis[i] = a[cv][i] + cw)));
				previous[i] = cv;
			}
		}
	}
}

void addPath(int source, int target, int flowers, paths_t &paths)
{
	path_t &sourcePaths = paths[source];
	path_t &targetPaths = paths[target];

	sourcePaths[target] = flowers;
	targetPaths[source] = flowers;
}

int main()
{
	scanf("%d %d", &numCrosses, &numPaths);

	vector<int> minDistances;
	vector<int> previous;

	paths_t paths;
	paths = new int*[numCrosses];
	for (int i = 0; i < numCrosses; i++) {
		paths[i] = new int[numCrosses];
		for (int j = 0; j < numCrosses; j++)
			paths[i][j] = -1;
	}

	int tmpSource, tmpTarget, tmpDistance;
	for (int i = 0; i < numPaths; i++)
	{
		scanf("%d %d %d", &tmpSource, &tmpTarget, &tmpDistance);

		addPath(tmpSource, tmpTarget, tmpDistance, paths);
	}


	//compute_paths(paths, minDistances, previous, 0);

	Dijkstra(0, paths, minDistances, previous);
	int shortest = minDistances[numCrosses - 1];

	int* path = new int[numCrosses];
	int n = 0;
	for (int vertex = numCrosses - 1; vertex != 0; vertex = previous[vertex])
		path[n++] = vertex;

	path[n++] = 0;

	vector<int> kpaths;
	int tmpPath1Index = -1, tmpPath2Index = -1;
	int tmpPathDistance = -1;

	int secondShortest = 99999999;

	// 0 1 2 3 4
	// 6 5 2 1 0
	for (int i = 0; i < n - 1; i++)
	{
		if(tmpPath1Index != -1 && tmpPath2Index != -1)
		{
			paths[tmpPath1Index][tmpPath2Index] = tmpPathDistance;
			paths[tmpPath2Index][tmpPath1Index] = tmpPathDistance;
		}

		tmpPath1Index = path[i];
		tmpPath2Index = path[i+1];

		tmpPathDistance = paths[tmpPath1Index][tmpPath2Index];
		paths[tmpPath1Index][tmpPath2Index] = -1;
		paths[tmpPath2Index][tmpPath1Index] = -1;

		Dijkstra(0, paths, minDistances, previous);

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