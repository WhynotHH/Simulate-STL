#pragma once
#include <vector>
namespace lzh{
	template<class T>
	struct less{//仿函数
		bool operator()(const T& A , const T& B){return A < B;} 
	};
	template<class T>
	struct greater{//仿函数
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
			//先尾插在数组中再向上调整
			_con.push_back(x);
			Adjust_up(_con.size() - 1);//向上调整
		}
		void pop(){
			// O(logN)
			//先交换首位元素， 再删除尾元素， 再从首元素开始向下调整
			swap(_con[0] , _con[ _con.size() - 1 ]);
			_con.pop_back();
			Adjust_down(0);//向下调整
		}
		void Adjust_up(int child){//向上调整
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
		void Adjust_down(size_t parent = 0){//向下调整
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