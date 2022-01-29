#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
using namespace std;

void print(int argc, char** argv);
void reverse(int argc, char** argv);
void upper(int argc, char** argv);
void shuffleWord(int argc, char** argv);
void shuffleStatement(int argc, char** argv);
void Delete(int argc, char** argv);
void middle(int argc, char** argv);
void add(int argc, char** argv);
void random(int argc, char** argv);

int main(int argc, char** argv){
	if(argc <=1){
		cout<<"Undefined Command"<<endl;
		return 0;}
	string command = string(argv[1]);
	if(argc <= 1){
		cout<<"Undefined Command"<<endl;}
	if(command == "print"){
		print(argc, argv);}
	else if(command == "reverse"){
		reverse(argc, argv);}
	else if(command == "upper"){
		upper(argc, argv);}
	else if(command == "shuffle"){
		shuffleWord(argc, argv);}
	else if(command == "shuffleStatement"){
		shuffleStatement(argc, argv);}
	else if(command == "delete"){
		Delete(argc, argv);}
	else if(command == "middle"){
		middle(argc, argv);}
	else if(command == "add"){
		add(argc, argv);}
	else if(command == "random"){
		random(argc, argv);}
	else{
		cout<<"Undefined Command"<<endl;
	}
	return 0;
};

void print(int argc, char** argv){
	if (argc <=2){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;
	}
	for(int i = 2; i<argc; i++){
		cout<<argv[i]<<" ";
	}
	cout << endl;
	return;
};

void reverse(int argc, char** argv){
	if (argc <=2){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;
	}
	for(int i = argc-1; i>1; i--){
		cout<<argv[i]<<" ";
	}
	cout << endl;
	return;
};

void upper(int argc, char** argv){
	if (argc <=2){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;
	}
	for(int i = 2; i<argc; i++){
		for(int j = 0; j<strlen(argv[i]); j++){
			argv[i][j] = toupper(argv[i][j]);
		}
	}
	print(argc, argv);
	return;
};

void shuffleWord(int argc, char** argv){
	if (argc != 3){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;
	}
	char temp;
	for(int i = 1; i<strlen(argv[2]); i+=2){
		temp = argv[2][i];
		argv[2][i] = argv[2][i-1];
		argv[2][i-1] = temp;
	}
	print(argc, argv);
	return;
};

void shuffleStatement(int argc, char** argv){
	if (argc <=2){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;
	}
	char* temp;
	for(int i = 3; i<argc; i+=2){
		temp = argv[i];
		argv[i] = argv[i-1];
		argv[i-1] = temp;
	}
	print(argc, argv);
	return;
};

void Delete(int argc, char** argv){
	if(argc<4){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;}
	stringstream input;
	input << string(argv[2]);
	int index;
	bool validData (input >> index);
	if(!validData){
		cout<<"Incorrect Data Type"<<endl;
		input.clear();
		return;}
	if(index <= 0){
		cout<<"Incorrect Data Type"<<endl;
		input.clear();
		return;}
	if(index > argc-3){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;}
	for(int i = 3; i < argc; i++){
		if(i != (index + 2)){
			cout<<argv[i]<<" ";
		}
	}
	cout<<endl;
	return;
};

void middle(int argc, char** argv){
	int no_of_words = argc-2;
	if (no_of_words == 0){
		cout<<"Incorrect Number of Arguments"<<endl;
	}
	else if (no_of_words%2 == 0){
		cout<<argv[(no_of_words/2)+1]<<" "<<argv[(no_of_words/2)+2]<<endl;
	}
	else {
		cout<<argv[((no_of_words-1)/2)+2]<<endl;
	}
	return;
};

void add(int argc, char** argv){
	if (argc < 3){
		cout << "Incorrect Number of Arguments" << endl;
		return;
	}
	int sum = 0;
	int currentValue;
	stringstream input;
	string emptyCheck;
	for(int i = 2; i < argc; i++){
		input << string(argv[i]) << " ";
	}
	for(int i = 2; i < argc; i++){
		if (!(input >> currentValue)){
			input.clear();
			cout<<"Incorrect Data Type"<<endl;
			return;
		}
		sum += currentValue;
	}
	if (input >> emptyCheck){
		cout << "Incorrect Data Type"<<endl;
		return;
	}
	cout<<sum<<endl;
	return;
};

void random(int argc, char** argv){
	if (argc != 6){
		cout<<"Incorrect Number of Arguments"<<endl;
		return;
	}
	stringstream input;
	int sequenceLength;
	int minNumber;
	int maxNumber;
	int range;
	int seedValue;
	int randValue;

	input<<string(argv[2])<<" "<<string(argv[3])<<" "<<string(argv[4])<<" "<<string(argv[5]);
	bool validSequenceLength (input >> sequenceLength);
	bool validMinNumber (input >> minNumber);
	bool validMaxNumber (input >> maxNumber);
	bool validSeedValue (input >> seedValue);
	string emptyCheck;
	bool notEmpty (input >> emptyCheck);
	if (!validSequenceLength | !validMinNumber | !validMaxNumber | !validSeedValue | notEmpty){
		cout<<"Incorrect Data Type"<<endl;
		return;
	}
	if((sequenceLength <= 0) | (minNumber < 0) | (maxNumber <= minNumber)){
		cout<<"Incorrect Data Type"<<endl;
		return;
	}

	range = maxNumber - minNumber;
	srand(seedValue);
	for(int i = 0; i<sequenceLength; i++){
		randValue = minNumber + (rand()%(range+1));
		cout<<randValue<<" ";
	}
	cout<<endl;
	return;
};
