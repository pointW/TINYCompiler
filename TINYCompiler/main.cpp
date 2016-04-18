//
//  main.cpp
//  TINYCompiler
//
//  Created by 王点 on 16/4/18.
//  Copyright © 2016年 wd. All rights reserved.
//

#include <iostream>
#include "globals.h"
#include "scan.h"

int lineno = 0;
FILE* source;
FILE* listing;
FILE* code;

int EchoSource = TRUE;
int TraceScan = TRUE;


int main(int argc, const char * argv[]) {
    char pgm[20] = "1.tny";
//    if (argc != 2){
//        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
//        exit(1);
//    }
//    strcpy(pgm, argv[1]);
//    if (strchr(pgm, '.') == NULL)
//        strcat(pgm, ".tny");
    source = fopen(pgm, "r");
    if (source == NULL){
        fprintf(stderr, "File %s not found\n", pgm);
        exit(1);
    }
    listing = stdout;
    fprintf(listing, "\nTINY COMPILATION: %s\n", pgm);
    while (getToken()!=ENDFILE);
    return 0;
}
