#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;
namespace lzh{
	class string{
	public:
		typedef char* iterator;//������
		string(char* str = nullptr){//���캯��
			_size = strlen( str );
			_capacity = _size;
			_str = new char[ _capacity + 1 ];
			strcpy(_str,str);
		}
		void swap(string& tem){//����tem �� *this����������
			::swap(_size,tem._size);
			::swap(_capacity,tem._capacity);
			::swap(_str,tem._str);
		}
		string(const string& s) :_str(nullptr){//�������캯��
			string tem(s._str);
			swap(tem);
		}

		~string(){
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		void reserve(size_t newcapacity = 0){//���ݵ�newcapacity
			if(newcapacity){
				//�����¿ռ�
				char* newstr = new char[newcapacity + 1];//��'\0'Ԥ���ռ�
				strcpy(newstr, _str);//����
				delete[] _str;//�ͷžɿռ�
				//���¶�Ӧ��ֵ
				_capacity = newcapacity;
				_str = newstr;
			}
		}
		void push_back(char ch){//����һ���ַ�
			if(_size == _capacity){//����
				//_capacity ��¼������Ч�ַ��ĳ��� �����ַ�����ʱ ֵΪ��
				size_t newcapacity = (_capacity == 0) ? 1 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size ] = ch;
			_size++;
			_str[_size] = '\0';
		}
		
		void append(const char* str){//����һ���ַ���
			size_t len = strlen(str);
			if(_size + len > _capacity){//����
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
				//���ڵ���_size
				//�ж��Ƿ����_capacity,��Ҫ����
				if (n > _capacity){
					reserve(n);
				}
				//��_str��size��ʼ��n - 1��ֵΪ�ض���Ԫ��ch��_str[n]��λ�ø�ֵΪ'\0'
				for (size_t i = _size; i < n; i++){
					_str[i] = ch;
				}
				_str[n] = '\0';
				//����_size��ֵ
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
		char& operator[](size_t i){//�����[]����
			assert(i < _size);
			return _str[i];
		}
		const char& operator[](size_t i)const{//���const����
			assert(i < _size);
			return _str[i];
			
		}
		string& operator=(const string s ){//ע�����ﴫ�Ĳ�������
			
			string tem(s._str);//���캯��
			swap(tem); //�뿽�����첻ͬ�� tem�����ں���������ʱ���ͷŵ�ԭ��_str������
			
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
		size_t _capacity;//�ܴ���ٸ���Ч�ַ�     '\0'��������Ч�ַ�
		size_t _size;//�Ѿ����˶��ٸ���Ч�ַ�
		static size_t npos;
	};
	size_t string::npos = -1;
	
	
	ostream& operator<<(ostream& out , const string& s){//��������<<���ؿ��Բ�����Ԫ����
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