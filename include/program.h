#ifndef PROGRAM_H
#define PROGRAM_H
#include "dllist.h"
#include "fields.h"
#include "boolean.h"

// YORUM SATIRI YAPTIKLARIM PRIVATE OLAN FONKSIYONLAR

struct PROGRAM
{
    IS is;
    Dllist cursorNode;
    Dllist sentinelNode;
    char** inputFileFormat;
    int supportedFormats;
    char* inputFileName;
    char* outputFileName;

    void (*start)(struct PROGRAM*,char* inputFileName,char* outputFileName);
    bool (*checkTextFile)(struct PROGRAM*,char* inputFileName);
    char*  (*toString)(struct PROGRAM*);
    void (*executeCommands)(struct PROGRAM*);
    void (*toFile)(struct PROGRAM*,char* outputFileName);
    void (*write_letter_Program)(struct PROGRAM*,int,char);
    void (*remove_letter_Program)(struct PROGRAM*,int,char);
    void (*stop_Program)(struct PROGRAM*);
    void (*to_end_Program)(struct PROGRAM*);
    char (*get_letter)(struct PROGRAM*,char* );
    void (*del)(struct PROGRAM*);

};
typedef struct PROGRAM* Program;

// YORUM SATIRI YAPTIKLARIM PRIVATE OLAN FONKSIYONLAR

Program new_Program();
void start(const Program,char* inputFileName,char* outputFileName);
bool checkTextFile(const Program,char* inputFileName);
void executeCommands(const Program);
char* toString_Program(const Program);
void toFile_Program(const Program,char* outputFileName);
void write_letter_Program(const Program,int,char);
void remove_letter_Program(const Program,int,char);
void stop_Program(const Program);
void to_end_Program(const Program);
char get_letter(const Program ,char*);
void del_Program(const Program);

#endif
