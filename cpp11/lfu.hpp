/***************************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * @author duanbing(duanbing@baidu.com) 
 *
 **************************************************************************/


/**
 * @filename lfu.hpp
 * @desc 
 * @create time 2018-03-16 20:37:51
**/
#include <map>
#include <cstdio>
class LFUCache {
public:
    LFUCache(int capacity): cap(capacity),size(0) {
    	head = tail = nullptr;   
    }
    
    int get(int key) {
    	if(val.count(key)  == 0) return -1;
		link_node *cur = val[key];
		cur->count++;
		swap(cur);
		return cur->value;
    }

	void put(int key, int value) {
		//if existed
		if(val.count(key) != 0) {
			val[key]->value = value;
			val[key]->count ++;
			swap(val[key]);
			return ;
		}
		//  
		if(size < cap) {
			link_node *cur = new link_node();
			cur->count = 1;
			cur->key = key;
			cur->value = value;
			cur->prev = tail;
			if(tail)tail->next = cur;
			tail = cur;
			if(!head) head = cur;
			val[key] = cur;
			size += 1;
		} else if(size >= cap && size != 0) {
		    tail->count = 1;
			tail->value = value;
			val.erase(val.find(tail->key));
			tail->key = key;
			val[key] = tail; 
		}
		swap(tail);
	}
	void show() {
		link_node *cur = head;
		while(cur) {
			printf("(k=%d,v=%d,c=%d) ",cur->key,cur->value,cur->count);
			cur = cur->next;
		}
		std::cout << std::endl;
	}
private:
	struct link_node {
		int count;
		int value;
		int key;
		link_node *next, *prev;
		link_node():count(0), value(0), next(nullptr), prev(nullptr) {
		}
	}; 
	void swap(link_node *cur) {
		if(!cur) return ;
		while(cur->prev != nullptr) {
			link_node *prev = cur->prev;
			bool ok = (prev->count < cur->count);
			if(ok) {
				//swap prev and cur
				prev->next = cur->next;
				if(cur->next != nullptr) {
					cur->next->prev = prev;
				}
				cur->prev = prev->prev;
				if(prev->prev != nullptr) {
					prev->prev->next = cur;
				}
				prev->prev = cur; 
				cur->next = prev;  
			} else {
				break;
			}
		}
		while(head->prev != nullptr) head = head->prev;
		while(tail->next != nullptr) tail = tail->next;
	}
	link_node *head,*tail;
	std::map<int,link_node*> val;
	int cap;
	int size;
};
