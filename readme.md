
# linkedList

## 사전 세팅
- dump
	- 덤프 생성을 위해 사용 전에 CDump 객체 생성자 호출 필요

## 함수
 - class CLinkedList
	 - void push_front(T)
		 > 가장 앞의 노드에 데이터 삽입
	 - void push_back(T)
		 > 가장 뒤의 노드에 데이터 삽입
	 - bool insert(T, CIterator&)
		 > 전달받은 iterator에 해당하는 노드의 다음 노드로 데이터 삽입 <br>
		 > 이상한 iterator가 전달되면 실패
     - CIterator erase(CIterator&)
	     > 전달받은 노드 제거 후, 다음 노드 전달
	 - void clear()
		 > 모든 노드 제거
	 - CIterator begin()
		 > 첫번째 노드의 iterator 전달
	 - CIterator end()
		 > 마지막 노드의 iterator 전달
- class CLinkedList<T>::CIterator
	-  CIterator& operator=(stNode&)
	    CIterator& operator=(CIterator&)
	    > 전달 받은 데이터로 클래스 초기화
	 - T&  operator*()
	    T& operator->()
	    > iterator에 있는 T 타입 데이터 리턴
	 - CIterator& operator++()
	    > iterator의 다음 iterator 리턴
	 - CIterator& operator--()
	    > iterator의 이전 iterator 리턴
     - bool operator!=(CIterator&)
       bool operator==(Citerator&)
	     > iterator가 같은지 다른지 비교
## 사용법
```cpp

CDump dump;

void main() {

	CLinkedList<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);

    for(CLinkedList<int>::CIterator iter = li.begin();
		    iter != li.end();
		    ++iter){

		printf("%d", *iter);

	}

}
```
