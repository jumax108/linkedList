#include "../header/linkedList.h"
#pragma comment(lib, "../release/linkedList")

struct stNode {
	int _value;
};

int main() {

	CLinkedList<stNode> list;

	list.push_back(stNode());
	CLinkedList<stNode>::CIterator iter = list.begin();
	list.erase(iter);

	list.push_front(stNode());

	return 0;
}

