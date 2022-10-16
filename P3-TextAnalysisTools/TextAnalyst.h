
/// Created by ling on 2022/10/10.

#ifndef TEXTANALYSISTOOLS_TEXTANALYST_H
#define TEXTANALYSISTOOLS_TEXTANALYST_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <cctype>
using std::cin;
using std::cout;
using std::string;
using std::map;
using std::unordered_map;
using std::pair;
using std::vector;
using std::ifstream ;
using std::stringstream;
using std::set;
using std::exception;
using std::function;
using std::remove_if;

/* 处理过一次文本后，提供查询方法：
 * 方法1：显示所有单词，以及出现次数
 * 方法2：手动输入想要查询的单词（使用KMP以提供非精准查找方案）。将显示所有的可能结果。询问查询哪个单词（输入序号）。提供指定单词的出现行序与在各行的个数
 * 方法3：
 *
*/
class TextAnalyst {
	map<string, int> wordsByDict; // 按字典序为单词排序
//	vector<pair<string, int>> wordsByCount; // 按词频排序
	map<string, map<int,int>> wordsLine; // 单词出现的行序号


public:
//	TextAnalyst();
	void perform();                                          // 主函数入口
	void initContainer();                                    // 初始化信息载体容器
	void ShowAllWord_byMAPDICT() const;                      // 展示所有单词及其出现次数（从成员wordsByDict，按字典序）
	void ShowAllWord_byVECTOR(vector<string>) const;         // 展示所有单词及其出现次数（从给定的向量，按字典序）
	void InputSearch() const;                                // 输入想要查询的内容
	void displayTheWord(const string&) const;                // 展示一个特定单词的出现行数与每行个数.参数确保存在
	static int myKMP(const string&, const string&) ;         // 实现一个KMP
	static bool trimLine2Word(string &line, string &word);   // 将一行文本修建修建为一个单词，同时文本减去相应部分
	void allClear();                                         // 清空所有容器

};


#endif //TEXTANALYSISTOOLS_TEXTANALYST_H
/*
 * bug日志：
 * 1、map无法以[]读取value
 * 2、重载出了问题
 * 3、输入流出错，检查所有输入输出的健壮性
 *
 * 实现日志：
 * 1、识别_
 * 2、取消大小写区别√
 *
 */