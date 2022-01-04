The mini shell is designed to simulate the bash shell of UNIX kernel <br/>

COMPILE FILE AS:      g++ minishell.c <br/>
RUN FILE AS:          ./a.out <br/>

Functions in Mini shell and their description:<br/>

bool takeInput(char*) - TAKES INPUT FROM USER
char** ConverttoList(char*) - BREAKS GIVEN INPUT INTO WORDS 
void printShellPrompt() - PRINTS THE CURRENT DIRECTORY PROMPTING THE USER TO GIVE INPUT
void AddtoHistory(char*) - ADDS COMMAND GIVEN BY USER TO HISTORY
bool isHistory(char*) - CHECKS IF USER HAS ENETERD COMMAND TO PRINT HISTORY
bool ChangeDir(char*) - ALLOWS USER THE CHANGE DIRECTORY
bool Echo(char*) -     PRINTS USER INPUT OR IN CASE OF ENVIRONMENT VARIABLES , THEIR VALUE 
bool SetEnv(char*,char**) - TO SET VALUE OF ENVIRONMENT VARIABLE
bool Printenv(char*,char**) - TO PRINT VALUE OF ENVIRONMENT VARIABLE
bool isPipe(char*) - CHECKS IF COMMAND CONTAINS A PIPE OR NOT
bool ExecutePipedCmds(char*) - FUNCTION TO EXECUTE PIPED COMMANDS 
bool Execute(char**) - FUNCTION TO EXECUTE EXTERNAL COMMANDS
bool toExit(char*) - ALLOWS USER TO TERMINATE THE SHELL 
bool CheckRedir(char*) - CHECKS IF USER REQUIRES REDIRECTION OF INPUT OR OUTPUT
bool InputRedir(char*) - CHECKS IF USER REQUIRES REDIRECTION OF INPUT 
bool OutputRedir(char*) - CHECKS IF USER REQUIRES REDIRECTION OF OUTPUT
bool AppendRedir(char*) -CHECKS IF USER REQUIRES APPENDING A FILE

Environment variables are: USER, HOME, SHELL, TERM

Features and example commands of designed Mini Shell:

For help :                       help
For echo :                       echo hey there
For echo environment variable:   echo $TERM
For setting an envir. variable:  setenv TERM=vt100
For printing an envir. variable: printenv TERM
For changing the directory:      cd
For history:                     history
For piping :                     cat input.txt | wc
For input redirection :          wc -c <input.txt      
For output redirection:          ls >output.txt
For input+output redirection:    wc <input.txt >output.txt
For append:                      ls >>output.txt
For exiting:                     exit

List of linux external commands included in  minishell :
man, which, chsh, whereis, passwd, date, cal, clear, sleep, history, apropos, exit, logout, shutdown, ls, cat, more, less, touch, cp, mv, rm, find, mkdir, cd, pwd, rmdir, chmod, grep
