/*** Author @ Gaurav Mitra	***/
/***	A lexical analyser for restricted C language	***/
/***	Key features :	
			1.	Tokenizes C program
			2.	Identifies the Token types namely KEYWORDS, IDENTIFIERS,
				LITERALS, ASSIGN OP, RELATIONAL OP, ARITHMETIC OP,
				WHITE SPACE CHARS, DELIMITERS.
			3.	PROCESSES COMMENTS AND IGNORES THEM.
			4.	CREATES A SYMBOL TABLE.
			5.	DISPLAYS ROW AND COLUMN POSITION OF LEXEME.
***/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BUFFER_SIZE 10000

typedef enum types {
	KEYWORD = 1,
	IDENTIFIER = 2,
	ARITHMETIC = 3,
	RELATIONAL = 4,
	ASSIGN = 5,
	DELIMITER = 6,
	NUM = 7
}type;

struct symbol {
	unsigned int id;
	int xpos;
	int ypos;
	char* lex;
}SYMTAB[1000];

int PC = 0;
char* keywords[] = {"else","if","for","int","float","void","return"};
char arith_op[] = {'+' , '-' , '*' , '/'};
char assign_op = '=';
char relat_op[] = {'<','>'};
char ws[] = {' ','\t','\n'};
char delim[] = {'(', ')', ';', ',','{','}'};
char *buffer;
int breaks[100];
int lines = 1;

void readFile(char *filename) {
	FILE *fp;
	breaks[0] = 0;
	char line[200];
	fp = fopen(filename,"r");
	//int count = 0;
	while(fgets(line,255,(FILE*)fp)) {
		//printf("%d\n",strlen(line));
		int i;
		for(i = 0; i < sizeof(line); i++){
			if(line[i] == '/' && line[i + 1] == '/') {
				break;
			}
		}
		line[i] = '\0';
		//strncpy(dest,line,slash);
		//strncpy(line,dest,sizeof(dest));
		strcat(buffer,line);
		breaks[lines + 1] = breaks[lines] + strlen(line);
		lines++;
	}
}

int is_arithop(char c) {
	int i;
	for(i = 0; i < 3; i++) 
		if(arith_op[i] == c)
			return 1;
	return 0;
}

int is_assignop(char c) {
	if(assign_op == c)
		return 1;
	else
		return 0;
}

int is_relatop(char c) {
	int i;
	for(i = 0; i < 2; i++) 
		if(relat_op[i] == c)
			return 1;
	return 0;
}

int is_delim(char c) {
	int i;
	for(i = 0; i < 5; i++) 
		if(delim[i] == c)
			return 1;
	return 0;
}

int is_ws(char c) {
	int i;
	for(i = 0; i < 2; i++) 
		if(ws[i] == c)
			return 1;
	return 0;
}

int is_keyword(char *token) {
	int i;
	for(i = 0; i < 7; i++) {
		if(!strcmp(token,keywords[i])) {
			return 1;
		}
	}
	return 0;
}

int calculateYpos(int x) {
	//printf("%d\n",x);
	int i;
	for(i = 2; i < lines; i++) {
		if(breaks[i] > x) {
			//printf("%d : %d\n",breaks[i],x);
			return i - 1;
		}
	}
}

int checkNUM(char *token) {
	int i;
	int len = strlen(token);
	//printf("%s : %d\n",token,len);
	if(isdigit(token[0]))
		return 1;
	if(token[0] == '\"')
		return 1;
	return 0;
}

void addNode(type var,char *token,int x) {
	int result = 0;
	if(strlen(token) == 0 || token[0] == 10)
		return;
	if(var == IDENTIFIER) {
		result = checkNUM(token);
		//printf("result : %d",result);
	}
	SYMTAB[PC].lex = (char*)malloc(sizeof(char)*100);
	if (!result)
		SYMTAB[PC].id = var;
	else
		SYMTAB[PC].id = NUM;
	SYMTAB[PC].ypos = calculateYpos(x);
	SYMTAB[PC].xpos = x - breaks[SYMTAB[PC].ypos];
	strcpy(SYMTAB[PC].lex,token);
	PC++;
}

