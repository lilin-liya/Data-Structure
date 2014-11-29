#include "RedBlackTree.h"
#include <iostream>

using namespace std;

int main()
{
	RedBlackTree<int> rbtree(0);
	rbtree.insert(3);
	rbtree.insert(2);
	rbtree.insert(4);
	rbtree.insert(1);

	rbtree.remove(2);
	rbtree.remove(4);
	rbtree.printTree();
	cout<<"test3:"<<endl;
	cout<<rbtree.contains(3)<<endl;
	cout<<"test2:"<<endl;
	cout<<rbtree.contains(2)<<endl;
	cout<<"test4:"<<endl;
	cout<<rbtree.contains(4)<<endl;
	cout<<"test1:"<<endl;
	cout<<rbtree.contains(1)<<endl;
	return 0;
}