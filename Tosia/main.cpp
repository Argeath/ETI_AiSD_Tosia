#include <vector>

#include "Tree.h"

using namespace std;

int numPaths = 0;
int maxPaths = 0;

int treeLength = 0;
int pathsLength = 0;

int compute(int** distances, Node* current, int depth)
{
	if (depth == -1 || current == nullptr)
		return 0;

	if (current->left == nullptr && current->right == nullptr)
		return distances[current->distancesIndex][0];

	if (distances[current->distancesIndex][depth] != -1)
		return distances[current->distancesIndex][depth];

	int max = 0;
	int child = 0;

	for (int i = 0; i <= depth; i++) {
		if ((child = compute(distances, current->left, i - 1) + compute(distances, current->right, depth - i - 1)) && child > max)
			max = child;
	}

	max += distances[current->distancesIndex][0];
	distances[current->distancesIndex][depth] = max;

	if(distances[current->distancesIndex][depth] == distances[current->distancesIndex][depth-1])
		for (int i = depth; i < maxPaths - depth - 1; i++)
			distances[current->distancesIndex][i] = max;

	return max;
}

Node* putPathOnTree(Path** paths, Node** tree, Path* path, Node* parent)
{
	Node* n = new Node(path);

	if (parent != nullptr) {
		if (parent->left == nullptr)
			parent->left = n;
		else if (parent->right == nullptr)
			parent->right = n;
	}

	tree[treeLength++] = n;

	Path::erasePath(paths, path->source, path->destination, pathsLength);

	return n;
}

void buildTree(Path** paths, Node** tree, int lookForSource = 1, Node* parent = nullptr)
{
	if (parent != nullptr && parent->left != nullptr && parent->right != nullptr) return;

	Path* foundPath = Path::findPathWithSource(paths, lookForSource, pathsLength);
	if (foundPath == nullptr) {
		foundPath = Path::findPathWithDestination(paths, lookForSource, pathsLength);
		if(foundPath == nullptr)
			return;
		foundPath->swapSrcDest();
	}

	Node* n = putPathOnTree(paths, tree, foundPath, parent);

	buildTree(paths, tree, foundPath->destination, n);
	buildTree(paths, tree, foundPath->destination, n);
}

int main()
{
	scanf("%d %d", &numPaths, &maxPaths);

	Node** tree = new Node*[numPaths];
	Path** paths = new Path*[numPaths];

	int tmpSource, tmpDest, tmpFlowers;

	for (int i = 0; i < numPaths; i++) {
		scanf("%d %d %d", &tmpSource, &tmpDest, &tmpFlowers);

		paths[i] = new Path(tmpSource, tmpDest, tmpFlowers);
		pathsLength++;
	}

	buildTree(paths, tree);
	buildTree(paths, tree);

	int** distancesTable = new int*[numPaths];

	for (int i = 0; i < numPaths; i++) {
		if(tree[i]->left != nullptr || tree[i]->right != nullptr) {
			distancesTable[i] = new int[maxPaths];
			for (int j = 0; j < maxPaths; j++)
				distancesTable[i][j] = -1;
		} else
			distancesTable[i] = new int[1];

		tree[i]->distancesIndex = i;
		distancesTable[i][0] = tree[i]->path->flowers;
	}

	int result = compute(distancesTable, tree[0], maxPaths - 1);

	printf("%d", result);

	for (int i = 0; i < numPaths; i++)
		delete[] distancesTable[i];
	delete[] distancesTable;
	delete[] tree;
	return 0;
}
