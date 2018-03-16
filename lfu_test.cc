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
#include <iostream>
#include <map>

#include "lfu.hpp"
using namespace std;

int main() {
	LFUCache cache = LFUCache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	cache.show();
	int t = cache.get(1);       // returns 1
	cout << t << endl;
	cache.put(3, 3);    // evicts key 2
	cache.show();
	t = cache.get(2);       // returns -1 (not found)
	cout << t << endl;
	t = cache.get(3);       // returns 3.
	cout << t << endl;
	cache.show();
	cache.put(4, 4);    // evicts key 1.
	cache.show();
	t = cache.get(1);       // returns -1 (not found)
	cout << t << endl;
	t = cache.get(3);       // returns 3
	cout << t << endl;
	t = cache.get(4);       // returns 4
	cout << t << endl;
	return 0;
}
