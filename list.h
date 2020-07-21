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
		__list_iterator(Node* node):_node(node){//���캯��
			
		}
		Ref operator*(){//�����*����
			return _node ->_date;
		}
		Ptr operator->(){//->���������
			return &_node->_data;
		}
		__list_iterator<T,Ref,Ptr>& operator++(){//�����(ǰ��)++����
			_node = _node ->_next;
			return *this;
		}
		__list_iterator<T,Ref,Ptr>& operator--(){//�����(ǰ��)--����
			_node = _node ->_prev;
			return *this;
		}
		__list_iterator<T,Ref,Ptr> operator++(int){//�����(����)++����
			__list_iterator<T,Ref,Ptr> tem(_node);
			_node = _node ->_next;
			return tem;
		}
		__list_iterator<T,Ref,Ptr> operator--(int){//�����(����)--����
			__list_iterator<T, Ref, Ptr> tem(_node);
			_node = _node ->_prev;
			return tem;
		}
		bool operator!=(const __list_iterator<T,Ref,Ptr>& it){//�����!=����
			if(_node != it._node){
				return true;
			}
			return false;
		}
		bool operator==(const __list_iterator<T,Ref,Ptr>& it){//�����==����
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
			//��ͷ���˫��ѭ������
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
		~list(){//��������
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
		void insert(iterator pos, const T& x){//posλ�����Ԫ��
			Node* newnode = new Node(x);
			Node* prev = pos._node ->_prev;
			Node* cur = pos._node;
			
			//����
			prev ->_next = newnode;
			newnode ->_prev = prev;
			cur ->_prev = newnode;
			newnode ->_next = cur;
		}
		void erase(iterator& pos){//ɾ��posλ�õĽڵ�
			assert(pos != end());//����ɾ��ͷ���
			Node* cur = pos._node;
			Node* prev = cur ->_prev;
			Node* next = cur ->_next;
			delete cur;
			next ->_prev = prev;
			prev ->_next = next;
		}
		void push_back(const T& x ){//β��
			insert(end(),x);
		}
		void push_front(const T& x){//ͷ��
			insert(begin(), x);
		}

		void pop_front(){//ͷɾ
			erase(begin());
		}
		void pop_back(){//βɾ
			erase(--end());
		}
		void clear(){//�������Ԫ��
			while( begin() != end() ){
				erase( begin() );
			}
		}
		list<T>& operator=(list<T> lt){//�����= ����
			swap(head,lt.head);
			return *this;
		}
	private:
		Node* head;
	};
}