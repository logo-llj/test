#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 定义单词种别码
#define BEGIN 1
#define IF 2
#define THEN 3
#define WHILE 4
#define FOR 5
#define END 6
#define INT 7
#define ELSE 8
#define IDENTIFIER 10
#define DIGIT 20
#define ASSIGN 21
#define ADD 22
#define SUB 23
#define MUL 24
#define DIV 25
#define LPAREN 26
#define RPAREN 27
#define LBRACKET 28
#define RBRACKET 29
#define LBRACE 30
#define RBRACE 31
#define COMMA 32
#define COLON 33
#define SEMICOLON 34
#define GREATER 35
#define LESS 36
#define GREATER_EQUAL 37
#define LESS_EQUAL 38
#define NOT_EQUAL 40
#define ERROR -1
#define OVER 1000

// 检查是否为关键字并返回种别码
int isKeyword(char* str) {
    if (strcmp(str, "begin") == 0) return BEGIN;
    if (strcmp(str, "if") == 0) return IF;
    if (strcmp(str, "then") == 0) return THEN;
    if (strcmp(str, "while") == 0) return WHILE;
    if (strcmp(str, "for") == 0) return FOR;
    if (strcmp(str, "end") == 0) return END;
    if (strcmp(str, "int") == 0) return INT;
    if (strcmp(str, "else") == 0) return ELSE;
    return 0;
}

// 词法分析函数
void lexer(char* input) {
    int i = 0, len = strlen(input);
    printf("Your words:\n%s\n", input);
    while (i < len) {
        // 跳过空白字符
        while (isspace(input[i])) i++;
        if (i >= len) break;
        // 识别标识符或关键字
        if (isalpha(input[i])) {
            char token[50] = {0};
            int j = 0;
            while (isalnum(input[i])) {
                token[j++] = input[i++];
            }
            int code = isKeyword(token);
            if (code) {
                printf("(%d,%s)\n", code, token);
            } else {
                printf("(%d,%s)\n", IDENTIFIER, token);
            }
            continue;
        }
        // 识别数字
        if (isdigit(input[i])) {
            char token[20] = {0};
            int j = 0;
            while (isdigit(input[i])) {
                token[j++] = input[i++];
            }
            printf("(%d,%s)\n", DIGIT, token);
            continue;
        }
        // 识别运算符和界符
        switch (input[i]) {
            case '=':
                if (input[i + 1] == '=') {
                    printf("(%d,==)\n", NOT_EQUAL);
                    i++;
                } else {
                    printf("(%d,=)\n", ASSIGN);
                }
                break;
            case '+':
                printf("(%d,+)\n", ADD);
                break;
            case '-':
                printf("(%d,-)\n", SUB);
                break;
            case '*':
                printf("(%d,*)\n", MUL);
                break;
            case '/':
                printf("(%d,/)\n", DIV);
                break;
            case '(':
                printf("(%d,()\n", LPAREN);
                break;
            case ')':
                printf("(%d,))\n", RPAREN);
                break;
            case '[':
                printf("(%d,[)\n", LBRACKET);
                break;
            case ']':
                printf("(%d,])\n", RBRACKET);
                break;
            case '{':
                printf("(%d,{)\n", LBRACE);
                break;
            case '}':
                printf("(%d,})\n", RBRACE);
                break;
            case ',':
                printf("(%d,)\n", COMMA);
                break;
            case ':':
                printf("(%d,)\n", COLON);
                break;
            case ';':
                printf("(%d,;)\n", SEMICOLON);
                break;
            case '>':
                if (input[i + 1] == '=') {
                    printf("(%d,>=)\n", GREATER_EQUAL);
                    i++;
                } else {
                    printf("(%d,>)\n", GREATER);
                }
                break;
            case '<':
                if (input[i + 1] == '=') {
                    printf("(%d,<=)\n", LESS_EQUAL);
                    i++;
                } else {
                    printf("(%d,<)\n", LESS);
                }
                break;
            default:
                printf("(%d,ERROR)\n", ERROR);
        }
        i++;
    }
}

int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);
    // 去除fgets读取的换行符
    input[strcspn(input, "\n")] = '\0'; 
    lexer(input);
    return 0;
}