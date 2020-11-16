#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;
namespace lzh{
	class string{
	public:
		typedef char* iterator;//迭代器
		string(char* str = nullptr){//构造函数
			_size = strlen( str );
			_capacity = _size;
			_str = new char[ _capacity + 1 ];
			strcpy(_str,str);
		}
		void swap(string& tem){//交换tem 和 *this的所有数据
			::swap(_size,tem._size);
			::swap(_capacity,tem._capacity);
			::swap(_str,tem._str);
		}
		string(const string& s) :_str(nullptr){//拷贝构造函数
			string tem(s._str);
			swap(tem);
		}

		~string(){
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		void reserve(size_t newcapacity = 0){//增容到newcapacity
			if(newcapacity){
				//申请新空间
				char* newstr = new char[newcapacity + 1];//给'\0'预留空间
				strcpy(newstr, _str);//复制
				delete[] _str;//释放旧空间
				//更新对应的值
				_capacity = newcapacity;
				_str = newstr;
			}
		}
		void push_back(char ch){//插入一个字符
			if(_size == _capacity){//增容
				//_capacity 记录的是有效字符的长度 所以字符串空时 值为零
				size_t newcapacity = (_capacity == 0) ? 1 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size ] = ch;
			_size++;
			_str[_size] = '\0';
		}
		
		void append(const char* str){//插入一个字符串
			size_t len = strlen(str);
			if(_size + len > _capacity){//增容
				size_t newcapacity = _size + len;
				reserve(newcapacity);
			}
			strcpy(_str + _size,str);
			_size += len;
		}
		
		void insert(size_t pos,char ch){
			assert(pos < _size);
			if(_size == _capacity){
				size_t newcapacity = (_capacity == 0) ? 1 : _capacity * 2;
				reserve(newcapacity);
			}
			int i = _size;
			while(i >= (int)pos){
				_str[i + 1] = _str[i];
				i--;
			}
			_str[pos] = ch;
			_size++;
		}
		void insert(size_t pos,const char* str){
			size_t len = strlen(str);
			if( _size + len > _capacity ){
				size_t newcapacity = _size + len;
				reserve(newcapacity);
			}
			int i = _size;
			while(i >= (int)pos){
				_str[i + len] = _str[i];
				i--;
			}
			strncpy(_str + pos,str,len);
			_size +=len;
		}
		void resize(size_t n,char ch = '\0'){
			if(n < _size){
				_str[n] = '\0';
				_size = n; 
			}else{
				//大于等于_size
				//判断是否大于_capacity,需要扩容
				if (n > _capacity){
					reserve(n);
				}
				//将_str从size开始到n - 1赋值为特定的元素ch，_str[n]的位置赋值为'\0'
				for (size_t i = _size; i < n; i++){
					_str[i] = ch;
				}
				_str[n] = '\0';
				//更新_size的值
				_size = n;
			}
		}
		void erase(size_t pos, size_t len = npos ){
			if(pos + len >= _size ){
				_str[pos] = '\0';
				_size = pos;
			}else{
				size_t i = pos + len;
				while(i <= _size){
					_str[i - len] = _str[i];
					i++;
				}
				_size -= len; 
			}
		}
		size_t find(char ch,size_t pos){
			for(size_t i = 0; i < _size ;i++){
				if(_str[i] == ch){
					return i;
				}
			}
			return npos;
		}
		string& operator+=(char ch){
			this ->push_back(ch);
			return *this;
		}
		string& operator+=(const char* ch){
			this ->append(ch);
			return *this;
		}
		char& operator[](size_t i){//运算符[]重载
			assert(i < _size);
			return _str[i];
		}
		const char& operator[](size_t i)const{//针对const对象
			assert(i < _size);
			return _str[i];
			
		}
		string& operator=(const string s ){//注意这里传的不是引用
			
			string tem(s._str);//构造函数
			swap(tem); //与拷贝构造不同， tem将会在函数结束的时候，释放掉原来_str的内容
			
			return *this;
		}
		bool operator<(const string& s){
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}

		bool operator== (const string& s){
			int ret = strcmp( _str, s._str);
			return ret == 0;
		}
		bool operator!=(const string& s){
			return ! (*this == s);
		}
		bool operator<=(const string& s){
			return *this < s || *this == s;
		}
		bool operator>=(const string& s){
			return !(*this < s);
		}
		bool operator>(const string& s){
			return !(*this < s) && !(*this == s);
		}
		size_t size()const{
			return _size;
		}
		const char* c_str(){
			return  _str;
		}
		size_t capacity(){
			return  _capacity; 
		}
		iterator begin(){
			return _str;
		}
		iterator end(){
			return _str + size();
		}
	private:
		char* _str;
		size_t _capacity;//能存多少个有效字符     '\0'不属于有效字符
		size_t _size;//已经存了多少个有效字符
		static size_t npos;
	};
	size_t string::npos = -1;
	
	
	ostream& operator<<(ostream& out , const string& s){//输出运算符<<重载可以不是友元函数
		for(size_t i = 0; i < s.size(); i++){
			cout << s[i];
		}
		return out;
	}
	istream& operator>>(istream& in , string& s){
		char date;
		while(1){
			char ch;
			ch = in.get();
			if(ch == ' ' || ch == '\0' ){
				break;
			}else{
				s += ch;
			}
		}
		return in;
	}
	
}