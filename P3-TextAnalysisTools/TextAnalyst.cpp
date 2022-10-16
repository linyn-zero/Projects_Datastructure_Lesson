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
				case 0: // �˳�
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
	allClear(); // �������

	cout << "Input the address:" << std::endl;
	string fileAddr;              // ����һ���ļ��ĵ�ַ
	cin >> fileAddr;
	ifstream sourse;  // ���ļ��л�ȡ����Դ
	sourse.open(fileAddr); // ��ȡ�ļ���

	int lineIndex = 0; // �к�
	string isLine;
	getline(sourse,isLine,'\n');       // ���ļ����л�ȡһ������string
	bool stopFlag1 = false;
	while(true){
		if(!isLine.empty()) {
//			stringstream issLine(isLine);   // ��һ������stringת��Ϊһ������sstream
//		    issLine << isLine;
			string word;
			bool stopflag2 = false;
			trimLine2Word(isLine,word);       //�޼�����
			while(true) {                        // ��һ�������л�ȡ����
				if(!word.empty()) {
					wordsByDict[word]++;             //��������++
					wordsLine[word][lineIndex]++;    //���е�����++
					cout << word << " " ;
				}
				if(stopflag2) { break; }
				stopflag2 = !trimLine2Word(isLine,word);  //�޼�����
			}
			cout << std::endl; // ��������Ƿ�����
			lineIndex++;
		}
		if(stopFlag1) { break; }
		getline(sourse,isLine,'\n');   // ���ļ����л�ȡһ������string
	    stopFlag1 = sourse.eof();
	}
}
void TextAnalyst::ShowAllWord_byMAPDICT() const {
    cout << std::setw(10) << std::right << "Word" << std::setw(15) << std::left << "List" << std::right << "Number" << std::endl;
	int i = 0;
	for(auto & str_num : wordsByDict){
		cout << i++ << ". " <<  std::setw(25) << std::left << str_num.first << str_num.second << std::endl;
	}

	// �������񣺽�һ����ѭ�����ʼ���
	int command = -2;
	while(true){
		cout << "Which word would you like to Search? input please." << std::endl
		     << "(-1 for Quit | Other will loop):" ; // ѯ���Ƿ���ͨ����Ų�ѯ������Ϣ
		string input;
		cin >> input;
		if(std::isdigit(input[0]) || input[0] == '-' && std::isdigit(input[1])){
			command = std::stoi(input);
		}
		else {continue;}
		if(command >= 0 && command < wordsByDict.size()){
			auto itw = wordsByDict.begin();
			while(command--) itw++;                 // �Ȼ�ȡ��Ŷ�Ӧ�ĵ���
			displayTheWord(itw->first);    // չʾ��ѡ����
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
		string target; // �������ĵ���
		cin >> target;

		if(target[0] == '0') { break; } // �˳�ָ���ж�

		vector<string> found;
		for(const auto& it : wordsByDict){ // ���Ҳ���¼
			if(myKMP(it.first, target) != -1){
				found.emplace_back(it.first);
			}
		}
		if(found.empty()) { cout << "Found nothing, will try again." << std::endl; }
		else { ShowAllWord_byVECTOR(found); } // ��ӡ���п��ܴ�
	}
}
void TextAnalyst::ShowAllWord_byVECTOR(vector<string> strs) const {
	cout <<std::endl << "The Searching outcome:" << std::endl;
	cout << std::setw(10) << std::right << "Word" << std::setw(15) << std::left << "List" << std::right << "Number" << std::endl;
	int i = 0;
	for(auto & word : strs){
		cout << i++ << ". " <<  std::setw(25) << std::left << word << wordsByDict.find(word)->second << std::endl;
	}

	// �������񣺽�һ����ѭ�����ʼ���
	int command = -2;
	while(true){
		cout << "Which word would you like to Search? input please." << std::endl
		     << "(-1 for Quit | Other will loop): " ; // ѯ���Ƿ���ͨ����Ų�ѯ������Ϣ
		string input;
		cin >> input;
		if(std::isdigit(input[0]) || input[0] == '-' && std::isdigit(input[1])){
			command = std::stoi(input);
		}
		else {continue;}
		if(command >= 0 && command < strs.size()){
			displayTheWord(strs[command]);    // չʾ��ѡ����
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
	if(index+1 < line.size() && line[index] == '\'' && line[index + 1] == 's'){ // ����'s��
		index += 2;
	}
	while(index < line.size() && !std::isalpha(line[index])) { // ��������ĸ
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
//	string theWord = itw->first;     // �Ȼ�ȡ��Ŷ�Ӧ�ĵ���
//
//	cout << "Word: " << theWord << std::endl;
//	cout <<std::setw(10) << std::left << "Line" << "nums" << std::endl;
//	auto it = wordsLine.find(theWord);
//	for(auto item : it->second){
//		cout << item.first << " " << item.second << std::endl;
//	}
//
//}

