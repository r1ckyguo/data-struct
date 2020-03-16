#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


namespace FileOps {
	// ���ص�һ��Ӣ���ַ�������
	int firstCharacterIndex(const string& s, int start) {
		for (int i = start; i < s.length(); ++i) {
			if (isalpha(s[i])) {
				return i;
			}
		}
		return s.length();	//��ʱ�Ҳ���
	}
	// �������ַ������Сд
	string lowerS(const string& s) {
		string ret = "";
		for (int i = 0;  i < s.length(); i++) {
			ret += tolower(s[i]);
		}
		return ret;
	}
	// ��ȡ�ļ�,�������е��ʲ���vector
	bool readFile(const string& filename, vector<string> &words) {
		// word�ǰ��ļ�����ĵ���
		string line;
		string contents = "";
		ifstream file(filename);
		if (file.is_open()) {		// ���ļ�
			while (getline(file, line)) {		// ���ļ���ȡһ��
				contents += (line + "\n");
			}
			file.close();
		}
		else {
			cout << "Can not open " << filename << " !!!" << endl;
			return false;
		}
		// ���ı��ж�ȡ�ʻ㣬���ҷ���words��
		int start = firstCharacterIndex(contents, 0);		// txt�ĵ�һ���ַ�����
		for (int i = start + 1; i <= contents.length(); ) {
			if (i == contents.length() || !isalpha(contents[i])) {	// ���Ͽո���ߵ��ı�ĩβ��ǰ��Ĵ�Ҫ�Ž�words����
				words.push_back(lowerS(contents.substr(start, i - start)));		// �ʷ�Χ��start~i-start
				start = firstCharacterIndex(contents, i);		// ��i��ʼ����һ���ʵĵ�һ������
				i = start + 1;
			}
			else {
				++i;
			}
		}
		return true;
	}
}