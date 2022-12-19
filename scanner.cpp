#include <iostream>
#include <string>
#include <fstream>
#include "scanner.hpp"
using namespace std;
/*All Tiny language reserved words stored for further use*/
string Reserved_Words[] = { "if","then","else","end","repeat","until","read","write" };

/*The State machine states to be traversed on*/
enum Allstates { START, COMMENT, NUMBER, ID, ASSIGN, SYMBOL, ERROR, END };

/*The RESERVED words types*/
enum Allreserved { IF, THEN, ELSE, ENDWORD, REPEAT, UNTIL, READ, WRITE};

/*The special symbols types*/
enum Alltypes { SEMICOLON, LESSTHAN, GREATERTHAN, EQUAL, PLUS, MINUS, MULT, DIV, OPENBRACKET, CLOSEDBRACKET };
Allstates current_state = START;//global variable to store the current state

/*Utility functions to check for type of current character*/
bool is_letter(char c) {
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
		return true;
	else
		return false;
}

/*Tokens to be return to parser*/
bool is_digit(char c) {
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

bool is_symbol(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '(' || c == ')' || c == ';')
		return true;
	else
		return false;
}

int reserved_type(string str){
	if(str == "if"){
		return IF;
	}
	else if(str == "then"){
		return THEN;
	}
	else if(str == "else"){
		return ELSE;
	}
	else if(str == "end"){
		return ENDWORD;
	}
	else if(str == "repeat"){
		return REPEAT;
	}
	else if(str == "until"){
		return UNTIL;
	}
	else if(str == "read"){
		return READ;
	}
	else if(str == "write"){
		return WRITE;
	}
	return 100;
}

int symbol_type(char c) {
	if (c == ';') {
		return SEMICOLON;
	}
	else if (c == '<') {
		return LESSTHAN;
	}
	else if (c == '>') {
		return GREATERTHAN;
	}
	else if (c == '=') {
		return EQUAL;
	}
	else if (c == '+') {
		return PLUS;
	}
	else if (c == '-') {
		return MINUS;
	}
	else if (c == '*') {
		return MULT;
	}
	else if (c == '/') {
		return DIV;
	}
	else if (c == '(') {
		return OPENBRACKET;
	}
	else if (c == ')') {
		return CLOSEDBRACKET;
	}
	return 100;
}

bool is_space(char c) {
	if (c == '\t' || c == ' ' || c == '\n')
		return true;
	else
		return false;
}

Token getToken(string Code) {
	Token token;
	
	bool is_Reserved = false;
	int currentChar = 0;
	int reservedType = 0;
	int symbolType = 0;
	string type;
	/*State machine implementation and transitions are based on current character*/
	while (current_state != END) {
		switch (current_state) {
		case START:
			if (is_digit(Code[currentChar])) {
				token.Type = "NUMBER";
				current_state = NUMBER;
			}
			else if (is_space(Code[currentChar])) {
				currentChar++;
				if (currentChar == Code.length())
					current_state = END;
				else
					current_state = START;
			}
			else if (Code[currentChar] == ':') {
				token.Type = "ASSIGN";
				current_state = ASSIGN;
			}
			else if (is_letter(Code[currentChar])) {
				
				current_state = ID;
			}
			else if (Code[currentChar] == '{') {
				token.Type = "COMMENT";
				currentChar++;
				current_state = COMMENT;
			}
			else if (is_symbol(Code[currentChar])) {
				token.Type = "Symbol";
				current_state = SYMBOL;

			}
			else current_state = ERROR;
			break;

		case NUMBER:
			while (is_digit(Code[currentChar])) {
				token.Value += Code[currentChar];
				currentChar++;
			}
			cout << token.Value << ", " << "NUMBER" << endl;
			token.Value = "";
			if (currentChar == Code.length())
				current_state = END;
			else
				current_state = START;
			break;
			return token;

		case ID:
			while (is_letter(Code[currentChar]) && !is_space(Code[currentChar])) {
				token.Value += Code[currentChar];
				currentChar++;
			}
			for (int currentChar = 0; currentChar < 8; currentChar++)
			{
				if (Reserved_Words[currentChar] == token.Value)
					is_Reserved = true;
			}
			if (is_Reserved){
				reservedType = reserved_type(token.Value);
				switch (reservedType) {
				case IF:
					token.Type = "IF";
					break;
				case THEN:
					token.Type = "THEN";
					break;
				case ENDWORD:
					token.Type = "END";
					break;
				case REPEAT:
					token.Type = "REPEAT";
					break;
				case UNTIL:
					token.Type = "UNTIL";
					break;
				case READ:
					token.Type = "READ";
					break;
				case WRITE:
					token.Type = "WRITE";
					break;
			}
			cout << token.Value << ", " << token.Type << endl;
			}
			else{
				cout << token.Value << ", " << "IDENTIFIER" << endl;
				token.Type = "IDENTIFIER";
			}
			token.Value = "";
			is_Reserved = false;
			if (currentChar == Code.length())
				current_state = END;
			else
				current_state = START;
			break;
			return token;

		case COMMENT:
			if (current_state == COMMENT) {
				while (Code[currentChar] != '}') {
					currentChar++;
				}
				currentChar++;
				if (currentChar == Code.length())
					current_state = END;
				else
					current_state = START;
			}
			break;

		case ASSIGN:
			if (Code[currentChar] == ':') {
				currentChar += 2;
				cout << ":=" << ", " << "ASSIGN" << endl;
				/*return to start case to handle next character state*/
				current_state = START;
			}
			else {
				if (currentChar == Code.length())
					current_state = END;
				else
					current_state = START;
			}
			break;
		case SYMBOL:
			symbolType = symbol_type(Code[currentChar]);
			switch (symbolType) {
			case SEMICOLON:
				token.Type = "SEMICOLON";
				break;
			case LESSTHAN:
				token.Type = "LESS THAN";
				break;
			case GREATERTHAN:
				token.Type = "GREATER THAN";
				break;
			case EQUAL:
				token.Type = "EQUAL";
				break;
			case PLUS:
				token.Type = "PLUS";
				break;
			case MINUS:
				token.Type = "MINUS";
				break;
			case MULT:
				token.Type = "MULT";
				break;
			case DIV:
				token.Type = "DIV";
				break;
			case OPENBRACKET:
				token.Type = "OPENBRACKET";
				break;
			case CLOSEDBRACKET:
				token.Type = "CLOSEDBRACKET";
				break;
			}
			cout << Code[currentChar] << ", " << token.Type << endl;
			currentChar++;
			if (currentChar == Code.length())
				current_state = END;
			else
				current_state = START;
			break;
			return token;
		case ERROR:
			cout<<"ERROR"<<endl;
			current_state = END;
			break;
		case END:
			break;
		//default:
			//current_state = ERROR;
			//break;


		}
	}
}
vector<Token> getTokenList(string input){
	vector<Token> tokens;
	int index = 0;
	while((index < (input.length()-1))){
		tokens.push_back(getToken(input));
	}
	return tokens;
}

int main(int argc, char* argv[]) {

	if (argc != 3) 
	{	
		cout << "Invalid Arguments";
		return 0;
	}

	//cout << "A file \"output.txt\" will be generated with the scanner output";

	ifstream file;
	string line, code;
	file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Input file not found";
    }
	while (!file.eof()) {
		getline(file, line);
		line += '\n';
		code += line;
	}

	//cout<<code;
	freopen(argv[2], "w", stdout);
	getToken(code);
	fclose(stdout);
	return 0;

}
