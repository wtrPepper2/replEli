#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// function prototypes
void initializeScanner(char*);
token_t* scan(void);

// define a scanner which is only used in this module.
static scanner_t scanner;



// input array from file
void initializeScanner(char* file) {
	scanner.position = file;
	scanner.line = 1;
}


// scan scanner data checking for valid inputs
token_t* scan() {

	token_t tokenData;

	// check for special character input
	switch (*scanner.position) {
		case '\0':    // decimal 0
			tokenData.type = T_EOF;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
			
		case '(':     // decimal 40
			scanner.position++;
			tokenData.type = T_LPAR;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
		
		case ')':	   // decimal 41
			scanner.position++;
			tokenData.type = T_RPAR;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
			
		case '+':      // decimal 43
			scanner.position++;
			tokenData.type = T_PLUS;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
		
		case '-':	  // decimal 45
			scanner.position++;
			tokenData.type = T_MINUS;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
		
		case '=':	  // decimal 51
			scanner.position++;
			tokenData.type = T_EQ;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
		
		case '\n':    // decimal 10 (LF)
		{  // need brackets on this case else error C2361 on default case(??)
			scanner.position++;
			scanner.line++;
			int line = scanner.line - 1;
			while (*scanner.position == '\n') {
				scanner.position++;
				scanner.line++;
			}

			tokenData.type = T_SEP;
			tokenData.value = *scanner.position;
			tokenData.line = scanner.line;
			return &tokenData;
		}

		default:
			// do nothing and continue to parse alpha chars
			break;
		}; // end special character check

	
	// check for alphabetic input
	if (isalpha(*scanner.position) || *scanner.position == '_') {
		char* start = scanner.position;
		while (isalpha(*scanner.position) || *scanner.position == '_') {
			scanner.position++;
		}
		size_t len = sizeof(char) * (scanner.position - start);

		char* value = (char*)malloc(len + 1);
		memcpy(value, start, len);
		value[len] = '\0';

		if (strcmp(value, "VAR") == 0) {
			tokenData.type = T_LET;
			tokenData.value = *value;
			tokenData.line = scanner.line;
			return &tokenData;
		}
		else if (strcmp(value, "WHILE") == 0) {
			tokenData.type = T_WHILE;
			tokenData.value = *value;
			tokenData.line = scanner.line;
			return &tokenData;
		}
		else if (strcmp(value, "DO") == 0) {
			tokenData.type = T_DO;
			tokenData.value = *value;
			tokenData.line = scanner.line;
			return &tokenData;
		}
		else if (strcmp(value, "END") == 0) {
			tokenData.type = T_END;
			tokenData.value = *value;
			tokenData.line = scanner.line;
			return &tokenData;
		}
		else if (strcmp(value, "PRINT") == 0) {
			tokenData.type = T_PRINT;
			tokenData.value = *value;
			tokenData.line = scanner.line;
			return &tokenData;
		}
		else {
			tokenData.type = T_ID;
			tokenData.value = *value;
			tokenData.line = scanner.line;
			return &tokenData;
		}
	}// end alpha check

	
	// check for a digit
	if (isdigit(*scanner.position)) {
		char* start = scanner.position;
		while (isdigit(*scanner.position)) {
			scanner.position++;
		}

		size_t len = sizeof(char) * (scanner.position - start);
		char* value = (char*)malloc(len + 1);
		memcpy(value, start, len);
		value[len] = '\0';

		tokenData.type = T_NUM;
		tokenData.value = *value;
		tokenData.line = scanner.line;
		return &tokenData;
	}// end check for digit

	// if we are still in the function, then it is unknown token
	printf("Unknown token %c at line %d\n", *scanner.position, scanner.line);
	
	
	// this might be too extreme, lets just send back a tokenData indicating 
	// we couldn't process anything.
	//exit(1);

	tokenData.type = T_NULL;
	tokenData.value = 0;
	tokenData.line = 0;
	return &tokenData;
}

