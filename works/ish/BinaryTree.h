/*
 * BinaryTree.h (C) Zhao Yanbai
 *
 * 07/07/2008
 *
 */
#ifndef	_BINARYTREE_H
#define	_BINARYTREE_H

typedef	class	BTNode
{
public:
	BTNode(const char *key, const char *data);
	~BTNode();
	BTNode	*parent;
	BTNode	*left,*right;
	char	*key,*data;
}BinaryTreeNode,*pBinaryTreeNode;


class	BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	bool insertNode(const char *key, const char *data);
	bool deleteNode(const char *key);
	bool containKey(const char *key) const;
	const char *getNode(const char *key) const;
	int getSize() const;
private:
	pBinaryTreeNode createNode(const char *key, const char *data);
	pBinaryTreeNode searchNode(const char *key) const;
	pBinaryTreeNode	m_root,m_rootp/*root's parent*/;
	int m_size;
};

typedef	BinaryTree* pBinaryTree;

#endif	//_BINARYTREE_H
