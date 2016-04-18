//
//  scan.h
//  TINYCompiler
//
//  Created by 王点 on 16/4/18.
//  Copyright © 2016年 wd. All rights reserved.
//

#include "globals.h"

#ifndef scan_h
#define scan_h

#define MAXTOKENLEN 40

extern char tokenString[MAXTOKENLEN+1];

TokenType getToken(void);


#endif /* scan_h */
