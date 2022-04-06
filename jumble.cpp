#include <iostream>
#include <ctime>
using namespace std;
#include "jumble.h"

string word;
int column, row, wordLen, size1, len;
char** Jumble = new char*[size1];
int flag = 0;
char x;
string& BadJumbleException::what(){return message;}	// through exception here
BadJumbleException::BadJumbleException(const string& m) : message(m){}

JumblePuzzle::JumblePuzzle() {	// default constructor
	this->column = 0;
	this->row = 0;
	this->size1 = 0;
	this->Jumble = nullptr;
	this->x = ' ';
}
JumblePuzzle::JumblePuzzle(const JumblePuzzle& JP2) {	// simple constructor
	this->column = JP2.column;
	this->row = JP2.row;
	this->size1 = JP2.size1;
	this->x = JP2.x;
	this->Jumble = new char*[size1];	// initialize Jumble again
	for (int i = 0; i < this->size1; i++){
		this->Jumble[i] = new char[size1];
		for (int j = 0; j < this->size1; j++) {
			this->Jumble[i][j] = JP2.Jumble[i][j];
		}
	}
}

JumblePuzzle::~JumblePuzzle() {	//destructor
//	for (int i = 0; i < this->size1; i++) {
//		delete[] Jumble[i];
//	}
	delete[] this->Jumble;	// clear heap memory
}

JumblePuzzle::JumblePuzzle(string hidden, string difficulty){
    int wordLen = hidden.length();
    len = wordLen;
    word = hidden;
	int diffNum;
//	cout << "len is:" << len << endl;
    // void* Size = &size1;

	// choose difficulty & throw exceptions
	if (difficulty == "easy"){
		diffNum = 2;
	} else if (difficulty == "medium") {
		diffNum = 3;
	} else if (difficulty == "hard") {
		diffNum = 4;
	} else {throw BadJumbleException("Please Enter A Valid Difficulty Level");}
	this->size1 = (len*diffNum);
//	cout << "size is:" << size1 << endl;


	// initialize random picked column and row number
	srand(time(NULL));
	this->column = (rand() % size1);
	this->row = (rand() % size1);
//	cout << "col is:" << column << endl;
//	cout << "row is:" << row << endl;

	initialize();

//    cout << "mid" << endl;
    // repeat finding direction of the hidden word until it's valid
    randDirect();
    while(flag != 1) {
        valid();
    }
    replace();
};

// once valid, replace hidden wordin
void JumblePuzzle::replace(){
    if (flag == 1) {
        if (this->x == 'n') {
            for(int a=0; a< len; ++a) {
            	Jumble[column-a][row] = word[a];
                }
        } else if (this->x == 's') {
            for(int b=0; b< len; ++b) {
            	Jumble[column+b][row] = word[b];
                }
        } else if (this->x == 'w') {
            for(int c=0; c< len; ++c) {
            	Jumble[column][row-c] = word[c];
                }
        } else if (this->x == 'e') {

            for(int d=0; d< len; ++d) {
            	Jumble[column][row+d] = word[d];
                }
        }
    }
}

void JumblePuzzle::initialize(){
	// initialize array Jumble again
    // char** Jumble = new char*[size1];
    Jumble = new char*[size1];
    for(int i=0; i< size1; ++i) {
    	//cout << "**" << endl;
    	Jumble[i] = new char[size1];
    	//cout << "***" << endl;
        for(int j=0; j< size1; ++j) {
        	//cout << "****" << endl;
        	Jumble[i][j] = char((rand()%26) + 'a');
        }
    }
}

// random direction
void JumblePuzzle::randDirect(){
    srand(time(NULL));
    char letters[] = "nswe";
    this->x = letters[rand() % 4];
}

// check if direction is valid
void JumblePuzzle::valid() {
    if (this->x == 'n') {
         if (column-wordLen >= 0) {
             flag = 1;
         } else {
             flag = 0;
             randDirect();}
    } else if (this->x == 's') {
         if (column+wordLen < this->size1) {
             flag = 1;
         } else {
             flag = 0;
             randDirect();}
    } else if (this->x == 'w') {
         if (row-wordLen >= 0) {
             flag = 1;
         } else {
             flag = 0;
             randDirect();}
    } else if (this->x == 'e') {
         if (row+wordLen < this->size1) {
             flag = 1;
         } else {
             flag = 0;
             randDirect();}
    }
}
// '=' overloading
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& JP2) {
	if (this != &JP2) {
		delete[] this->Jumble;
		this->column = JP2.column;
		this->row = JP2.row;
		this->size1 = JP2.size1;
		this->x = JP2.x;
		this->Jumble = new char*[this->size1];
		for (int i = 0; i < this->size1; i++){
			this->Jumble[i] = new char[this->size1];
			for (int j = 0; j < this->size1; j++) {
				this->Jumble[i][j] = JP2.Jumble[i][j];
			}
		}
	}
	return *this;
}
char** JumblePuzzle::getJumble() const {
	return this->Jumble;
}

int JumblePuzzle::getSize() const {
	return this->size1;
}

int JumblePuzzle::getRowPos() const {
	return this->row;
}

int JumblePuzzle::getColPos() const {
	return this->column;
}

char JumblePuzzle::getDirection() const {
	return this->x;
}
