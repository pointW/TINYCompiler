//
//  scan.cpp
//  TINYCompiler
//
//  Created by 王点 on 16/4/18.
//  Copyright © 2016年 wd. All rights reserved.
//

#include "scan.h"
#include "globals.h"
#include "util.h"

using namespace std;

typedef enum {
    START, INASSIGN, INCOMMENT, INNUM, INID, DONE
}StateType;

char tokenString[MAXTOKENLEN+1];

#define BUFLEN 256

static char lineBuf[BUFLEN];
static int linepos = 0;
static int bufsize = 0;

static char getNextChar(void){
    if (!(linepos < bufsize)){
        lineno++;
        if (fgets(lineBuf, BUFLEN-1, source)){
            if (EchoSource) fprintf(listing, "%4d: %s", lineno, lineBuf);
            bufsize = strlen(lineBuf);
            linepos = 0;
            return lineBuf[linepos++];
        }
        else {
            linepos++;
            return EOF;
        }
    }
    else return lineBuf[linepos++];
}

static void ungetNextChar(void){
    linepos--;
}

static struct{
    string str;
    TokenType tok;
} reservedWords[MAXRESERVED]
= {{"if", IF}, {"then", THEN}, {"else", ELSE}, {"end", END},
    {"repeat", REPEAT}, {"until", UNTIL}, {"read", READ}, {"write", WRITE}};

static TokenType reservedLookUp(string s){
    for(int i = 0; i<MAXRESERVED; i++){
        if(s == reservedWords[i].str){
            return reservedWords[i].tok;
        }
    }
    return ID;
}

TokenType getToken(void){
    int tokenStringIndex = 0;
    TokenType currentToken;
    StateType state = START;
    bool save;
    while (state != DONE){
        char c = getNextChar();
        save = true;
        switch (state){
            case START:
                if (isdigit(c))
                    state = INNUM;
                else if (isalpha(c))
                    state = INID;
                else if (c == ':')
                    state = INASSIGN;
                else if ((c == ' ') || (c == '\t') || (c == '\n'))
                    save = false;
                else if (c == '{'){
                    save = false;
                    state = INCOMMENT;
                }
                else{
                    state = DONE;
                    switch(c)
                    {
                        case EOF:
                            save = false;
                            currentToken = ENDFILE;
                            break;
                        case '=':
                            currentToken = EQ;
                            break;
                        case '<':
                            currentToken = LT;
                            break;
                        case '+':
                            currentToken = PLUS;
                            break;
                        case '-':
                            currentToken = MINUS;
                            break;
                        case '*':
                            currentToken = TIMES;
                            break;
                        case '/':
                            currentToken = OVER;
                            break;
                        case '(':
                            currentToken = LPAREN;
                            break;
                        case ')':
                            currentToken = RPAREN;
                            break;
                        case ';':
                            currentToken = SEMI;
                            break;
                        default:
                            currentToken = ERROR;
                            break;
                    }
                }
                break;
            case INCOMMENT:
                save = false;
                if (c == '}'){
                    state = START;
                }
                break;
            case INASSIGN:
                state = DONE;
                if (c == '='){
                    currentToken = ASSIGN;
                }
                else{
                    ungetNextChar();
                    save = false;
                    currentToken = ERROR;
                }
                break;
            case INNUM:
                if (!isdigit(c)){
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID:
                if (!isalpha(c)){
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case DONE:
            default:
                fprintf(listing, "Scanner Bug: state= %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
        }
        if ((save) && (tokenStringIndex <= MAXTOKENLEN)){
            tokenString[tokenStringIndex++] = c;
        }
        if (state == DONE){
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID){
                currentToken = reservedLookUp(tokenString);
            }
        }
    }
    if (TraceScan){
        fprintf(listing, "\t%d: ", lineno);
        printToken(currentToken, tokenString);
    }
    return currentToken;
}






