void addNodeChar(type var,char token,int x) {
	char *p = malloc(sizeof(char)*3);
	*p = token;
	*(p + 1) = '\0';
	SYMTAB[PC].lex = (char*)malloc(sizeof(char)*10);
	SYMTAB[PC].id = var;
	//SYMTAB[PC].xpos = x;
	SYMTAB[PC].ypos = calculateYpos(x);
	SYMTAB[PC].xpos = x - breaks[SYMTAB[PC].ypos];
	strcpy(SYMTAB[PC].lex,p);
	PC++;
}

void printSymbolTable() {
	FILE *f;
	f = fopen("output.txt","w");
	fprintf(f,"\t\tSYMBOL TABLE\n");
	fprintf(f,"\t\t------ -----\n\n");
	fprintf(f,"ID\tTOKEN\t\tLEXEME\tXPOS\tYPOS\n");
	fprintf(f,"--\t-----\t\t------\t----\t----\n");
	int i;
	for(i = 0; i < PC; i++) {
		char typ[15];
		switch(SYMTAB[i].id) {
			case 1 :
				strcpy(typ,"KEYWORD");
				break;
			case 2 :
				strcpy(typ,"IDENTIFIER");
				break;
			case 3 : 
				strcpy(typ,"ARITHMETIC");
				break;
			case 4 :
				strcpy(typ,"RELATIONAL");
				break;
			case 5 :
				strcpy(typ,"ASSIGN");
				break;
			case 6 :
				strcpy(typ,"DELIMITER");
				break;
			case 7 :
				strcpy(typ,"NUM");
		}
		if(SYMTAB[i].id == KEYWORD || SYMTAB[i].id == NUM)
			fprintf(f,"%d\t%s\t\t%s\t\t%d\t\t%d\n",SYMTAB[i].id,typ,SYMTAB[i].lex,SYMTAB[i].xpos,SYMTAB[i].ypos);
		else
			fprintf(f,"%d\t%s\t%s\t\t%d\t\t%d\n",SYMTAB[i].id,typ,SYMTAB[i].lex,SYMTAB[i].xpos,SYMTAB[i].ypos);		
		/*if(SYMTAB[i].id == 2) {
			printf("%c %c\n",SYMTAB[i].lex[0],SYMTAB[i].lex[1]);
		}*/
	}
	fclose(f);
}

int main(void) {
	int global_xpos = 0;
	char *filename = (char*)malloc(sizeof(char)*100);
	printf("Enter the filename : ",filename);
	scanf("%s",filename);
	buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	readFile(filename);
	int len = strlen(buffer);
	int tok_pos = 0, i;
	char *token = (char*)malloc(150);
	token[0] = '\0';
	for(i = 3; i < len; i++) {
		global_xpos++;
		char p = buffer[i];
		if(is_arithop(p) || is_assignop(p) || is_relatop(p) || is_delim(p)) {
			if(tok_pos > 0 && is_keyword(token)) {
	//			printf("Keyword : %s\n",token);
				addNode(KEYWORD,token,global_xpos);
				token[0] = '\0';
				tok_pos = 0;
			}
			else if(tok_pos > 0) {
	//			printf("Identifier : %s\n",token);
				addNode(IDENTIFIER,token,global_xpos);
				token[0] = '\0';
				tok_pos = 0;
			}
			
			if(is_arithop(p)) {
				addNodeChar(ARITHMETIC,p,global_xpos);
	//			printf("Arith op : %c\n",p);
			}
			else if(is_assignop(p)) {
				addNodeChar(ASSIGN,p,global_xpos);
	//			printf("Assign op : %c\n",p);
			}
			else if(is_relatop(p)) {
				addNodeChar(RELATIONAL,p,global_xpos);
	//			printf("Relational op : %c\n",p);
			}
			else if(is_delim(p)) {
				addNodeChar(DELIMITER,p,global_xpos);
	//			printf("Delimiter op : %c\n",p);
			}
		}
		else {
			if(is_ws(p)) {
				if(is_keyword(token)) {
	//				printf("Keyword : %s\n",token);
					addNode(KEYWORD,token,global_xpos);
					token[0] = '\0';
					tok_pos = 0;
				}
				else {
	//				printf("Identifier : %s\n",token);
					addNode(IDENTIFIER,token,global_xpos);
					token[0] = '\0';
					tok_pos = 0;
				}
			}
			else {
				token[tok_pos++] = p;
				token[tok_pos] = '\0';
			}
		}
	}
	printSymbolTable();
}
