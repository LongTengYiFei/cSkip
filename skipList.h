#include <vector>
#include <iostream> 
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <fstream>
#include <type_traits>
#include <time.h>

using namespace std;

float p = 0.5;

// ----- ----- ----- ----- ----- ----- ----- ----- -----

template<typename K, typename V>
class Node{
    public:
        Node() {} 
        Node(K k, V v, int); 
        ~Node();
        K get_key() const;
        V get_value() const;
        void set_value(V);
        vector<Node<K, V>*> forward_vec;
        K key;
        V value;
};

template<typename K, typename V>
Node<K, V>::Node(K k, V v, int level){
    this->key = k;
    this->value = v;
    forward_vec.resize(level+1);
    for(int i=0; i<=level; i++)
        forward_vec[i] = nullptr;
}


// ----- ----- ----- ----- ----- ----- ----- ----- -----

template<typename K, typename V>
class SkipList{
    public:
        SkipList(int);
        ~SkipList();
        V Search(K);
        void Insert(K, V);
        void Delete(K);
        
        int size();
        void display_SkipList();
        int randomLevel();

    private:
        int size;
        int max_level;
        int level;
        Node<K, V>* header;
};

template<typename K, typename V>
SkipList<K, V>::SkipList(int n){
    this->level = 1;
    this->size = 0;
    this->max_level = n;
    K k;
    V v;
    this->header = new Node<K, V>(k, v, this->max_level);
}

template<typename K, typename V>
V SkipList<K, V>::Search(K search_key){
    Node<K, V>* x = this->header;
    for(int i=this->level; i>=1; i--){
        while(x->forward_vec[i]->key < search_key){
            x = x->forward_vec[i];
        }
    }
    x = x->forward_vec[1];
    if(x->key == search_key)
        return x->value;
    return returnNullValue<V>();
}

template<typename K, typename V>
void SkipList<K, V>::Insert(K search_key, V new_value){
    vector<Node<K, V>*> update;
    update.resize(this->max_level + 1);

    Node<K, V>* x = this->header;
    for(int i=this->level; i>=1; i--){
        while(x->forward_vec[i]->key < search_key){
            x = x->forward_vec[i];
        }
        update[i] = x;
    }
    x = x->forward_vec[1];

    if(x->key == search_key)
        x->value = new_value;
    else{
        this->size++;

        int new_level = this->randomLevel();
        if(new_level > this->level){
            for(int i=this->level+1; i<=new_level; i++)
                update[i] = this->header;
            this->level = new-level;
        }

        x = new Node<K, V>(search_key, new_value, new_level);
        for(int i=1; i<=new_level; i++){
            x->forward_vec[i] = update[i]->forward_vec[i];
            update[i]->forward_vec[i] = x;
        }
    }
}   

template<typename K, typename V>
void SkipList<K, V>::Delete(K search_key){
    vector<Node<K, V>*> update;
    update.resize(this->max_level + 1);

    Node<K, V>* x = this->header;
    for(int i=this->level; i>=1; i--){
        while(x->forward_vec[i]->key < search_key){
            x = x->forward_vec[i];
        }
        update[i] = x;
    }
    x = x->forward_vec[1];

    if(x->key == search_key){
        this->size--;

        for(int i=1; i<=this->level; i++){
            if(update[i]->forward_vec[i] != x)
                break;
            update[i]->forward_vec[i] = x->forward_vec[i];// 穿透
        }
        delete x;

        while(this->level>1 && 
            this->header->forward_vec[this->level]==nullptr){
                this->level--;
            }
    }
}

template<typename K, typename V>
int SkipList<K, V>::randomLevel(){
    int new_level = 1;
    while(pRandom() < p)
        new_level ++;
    return min(new_level, this->max_level)
}

// ----- ----- ----- ----- ----- ----- ----- ----- -----
template<typename V>
V returnNullValue(){
    if(std::is_same<V, int>::value)
        return 0;
    if(std::is_same<V, float>::value)
        return 0;
    if(std::is_same<V, string>::value)
        return "";
}

float pRandom(){
    return rand()%100/(double)101;
}

