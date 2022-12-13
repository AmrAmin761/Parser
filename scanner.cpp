#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/*All Tiny language reserved words stored for further use*/
string Reserved_Words[] = { "if","then","else","end","repeat","until","read","write" };

/*The State machine states to be traversed on*/
enum Allstates { START, COMMENT, NUMBER, ID, ASSIGN, SYMBOL, ERROR, END };

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

void getToken(string Code) {
	string token;
	bool is_Reserved = false;
	int currentChar = 0;
	int symbolType = 0;
	string type;
	/*State machine implementation and transitions are based on current character*/
	while (current_state != END) {
		switch (current_state) {
		case START:
			if (is_digit(Code[currentChar])) {
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
				current_state = ASSIGN;
			}
			else if (is_letter(Code[currentChar])) {
				current_state = ID;
			}
			else if (Code[currentChar] == '{') {
				currentChar++;
				current_state = COMMENT;
			}
			else if (is_symbol(Code[currentChar])) {

				current_state = SYMBOL;

			}
			else current_state = ERROR;
			break;

		case NUMBER:
			for (int i = currentChar ; ((!is_space(Code[i])) && (!is_symbol(Code[i]))) ; i++)
			{
				if (!is_digit(Code[i])) {
					current_state = ERROR;
					break;
				}
			} 
			if (current_state == ERROR) {
				break;
			}
			while (is_digit(Code[currentChar])) {
				token += Code[currentChar];
				currentChar++;
			}
			cout << token << ", " << "number" << endl;
			token = "";
			if (currentChar == Code.length())
				current_state = END;
			else
				current_state = START;
			break;

		case ID:
			for (int i = currentChar ; ((!is_space(Code[i])) && (!is_symbol(Code[i]))) ; i++)
			{
				if (!is_letter(Code[i])) {
					current_state = ERROR;
					break;
				}
			}
			if (current_state == ERROR) {
				break;
			}
			while (is_letter(Code[currentChar]) && !is_space(Code[currentChar])) {
				token += Code[currentChar];
				currentChar++;
			}
			for (int currentChar = 0; currentChar < 8; currentChar++)
			{
				if (Reserved_Words[currentChar] == token)
					is_Reserved = true;
			}
			if (is_Reserved)
				cout << token << ", " << "Reserved Word" << endl;
			else
				cout << token << ", " << "Identifier" << endl;
			token = "";
			is_Reserved = false;
			if (currentChar == Code.length())
				current_state = END;
			else
				current_state = START;
			break;

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
				cout << ":=" << ", " << "assign" << endl;
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
				type = "semicolon";
				break;
			case LESSTHAN:
				type = "less than";
				break;
			case GREATERTHAN:
				type = "greater than";
				break;
			case EQUAL:
				type = "equal";
				break;
			case PLUS:
				type = "plus";
				break;
			case MINUS:
				type = "minus";
				break;
			case MULT:
				type = "mult";
				break;
			case DIV:
				type = "div";
				break;
			case OPENBRACKET:
				type = "open bracket";
				break;
			case CLOSEDBRACKET:
				type = "closed bracket";
				break;
			}
			cout << Code[currentChar] << ", " << type << endl;
			currentChar++;
			if (currentChar == Code.length())
				current_state = END;
			else
				current_state = START;
			break;
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
