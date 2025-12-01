#include "Kyojin/node.hpp"

/*
	Node is the base of almost everything in Doshin.

	I'm not sure what its trying to be, something like a scene graph?
*/

Node::~Node()
{
	this->magic = 0;
}

void Node::checkMagic()
{
	if (this->magic != 0x12345678) 
	{
		// Needs sys variable for a print
	}
}

void Node::procEvent(int id)
{
	Node* n = this->child;

	while (n != NULL)
	{
		n->procEvent(id);

		n = n->next;
	}
}

void Node::update()
{
	Node* n = this->child;

	while (n != NULL)
	{
		n->update();

		n = n->next;
	}
}

void Node::draw(Gfx& g)
{
	Node* n = this->child;

	while (n != NULL)
	{
		// If the node isn't hidden we draw it
		if (n->hidden == false) 
		{
			n->draw(g);
		}

		n = n->next;
	}
}

void Node::initGfx()
{
	// TODO: This function relies on a sys virtual to obtain a kind of Gfx
}

void Node::initGfx(Gfx& g)
{
	Node* n = this->child;

	while (n != NULL)
	{
		n->initGfx(g);

		n = n->next;
	}
}

// NONMATCHING - Missing the print statement
void Node::add(Node* n)
{
	if (n->parent != NULL)
	{
		// "Node already has parent" print here
	}

	n->next = 0;
	n->parent = this;

	if (this->child == NULL)
	{
		this->child = n;
	}
	else
	{
		Node* c = this->child;
		while (c->next != 0) {
			c = c->next;
		}
		c->next = n;
	}
}

// NONMATCHING - This is probably VERY wrong, and missing the print...
void Node::remove(Node* n)
{
	if (n->parent != this)
	{
		// "Not Node's parent" print
	}

	Node* c = this->child;
	Node* pr = 0;

	// Removal process
	while (c)
	{
		// If the child node is equal to the node we want..
		if (c == n)
		{
			if (pr)
			{
				// If prev node was set, this node's child will be n's next node
				this->child = n->next;
			}
			else
			{
				// this cant possibly be right...
				pr->next = n->next;
			}

			// Fake? Does this actually use a real goto?
			goto done;
		}

		// Store the current node as the previous one
		pr = c;

		// Update the current node to the next node.
		c = c->next;
	}

done:
	n->parent = 0;
}
