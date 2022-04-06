#pragma once

#include <iostream>
using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle{
public:
	// generate puzzle
	JumblePuzzle();
	JumblePuzzle(string word, string difficulty);	// default? constructor
	JumblePuzzle(const JumblePuzzle&);	// copy constructor
	~JumblePuzzle();	// Destructor
	JumblePuzzle& operator=(const JumblePuzzle&);
	char** getJumble() const;
	int getSize() const;
	int getRowPos() const;
	int getColPos() const;
	char getDirection() const;

private:
	void randDirect();
	void valid();
	void replace();
	void initialize();
	int column, row, size1;
	char x;
	char** Jumble;
};


class BadJumbleException{
public:
	BadJumbleException(const string&);
	string& what();
private:
	string message;
};
