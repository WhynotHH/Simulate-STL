#pragma once
#include <vector>
namespace lzh{
	template<class T>
	struct less{//�º���
		bool operator()(const T& A , const T& B){return A < B;} 
	};
	template<class T>
	struct greater{//�º���
		bool operator()(const T& A , const T& B){return A > B;} 
	};
	template <class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue{
	public:
		bool empty(){return _con.empty();}
		int size(){return _con.size();}
		T& top(){return _con.front();}
		void push(T x){
			// O(logN)
			//��β���������������ϵ���
			_con.push_back(x);
			Adjust_up(_con.size() - 1);//���ϵ���
		}
		void pop(){
			// O(logN)
			//�Ƚ�����λԪ�أ� ��ɾ��βԪ�أ� �ٴ���Ԫ�ؿ�ʼ���µ���
			swap(_con[0] , _con[ _con.size() - 1 ]);
			_con.pop_back();
			Adjust_down(0);//���µ���
		}
		void Adjust_up(int child){//���ϵ���
			int parent = (child - 1) / 2;
			Compare compare;
			while(child > 0){
				if( compare(_con[parent] , _con[child]) ){
					swap(_con[parent] , _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}else{
					break;
				}
			}
		}
		void Adjust_down(size_t parent = 0){//���µ���
			size_t child = parent * 2 + 1;
			Compare compare;
			while(child < _con.size()){
				if( child + 1 < _con.size() && compare(_con[child] , _con[child + 1]) ){
					child++;
				}
				if( compare(_con[parent] , _con[child]) ){
					swap(_con[parent] , _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}else{
					break;
				}
			}
		}
	private:
		Container _con;
	};


}