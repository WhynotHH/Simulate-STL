namespace lzh{
template <class T,class Container>
class queue{
public:
	void push( const T& x ){_con.push_back(x);}
	void pop(){_con.pop_front();}
	bool empty(){return _con.empty();}
	size_t size(){return _con.size();}
	T& back(){return _con.back();}
	T& front(){return _con.front();}
private:
	Container _con;
};
}