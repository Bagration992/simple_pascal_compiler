%option noyywrap
%option nounput
%option noinput
%{
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

#include "ast.hpp"
#include "izraz.hpp"

#include "parser.tab.hpp"

%}


%%

program     return program_token;
uses        return uses_token;
crt         return crt_token;
begin       return begin_token;
end         return end_token;
writeln     return writeln_token;
mod         return mod_token;
div         return div_token;
var         return var_token;
if			return if_token;
then		return then_token;
else		return else_token;
while           return while_token;
do              return do_token;

integer   { yylval.c = 'i'; return tip_token; }
real			{ yylval.c = 'r'; return tip_token; }
:=				{ return dodjela_token; }


[{][^}]*[}]     {}

["][^"]*["]        {
                      string tmp(yytext);
                      yylval.s = new string(tmp.substr(1, tmp.size() - 2));
                      return string_token;
	           }
[0-9]+(\.[0-9]+)?       {
                            yylval.x = atof(yytext);
                            return broj_token;
                        }
            
[a-zA-Z_][a-zA-Z_0-9]*  {
                          yylval.s = new string(yytext);
                          return id_token;
                        }
                        
[<>().;,+*/:=-]     return *yytext;
[ \n\t]            {  }
.   {
  cerr << "Leksicka greska: Neprepoznat karakter " << *yytext << endl;
  exit(EXIT_FAILURE);
}

%%

