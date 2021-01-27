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
#include <string>
#include "lru.hpp"

using namespace std;

/**
 * Your LRUCache object will be instantiated and called as such:
 */
int main(int argc, char *argv[]) {
	LRUCache<> *cache = new LRUCache<>( 2 /* capacity */ );
	cache->put(1, 1);
	cache->put(2, 2);
	cache->get(1);       // returns 1
	cache->put(3, 3);    // evicts key 2
	cache->get(2);       // returns -1 (not found)
	cache->put(4, 4);    // evicts key 1
	cache->get(1);       // returns -1 (not found)
	cache->get(3);       // returns 3
	cache->get(4);       // returns 4
	delete cache;
	
	LRUCache<string, int> *ca = new LRUCache<string,int>(3);
	ca->put("1", 1);
	ca->put("2", 2);
	printf("get(1) = %d\n",ca->get("1"));
	ca->put("3", 3);
	ca->get("2");
	ca->put("4", 4);
	ca->get("1");
	ca->get("3");
	ca->get("4");
	delete ca;

	return 0;
}
