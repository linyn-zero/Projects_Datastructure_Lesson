//
// Created by ling on 2022/10/10.
//

#include "TextAnalyst.h"

void TextAnalyst::perform() {
	try{ //
		initContainer();
		while(true){
			cout << "what to do? (ѡ��������еĲ���)��" << std::endl
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
				case '0': // �˳�
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
	clearAllContainer(); // �������

	cout << "Input the address:" << std::endl;
	ifstream source;  // ���ļ��л�ȡ����Դ
	string fileAddress;  // ����һ���ļ��ĵ�ַ
	// �ļ��������ȷ�Լ��
	do{
		cin >> fileAddress;
		source.open(fileAddress); // ��ȡ�ļ���c
		if(!source.is_open()) { cout << "Tr again?" << std::endl; }
	} while(!source.is_open());

	int lineIndex = 0; // �к�
	string isLine;
	getline(source, isLine, '\n');       // ���ļ����л�ȡһ������string
	bool stopFlag1 = false;
	// ���ı��еĴʻ���ϢԤ�����������Ա������
	unordered_set<string> findKeyword; // ��set�����ݴ�keyword�Է�ֹ�ظ�
	while(true){
		if(!isLine.empty()) {
			string word;
			bool stopFlag2 = false;
			trimLine2Word(isLine,word);       //�޼�����
			while(true) {                        // ��һ�������л�ȡ����
				if(!word.empty()) {
					wordsByDict[word]++;             //��������++
					wordsLine[word][lineIndex]++;    //���е�����++
					cout << word << " " ;
					for(const string& keyword : keyWords){  // ���ؼ���Ԥ������Ա����Existing_keywords��
						if(word == keyword){
							findKeyword.insert(keyword);
						}
					}
				}
				if(stopFlag2) { break; }
				stopFlag2 = !trimLine2Word(isLine, word);  //�޼�����
			}
			cout << std::endl; // ��������Ƿ�����
			lineIndex++;
		}
		if(stopFlag1) { break; }
		getline(source, isLine, '\n');   // ���ļ����л�ȡһ������string
	    stopFlag1 = source.eof();
	}
	existing_keywords_sorted.assign(findKeyword.begin(), findKeyword.end());
	// Ԥ�����Ա����existing_keywords_sorted�еĹؼ��֣�ʹexisting_keywords_sorted����Ƶ��������
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
	// Ԥ�����Ա����existing_allWords_sorted�еĵ��ʣ�ʹexisting_allWords_sorted����Ƶ��������
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
	} // ��ӡ���п��ܴ�
}
void TextAnalyst::InputSearch() const {
	cout << "Please input the word you want to Search" << std::endl
	     << "(0 for quit):";
	while(true){
		string target;
		cin >> target;

		if(target[0] == '0') { break; } // �˳�ָ���ж�

		vector<string> found;
		for(const auto& it : wordsByDict){ // ���Ҳ���¼
			if(myKMP(it.first, target) != -1){
				found.emplace_back(it.first);
			}
		}
		if(found.empty()) { cout << "Found nothing, try again?" << std::endl; }
		else {
			// Ԥ����found�еĵ��ʣ�ʹfound����Ƶ��������
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
		} // ��ӡ���п��ܴ�
	}
}
void TextAnalyst::ShowAllWord_byVECTOR(const vector<string>& words) const {
	cout <<std::endl << "The Searching outcome:" << std::endl;
	cout << std::setw(10) << std::right << "Word" << std::setw(15) << std::left << "List" << std::right << "Number" << std::endl;
	int i = 0;
	for(auto & word : words){
		cout << i++ << ". " <<  std::setw(25) << std::left << word << wordsByDict.find(word)->second << std::endl;
	}

	// �������񣺽�һ����ѭ�����ʼ���
	int command {};
	while(true){
		cout << "Which word would you like to Search? input please." << std::endl
		     << "(-1 for Quit | Other will loop): " ; // ѯ���Ƿ���ͨ����Ų�ѯ������Ϣ
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
			displayTheWord(words[command]);    // չʾ��ѡ����
		}
		else if(command == -1){
			break;
		}
	}
}
void TextAnalyst::displayTheWord(const string & theWord) const {
	if (wordsByDict.find(theWord) == wordsByDict.end()) { // �ٴμ������ָ������
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
	if(index+1 < line.size() && line[index] == '\'' && line[index + 1] == 's'){ // ����'s��
		index += 2;
	}
	while(index < line.size() && !std::isalpha(line[index])) { // ��������ĸ
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






