%{ /* Declarations section */
#include "tokens.hpp" 
#include <stdio.h>
%}

%option yylineno 
%option noyywrap
 
 
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n\r ])
printable ([\x20-\x7F])
non-printable ([\x00-\x1F])
HEXA ([0-9]|[a-f]|[A-F])

%%
int 	return INT;
void 	return VOID;
byte 	return BYTE;
b 		return B;
bool 	return BOOL;
and 	return AND;
or 	return OR;
not 	return NOT;
true	return TRUE;
false 	return FALSE;
return 	return RETURN;
if 	return IF;
else 	return ELSE;
while 	return WHILE;
break 	return BREAK;	
continue 	return CONTINUE;
\; 	return SC;
\,	return COMMA;
\( return LPAREN;
\) return RPAREN;
\{ return LBRACE;
\} return RBRACE;
\= return ASSIGN;
\n return -2;
==|!=|<|>|<=|>= return RELOP;
\+|\-|\*|"/" return BINOP;
"//"[^{\n|\r|\n\r}]* return COMMENT;
[a-zA-Z][a-zA-Z0-9]* return ID;
0 return NUM;
[1-9]+{digit}* return NUM;
\"(\\n|\\r|\\\\|\\\"|\\t|\\0|\\x{HEXA}{2}|[^\x00-\x1F\\\"])*\" return STRING;
 


{whitespace} ; 
. return -1;
%%