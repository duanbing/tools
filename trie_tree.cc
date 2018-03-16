/***************************************************************************
 *
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * @author duanbing(duanbing@baidu.com) 
 *
 **************************************************************************/


/**
 * @filename trie_tree.cc
 * @desc 
 * @create time 2018-03-08 01:06:39
**/

#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

struct trie_node {
	int mark;
	int next[255];
	trie_node(int m=0):mark(m){
		memset(next,0,sizeof(next));
	}
};
void build(vector<trie_node>& root,string word) {
	if(word.length()<=0) return;
	if(root.size() == 0) {
		root.push_back(trie_node());
	}
	int idx = 0;

	for(int i=0;i<word.length();i++) {
		trie_node cur = root[idx];
		if(cur.next[word[i]] == 0) {
			root[idx].next[word[i]] = root.size();
			root.push_back(trie_node(1));
		}
		idx = root[idx].next[word[i]];
	}
	root[idx].mark = 1;
}

int find(vector<trie_node>& root,string word) {
	int idx = 0;
	for(int i=0;i<word.length();i++) {
		trie_node cur = root[idx];
		if(cur.next[word[i]] == 0) {
			cout << word[i] << endl;
			return 0;
		}
		idx = cur.next[word[i]];
	}
	return root[idx].mark;
}

int main() {
	vector<trie_node>root;
	vector<string> vs = {"bbaabaabaaaaabaababaaaaababb","aabbaaabaaabaabaaaaaabbaaaba","babaababbbbbbbaabaababaabaaa","bbbaaabaabbaaababababbbbbaaa","babbabbbbaabbabaaaaaabbbaaab","bbbababbbbbbbababbabbbbbabaa","babababbababaabbbbabbbbabbba","abbbbbbaabaaabaaababaabbabba","aabaabababbbbbbababbbababbaa","aabbbbabbaababaaaabababbaaba","ababaababaaabbabbaabbaabbaba","abaabbbaaaaababbbaaaaabbbaab","aabbabaabaabbabababaaabbbaab","baaabaaaabbabaaabaabababaaaa","aaabbabaaaababbabbaabbaabbaa","aaabaaaaabaabbabaabbbbaabaaa","abbaabbaaaabbaababababbaabbb","baabaababbbbaaaabaaabbababbb","aabaababbaababbaaabaabababab","abbaaabbaabaabaabbbbaabbbbbb","aaababaabbaaabbbaaabbabbabab","bbababbbabbbbabbbbabbbbbabaa","abbbaabbbaaababbbababbababba","bbbbbbbabbbababbabaabababaab","aaaababaabbbbabaaaaabaaaaabb","bbaaabbbbabbaaabbaabbabbaaba","aabaabbbbaabaabbabaabababaaa","abbababbbaababaabbababababbb","aabbbabbaaaababbbbabbababbbb","babbbaabababbbbbbbbbaabbabaa"};
	for(auto ts : vs)
		build(root,ts);
	cout << find(root,"bbbbbbbabbbababbabaabababaab") << endl;
	return 0;
}
