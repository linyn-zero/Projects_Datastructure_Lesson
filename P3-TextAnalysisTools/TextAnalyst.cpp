//
// Created by ling on 2022/10/10.
//

#include "TextAnalyst.h"

void TextAnalyst::perform() {
	try{ //
		initContainer();
		while(true){
			cout << "what to do? (选择你想进行的操作)：" << std::endl
			     << "1 for Displaying all the words." << std::endl
			     << "2 for Input what you want." << std::endl
			     << "0 for Change file." << std::endl;
			int command = 3;
			cin >> command;
			switch (command) {
				case 1:
					ShowAllWord_byMAPDICT();
					break;
				case 2:
					InputSearch();
					break;
				case 0: // 退出
					return ;
				default:
					cout << "Try again?" << std::endl;
			}
		}
	} catch (const exception& e){
		cout << "WRONG somewhere!" ;
	}
}
void TextAnalyst::initContainer() {
	allClear(); // 清空容器

	cout << "Input the address:" << std::endl;
	string fileAddr;              // 输入一个文件的地址
	cin >> fileAddr;
	ifstream sourse;  // 从文件中获取数据源
	sourse.open(fileAddr); // 获取文件流

	int lineIndex = 0; // 行号
	string isLine;
	getline(sourse,isLine,'\n');       // 从文件流中获取一行输入string
	bool stopFlag1 = false;
	while(true){
		if(!isLine.empty()) {
//			stringstream issLine(isLine);   // 将一行输入string转化为一行输入sstream
//		    issLine << isLine;
			string word;
			bool stopflag2 = false;
			trimLine2Word(isLine,word);       //修剪单词
			while(true) {                        // 从一行输入中获取单词
				if(!word.empty()) {
					wordsByDict[word]++;             //单词总数++
					wordsLine[word][lineIndex]++;    //该行单词数++
					cout << word << " " ;
				}
				if(stopflag2) { break; }
				stopflag2 = !trimLine2Word(isLine,word);  //修剪单词
			}
			cout << std::endl; // 检查输入是否正常
			lineIndex++;
		}
		if(stopFlag1) { break; }
		getline(sourse,isLine,'\n');   // 从文件流中获取一行输入string
	    stopFlag1 = sourse.eof();
	}
}
void TextAnalyst::ShowAllWord_byMAPDICT() const {
    cout << std::setw(10) << std::right << "Word" << std::setw(15) << std::left << "List" << std::right << "Number" << std::endl;
	int i = 0;
	for(auto & str_num : wordsByDict){
		cout << i++ << ". " <<  std::setw(25) << std::left << str_num.first << str_num.second << std::endl;
	}

	// 后续服务：进一步可循环单词检索
	int command = -2;
	while(true){
		cout << "Which word would you like to Search? input please." << std::endl
		     << "(-1 for Quit | Other will loop):" ; // 询问是否想通过序号查询单词信息
		string input;
		cin >> input;
		if(std::isdigit(input[0]) || input[0] == '-' && std::isdigit(input[1])){
			command = std::stoi(input);
		}
		else {continue;}
		if(command >= 0 && command < wordsByDict.size()){
			auto itw = wordsByDict.begin();
			while(command--) itw++;                 // 先获取序号对应的单词
			displayTheWord(itw->first);    // 展示所选单词
		}
		else if(command == -1){
			break;
		} else{
			continue;
		}
	}
}
void TextAnalyst::InputSearch() const {
	while(true){
		cout << "Plesae input the word you want to Search" << std::endl
		     << "(0 for quit):";
		string target; // 输入想查的单词
		cin >> target;

		if(target[0] == '0') { break; } // 退出指令判断

		vector<string> found;
		for(const auto& it : wordsByDict){ // 查找并记录
			if(myKMP(it.first, target) != -1){
				found.emplace_back(it.first);
			}
		}
		if(found.empty()) { cout << "Found nothing, will try again." << std::endl; }
		else { ShowAllWord_byVECTOR(found); } // 打印所有可能答案
	}
}
void TextAnalyst::ShowAllWord_byVECTOR(vector<string> strs) const {
	cout <<std::endl << "The Searching outcome:" << std::endl;
	cout << std::setw(10) << std::right << "Word" << std::setw(15) << std::left << "List" << std::right << "Number" << std::endl;
	int i = 0;
	for(auto & word : strs){
		cout << i++ << ". " <<  std::setw(25) << std::left << word << wordsByDict.find(word)->second << std::endl;
	}

	// 后续服务：进一步可循环单词检索
	int command = -2;
	while(true){
		cout << "Which word would you like to Search? input please." << std::endl
		     << "(-1 for Quit | Other will loop): " ; // 询问是否想通过序号查询单词信息
		string input;
		cin >> input;
		if(std::isdigit(input[0]) || input[0] == '-' && std::isdigit(input[1])){
			command = std::stoi(input);
		}
		else {continue;}
		if(command >= 0 && command < strs.size()){
			displayTheWord(strs[command]);    // 展示所选单词
		}
		else if(command == -1){
			break;
		}
	}
}
void TextAnalyst::displayTheWord(const string & theWord) const {
	if (wordsByDict.find(theWord) == wordsByDict.end()) { // 再次检查有无指定单词
		throw std::runtime_error{string{"no this word.when call displayTheWord"}};
	}
	cout <<std::endl << "Word: \"" << theWord << "\"" << std::endl;
	cout <<std::setw(16) << std::left << "Appear at:" << "Times:" << std::endl;
	auto it = wordsLine.find(theWord);
	for(auto item : it->second){
		cout <<std::setw(16) << std::left << item.first << item.second << std::endl;
	}
	cout << std::endl;
}
int TextAnalyst::myKMP(const string& str, const string& model)  {
	function<vector<int>(string)> getNextVal = [](const string& model){
		vector<int> next(model.size(),0);
		for(int i = 1, j = 0; i < model.size(); i++){
			while(j > 0 && model[i]!=model[j]){
				j = next[j-1];
			}
			if(model[i] == model[j]){
				j++;
			}
			next[i] = j;
		}
		return next;
	};

	vector<int> next(move(getNextVal(model)));
	int j;
	for(int i = 0; i < str.size(); i++){
		while(j > 0 && model[j] != str[i]) j = next[j-1];
		if(str[i] == model[j]) j++;
		if(j == model.size()) return i - j + 1;
	}
	return -1;
}
bool TextAnalyst::trimLine2Word(string &line, string &word) {
	word.clear();
	int index{};
	while(index < line.size() && (std::isalpha(line[index]) || line[index] == '_')) {
		word += tolower(line[index++]);
	}
	if(index+1 < line.size() && line[index] == '\'' && line[index + 1] == 's'){ // 处理“'s”
		index += 2;
	}
	while(index < line.size() && !std::isalpha(line[index])) { // 跳过非字母
		index++;
	}
	line = line.substr(index);
	return !line.empty();
}

void TextAnalyst::allClear() {
	wordsByDict.clear();
	wordsLine.clear();
}

//void TextAnalyst::displayTheWord(int index) const {
//	auto itw = wordsByDict.begin();
//	while(index--) itw++;
//	string theWord = itw->first;     // 先获取序号对应的单词
//
//	cout << "Word: " << theWord << std::endl;
//	cout <<std::setw(10) << std::left << "Line" << "nums" << std::endl;
//	auto it = wordsLine.find(theWord);
//	for(auto item : it->second){
//		cout << item.first << " " << item.second << std::endl;
//	}
//
//}

