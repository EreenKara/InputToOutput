#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "program.h"

int main(int argc, char **argv)
{
    char* inputFileName= (char*) malloc(sizeof(char)*100);
    char* outputFileName= (char*) malloc(sizeof(char)*100);
    strcpy(inputFileName,"sampleInput.dat");
    strcpy(outputFileName,"sampleOutput.dat");
    Program program = new_Program();
    if(argc<3) 
    {
        fprintf(stderr,"Input ve/veya output dosyasi girmediginiz icin tanimli olanlar kullanilacaktir\n");
    }
    else if( strcmp(argv[1],"")==0||strcmp(argv[2],"")==0) {
        fprintf(stderr,"Input veya output dosyasini bos girdiginiz icin tanimli olanlar kullanilacaktir\n");
    }
    else{
        // Her sey yolunda.
        strcpy(inputFileName,argv[1]);
        strcpy(outputFileName,argv[2]);
    }
    

    
    program->start(program,inputFileName,outputFileName);
    program->del(program);

    
    free(inputFileName);
    free(outputFileName);


}