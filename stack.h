namespace lzh{
template <class T,class Container>
class stack{
public:
	void push( const T& x ){_con.push_back(x);}
	void pop(){_con.pop_back();}
	bool empty(){return _con.empty();}
	size_t size(){return _con.size();}
	T& top(){return _con.back();}
private:
	Container _con;
};
}