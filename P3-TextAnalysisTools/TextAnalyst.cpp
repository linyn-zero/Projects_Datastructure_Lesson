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
				 << "3 for check how much keyWord in the file." << std::endl
			     << "0 for Change file." << std::endl;
			string command;
			cin >> command;
			switch (command[0]) {
				case '1':
					ShowAllWord_byVECTOR(existing_allWords_sorted);
					break;
				case '2':
					InputSearch();
					break;
				case '3':
					showKeyword();
					break;
				case '0': // 退出
					return ;
				default:
					cout << "Try again?" << std::endl;
			}
		}
	} catch (const exception& e){
		cout << e.what() ;
	}
}
void TextAnalyst::initContainer() {
	clearAllContainer(); // 清空容器

	cout << "Input the address:" << std::endl;
	ifstream source;  // 从文件中获取数据源
	string fileAddress;  // 输入一个文件的地址
	// 文件输入的正确性检查
	do{
		cin >> fileAddress;
		source.open(fileAddress); // 获取文件流c
		if(!source.is_open()) { cout << "Tr again?" << std::endl; }
	} while(!source.is_open());

	int lineIndex = 0; // 行号
	string isLine;
	getline(source, isLine, '\n');       // 从文件流中获取一行输入string
	bool stopFlag1 = false;
	// 将文本中的词汇信息预处理到各个类成员变量中
	unordered_set<string> findKeyword; // 用set容器暂存keyword以防止重复
	while(true){
		if(!isLine.empty()) {
			string word;
			bool stopFlag2 = false;
			trimLine2Word(isLine,word);       //修剪单词
			while(true) {                        // 从一行输入中获取单词
				if(!word.empty()) {
					wordsByDict[word]++;             //单词总数++
					wordsLine[word][lineIndex]++;    //该行单词数++
					cout << word << " " ;
					for(const string& keyword : keyWords){  // 将关键字预处理到成员变量Existing_keywords中
						if(word == keyword){
							findKeyword.insert(keyword);
						}
					}
				}
				if(stopFlag2) { break; }
				stopFlag2 = !trimLine2Word(isLine, word);  //修剪单词
			}
			cout << std::endl; // 检查输入是否正常
			lineIndex++;
		}
		if(stopFlag1) { break; }
		getline(source, isLine, '\n');   // 从文件流中获取一行输入string
	    stopFlag1 = source.eof();
	}
	existing_keywords_sorted.assign(findKeyword.begin(), findKeyword.end());
	// 预处理成员变量existing_keywords_sorted中的关键字，使existing_keywords_sorted按词频降序排列
	std::sort(existing_keywords_sorted.begin(),
	          existing_keywords_sorted.end(),
	          [&](const string& a, const string& b){
		if(wordsByDict[a]==wordsByDict[b]){
			return a<b;
		}
		return wordsByDict[a] > wordsByDict[b];
	});

	for(const auto& item : wordsByDict ){
		existing_allWords_sorted.emplace_back(item.first);
	}
	// 预处理成员变量existing_allWords_sorted中的单词，使existing_allWords_sorted按词频降序排列
	std::sort(existing_allWords_sorted.begin(),
			  existing_allWords_sorted.end(),
			  [&](const string& a, const string& b){
				  if(wordsByDict[a]==wordsByDict[b]){
					  return a<b;
				  }
				  return wordsByDict[a] > wordsByDict[b];
			  });
}
void TextAnalyst::showKeyword() const{
	if(existing_keywords_sorted.empty()) { cout << "Found nothing, try again?" << std::endl; }
	else {
		ShowAllWord_byVECTOR(existing_keywords_sorted);
		cout << "Please input the word you want to Search" << std::endl
		     << "(0 for quit):";
	} // 打印所有可能答案
}
void TextAnalyst::InputSearch() const {
	cout << "Please input the word you want to Search" << std::endl
	     << "(0 for quit):";
	while(true){
		string target;
		cin >> target;

		if(target[0] == '0') { break; } // 退出指令判断

		vector<string> found;
		for(const auto& it : wordsByDict){ // 查找并记录
			if(myKMP(it.first, target) != -1){
				found.emplace_back(it.first);
			}
		}
		if(found.empty()) { cout << "Found nothing, try again?" << std::endl; }
		else {
			// 预处理found中的单词，使found按词频降序排列
			std::sort(found.begin(),
			          found.end(),
			          [&](const string& a, const string& b){
				          if(wordsByDict.find(a)->second == wordsByDict.find(b)->second){
					          return a<b;
				          }
				          return wordsByDict.find(a)->second > wordsByDict.find(b)->second;
			          });
			ShowAllWord_byVECTOR(found);
			cout << "Please input the word you want to Search" << std::endl
			     << "(0 for quit):";
		} // 打印所有可能答案
	}
}
void TextAnalyst::ShowAllWord_byVECTOR(const vector<string>& words) const {
	cout <<std::endl << "The Searching outcome:" << std::endl;
	cout << std::setw(10) << std::right << "Word" << std::setw(15) << std::left << "List" << std::right << "Number" << std::endl;
	int i = 0;
	for(auto & word : words){
		cout << i++ << ". " <<  std::setw(25) << std::left << word << wordsByDict.find(word)->second << std::endl;
	}

	// 后续服务：进一步可循环单词检索
	int command {};
	while(true){
		cout << "Which word would you like to Search? input please." << std::endl
		     << "(-1 for Quit | Other will loop): " ; // 询问是否想通过序号查询单词信息
		string input;
		while(true){
			cin >> input;
			if(std::isdigit(input[0]) || input[0] == '-' && std::isdigit(input[1])){
				command = std::stoi(input);
				break;
			}
			else { cout << "Try again? " << std::endl; }
		}
		if(command >= 0 && command < words.size()){
			displayTheWord(words[command]);    // 展示所选单词
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
	int j = 0;
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
	while(index < line.size() && (std::isalpha(line[index]) || line[index] == '_' || std::isdigit(line[index]))) {
		if(std::isalpha(line[index])) { word += tolower(line[index++]); }
		else { word += line[index++]; }
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
void TextAnalyst::clearAllContainer() {
	wordsByDict.clear();
	wordsLine.clear();
	existing_keywords_sorted.clear();
	existing_allWords_sorted.clear();
}

TextAnalyst::TextAnalyst() : keyWords({"alignas","alignof"	,"asm"	,"auto"	,"bool",
                                       "break"	,"case"	,"catch",	"char"	,"char16_t",
                                       "char32_t"	,"class",	"const",	"const_cast",	"constexpr",
                                       "continue",	"decltype",	"default"	,"delete",	"do",
                                       "double",	"dynamic_cast"	,"else"	,"enum"	,"explicit",
                                       "export"	,"extern",	"false",	"float",	"for",
                                       "friend",	"goto"	,"if"	,"inline"	,"int",
                                       "long",	"mutable"	,"namespace","new"	,"noexcept",
                                       "nullptr"	,"operator"	,"private",	"protected"	,"public",
                                       "register"	,"reinterpret_cast",	"return",	"short",	"signed",
                                       "sizeof",	"static",	"static_assert"	,"static_cast"	,"struct",
                                       "switch",	"template"	,"this"	,"thread_local",	"throw",
                                       "true",	"try",	"typedef",	"typeid"	,"typename",
                                       "union",	"unsigned",	"using",	"virtual"	,"void",
                                       "volatile"	,"wchar_t",	"while"}){
	keyWords.shrink_to_fit();
}






