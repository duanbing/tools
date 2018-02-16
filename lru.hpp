/***************************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * @author duanbing(duanbing@baidu.com) 
 *
 **************************************************************************/


/**
 * @filename 146_lru.cc
 * @desc  leetcode problem 146 
 * @create time 2018-02-15 15:40:04
**/
#include <cstdio>
#include <map>
#include <queue>

using namespace std;


class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
	~LRUCache() {
		cap = 0;
    	key_node_map.clear();
		while(head) {
			node *tmp = head;
			head = head->next;
			delete tmp;
		}
		head = nullptr;
		tail = nullptr;
		node_size = 0;
	}
    
    int get(int key) {
		auto it = key_node_map.find(key);
		if(it != key_node_map.end()) {
			node* cur = it->second;	
			int value = cur->value;
			move_to_head(cur,cur->key, value);
			return value;
        }
        return -1;
    }
    
    void put(int key, int value) {
		auto it = key_node_map.find(key);
		if(it != key_node_map.end()) {
			//update value and move the node to head
			node* cur = it->second;
			move_to_head(cur,key,value);
			return;
		} 

		if(node_size < cap) {	
			node_size += 1;
			// insert into head
			node *cur = new node{key,value,nullptr,nullptr};
			if(head==nullptr) {
				head = cur;
				tail = cur;
				key_node_map.insert(pair<int,node*>(key,cur));
				return;
			}
			cur->next= head;
			head->prev = cur;
			head = cur;
			key_node_map.insert(pair<int,node*>(key,cur));
			return;
		}

		// remove: move the last one to head, and update the value, tail maybe be changed when call move_to_head
		// find and erase the tail node's key 
		it = key_node_map.find(tail->key);
		if(it != key_node_map.end()) key_node_map.erase(it);
		move_to_head(tail,key,value); 
		key_node_map.insert(pair<int,node*>(key,head));
    }
    struct node {
		int key;
		int value;
		struct node* prev;
		struct node* next;
		~node() {
			key = value = 0;
			prev = next = nullptr;
		}
	}; 

private:
    int cap;
    map<int, node*> key_node_map;
	node* head{nullptr};
	node* tail{nullptr};
    int node_size = 0;
	void move_to_head(node* cur,int key, int value) {
		if(cur->prev == nullptr) {
			//locate at the head, do nothing
			cur->value = value;
			cur->key = key;
			return;
		}
		if(cur->next == nullptr) {
			//locate at the tail
			tail = cur->prev;
			cur->next = head;
			head->prev = cur;
			cur->value = value;
			cur->key = key;
			head = cur;
			head->prev = nullptr;
			tail->next = nullptr;
			return;
		}

		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
		cur->next = head;
		head->prev = cur;
		cur->value = value;
		cur->key = key;
		head = cur;
		head->prev = nullptr;
	}
	void print() {
		node *tmp = head;
		printf("new print link:");
		while(tmp) {
			printf("%d ",tmp->value);
			tmp = tmp->next;
		}
		printf("\nprint map:");
		for(auto it=key_node_map.begin();it!=key_node_map.end();it++) {
			printf("[%d=%d] ",it->second->key, it->second->value);
		}
		printf("\n");
	}
};
