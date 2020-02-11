#ifndef ___TREE_H___
#define ___TREE_H___

#include <vector>

template<typename Element> 
class TreeNode
{
	private:
	
	public:
	int layer;																	//root is the highest layer
	Element e;
	TreeNode* parent;
	std::vector<TreeNode< Element >*> children;
	
	TreeNode(Element _e);
	virtual ~TreeNode();
	
};

template<typename Element> 
TreeNode< Element >::TreeNode(Element _e)
{
	e = _e;	
	parent = NULL;
}

template<typename Element> 
TreeNode< Element >::~TreeNode()
{
	
}

template<typename Element> 
class Tree
{
	private:
	TreeNode< Element >* root;
	int currentLayer;
	std::vector<TreeNode< Element >*> index;
	
	public:
	int PushAsParent(Element _e);
	int PushAsChild(Element _e);
	
	Element operator[](int _id)
	{
		return index[_id]->e;
	}
	
	int GetLayer(int _id)
	{
		return index[_id]->layer;
	}
	
	int size()
	{
		return index.size();
	}
	
	Tree();
	virtual ~Tree();
};

template<typename Element>
int Tree< Element >::PushAsParent(Element _e)
{
	TreeNode< Element >* tmpTreeNode = new TreeNode< Element >(_e);
	tmpTreeNode->layer = currentLayer;
	index.push_back(tmpTreeNode);
	if(root == NULL)
	{
		root = tmpTreeNode;
	}
	else
	{
		TreeNode< Element >* tmpRoot;
		tmpRoot = root;
		root->parent = tmpTreeNode;
		root = tmpTreeNode; 
		root->children.push_back(tmpRoot);
	}
	currentLayer++;
}

template<typename Element>
int Tree< Element >::PushAsChild(Element _e)
{
	TreeNode< Element >* tmpTreeNode = new TreeNode< Element >(_e);
	tmpTreeNode->layer = currentLayer - 2;
	index.push_back(tmpTreeNode);
	if(root == NULL)
	{
		return -1;
	}
	else
	{
		tmpTreeNode->parent = root;
		root->children.push_back(tmpTreeNode);
	}
}

template<typename Element>
Tree< Element >::Tree()
{
	currentLayer = 1;
	root = NULL;
}

template<typename Element>
Tree< Element >::~Tree()
{	
	for(int i = 0; i < index.size(); i++) 
	{
		delete index[i];
	}
}

#endif //___TREE_H___
