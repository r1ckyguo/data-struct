#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


namespace FileOps {
	// 返回第一个英文字符的索引
	int firstCharacterIndex(const string& s, int start) {
		for (int i = start; i < s.length(); ++i) {
			if (isalpha(s[i])) {
				return i;
			}
		}
		return s.length();	//这时找不到
	}
	// 把所有字符都变成小写
	string lowerS(const string& s) {
		string ret = "";
		for (int i = 0;  i < s.length(); i++) {
			ret += tolower(s[i]);
		}
		return ret;
	}
	// 读取文件,并将所有单词插入vector
	bool readFile(const string& filename, vector<string> &words) {
		// word是把文件插入的单词
		string line;
		string contents = "";
		ifstream file(filename);
		if (file.is_open()) {		// 打开文件
			while (getline(file, line)) {		// 从文件中取一行
				contents += (line + "\n");
			}
			file.close();
		}
		else {
			cout << "Can not open " << filename << " !!!" << endl;
			return false;
		}
		// 从文本中读取词汇，并且放入words中
		int start = firstCharacterIndex(contents, 0);		// txt的第一个字符索引
		for (int i = start + 1; i <= contents.length(); ) {
			if (i == contents.length() || !isalpha(contents[i])) {	// 遇上空格或者到文本末尾，前面的词要放进words里面
				words.push_back(lowerS(contents.substr(start, i - start)));		// 词范围从start~i-start
				start = firstCharacterIndex(contents, i);		// 从i开始找下一个词的第一个索引
				i = start + 1;
			}
			else {
				++i;
			}
		}
		return true;
	}
}