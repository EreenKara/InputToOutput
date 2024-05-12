#include "program.h"
#include "stdlib.h"
#include "string.h"
#include "utility.h"
Program new_Program()
{
    Program this = (Program) malloc(sizeof(struct PROGRAM));
    this->sentinelNode = new_dllist();
    this->cursorNode=this->sentinelNode;
    this->is=NULL;
    this->supportedFormats=1;
    this->inputFileFormat = (char**)malloc(sizeof(char*)*this->supportedFormats);
    for (size_t i = 0; i < this->supportedFormats; i++)
    {
        this->inputFileFormat[i] = (char*)malloc(sizeof(char)*5);
        strcpy(this->inputFileFormat[i],".dat");
    }


    this->start=&start;
    this->checkTextFile=&checkTextFile;
    this->toString=&toString_Program,
    this->executeCommands=&executeCommands;
    this->toFile=&toFile_Program;
    this->write_letter_Program=&write_letter_Program;
    this->remove_letter_Program=&remove_letter_Program;
    this->to_end_Program=&to_end_Program;
    this->stop_Program=&stop_Program;
    this->get_letter=&get_letter;
    this->del=&del_Program;


    return this;
}
void start(const Program this,char* inputFileName,char* outputFileName)
{
    // egerki input istenilen formatta degilse
    if(!(this->checkTextFile(this,inputFileName)))
    {
        fprintf(stderr, "HATALI BIR TEXT GIRISI: UZANTISI .dat DEGIL. Varsayilan input kullanilacaktir\n");
        strcpy(inputFileName,"sampleInput.dat");
    }
    if(!this->checkTextFile(this,outputFileName))
    {
        fprintf(stderr, "HATALI BIR TEXT CIKISI: UZANTISI .dat DEGIL. Varsayilan output kullanilacaktir\n");
        strcpy(outputFileName,"sampleOutput.dat");
    }
    this->inputFileName=inputFileName;
    this->outputFileName=outputFileName;
    this->is=new_inputstruct(inputFileName);
    this->executeCommands(this);
    char * text = this->toString(this);
    printf("%s",text);
}
bool checkTextFile(const Program this,char* fileName)
{
    // main'de hallettim.
    // if(inputFileName==NULL||inputFileName=="") return False;

    char* inputFileFormat=NULL;
    char* temp=NULL;
    // input file'da nokta olarak isimde kullanılmıs olabilri ben ise en sonda uzantıyı 
    // tanımlayan noktayı bulmak için butun input file'ı donuyorum
    temp = strchr(fileName,'.');
    while(temp!=NULL){
        inputFileFormat =temp; 
        temp= strchr(temp+1,'.');
    }  
    
    if(inputFileFormat==NULL) return False;

    bool equal =False;
    // input'un uzantısının desteklenen bir formatta olup olmadıgını kontrol ediyorum.
    for(int i = 0 ; i<this->supportedFormats; i++)
    {
        if(strcmp(inputFileFormat,this->inputFileFormat[i])==0) equal = True;
    }
    return equal;
}
void executeCommands(const Program this)
{
    while (get_line(this->is)>=0)
    {
        // Egerki bir satir bos ise onu geciyorum.
        if(this->is->NF==0) continue;
        // Girdi olarak gelen komutun command icerisindeki esdeger fonksiyonu 

        if(strcmp(this->is->fields[0],"dur:")==0)
        {
            // printf("dur calisti.\n");
            this->stop_Program(this);
            return;
        }
        else if(strcmp(this->is->fields[0],"yaz:")==0){
            // printf("yaz calisti.\n");
            for (size_t i = 1; i < this->is->NF; i=i+2)
            {
                // BURADA HATA OLABILIR DIKKAT ET.
                bool is_number = isNumber(this->is->fields[i]);
                if(!is_number)
                {
                    fprintf(stderr, "%d. satirda sayi olmasi gerekirken farkli bir format algilandi. Bu islenen atlaniyor: %s \n",this->is->line,this->is->fields[i]);
                    continue;
                } 
                    
                int numberOfLetters=atoi(this->is->fields[i]);
                char letter = this->get_letter(this,this->is->fields[i+1]);
                this->write_letter_Program(this,numberOfLetters,letter);
            }
        }
        else if(strcmp(this->is->fields[0],"sil:")==0){
            // printf("sil calisti.\n");
            for (size_t i = 1; i < this->is->NF; i=i+2)
            {
                // BURADA HATA OLABILIR DIKKAT ET.
                bool is_number = isNumber(this->is->fields[i]);
                if(!is_number){
                    fprintf(stderr, "%d. satirda sayi olmasi gerekirken farkli bir format algilandi. Bu islenen atlaniyor: %s \n",this->is->line,this->is->fields[i]);
                    continue;
                }
                int numberOfLetters=atoi(this->is->fields[i]);
                char letter = this->get_letter(this,this->is->fields[i+1]);
                this->remove_letter_Program(this,numberOfLetters,letter);
            }
        }
        else if (strcmp(this->is->fields[0],"sonagit:")==0){
            // printf("sonagit calisti.\n");
            this->to_end_Program(this);
        }
        else{
            // printf("hata var calisti.\n");
            fprintf(stderr, "Input file icerisinde hatali bir komut bulundu. Bu komut islenemedi ve bu satir atlaniyor.\n");
        }
        
    }
}
char get_letter(const Program this ,char* text){
    char letter =*text;
    int length = strlen(text);
    if (length>1){
        // normal bir karakter değilse ( ornegin : \n ) buraya düşecek
        if(text[0]=='\\') {
            switch (text[1])
            {
            case 'n' :
                letter = '\n';
                break;
            case 'b': 
                letter = ' ';
                break;
            case 't':
                letter = '\t';
                break;
            case '\"':
                letter = '\"';
                break;
            case '\'':
                letter = '\'';
                break;
            case '\\' :
                letter = '\\';
                break;
            case '\?':
                letter = '\?';
                break;
            default:
                fprintf(stderr, "Escape karakteri algilandi ancak ozel karakter tanimli degil. Sadece escape karakteri basiliyor.\n");
                letter= '\\';
                break;
            }
        }
        else
        {
            // Burada hatalı bir format var ancak ben bu hatalı formattan dolayı sistemin çökmesi yerine uyarı mesajı ile yazdırıacagım.
            fprintf(stderr, "Islenecek olan karakter 2'den buyuk oldugu icin sadece ilk karakteri alindi : %c\n",*text);
            letter=*text;
        }
        
    }

    return letter;
}
void write_letter_Program(const Program this,int number_of_letters,char letter)
{
    for (size_t i = 0; i < number_of_letters; i++)
    {
        dll_insert_a(this->cursorNode, new_jval_c(letter));
        this->cursorNode = this->cursorNode->flink;
    }
}
void remove_letter_Program(const Program this,int number_of_letters,char letter)
{
    Dllist temp=this->cursorNode;
    int deletedNodeNumber=0;
    while(temp!=this->sentinelNode)
    {
        if(deletedNodeNumber>=number_of_letters) break;
        if(temp->val.c==letter)
        {
            Dllist removeNode=temp;
            temp=temp->blink;
            dll_delete_node(removeNode);
            deletedNodeNumber++;
        } 
        else{
            temp=temp->blink;
        }
    }

    // Cursor başa kadar gidiyor her bir silme işleminde Bu yüzden burada cursoru guncelliyorum
    // Egerki daha sonradan farklı yapmak sitersen burada cursoru guncelleme oldugu yerde kalsın.
    
    // en son silinen node'un bir öncesi
    this->cursorNode=temp;
}
void stop_Program(const Program this)
{
    this->toFile(this,NULL);
}
void to_end_Program(const Program this)
{
    this->cursorNode=this->sentinelNode->blink;
}


