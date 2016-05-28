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

Node* putPathOnTree(vpath_t paths, vnode_t tree, Path* path, Node* parent)
{
	Node* n = new Node(path);

	if (parent != nullptr) {
		if (parent->left == nullptr)
			parent->left = n;
		else if (parent->right == nullptr)
			parent->right = n;
	}

	tree.push_back(n);

	Path::erasePathWithSource(paths, path->source);

	return n;
}

void buildTree(vpath_t paths, vnode_t tree, int lookForSource = 1, Node* parent = nullptr)
{
	Path* foundPath = Path::findPathWithSource(paths, lookForSource);
	if (foundPath == nullptr) {
		return;
	}

	Node* n = putPathOnTree(paths, tree, foundPath, parent);

	buildTree(paths, tree, foundPath->destination, n);
	buildTree(paths, tree, foundPath->destination, n);
}

void fillTree(vpath_t paths, vnode_t tree)
{
	while (!paths.empty())
	{
		Path* path = paths.at(0);
		path->swapSrcDest();
		Node* parent = Node::findNodeWithDestination(tree, path->source);

		Node* n = putPathOnTree(paths, tree, path, parent);

		buildTree(paths, tree, path->destination, n);
		buildTree(paths, tree, path->destination, n);
	}
}

struct ii
{
	string i;
	ii* d;

	ii() : i(""), d(nullptr) {}
	ii(string s) : i(s), d(nullptr) {}
};

ii* in1 = new ii();
ii* in2 = new ii();
ii* in3 = new ii();
ii* in4 = new ii();
ii* in5 = new ii();
ii* in6 = new ii();
ii* in7 = new ii();
ii* in8 = new ii();

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

	ii* in = in1;

	for (int i = 0; i < numPaths; i++) {
		scanf("%d %d %d", &tmpSource, &tmpDest, &tmpFlowers);

		in->d = new ii( to_string((long long)tmpSource) + " " + to_string((long long)tmpDest) + " " + to_string((long long)tmpFlowers));
		if (i == 2)
			in = in2;
		else if (i == 5)
			in = in3;
		else if (i == 8)
			in = in4;
		else if (i == 11)
			in = in5;
		else if (i == 14)
			in = in6;
		else if (i == 17)
			in = in7;
		else if (i == 20)
			in = in8;
		else
			in = in->d;

		paths.push_back(new Path(tmpSource, tmpDest, tmpFlowers));
	}

	throw new exception();

	buildTree(paths, tree);
	buildTree(paths, tree);
	fillTree(paths, tree);

	for (int i = 0; i < numPaths; i++) {
		tree[i]->distancesIndex = i;
		distancesTable[i][0] = tree[i]->path->flowers;
	}

	int result = compute(distancesTable, tree[0], maxPaths - 1);

	printf("%d", result);
	return 0;
}