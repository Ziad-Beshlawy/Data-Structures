#include"inord_list.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;
void wordCount(inord_list &L);
void distWords(inord_list &L);
void charCount(char* fileName);
void frequentWord(inord_list &L);
void countWord(inord_list &L, string word);
void starting(inord_list &L, string word);
void containing(inord_list &L, string word);
void search(inord_list &L, string word);

int main(int argc, char** argv){

	if(argc !=3){
		cout << "Incorrect number of arguments"<<endl;
		return 0;
	}
	ifstream readFile(argv[1], ios::in);
	ifstream commandsFile(argv[2], ios::in);
	if(! commandsFile || ! readFile){
		cout << "File not found"<<endl;
		return 0;
	}
	inord_list words;
	string line;
	string addedWord;
	char delims[] = " ()?![]{}&.,;:'`\"\r";
	char* token;
	int LineNumber = 1;
	while(getline(readFile, line)){
		char* c_line;
		c_line = new char[line.length()+1];
		strcpy(c_line, line.c_str());
		token = strtok(c_line, delims);
		while(token != NULL){
			for(int i = 0; i < strlen(token); i++)
				token[i] = tolower(token[i]);
			addedWord = string(token);
			words.insert(addedWord, LineNumber);
			token = strtok(NULL, delims);
		}
		delete c_line;
		LineNumber++;
	}
	readFile.close();
	string commandLine;
	string command;
	string arg1;
	char* c_command;
	char* c_arg1;
	while(getline(commandsFile, commandLine)){
		char* c_line;
		c_line = new char[commandLine.length()+1];
		strcpy(c_line, commandLine.c_str());
		c_command = strtok(c_line, " ");
		if(c_command == NULL){
			cout << "Undefined command"<<endl;
			continue;
		}
		command = string(c_command);
		if(command == "wordCount"){
			if(strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else
				wordCount(words);

		}
		else if(command == "distWords"){
			if(strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else
				distWords(words);
		}
		else if(command == "charCount"){
			if(strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else
				charCount(argv[1]);
		}
		else if(command == "frequentWord"){
			if(strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else
				frequentWord(words);
		}
		else if(command == "countWord"){
			c_arg1 = strtok(NULL, " ");
			if(c_arg1 == NULL || strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else{
				for(int i = 0; i < strlen(c_arg1); i++)
					c_arg1[i]=tolower(c_arg1[i]);
				arg1 = string(c_arg1);
				countWord(words, arg1);
			}

		}
		else if(command == "starting"){
			c_arg1 = strtok(NULL, " ");
			if(c_arg1 == NULL || strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else{
				for(int i = 0; i < strlen(c_arg1); i++)
					tolower(c_arg1[i]);
				arg1 = string(c_arg1);
				starting(words, arg1);
			}

		}
		else if(command == "containing"){
			c_arg1 = strtok(NULL, " ");
			if(c_arg1 == NULL || strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else{
				for(int i = 0; i < strlen(c_arg1); i++)
					tolower(c_arg1[i]);
				arg1 = string(c_arg1);
				containing(words, arg1);
			}

		}
		else if(command == "search"){
			c_arg1 = strtok(NULL, " ");
			if(c_arg1 == NULL || strtok(NULL, " ") != NULL)
				cout << "Incorrect number of arguments"<<endl;
			else{
				for(int i = 0; i < strlen(c_arg1); i++)
					c_arg1[i]=tolower(c_arg1[i]);
				arg1 = string(c_arg1);
				search(words, arg1);
			}

		}
		else cout << "Undefined command"<<endl;
		delete c_line;
	}
	commandsFile.close();

	return 0;
}

void wordCount(inord_list &L){
	int count = 0;
	string dummy;
	if(L.first(dummy)){
		count += L.getOcc();
		while(L.next(dummy))
			count += L.getOcc();
	}
	cout << count << " words"<<endl;
	return;
}

void distWords(inord_list &L){
	int count = 0;
	string dummy;
	if(L.first(dummy)){
		count ++;
		while(L.next(dummy))
			count ++;
	}
	cout << count << " distinct words"<<endl;
	return;
}

void charCount(char* fileName){
	ifstream readFile(fileName, ios::binary | ios::ate);
	cout << readFile.tellg() << " characters"<<endl;
}

void frequentWord(inord_list &L){
	int max = 0;
	int curr;
	string word;
	if(! (L.first(word))){
		cout <<endl;
		return;
	}
	if(!(word=="a"||word=="an"||word=="the"||word=="in"||word=="on"||word=="of"||word=="and"
	||word=="is"||word=="are")){
		max = L.getOcc();}
	while(L.next(word)){
		if(word=="a"||word=="an"||word=="the"||word=="in"||word=="on"||word=="of"||word=="and"
		||word=="is"||word=="are")
			continue;
		curr = L.getOcc();
		if(curr > max)
			max = curr;
	}
	L.first(word);
	curr = L.getOcc();
	bool firstPrinted = false;
	if(!(word=="a"||word=="an"||word=="the"||word=="in"||word=="on"||word=="of"||word=="and"
	||word=="is"||word=="are") && curr == max){
		cout << "Most frequent word is: " << word;
		firstPrinted = true;
	}
	while(L.next(word)){
		curr = L.getOcc();
		if(!(word=="a"||word=="an"||word=="the"||word=="in"||word=="on"||word=="of"||word=="and"
			||word=="is"||word=="are") && curr == max)
				if(firstPrinted) cout << " " << word;
				else{
					cout << "Most frequent word is: " << word;
					firstPrinted = true;
				}
	}
	cout<<endl;
	return;
}


void countWord(inord_list &L, string word){
	string currWord;
	int count;
	if(L.first(currWord)){
		if(currWord == word){
			count = L.getOcc();
			cout << word << " is repeated " << count << " times"<<endl;;
			return;
		}
	}
	while(L.next(currWord)){
		if(currWord == word){
			count = L.getOcc();
			cout << word << " is repeated " << count << " times"<<endl;
			return;
		}
	}
	cout << "Word not found"<<endl;;
	return;
}

void starting(inord_list &L, string word){
	int length = word.length();
	int currLength;
	string currWord;
	string out = "";
	bool outOK = false;
	if(L.first(currWord)){
		currLength = currWord.length();
		if(length <= currLength && word == currWord.substr(0, length)){
			outOK = true;
			out = out +"\t"+currWord+": "+to_string(L.getOcc());
		}
	}
	while(L.next(currWord)){
		currLength = currWord.length();
		if(length <= currLength && word == currWord.substr(0, length)){
			outOK = true;
			out = out +"\t"+currWord+": "+to_string(L.getOcc());
		}
	}
	if(!outOK){
		cout << "Word not found"<<endl;
		return;
	}
	out = out.substr(1, out.length()-1);
	cout << out<<endl;
	return;
}

void containing(inord_list &L, string word){
	int length = word.length();
	int currLength;
	string currWord;
	string out = "";
	bool outOK = false;
	if(L.first(currWord)){
		currLength = currWord.length();
		if(length <= currLength){
			for(int i = 0; i<=currLength-length; i++)
				if(currWord.substr(i,length) == word){
					outOK = true;
					out = out +"\t"+currWord+": "+to_string(L.getOcc());
					break;
				};
		}
	}
	while(L.next(currWord)){
		currLength = currWord.length();
		if(length <= currLength){
			for(int i = 0; i<=currLength-length; i++)
				if(currWord.substr(i,length) == word){
					outOK = true;
					out = out +"\t"+currWord+": "+to_string(L.getOcc());
					break;
				};
		}
	}
	if(!outOK){
		cout << "Word not found"<<endl;
		return;
	}
	out = out.substr(1, out.length()-1);
	cout << out<<endl;
	return;
}

void search(inord_list &L, string word){
	int length = word.length();
	int currLength;
	int LNum;
	string currWord;
	string out = "";
	bool outOK = false;
	if(L.first(currWord)){
		currLength = currWord.length();
		if(length <= currLength){
			for(int i = 0; i<=currLength-length; i++)
				if(currWord.substr(i,length) == word){
					outOK = true;
					cout << currWord << ":\t" << "lines";
					while(L.getLineNumber(LNum)) cout << " " << LNum;
					cout << endl;
					break;
				};
		}
	}
	while(L.next(currWord)){
		currLength = currWord.length();
		if(length <= currLength){
			for(int i = 0; i<=currLength-length; i++)
				if(currWord.substr(i,length) == word){
					outOK = true;
					cout << currWord << ":\t" << "lines";
					while(L.getLineNumber(LNum)) cout << " " << LNum;
					cout << endl;
					break;
				};
		}
	}
	if(!outOK){
		cout << "Word not found"<<endl;
		return;
	}
}


