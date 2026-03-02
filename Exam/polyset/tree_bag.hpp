						/* File deja m3ti */

#ifndef EXAM_ASSIGNMENTS_TREE_BAG_HPP
#define EXAM_ASSIGNMENTS_TREE_BAG_HPP
#include "bag.hpp"

class tree_bag : virtual public bag {
protected:
	struct node {
		node *l;
		node *r;
		int value;
	};
	node *tree;
public:
	//1
	tree_bag();
	tree_bag(const tree_bag &);
	tree_bag &operator=(const tree_bag &);
	~tree_bag();
	
	//2
	node *extract_tree();
	void set_tree(node *);

	//3
	virtual void insert(int);
	virtual void insert(int *array, int size);
	virtual void print() const;
	virtual void clear();

private:
	//4
	static void destroy_tree(node *);
	static void print_node(node *);
	static node *copy_node(node *);
};


#endif //EXAM_ASSIGNMENTS_TREE_BAG_HPP

/* 

	NULL

	5


 */