/*
 * BinaryTree.cc (C) Zhao Yanbai
 *
 * 07/07/2008
 */
#include"Debug.h"
#include"BinaryTree.h"
#include<string.h>
#include<iostream>
using namespace std;
//======================Binary Node Part================================
BTNode::BTNode(const char *key, const char *data)
:parent(NULL),left(NULL),right(NULL)
{
	this->key	= new char[strlen(key)+1];
	if(this->key != NULL)
		strcpy(this->key, key);

	if(data != NULL)
	{
		this->data	= new char[strlen(data)+1];
		if(this->data != NULL)
			strcpy(this->data, data);
	}
	else
		this->data = NULL;
}
BTNode::~BTNode()
{
#ifdef	DEBUG_BINARYTREE
	cout<<"~"<<this->key<<endl;
#endif
	if(key != NULL)
		delete [] key;
	if(data != NULL)
		delete [] data;

	//delete the left and right child...
	//we just need to delete the root node
	//and it will go on...
	//if you destory just one node
	//please rember to set the left and right as NULL
	delete left;
	delete right;
}

//======================Binary Tree Part================================
//public part
BinaryTree::BinaryTree():m_root(NULL),m_rootp(NULL),m_size(0)
{

}
BinaryTree::~BinaryTree()
{
	delete m_rootp;
}

pBinaryTreeNode BinaryTree::searchNode(const char *key) const
{
	pBinaryTreeNode p = m_root;

	while(p)
	{
		int r = strcmp(key, p->key);
		if( r < 0 )
			p = p->left;
		else if( r > 0 )
			p = p->right;
		else
			return p;
	}

	return NULL;
}

bool BinaryTree::insertNode(const char *key, const char *data)
{
	pBinaryTreeNode	p = createNode(key, data);
	if(p == NULL)	return false;

	if(m_root != NULL)	//if it's not a empty tree...
	{
		pBinaryTreeNode parent = m_root;
		while(true)
		{
			int r =  strcmp(p->key, parent->key);
			if( r < 0 )
			{
				if(parent->left != NULL)
					parent = parent->left;
				else
				{
					parent->left = p;
					p->parent = parent;
					break;
				}
			}
			else if( r > 0 )
			{
				if(parent->right != NULL)
					parent = parent->right;
				else
				{
					parent->right = p;
					p->parent = parent;
					break;
				}
			}
			else
			{
				//it means that this node aleady exists.
				//we should destory the temporary memory.
				delete p;
				return false;
			}

		}
	}
	else
	{
		
		//if it's a empty tree set the node
		//to be the tree's root.
		m_root = p;
		//and i'll add a parent for root.
		//and root will be it's left child.
		//and it will let our program easier
		//we can not delete it until the object be destoryed.
		if(m_rootp == NULL)
		{
			p = createNode("Reserved","Reserved");
			if( p == NULL)
			{
				delete m_root;
				return false;
			}
			p->left = m_root;
			m_root->parent = p;
			m_rootp = p;
		}
	}
	
	m_size++;
	return true;
}

bool BinaryTree::deleteNode(const char *key)
{
	pBinaryTreeNode	p = searchNode(key);

	if( p == NULL ) return true;//false;

	if( p->left == NULL && p->right == NULL )
	{
		if( p->parent->left == p )
			p->parent->left = NULL;
		else
			p->parent->right = NULL;

	}
	else if(p->left != NULL && p->right == NULL)
	{
		if( p->parent->left == p )
			p->parent->left = p->left;
		else
			p->parent->right = p->left;

	}
	else if(p->left == NULL && p->right != NULL)
	{
		if( p->parent->left == p )
			p->parent->left = p->right;
		else
			p->parent->right = p->right;

	}
	else/* if(p->left != NULL && p->right != NULL)*/
	{
		//let left child replace current node.
		if( p->parent->left == p )
			p->parent->left = p->left;
		else
			p->parent->right = p->left;
		
		//get the right child in left tree
		pBinaryTreeNode rc = p->left;
		//find the last right child in the left tree.
		while(rc->right != NULL)
			rc = rc->right;
		//link to...
		rc->right = p->right;
	}


	//if the node to be deleted is the root node.
	//we should update the root pointer...
	if(p == m_root)
		m_root = m_rootp->left;
	if(m_root != NULL)
		m_root->parent = m_rootp;
	//it's very import to set NULL
	//or it's left and right child will be destoryed...
	p->left=p->right=NULL;
	delete p;
	m_size--;
	return true;
}

bool BinaryTree::containKey(const char *key) const
{
	return (searchNode(key) != NULL);
}

const char *BinaryTree::getNode(const char *key) const
{
	pBinaryTreeNode p = searchNode(key);
	if(p == NULL)	return NULL;
	return p->data;
}

int BinaryTree::getSize() const
{
	return m_size;
}



//private part
pBinaryTreeNode	BinaryTree::createNode(const char *key, const char *data)
{
	pBinaryTreeNode p = new BTNode(key, data);
	return p;
}

#ifdef	DEBUG_BINARYTREE
int main()
{
	BinaryTree	B;
	B.insertNode("C","CCCCCCCCCC");
	B.insertNode("A","AAAAAAAAAA");
	B.insertNode("B","BBBBBBBBBB");
	cout<<B.getSize()<<endl;
	B.deleteNode("C");
	B.deleteNode("A");
	B.insertNode("D","DDDDDDDDDD");
	B.insertNode("E","EEEEEEEEEE");
	B.insertNode("E","EEEEEEEEE-");
	B.insertNode("F","FFFFFFFFFF");
	B.deleteNode("C");
	cout<<B.getSize()<<endl;
	B.deleteNode("E");
	cout<<B.getSize()<<endl;
	
	cout<<B.getNode("A")<<endl;
	cout<<B.getNode("B")<<endl;
	//cout<<B.searchNode("C")->data<<endl;
	cout<<B.getNode("D")<<endl;
	//cout<<B.searchNode("E")->data<<endl;
	cout<<B.getNode("F")<<endl;
	cout<<B.getSize()<<endl;
}
#endif
