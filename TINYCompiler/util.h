//
//  util.h
//  TINYCompiler
//
//  Created by 王点 on 16/4/18.
//  Copyright © 2016年 wd. All rights reserved.
//

#ifndef util_h
#define util_h

void printToken(TokenType, const char*);

TreeNode* newStmtNode(StmtKind);

TreeNode* newExpNode(ExpKind);

char* copyString(char*);

void printTree(TreeNode*);


#endif /* util_h */
