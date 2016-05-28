#include <vector>
#include <string>

#include "Tree.h"

using namespace std;

int numPaths = 0;
int maxPaths = 0;

int compute(int** distances, Node* current, int depth)
{
	if (current == nullptr) 
		return 0;

	if (distances[current->distancesIndex][depth] != -1) 
		return distances[current->distancesIndex][depth];

	int max = 0;

	if (depth == 1) {
		if (current->left != nullptr && current->left->path->flowers > max)
			max = current->left->path->flowers;

		if (current->right != nullptr && current->right->path->flowers > max)
			max = current->right->path->flowers;

	} else {
		int child = 0;

		if (current->left != nullptr && (child = compute(distances, current->left, depth - 1)) && child > max)
			max = child;

		if (current->right != nullptr && (child = compute(distances, current->right, depth - 1) ) && child > max)
			max = child;

		if (current->left != nullptr && current->right != nullptr) {
			for (int i = 0; i < depth - 1; i++) {
				if ((child = compute(distances, current->left, i) + compute(distances, current->right, depth - i - 2)) && child > max)
					max = child;
			}
		}
	}

	max += current->path->flowers;
	distances[current->distancesIndex][depth] = max;

	return max;
}

Node* putPathOnTree(vpath_t &paths, vnode_t &tree, Path* path, Node* parent)
{
	Node* n = new Node(path);

	if (parent != nullptr) {
		if (parent->left == nullptr)
			parent->left = n;
		else if (parent->right == nullptr)
			parent->right = n;
	}

	tree.push_back(n);

	Path::erasePath(paths, path->source, path->destination);

	return n;
}

void buildTree(vpath_t &paths, vnode_t &tree, int lookForSource = 1, Node* parent = nullptr)
{
	Path* foundPath = Path::findPathWithSource(paths, lookForSource);
	if (foundPath == nullptr) {
		foundPath = Path::findPathWithDestination(paths, lookForSource);
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
	vnode_t tree;
	vpath_t paths;

	scanf("%d %d", &numPaths, &maxPaths);

	int tmpSource, tmpDest, tmpFlowers;

	int** distancesTable = new int*[numPaths + 1];
	for (int i = 0; i <= numPaths; i++)
	{
		distancesTable[i] = new int[maxPaths];
		for (int j = 0; j < maxPaths; j++)
			distancesTable[i][j] = -1;
	}

	for (int i = 0; i < numPaths; i++) {
		scanf("%d %d %d", &tmpSource, &tmpDest, &tmpFlowers);

		paths.push_back(new Path(tmpSource, tmpDest, tmpFlowers));
	}

	buildTree(paths, tree);
	buildTree(paths, tree);

	for (int i = 0; i < numPaths; i++) {
		tree[i]->distancesIndex = i;
		distancesTable[i][0] = tree[i]->path->flowers;
	}

	int result = compute(distancesTable, tree[0], maxPaths - 1);

	printf("%d", result);
	return 0;
}