#include <dolphin/types.h>

class Gfx;

class Node {
public:
	// Constructor (gets inlined and placed in another TU because header...)
	Node() 
	{
		this->child = 0;
		this->parent = 0;
		this->next = 0;
		this->_10 = 0;
		this->hidden = false;
		this->magic = 0x12345678;
	}

	// Destructor
	virtual ~Node();

	// Loop node callers
	// It will call (name) function on this node's child and then
	// repeat to the next node until that node is null.
	virtual void update();
	virtual void draw(Gfx& g);
	virtual void initGfx(Gfx& g);
	virtual void procEvent(int id);

	// Performs a check on the Node's magic
	// Typically the magic should always be 0x12345678
	void checkMagic();

	// This obtains graphics from a sys function and calls the other initGfx
	void initGfx();

	// Adds a node (n)
	void add(Node* n);

	// Removes a node (n)
	void remove(Node* n);

public:
	Node* next;		// The next node
	Node* parent;	// The parent node
	Node* child;	// The child node
	int _10;		// Unused?
	long magic;		// The magic of the node (always 0x12345678 until destructed)
	bool hidden;	// Whether the node is hidden (excluded from draw calls on that node)
};
