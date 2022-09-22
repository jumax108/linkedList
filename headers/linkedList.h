#pragma once

#include "dump/headers/dump.h"
#pragma comment(lib, "lib/dump/dump")

#include "objectFreeList/headers/objectFreeList.h"

template<typename T>
class CLinkedList {

private:
	struct stNode {

	public:
		inline stNode* operator=(const stNode& node);
		inline bool operator==(const stNode& node);
		inline bool operator!=(const stNode& node);

	private:
		T _value;
		stNode* _prev;
		stNode* _next;
		friend class CIterator;
		friend class CLinkedList;
	};

public:
	class CIterator {
	public:
		CIterator();
		CIterator(const stNode* node);

		inline CIterator& operator=(const stNode& node);
		inline CIterator& operator=(const CIterator& iter);
		inline T& operator*();

		inline CIterator& operator++();
		inline CIterator& operator--();

		inline bool operator!=(const CIterator& iter);
		inline bool operator==(const CIterator& iter);

		inline T& operator->() {
			return _node->_value;
		}

	private:
		stNode* _node;
		friend class CLinkedList;
	};

public:


	CLinkedList();

	void push_front(
		const T value // 저장할 값
	);
	void push_back(
		const T value // 저장할 값
	);

	bool insert(
		const T value, // 값을 저장할 데이터
		CIterator& prev  // 이 노드의 다음 노드로 저장됩니다.
	);

	CIterator erase(
		CIterator& iter // 지울 노드를 전달합니다.
	);

	void clear();

	inline CIterator begin() {
		return CIterator(_head._next);
	}

	inline CIterator end() {
		return CIterator(&_tail);
	}

	~CLinkedList();

private:
	stNode _head;
	stNode _tail;
	CObjectFreeList<stNode> _nodeFreeList;
	

};

template<typename T>
CLinkedList<T>::CLinkedList(): _nodeFreeList(false, false){
	
	_head._prev = nullptr;
	_head._next = &_tail;

	_tail._prev = &_head;
	_tail._next = nullptr;
}

template<typename T>
CLinkedList<T>::~CLinkedList() {
	clear();
}

template<typename T>
bool CLinkedList<T>::insert(T value, CLinkedList<T>::CIterator& parent) {

	if (parent._node == nullptr) {
		return false;
	}

	stNode* node = _nodeFreeList.allocObject();

	node->_value = value;
	node->_prev = parent._node;

	parent._node->_next->_prev = node;
	node->_next = parent._node->_next;
	parent._node->_next = node;
	
	return true;
}

template<typename T>
void CLinkedList<T>::push_front(const T value) {

	stNode* node = _nodeFreeList.allocObject();

	node->_value = value;
	node->_prev = &_head;
	node->_next = _head._next;

	_head._next->_prev = node;
	_head._next = node;
}

template<typename T>
void CLinkedList<T>::push_back(const T value) {

	stNode* node = _nodeFreeList.allocObject();

	node->_value = value;
	node->_prev = _tail._prev;
	node->_next = &_tail;

	_tail._prev->_next = node;
	_tail._prev = node;
}

template<typename T>
void CLinkedList<T>::clear() {
	for (CLinkedList<T>::CIterator iter = begin(); iter != end(); ) {
		iter = erase(iter);
	}
}

template<typename T>
typename CLinkedList<T>::CIterator CLinkedList<T>::erase(
	CIterator& iter // 지울 노드를 전달합니다.
) {

	CLinkedList<T>::stNode* node = iter._node;
	if (node == nullptr) {
		return end();
	}

	CLinkedList<T>::stNode* child = node->_next;

	node->_next->_prev = node->_prev;
	node->_prev->_next = node->_next;

	CIterator nextIter = ++iter;

	_nodeFreeList.freeObject(node);

	iter._node = nullptr;

	return nextIter;
}

template <typename T>
typename CLinkedList<T>::stNode* CLinkedList<T>::stNode::operator=(const stNode& node){

	_value	= node._value;
	_prev = node._prev;
	_next	= node._next;

	return this;
}

template <typename T>
bool CLinkedList<T>::stNode::operator==(const stNode& node) {
	return	memcmp(&_value, &node._value, sizeof(T)) == 0 &&
			_prev == node._prev &&
			_next  == node._next;
}

template <typename T>
bool CLinkedList<T>::stNode::operator!=(const stNode& node) {
	return	!this->operator==(node);
}

template <typename T>
CLinkedList<T>::CIterator::CIterator() {
	_node = nullptr;
}

template <typename T>
CLinkedList<T>::CIterator::CIterator(const stNode* node) {
	_node = (stNode*)node;
}

template <typename T>
typename CLinkedList<T>::CIterator& CLinkedList<T>::CIterator::operator=(const stNode& node) {
	_node->operator=(node);
	return *this;
}
template <typename T>
typename CLinkedList<T>::CIterator& CLinkedList<T>::CIterator::operator=(const CIterator& iter) {
	_node->operator=(*iter._node);
	return *this;
}

template <typename T>
T& CLinkedList<T>::CIterator::operator*() {
	return _node->_value;
}

template <typename T>
typename CLinkedList<T>::CIterator& CLinkedList<T>::CIterator::operator++() {
	_node = _node->_next;
	return *this;
}

template <typename T>
typename CLinkedList<T>::CIterator& CLinkedList<T>::CIterator::operator--() {
	_node = _node->_prev;
	return *this;
}

template <typename T>
bool CLinkedList<T>::CIterator::operator!=(const CIterator& iter) {
	return !this->operator==(iter);
}

template <typename T>
bool CLinkedList<T>::CIterator::operator==(const CIterator& iter) {
	return *(this->_node) == *iter._node;
}