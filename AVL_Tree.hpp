#pragma once 
#include<iostream>
#include<utility>
using namespace std;
template<class K, class V>
struct AVLTreeNode{// AVLTree节点结构
  AVLTreeNode<K,V>* _left;
  AVLTreeNode<K,V>* _right;
  AVLTreeNode<K,V>* _parent;
  int _bf; //平衡因子
  pair<K,V> _kv;//节点信息
  AVLTreeNode( const std::pair<K,V>& kv )
    :_left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_bf(0)
    ,_kv(kv){}

};

template<class K, class V>
class AVLTree{
  public: 
    typedef AVLTreeNode<K,V> Nodetype;
    bool Insert(const pair<K,V>& kv){
      //按照二叉搜索树的规则插入
      if( !_root ){
        _root = new Nodetype(kv);
        return true;
      }
      Nodetype* parent = nullptr;
      Nodetype* cur = _root;
      while(cur){
        parent = cur;
        if(kv.first > (cur ->_kv).first){
          cur =cur ->_right;
        }else if(kv.first < (cur ->_kv).first){
          cur = cur ->_left;
        }else{
          return false;
        }
      }
      cur = new Nodetype(kv);
      if( (cur ->_kv).first > (parent ->_kv).first ){
        parent ->_right = cur;
      }else{
        parent ->_left = cur;
      }
      cur ->_parent = parent;
      
      //(1)更新平衡因子
      while(parent){
        if(cur == parent ->_right){
          parent ->_bf ++;
        }else{
          parent ->_bf --;
        }
        
        if(parent ->_bf == 0){
          //以parent为根节点的子树插入节点后高度不变，不会影响更上层的节点的平衡因子。
          break;
        }else if(parent ->_bf == 1 || parent ->_bf == -1){
          //以parent为根节点的子树插入节点后高度变化，但不需要调整，应该继续观察更上层节点
          parent  = parent ->_parent;
          cur =cur ->_parent;
        }else if(parent ->_bf == 2 || parent ->_bf == -2){
          //以parent为根节点的子树插入节点后高度失调，需要根据不同情况进行调整
          if(parent ->_bf == 2){
            if(cur ->_bf == 1){
              RotateL(parent);//左单旋
            }else{
              RotateRL(parent);//右左双旋
            }
          }else{
            if(cur ->_bf == -1){
              RotateR(parent);//右单旋
            }else{
              RotateLR(parent);//左右双旋
            }
          }
          //调节完后，parent的平衡因子与插入节点前的平衡因子一样。对上层不会再有影响
          break;  
        }
        
      }//while更新平衡因子
      return true;
    }//inseart
    
    void RotateL(Nodetype* parent){
      Nodetype* subR = parent ->_right;
      Nodetype* subRL = subR ->_left;
      Nodetype* pparent = parent ->_parent;
      parent ->_right = subRL;
      if(subRL)
        subRL ->_parent = parent; 
      parent ->_parent = subR;
      subR ->_left = parent;
      subR ->_parent = pparent;
      if(parent == _root){
        _root = subR;
      }else{
        if(parent == pparent ->_left){
          pparent ->_left = subR;
        }else{
          pparent ->_right = subR;
        }
      }
      //更新平衡因子
      parent ->_bf = subR ->_bf = 0;
    }
    void RotateR(Nodetype* parent){
      Nodetype* subL = parent ->_left;
      Nodetype* subLR = subL ->_right;
      Nodetype* pparent = parent ->_parent;

      parent ->_left = subLR;
      if(subLR)
        subLR ->_parent = parent;
      
      subL ->_right = parent;
      parent ->_parent = subL;
      subL ->_parent = pparent;

      if(parent == _root){
        _root = subL;
      }else{
        if(pparent ->_left == parent){
          pparent ->_left = subL;
        }else{
          pparent ->_right = subL;
        }
      }
      //更新平衡因子
      parent ->_bf = subL ->_bf = 0;
    }
    
    void RotateRL(Nodetype* parent){
      Nodetype* subR = parent ->_right;
      Nodetype* subRL = subR ->_left;
      int bf = subRL ->_bf;
      RotateR(parent ->_right);
      RotateL(parent);
      
      if(bf == -1){
        parent ->_bf = 0;
        subR ->_bf = 1;
        subRL ->_bf = 0;
      }else if(bf == 1){
        subR ->_bf = 0;
        parent ->_bf = -1;
        subRL ->_bf = 0;
      }else if(bf == 0){
        subR ->_bf = 0;
        parent ->_bf = 0;
        subRL ->_bf = 0;
      }
    }
    

    void RotateLR(Nodetype* parent){
      Nodetype* subL = parent ->_left;
      Nodetype* subLR = subL ->_right;
      int bf = subLR ->_bf;
      RotateL(parent ->_left);
      RotateR(parent);
      
      if(bf == 1){
        parent ->_bf = 0;
        subL ->_bf = -1;
        subLR ->_bf = 0;
      }else if(bf == -1){
        parent ->_bf = 1;
        subL ->_bf = 0;
        subLR ->_bf = 0;
      }else{
        parent ->_bf = 0;
        subL ->_bf = 0;
        subLR ->_bf = 0;
      }
    }
    void _InOrder(Nodetype* root){
      if(root == nullptr){
        return;
      }
      _InOrder(root ->_left);
      cout << (root ->_kv).first << ":" <<(root ->_kv).second <<endl;
      _InOrder(root ->_right);
    }
    void Inorder(){
      _InOrder(_root);
    }
    int Height(Nodetype* root){
      if(root == nullptr){
        return 0;
      }
      int LeftHeight = Height(root ->_left);
      int RightHeight = Height(root ->_right);
      return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
    }
    bool _IsBalance(Nodetype* root){
      if(!root)
        return true;

      int LeftHeight = Height(root ->_left);
      int RightHeight = Height(root ->_right);
      int gap = RightHeight - LeftHeight;
      if(gap == 2 || gap == -2){
        return false;
      }
      return _IsBalance(root ->_left) && _IsBalance (root ->_right);
    }
    bool IsBalance(){
      return _IsBalance(_root);
    }
  private:
    Nodetype* _root = nullptr;//根节点
};
