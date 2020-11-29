#ifndef _LEXOR_H_
#define _LEXOR_H_

enum tokenType{
	T_NULL,
	T_LET,
	T_WHILE,
	T_DO,
	T_END,
	T_PRINT,
	T_ID,
	T_NUM,
	T_LPAR,
	T_RPAR,
	T_PLUS,
	T_MINUS,
	T_EQ,
	T_SEP,
	T_EOF
};


typedef struct {
	char value;
	int type;
	int line;
}token_t;

typedef struct {
	char* position;
	int line;
}scanner_t;

#endif
