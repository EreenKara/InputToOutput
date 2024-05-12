// #ifndef COMMANDS_H
// #define COMMANDS_H
// #include "dllist.h"
// #include "boolean.h"
// struct COMMANDS{

//     void* (*commandFunc)(struct COMMANDS*,char*);
//     Dllist (*write)(struct COMMANDS*,Dllist,int,char);
//     Dllist (*remove)(struct COMMANDS*,Dllist,int,char);
//     Dllist (*toEnd)(struct COMMANDS*,Dllist);
//     Dllist (*stop)(struct COMMANDS*);
//     void (*del)(struct COMMANDS*);
// };
// typedef struct COMMANDS* Commands;

// Commands new_Commands();
// void* commandFunc(const Commands,char*);
// Dllist write_Commands(const Commands,Dllist,int,char);
// Dllist remove_Commands(const Commands,Dllist,int,char);
// Dllist toEnd_Commands(const Commands,Dllist);
// Dllist stop_Commands(const Commands);
// void del_Commands(const Commands);

// #endif