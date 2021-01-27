/***************************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * @author duanbing(duanbing@baidu.com) 
 *
 **************************************************************************/


/**
 * @filename radix_sort.cc
 * @desc 
 * @create time 2018-03-05 22:38:28
 **/
#include <cstdio>

using namespace std;

vector<int> radix_sort(vector<int>& nums) {

	unsigned int pos[11] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,UINT_MAX};

	vector<vector<int>> vec(10);
	int idx = 0;
	for(int &c : nums) {
		while(c >= pos[idx]) idx++;
	}

	for(int i=1;i<=idx;i++) {
		for(int c : nums) {
			int idx = (c/pos[i-1])%10;

			vec[idx].push_back(c);
		}

		int i2 = 0;
		for(int j=0;j<10;j++) {
			for(int &c:vec[j]) {
				nums[i2++]=c;

			}
			vec[j].clear();
		}



	}

}
