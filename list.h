#pragma once
namespace lzh{
	template<class T>
	struct __list_node{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _date;
		__list_node(const T& x = T())
			:_date(x)
			,_next(nullptr)
			,_prev(nullptr)
		{}
	};
	template <class T, class Ref, class Ptr>
	struct __list_iterator{
		typedef __list_node<T> Node;
		Node* _node;
		__list_iterator(Node* node):_node(node){//构造函数
			
		}
		Ref operator*(){//运算符*重载
			return _node ->_date;
		}
		Ptr operator->(){//->运算符重载
			return &_node->_data;
		}
		__list_iterator<T,Ref,Ptr>& operator++(){//运算符(前置)++重载
			_node = _node ->_next;
			return *this;
		}
		__list_iterator<T,Ref,Ptr>& operator--(){//运算符(前置)--重载
			_node = _node ->_prev;
			return *this;
		}
		__list_iterator<T,Ref,Ptr> operator++(int){//运算符(后置)++重载
			__list_iterator<T,Ref,Ptr> tem(_node);
			_node = _node ->_next;
			return tem;
		}
		__list_iterator<T,Ref,Ptr> operator--(int){//运算符(后置)--重载
			__list_iterator<T, Ref, Ptr> tem(_node);
			_node = _node ->_prev;
			return tem;
		}
		bool operator!=(const __list_iterator<T,Ref,Ptr>& it){//运算符!=重载
			if(_node != it._node){
				return true;
			}
			return false;
		}
		bool operator==(const __list_iterator<T,Ref,Ptr>& it){//运算符==重载
			if( _node == it._node){
				return true;
			}
			return false;
		}
	};

	template<class T>
	class list{
	public:
		typedef __list_node<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		list(){
			//带头结点双向循环链表
			head = new Node;
			head ->_next = head;
			head ->_prev = head;
			head ->_date = T();
		}
		list(const list<T>& lt){
			head = new Node;
			head ->_next = head;
			head ->_prev = head;
			list<T> :: const_iterator it = lt.begin();
			while(it != lt.end()){
				push_back(*it);
				++it;
			}
		}
		~list(){//析构函数
			clear();
			delete head;
			head = nullptr;
		}
		iterator begin(){
			return iterator(head ->_next);
		}
		iterator end(){
			return iterator(head);
		}
		const_iterator begin()const{
			return const_iterator(head ->_next);
		}
		const_iterator end()const{
			return const_iterator(head);
		}
		void insert(iterator pos, const T& x){//pos位置添加元素
			Node* newnode = new Node(x);
			Node* prev = pos._node ->_prev;
			Node* cur = pos._node;
			
			//连接
			prev ->_next = newnode;
			newnode ->_prev = prev;
			cur ->_prev = newnode;
			newnode ->_next = cur;
		}
		void erase(iterator& pos){//删除pos位置的节点
			assert(pos != end());//不能删除头结点
			Node* cur = pos._node;
			Node* prev = cur ->_prev;
			Node* next = cur ->_next;
			delete cur;
			next ->_prev = prev;
			prev ->_next = next;
		}
		void push_back(const T& x ){//尾插
			insert(end(),x);
		}
		void push_front(const T& x){//头插
			insert(begin(), x);
		}

		void pop_front(){//头删
			erase(begin());
		}
		void pop_back(){//尾删
			erase(--end());
		}
		void clear(){//清空所有元素
			while( begin() != end() ){
				erase( begin() );
			}
		}
		list<T>& operator=(list<T> lt){//运算符= 重载
			swap(head,lt.head);
			return *this;
		}
	private:
		Node* head;
	};
}