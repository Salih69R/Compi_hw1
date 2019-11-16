#include <iostream>
#include <stack>
#include <string>
#include "tokens.hpp"


using namespace std;

//third type of error, found after starting to calculate the answer
void HandleError() {
	cout << "Error: Bad Expression\n";
	exit(0);
}


string Calc(string arg1, string arg2, string BinOp) {


	int arg1_int = stoi(arg1);
	int arg2_int = stoi(arg2);
	if (BinOp == "*") {
		return  to_string(arg1_int * arg2_int);
	}
	if (BinOp == "/") {
		return  to_string(arg1_int / arg2_int);
	}
	if (BinOp == "+") {
		return  to_string(arg1_int + arg2_int);
	}
	if (BinOp == "-") {
		return  to_string(arg1_int - arg2_int);
	}


}

bool IsBinOp(string str) {

	return (str == "+" || str == "-" || str == "/" || str == "*");
}


void calcVlidEqua(stack<string> val_stack) {

	stack<string> tmp_stack;
	string arg1, arg2;
	while (!val_stack.empty()) {

		if (!IsBinOp(val_stack.top())) {
			tmp_stack.push(val_stack.top());
			val_stack.pop();
			continue;
		}

		if (tmp_stack.size() < 2) {
			HandleError();
		}

		arg1 = tmp_stack.top();
		tmp_stack.pop();
		arg2 = tmp_stack.top();
		tmp_stack.pop();

		tmp_stack.push(Calc(arg1, arg2, val_stack.top()));
		val_stack.pop();


	}

	if (tmp_stack.size() != 1) {
		HandleError();
	}

	cout << tmp_stack.top() << endl;

}


void  printToken(int token) {
	string toprint;

	//cout << "in check, token = " << token << endl;
	switch (token)
	{
	case 1: toprint = "VOID";
		break;
	case 2: toprint = "INT";
		break;
	case 3: toprint = "BYTE";
		break;
	case 4: toprint = "B";
		break;
	case 5: toprint = "BOOL";
		break;
	case 6: toprint = "AND";
		break;
	case 7: toprint = "OR";
		break;
	case 8: toprint = "NOT";
		break;
	case 9: toprint = "TRUE";
		break;
	case 10: toprint = "FALSE";
		break;
	case 11: toprint = "RETURN";
		break;
	case 12: toprint = "IF";
		break;
	case 13: toprint = "ELSE";
		break;
	case 14: toprint = "WHILE";
		break;
	case 15: toprint = "BREAK";
		break;
	case 16: toprint = "CONTINUE";
		break;
	case 17: toprint = "SC";
		break;
	case 18: toprint = "COMMA";
		break;
	case 19: toprint = "LPAREN";
		break;
	case 20: toprint = "RPAREN";
		break;
	case 21: toprint = "LBRACE";
		break;
	case 22: toprint = "RBRACE";
		break;
	case 23: toprint = "ASSIGN";
		break;
	case 24: toprint = "RELOP";
		break;
	case 25: toprint = "BINOP";
		break;
	case 26: toprint = "COMMENT";
		break;
	case 27: toprint = "ID";
		break;
	case 28: toprint = "NUM";
		break;
	case 29: toprint = "STRING";
		break;
	}
	cout << toprint << endl;
}

int main()
{

	stack<string> valStack1;


	int token;
	while (token = yylex()) {


		//monitoring
		//cout << "token = " << token << "                    ";
	//	cout << "yytext = " << yytext << endl;

		if(token == -2)// because /n in our lexer returns -2, we assume there is only one line in the file
			calcVlidEqua(valStack1);
		if (token == -1) {//assume all errors that are not of second and 3rd type are of first
			cout << "Error " << yytext[0] << endl;
			exit(0);
		}
		if (token != NUM && token != BINOP ) {//this is second type error
			cout << "Error: ";
			printToken(token);
			exit(0);
		}

		//all chars are legal (nums or binops) now deal with expression struct
		//save in stack or somewhere

		string tmp = yytext;
		valStack1.push(tmp);

	}
	calcVlidEqua(valStack1);


	return 0;
}