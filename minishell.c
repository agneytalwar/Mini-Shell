#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
bool takeInput(char*);
char** ConverttoList(char*);
void printShellPrompt();
void AddtoHistory(char*);
bool InternalCommands(char*,char**);
bool isHistory(char*);
bool ChangeDir(char*);
bool Echo(char*);
bool SetEnv(char*,char**);
bool Printenv(char*,char**);
bool isPipe(char*);
bool ExecutePipedCmds(char*);
bool Execute(char**);
bool toExit(char*);
bool CheckRedir(char*);
bool InputRedir(char*);
bool OutputRedir(char*);
bool AppendRedir(char*);
bool isHelp(char*);
int main()
{
   char input[100];
   while(1)
    {

        printShellPrompt();
        fflush(stdin);
        bool check =takeInput(input);
        if(!check)
        {
             continue;
        }
        AddtoHistory(input);
        char c[100];
        strcpy(c,input);
        char** list=ConverttoList(c);
        if(isHelp(input))
        {
             continue;
        }
        else if(toExit(input))
        {
            free(list);
            remove("/tmp/history.txt");
            break;
        }
        else if(SetEnv(input,list))
        {
            continue;
        }
        else if(Echo(input))
        {
            continue;
        }
        else if(CheckRedir(input))
        {
            char *copy1=(char *)malloc(100*sizeof(char));
            strcpy(copy1,input);
            char *copy2=(char *)malloc(100*sizeof(char));
            strcpy(copy2,input);
            char* outputfile;
            char* inputfile;
            char* appendfile;
            bool o=false,i=false,a=false;
            i=InputRedir(input);
            a=AppendRedir(input);
            if(!a)
            {
                o=OutputRedir(input);
            }
            int fd1,fd2;
            if(i)
            {
                  char*temp =strtok(copy1,"<");
                  inputfile=strtok(NULL,"> ");
                  int i=0;
                  while(1)
                  {
                      if(strchr(list[i],'<')!=NULL)
                      {
                          list[i]=nullptr;
                          break;
                      }
                      i++;
                  }
                  fd1=open(inputfile,O_RDONLY);
                  if(fd1<0)
                  {
                    printf("ERROR opening the input file.\n");
                    continue;
                  }
            }
            if(a)
            {
                char*temp1=strchr(copy2,'>');
                appendfile=strtok(temp1+2," ");
                if(!i)
                {
                  int i=0;
                  while(1)
                  {
                      if(strchr(list[i],'>')!=NULL)
                      {
                          list[i]=nullptr;
                          break;
                      }
                      i++;
                  }
                   fd2=open(appendfile,O_WRONLY | O_APPEND, 0777);
                   if(fd2<0)
                   {
                       printf("ERROR appending the file.\n");
                       continue;
                   }
                }
            }
            else if(o)
            {
               char*temp2=strchr(copy2,'>');
                outputfile=strtok(temp2+1," ");
                if(!i)
                {
                  int i=0;
                  while(1)
                  {
                      if(strchr(list[i],'>')!=NULL)
                      {
                          list[i]=nullptr;
                          break;
                      }
                      i++;
                  }}
                  //printf("%s\n",outputfile);
                  fd2=creat(outputfile, 0777 );
                  if(fd2<0)
                   {
                     printf("ERROR outputting the file.\n");

                   }
            }
            pid_t k;
            k = fork();
            if (k==0)
            {
                if(i)
                {
                       fclose(stdin);
                       dup2(fd1,STDIN_FILENO);
                       close(fd1);
                }
                if(a)
                {
                   dup2(fd2, STDOUT_FILENO);
                   close(fd2);
                }
                else if(o)
                {
                   fclose(stdout);
                   dup2(fd2, STDOUT_FILENO);
                   close(fd2);
                }
                if (execvp(list[0],list) < 0)
                {
                    printf("Command not found\n");
                }

            }
            if(i)
             {
               close(fd1);
             }
             if(a)
            {
               close(fd2);
            }
            if(o)
            {
               close(fd2);
            }
            wait(NULL);
            free(copy1);
            free(copy2);
            continue;
        }
        else if(InternalCommands(input,list))
        {
             continue;
        }

        else if(isPipe(input))
        {
            ExecutePipedCmds(input);
            continue;
        }
        else if(Execute((list)))
        {
            continue;
        }
        free(list);
    }
}
void printShellPrompt()
{
    //PRINTS THE CURRENT DIRECTORY PROMPTING THE USER TO GIVE INPUT
    char dir[100];
    getcwd(dir,100);
    printf("%s ",dir);
}
bool takeInput(char *c)
{
    //TAKES INPUT FROM USER
    scanf("%[^\n]%*c",c);
    if(c[0]=='\0' ||c[0]=='\n')
        return (false);
    else return (true);
}
char** ConverttoList(char* c)
{
    //BREAKS GIVEN INPUT INTO WORDS
    char** list=(char **)malloc(20*sizeof(char*));
    char* token=strtok(c," ");
    list[0]=token;
    int i=1;
    do{
        token=strtok(NULL," ");
        list[i]=token;
        i++;
    }while(token!=NULL);
      list[i-1]=NULL;
    return list;
}
void AddtoHistory(char *c)
{
    //ADDS COMMAND GIVEN BY USER TO HISTORY
    FILE *fPtr;
    fPtr = fopen("/tmp/history.txt", "a");
    fputs(c, fPtr);
    fputs("\n",fPtr);
    fclose(fPtr);
}
bool isHistory(char* input)
{
    //CHECKS AND PRINTS IF USER HAS ENTERED COMMAND TO PRINT HISTORY
    char c[100];
    strcpy(c,input);
    if(strcmp(strtok(c," "),"history"))
        {
             return false;
        }
        else{
            FILE *fptr;
            char s;
            fptr=fopen("/tmp/history.txt","r");
            while((s=fgetc(fptr))!=EOF) {
                   printf("%c",s);
            }
            fclose(fptr);
            return true;
        }
}
bool CheckEnv(char *input)
{
    //CHECKS IF USER HAS ENTERED AN ENVIRONMENT VARIABLE
    char c[100];
    strcpy(c,input);
    char *eptr=getenv(strtok(c," "));
    if(eptr!=NULL){
       printf("%s\n",eptr);
       return true;
    }
    return false;
}
bool ChangeDir(char *input)
{
    //ALLOWS USER THE CHANGE DIRECTORY
    char c[100];
    strcpy(c,input);
    char *firstword=strtok(c," ");
    if(strcmp(firstword,"cd")){
        return false;
    }
    else{
        char *reqddir=strtok(NULL," ");
        if(reqddir==NULL)
        {
            //change to /home/user
            chdir(getenv("HOME"));
        }
        else{
            //change to required directory
            if(chdir(reqddir)!=0){
                printf("Could not find the specified path\n");
            }
        }
        return true;
    }
}
bool Echo(char* input)
{
    //PRINTS USER INPUT OR IN CASE OF ENVIRONMENT VARIABLES , THEIR VALUE 
    if(strstr(input,"echo")==NULL)
          return false;
    if(strchr(input,'$')!=NULL)
    {
        char*temp =strtok(input,"$");
        temp=strtok(NULL,"$");
        if(temp==NULL)
        {
           printf("\n");
        }
        else{
            char* env=getenv(temp);
            if(env==NULL)
              printf("\n");
            else printf("%s\n",env);
        }
    }
    else 
    {
       char* temp=strtok(input," ");
       temp=strtok(NULL,"\n");
       if(temp==NULL)
           printf("\n");
       else printf("%s\n",temp);
    }
    return true;
}
bool SetEnv(char*input,char**list)
{
       //TO SET VALUE OF ENVIRONMENT VARIABLE
       if(strcmp(list[0],"setenv"))
           return false;
       else{ 
         char* envname=strtok(list[1],"=");
         char* envval=strtok(NULL,"=");
         if(envval==NULL)
         {
            printf("Please set value as : setenv envvarname=value (no spaces)\n");
            return true;
         }
         setenv(envname,envval,1);
         return true;
       }
}
bool Printenv(char* input,char** list)
{
    //TO PRINT VALUE OF ENVIRONMENT VARIABLE
    if(strcmp(list[0],"printenv"))
         return false;
    else{
        char* envname=getenv(list[1]);
        if(envname==NULL)
        {
            return true;
        }
        else{
            printf("%s\n",envname);
            return true;
        }
    }
}
bool InternalCommands(char*input,char**list)
{
    //TO EXECUTE SOME OF THE INTERNAL COMMANDS
    if(isHistory(input))
    {
        return true;
    }
    else if(Printenv(input,list)){
        return true;
    }
    else if(ChangeDir(input))
    {
        return true;
    }
    else return false;
}
bool toExit(char* input)
{
    //ALLOWS USER TO TERMINATE THE SHELL
    char c[100];
    strcpy(c,input);
    if(!strcmp(strtok(c," "),"exit") || !strcmp(strtok(c," "),"quit") || !strcmp(strtok(c," "),"x"))
        return true;
    else return false;
}
bool Execute(char** arglist)
{
    //FUNCTION TO EXECUTE EXTERNAL COMMANDS
    pid_t prcsid;
    int i=0;
    prcsid=fork();
    if(prcsid<0)
    {
        printf("Fork failure\n");
        return false;
    }
    else if(prcsid==0)
    {
        if(execvp(arglist[0],arglist)==-1){
            printf("Command Failed\n");
            return false;
        }
    }
    else
    {
       waitpid(prcsid,0,0);
    }
   return true;
}
bool isPipe(char* input)
{
    //CHECKS IF COMMAND CONTAINS A PIPE OR NOT
    int i=0;
    while(input[i]!='\0')
    {
        if(input[i]=='|')
        {
            return true;
        }
        i++;
    }
    return false;
}
bool ExecutePipedCmds(char *input)
{
    //FUNCTION TO EXECUTE PIPED COMMANDS
    char c[100];
    strcpy(c,input);
    char* cmd1=strtok(c,"|");
    char* cmd2=strtok(NULL,"|");

    char** arglist1=ConverttoList(cmd1);
    char** arglist2=ConverttoList(cmd2);

    int filedisctr[2];
    pid_t prcsid1,prcsid2;
    if(pipe(filedisctr)<0)
    {
        printf("Piping Failed\n");
        free(arglist1);
        free(arglist2);
        return false;
    }
    prcsid1=fork();
    if(prcsid1<0)
    {
        printf("Fork failure\n");
        free(arglist1);
        free(arglist2);
        return false;
    }
    else if(prcsid1==0)
    {
        dup2(filedisctr[1], 1);
        close(filedisctr[0]);
        close(filedisctr[1]);
        if(execvp(arglist1[0],arglist1)==-1){
            printf("Command 1 Failed\n");
            perror("bash");
            free(arglist1);
            free(arglist2);
            exit(EXIT_FAILURE);
            return false;
        }
    }
    else{
        prcsid2=fork();
        if(prcsid2<0)
        {
           printf("Fork failure\n");
           free(arglist1);
           free(arglist2);
           return false;
        }
        else if(prcsid2==0)
        {
            dup2(filedisctr[0], 0);
            close(filedisctr[1]);
            close(filedisctr[0]);
            if(execvp(arglist2[0],arglist2)==-1){
                 perror("bash");
                 free(arglist1);
                 free(arglist2);
                 exit(EXIT_FAILURE);
                 return false;
            }
        }
        else{
            close(filedisctr[0]);
            close(filedisctr[1]);
            wait(NULL);
            wait(NULL);
        }
    }
    free(arglist1);
    free(arglist2);
    return true;
}
bool CheckRedir(char* input)
{
     //CHECKS IF USER REQUIRES REDIRECTION OF INPUT OR OUTPUT
     if(strchr(input,'>')!=NULL || strchr(input,'<')!=NULL)
           return true;
     else return false;
}
bool InputRedir(char* input)
{
    //CHECKS IF USER REQUIRES REDIRECTION OF INPUT 
    if(strchr(input,'<')!=NULL)
    {
         return true;
    }
    else return false;
}
bool OutputRedir(char* input)
{
     //CHECKS IF USER REQUIRES REDIRECTION OF OUTPUT
     if(strchr(input,'>')!=NULL)
    {
        return true;
    }
    else return false;
}
bool AppendRedir(char*input)
{
    //CHECKS IF USER REQUIRES APPENDING A FILE
    if(strstr(input,">>")!=NULL)
    {
         return true;
    }
    else return false;
}
bool isHelp(char* input)
{
   //GIVES INFO ABOUT INTERNAL COMMANDS
   if(strstr(input,"help"))
   {
       printf("Hey there\nHere is the list of internal commands:\ncd (to change directory)\nhistory (to view commands entered in the past)\necho (to print the input or value of environment variables)\nsetenv envvarname=varvalue (to set value of environment variables)\nprintenv envvarname (to print value of environment variable)\nexit (to exit the shell)\n");
       return true;
   }
   else return false;
}
