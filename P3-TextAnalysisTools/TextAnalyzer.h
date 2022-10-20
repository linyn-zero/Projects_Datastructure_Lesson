
/// Created by ling on 2022/10/10.

#ifndef TEXTANALYSISTOOLS_TEXTANALYST_H
#define TEXTANALYSISTOOLS_TEXTANALYST_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
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
using std::unordered_set;
using std::pair;
using std::vector;
using std::ifstream ;
using std::stringstream;
using std::set;
using std::exception;
using std::function;
using std::remove_if;

/* 需求文档:
 * 处理过一次文本后，提供查询方法：
 * 方法1：显示所有出现的单词，以及出现次数
 * 方法2：手动输入想要查询的单词（使用KMP以提供非精准查找方案）。将显示所有的可能结果。询问查询哪个单词（输入序号）。提供指定单词的出现行序与在各行的个数
 * 方法3：显示所有找到的关键字
*/
class TextAnalyst {
	// 信息载体容器们
	map<string, int> wordsByDict;                // 词库1。记录所有出现过的单词，key是单词，value是出现次数
	map<string, map<int,int>> wordsLine;         // 词库2。单词与其出现的行序号与次数
	vector<string> existing_allWords_sorted;     // 用于功能1。出现过的单词，按词频降序存储。
	vector<string> existing_keywords_sorted;     // 用于功能3。出现过的关键字，按词频降序存储。
	vector<string> keyWords;                     // 存储所有C++保留关键字。在调用构造函数时加载。
public:
	TextAnalyst();                                           // 构造函数：加载keywords
	void perform();                                          // 主函数入口
	void initContainer();                                    // 初始化信息载体容器
	void InputSearch() const;                                // 功能2：输入想要查询的内容
	void showKeyword() const;                                // 功能3：展示保留字及其出现次数（按次数排序）
	static bool trimLine2Word(string &line, string &word);   // 初始化信息用接口：将一行文本修减为一个单词，同时文本减去相应部分
	void ShowAllWord_byVECTOR(const vector<string>&) const;  // 功能实现接口：展示所有单词及其出现次数（从给定的数组中，按单词在数组中存储的顺序展示）
	void displayTheWord(const string&) const;                // 功能实现接口：展示一个特定单词的出现行数与每行个数。确保了参数存在。
	static int myKMP(const string&, const string&) ;         // 用于功能2。一个KMP算法。
	void clearAllContainer();                                // 用于初始化信息载体容器。清空所有容器。
};
#endif //TEXTANALYSISTOOLS_TEXTANALYST_H
/*
 * bug日志：
 * 1、map无法以[]读取value: const函数不行
 * 2、重载出了问题: 那就不重载了
 * 3、输入流出错，检查所有输入输出的健壮性 √
 * 4、用文本2执行指令3时，会错误kmp出do和if。要拎出kmp来好好检查 √忘记清空新容器了
 *
 * 实现日志：
 * 1. 识别 '_' √
 * 2. 取消大小写区别√
 * 3. 关键字未按字典序排列√
 * 4. 功能2实现降序√
 */