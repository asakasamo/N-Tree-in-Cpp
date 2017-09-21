#include <assert.h>
#include <iostream>

#include "Ntree.h"

typedef tnode<std::string> node;

int main() {
  Ntree<std::string> tree("Food");		// Create tree with root containing the string "food"

	// Ntree::getRoot() should return a pointer to the tree's root
	// Ntree::node() should have an addChild method that takes a T, allocates a new node with that T as its value, and adds it to the called node's list of children
	node* a = tree.getRoot()->addChild("Plant");
	node* b = tree.getRoot()->addChild("Animal");
	
	node* c = a->addChild("Roots");
	node* d = a->addChild("Leaves");
	node* e = a->addChild("Fruits");
	
	node* f = b->addChild("Fish");
	node* g = b->addChild("Mammals");
	node* h = b->addChild("Birds");
	
	node* i = c->addChild("Potatoes");
	node* j = c->addChild("Carrots");
	
	node* k = d->addChild("Lettuce");
	node* l = d->addChild("Cabbage");
	
	node* m = e->addChild("Apples");
	node* n = e->addChild("Pears");
	node* o = e->addChild("Plums");
	node* p = e->addChild("Grapes");
	node* q = e->addChild("Oranges");
	
	node* r = f->addChild("Salmon");
	node* s = f->addChild("Tuna");
	
	node* t = g->addChild("Beef");
	node* u = g->addChild("Lamb");
	
	node* v = h->addChild("Chicken");
	node* w = h->addChild("Turkey");
	
	node* x = r->addChild("Wild");
	node* y = r->addChild("Farm");
	
	node* z = m->addChild("GrannySmith");
	node* aa = m->addChild("Gala");

	// write toString method
	std::cout << tree.toString() << std::endl;

	// write serialize method that takes filepath
	tree.serialize("foodtree.out");

	// default constructor creates empty tree.
	Ntree<std::string> tree2;
	// tree2 should become the tree deserialized from filepath
	tree2.deserialize("foodtree.out");

	assert(tree==tree2);		// overload equality operator
}