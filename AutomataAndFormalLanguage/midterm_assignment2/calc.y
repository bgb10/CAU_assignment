/* The Bison declarations section */
%{
/* C declarations and #define statements go here */
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#define YYSTYPE double
extern int yylex();
extern void yyerror(const char *);

double last_result; /* #1. Add a special variable which can remember last calculated value. */
%}

%token NUMBER /* define token type for numbers */
%token '_' /* define token type for last_result */
%left '+' '-' /* + and - are left associative */
%left '*' '/' /* * and / are left associative */
%left '%' '^' /* % and ^ are left associative */
%left '(' ')' /* ( and ) are left associative */

%%      /* calc grammar rules */
/* lower precedence */
/* precedence and associativity reference: https://m.blog.naver.com/PostView.nhn?blogId=brickbot&logNo=220499291918&proxyReferer=https:%2F%2Fwww.google.com%2F */
input   : /* empty production to allow an empty input */
        | input line
        ;
line    : expr '\n'     { printf("Result: %f\n", $1); last_result = $1; }
        | error '\n'    { yyerror; }
        | '\n' /* #3. allow an empty line */
        ;
expr    : expr '+' term { $$ = $1 + $3; }
        | expr '-' term { $$ = $1 - $3; }
        | term          { $$ = $1; }
        ;
term    : term '*' op1 { $$ = $1 * $3; }
        | term '/' op1 { $$ = $1 / $3; }
        | term '%' op1 { $$ = fmod($1, $3); }
        | op1 { $$ = $1; }
        ;
op1     : op1 '^' op2 { $$ = pow($1, $3); }
        | op2 { $$ = $1; }
        ;
op2     : NUMBER { $$ = $1; }
        | '-' NUMBER { $$ = -$2; }
        | '_' { $$ = last_result; }
        | '(' expr ')' { $$ = $2; }
        ;
/* #3. Add two or more operations (^, %, -) */
/* higher precedence */

%%
int yylex(void){
    int c = getchar(); /* read from stdin */
    if (c < 0) return 0; /* end of the input */
    while (c == ' ' || c == '\t') c = getchar();
    if(isdigit(c) || c == '.') {
        ungetc(c, stdin); /* put c back into input */
        scanf("%lf", &yylval); /* get value using scanf */
        return NUMBER; /* return the token type */
    }
    return c; /* anything else... return char itself */
}

void yyerror(const char *errmsg) {
    printf("%s\n", errmsg);
}

int main(){
    printf("type an expression: \n");
    yyparse();
}