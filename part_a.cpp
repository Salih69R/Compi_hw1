#include <iostream>
#include "tokens.hpp"
#include <fstream>



//prints everything til length or  til it finds "
void PrintError(char* line , int length){

    int index = 0;
    while(index < length ){
        if(line[index] == '\"'){
            break;
        }
        std::cout << line[index];
        index++;
    }

}



void findFirst(char* line){


    for (int j = 0; j < 1024 ; ++j) {

        //if found first backslash
        if(line[j]=='\\'){

            char a = line[j+1];
            if(a =='\\' || a=='\"' || a =='n' || a=='r'||a=='t'||a=='0') {
                continue;//legal use
            }


            if(a != 'x'){
                PrintError(line+j+1,1);//not starting with any valid char
            }
            else{
                // starts with \x
                if(j>1020)
                    PrintError(line+j+1,3);//has less than 2 chars after it before the "

                char b = line[j+2], c = line[j+3];
                //looks like this: \xbc
                if(((b>='0' && b <= '9') || (b >= 'a' && b <= 'f') || (b >= 'A' && b <= 'F'))
                   &&
                        ((c>='0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) ){

                    continue;

                }
                PrintError(line+j+1,3);//has a non hexa number
            }
        }
    }

}

void HandleError(){

    char line[1030];//iniated a little bigger
    int index=0;
    int token=0;


    if(yytext[0] == '\"'){

        line[0] = '\"';
        index++;
        token = yylex();

       while (yytext[0] != '\n' && yytext[0] != '\"'){

           int i = index;
           for ( i = index; i < index + yyleng; ++i) {
               line[i] = yytext[i-index];
           }


           index+=yyleng;

           token = yylex();
       }




        if(yytext[0] == '\"')
            line[index] = '\"';

        if (yytext[0] == '\n' || (line[index-1] == '\\' && line[index] == '\"')){
            std::cout << "Error unclosed string" << std::endl;
        }else{



            std::cout << "Error undefined escape sequence " ;
            findFirst(line);
            std::cout << std::endl; //<< "index:" << index;
            //std::cout << "line[0]: "<<line[0] << "     line[index-1]: "<<line[index-1];
        }


    }else {
    std::cout << "Error " << yytext[0] << std::endl;

    }
}

char HexaMangment(char tens,char ones){

    int one;
    int ten;

    if (ones >= '0' && ones <= '9'){
        one = ones - '0';
    }else if (ones >= 'a' && ones <= 'f'){
        one = ones - 'a' + 10;
    }else{
        one = ones - 'A' + 10;
    }

    if (tens >= '0' && tens <= '9'){
        ten = (tens - '0') * 16;
    }else if (tens >= 'a' && tens <= 'f'){
        ten = (tens - 'a' + 10) * 16;
    }else{
        ten = (tens - 'A' + 10) * 16;
    }



	//invalid ascii, biggest valid ascii is 7f, smallest 20
	if (ten > 7 * 16 || ten < 2 * 16) {
		std::cout << "Error undefined escape sequence x" << tens << ones << std::endl;
		exit(0);
	}
    return one + ten;
}


//returns the number of chars it printed
int HandlingPrint(char* string , int index){


    if (string[index] != '\\') {
        std::cout << string[index];
        return 1;

    }

        switch (string[index+1]){
            case '\\' : std::cout << string[index]; return 2;
            case '\"' : std::cout << string[index+1]; return 2;
            case 'n' : std::cout << "\n"; return 2;
            case 'r' : std::cout << "\r"; return 2;
            case 't' : std::cout << "\t"; return 2;
            case '0' : std::cout << "\0"; return 2;
            case 'x' : std::cout << HexaMangment(string[index+2],string[index+3]);return 4;
        }



}


void PrintString(char* string){

    int str_len = 0;
    int i = 0 ;
    while(*(string + i)){
        str_len++;
        i++;
    }
    int j = 1;
    while ( j < str_len - 1) {
        j+=HandlingPrint(string,j);

    }

}

int main()
{
    int token;
    while(token = yylex()) {


        if (token == INT){
            std::cout << yylineno << " INT " << yytext << std::endl;
        }
        if (token == VOID){
            std::cout << yylineno << " VOID " << yytext << std::endl;
        }
        if (token == BYTE){
            std::cout << yylineno << " BYTE " << yytext << std::endl;
        } if (token == B){
            std::cout << yylineno << " B " << yytext << std::endl;
        } if (token == BOOL){
            std::cout << yylineno << " BOOL " << yytext << std::endl;
        } if (token == AND){
            std::cout << yylineno << " AND " << yytext << std::endl;
        } if (token == OR){
            std::cout << yylineno << " OR " << yytext << std::endl;
        } if (token == NOT){
            std::cout << yylineno << " NOT " << yytext << std::endl;
        } if (token == TRUE){
            std::cout << yylineno << " TRUE " << yytext << std::endl;
        } if (token == FALSE){
            std::cout << yylineno << " FALSE " << yytext << std::endl;
        } if (token == RETURN){
            std::cout << yylineno << " RETURN " << yytext << std::endl;
        } if (token == IF){
            std::cout << yylineno << " IF " << yytext << std::endl;
        } if (token == ELSE){
            std::cout << yylineno << " ELSE " << yytext << std::endl;
        } if (token == WHILE){
            std::cout << yylineno << " WHILE " << yytext << std::endl;
        } if (token == BREAK){
            std::cout << yylineno << " BREAK " << yytext << std::endl;
        } if (token == CONTINUE){
            std::cout << yylineno << " CONTINUE " << yytext << std::endl;
        } if (token == SC){
            std::cout << yylineno << " SC " << yytext << std::endl;
        } if (token == COMMA){
            std::cout << yylineno << " COMMA " << yytext << std::endl;
        } if (token == LPAREN){
            std::cout << yylineno << " LPAREN " << yytext << std::endl;
        } if (token == RPAREN){
            std::cout << yylineno << " RPAREN " << yytext << std::endl;
        } if (token == RBRACE){
            std::cout << yylineno << " RBRACE " << yytext << std::endl;
        } if (token == LBRACE){
            std::cout << yylineno << " LBRACE " << yytext << std::endl;
        } if (token == ASSIGN){
            std::cout << yylineno << " ASSIGN " << yytext << std::endl;
        } if (token == RELOP){
            std::cout << yylineno << " RELOP " << yytext << std::endl;
        } if (token == BINOP){
            std::cout << yylineno << " BINOP " << yytext << std::endl;
        } if (token == COMMENT){
            std::cout << yylineno << " COMMENT " << "//" << std::endl;
        } if (token == ID){
            std::cout << yylineno << " ID " << yytext << std::endl;
        } if (token == NUM){
            std::cout << yylineno << " NUM " << yytext << std::endl;
        } if (token == STRING){
            std::cout << yylineno << " STRING ";
            PrintString(yytext);
            std::cout<<std::endl;

        } if (token == -1){

           HandleError();
            exit(0);

        }

    }
    return 0;
}