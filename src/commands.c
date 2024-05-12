// #include "commands.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "jval.h"

// Commands new_Commands()
// {

//     Commands this= (Commands)malloc(sizeof(struct COMMANDS));

//     this->commandFunc=&commandFunc;
//     this->del=&del_Commands;
//     this->write=&write_Commands;
//     this->remove=&remove_Commands;
//     this->stop=&stop_Commands;
//     this->toEnd=&toEnd_Commands;

//     return this;
// }

// void* commandFunc(const Commands this,char* commandText)
// {
//     void* func;
//     //void (*func)();
//     func=NULL;
//     if(commandText==NULL)
//     {
//         return NULL;
//     }
//     else if(strcmp(commandText,"yaz:")==0)
//     {
//         func=&write_Commands;
//     }
//     else if(strcmp(commandText,"sil:")==0)
//     {
//         func=&remove_Commands;
//     }
//     else if(strcmp(commandText,"sonagit:")==0)
//     {
//         func=&toEnd_Commands;
//     }
//     else if(strcmp(commandText,"dur:")==0)
//     {
//         func=&stop_Commands;
//     }
    
//     return func;
// }
// Dllist write_Commands(const Commands this,Dllist cursorNode,int numberOfLetters,char letter)
// {
//     for (size_t i = 0; i < numberOfLetters; i++)
//     {
//         dll_insert_a(cursorNode, new_jval_c(letter));
//         cursorNode = dll_next(cursorNode);
//     }
//     return cursorNode;
// }
// Dllist remove_Commands(const Commands this,Dllist cursorNode,int numberOfLetters,char letter)
// {
//     int deletedNodes=0;
//     Dllist ptr =cursorNode;
//     Dllist list =dll_first(cursorNode);
//     list = list->blink;
//     // verilen dugumden baslayarak sentinele kadar git sentinelde dur
//     while(ptr!=list)
//     {
//         if(ptr->val.c==letter && deletedNodes<numberOfLetters)
//         {
//             Dllist temp=ptr->blink;
//             dll_delete_node(ptr);
//             ptr=temp;
//             deletedNodes++;
//         } 
//         else{
//             ptr=ptr->blink;
//         }
//     }
//     // sentinelden sonraki dugum yani ilk dugumu döndüm. 
//     return ptr->flink;
// }
// Dllist toEnd_Commands(const Commands this,Dllist cursorNode)
// {
//     printf("toEND ..\n");

// }
// Dllist stop_Commands(const Commands this)
// {
//     printf("stop ..\n");

// }
// void del_Commands(const Commands this)
// {
//     printf("delete ..\n");

// }