#include <vector>

#include "Tree.h"

using namespace std;


struct State
{
	int flowers;
	int pathsToGo;


	vnode_t parents;
	vpath_t paths;

	State() : flowers(0), pathsToGo(0) {}
	State(int p) : flowers(0), pathsToGo(p) {}
};

State best = State();
int numPaths = 0;
int maxPaths = 0;

vnode_t tree;
vpath_t paths;

int error = 0;
Path errorPath = Path();
Path errorParent = Path();
Path errorParentLeft = Path();
Path errorParentRight = Path();

void compute(vnode_t paths, State state, Node* next)
{
	if(state.pathsToGo == 0)
	{
		if(state.flowers > best.flowers)
			best = state;
		return;
	}

	if(next == nullptr)
	{
		/*Node* mostFlowers = nullptr;
		for (int i = state.parents.size() - 1; i > 0; i--)
		{
			if (state.parents.at(i-1)->right != nullptr && state.parents.at(i) != state.parents.at(i-1)->right)
				compute(paths, state, state.parents.at(i-1)->right);

			if (state.parents.at(i - 1)->left != nullptr && state.parents.at(i) != state.parents.at(i - 1)->left)
				compute(paths, state, state.parents.at(i-1)->left);
		}*/
		return;
	}

	state.flowers += next->path->flowers;
	state.pathsToGo--;
	state.paths.push_back(next->path);
	state.parents.push_back(next);

	compute(paths, state, next->left);
	compute(paths, state, next->right);
	// TODO: Both
}


Node* putPathOnTree(Path* path, Node* parent)
{
	Node* n = new Node(path);

	if (parent != nullptr) {
		if (parent->left == nullptr)
			parent->left = n;
		else if (parent->right == nullptr)
			parent->right = n;
		else {
			error = 2;
			errorPath = *path;
			errorParent = *parent->path;
			errorParentLeft = *parent->left->path;
			errorParentRight = *parent->right->path;
			throw new exception();
		}
	}

	tree.push_back(n);

	Path::erasePathWithSource(paths, path->source);

	return n;
}

void buildTree(int lookForSource = 1, Node* parent = nullptr)
{
	Path* foundPath = Path::findPathWithSource(paths, lookForSource);
	if (foundPath == nullptr) {
		return;
	}

	Node* n = putPathOnTree(foundPath, parent);

	buildTree(foundPath->destination, n);
	buildTree(foundPath->destination, n);
}

void fillTree()
{
	while (!paths.empty())
	{
		Path* path = paths.at(0);
		path->swapSrcDest();
		Node* parent = Node::findNodeWithDestination(tree, path->source);

		Node* n = putPathOnTree(path, parent);

		buildTree(path->destination, n);
		buildTree(path->destination, n);
	}
}

int main()
{
	scanf("%d %d", &numPaths, &maxPaths);

	int tmpSource, tmpDest, tmpFlowers;

	for (int i = 0; i < numPaths; i++) {
		scanf("%d %d %d", &tmpSource, &tmpDest, &tmpFlowers);

		paths.push_back(new Path(tmpSource, tmpDest, tmpFlowers));
	}

	buildTree();
	buildTree();
	fillTree();

	compute(tree, State(maxPaths), tree.at(0));

	printf("%d", best.flowers);

	return 0;
}