char* toString_Program(const Program this)
{
    char * text = (char*)malloc(sizeof(char)*500);
    strcpy(text,"");
    char chr[2] ; 
    Dllist temp=this->sentinelNode->flink;
    while(temp!=this->sentinelNode)
    {
        chr[0]=temp->val.c;
        chr[1]='\0';
        strcat(text,chr);
        temp=temp->flink;
    }
    return text;
}
void toFile_Program(const Program this,char* outputFileName)
{
    // Varsayılan olarak sınıftaki outputu kullan.
    if(outputFileName==NULL) outputFileName=this->outputFileName;
    // verilmis outputu kullan. Yani output aynı kalsın
    
    FILE *file;
    file = fopen(outputFileName, "w"); // Open file in write mode ("w")
    char* text = this->toString(this);
    if (file != NULL) { // Check if file was opened successfully
       
        fprintf(file,"%s",text);
        fclose(file); // Close the file when done
        printf("Basariyla dosyaya yazdirildi. \n");
    } else {
        fprintf(stderr, "Dosyaya yazma islemi sirasinda bir hata gerceklesti.\n");
    }
    free(text);
}
void del_Program(const Program this)
{
    if(this->is!=NULL ) jettison_inputstruct(this->is);
    for (size_t i = 0; i < this->supportedFormats; i++)
    {
        free(this->inputFileFormat[i]);
    }
    free(this->inputFileFormat);
    free_dllist(this->sentinelNode);
}