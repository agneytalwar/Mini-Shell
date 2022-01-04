The mini shell is designed to simulate the bash shell of UNIX kernel <br/>

COMPILE FILE AS:      g++ minishell.c <br/>
RUN FILE AS:          ./a.out <br/>

Functions in Mini shell and their description:<br/>

bool takeInput(char*) - TAKES INPUT FROM USER<br/>
char** ConverttoList(char*) - BREAKS GIVEN INPUT INTO WORDS<br/> 
void printShellPrompt() - PRINTS THE CURRENT DIRECTORY PROMPTING THE USER TO GIVE INPUT<br/>
void AddtoHistory(char*) - ADDS COMMAND GIVEN BY USER TO HISTORY<br/>
bool isHistory(char*) - CHECKS IF USER HAS ENETERD COMMAND TO PRINT HISTORY<br/>
bool ChangeDir(char*) - ALLOWS USER THE CHANGE DIRECTORY<br/>
bool Echo(char*) -     PRINTS USER INPUT OR IN CASE OF ENVIRONMENT VARIABLES , THEIR VALUE<br/> 
bool SetEnv(char*,char**) - TO SET VALUE OF ENVIRONMENT VARIABLE<br/>
bool Printenv(char*,char**) - TO PRINT VALUE OF ENVIRONMENT VARIABLE<br/>
bool isPipe(char*) - CHECKS IF COMMAND CONTAINS A PIPE OR NOT<br/>
bool ExecutePipedCmds(char*) - FUNCTION TO EXECUTE PIPED COMMANDS <br/>
bool Execute(char**) - FUNCTION TO EXECUTE EXTERNAL COMMANDS<br/>
bool toExit(char*) - ALLOWS USER TO TERMINATE THE SHELL <br/>
bool CheckRedir(char*) - CHECKS IF USER REQUIRES REDIRECTION OF INPUT OR OUTPUT<br/>
bool InputRedir(char*) - CHECKS IF USER REQUIRES REDIRECTION OF INPUT <br/>
bool OutputRedir(char*) - CHECKS IF USER REQUIRES REDIRECTION OF OUTPUT<br/>
bool AppendRedir(char*) -CHECKS IF USER REQUIRES APPENDING A FILE<br/>
<br/>
Environment variables are: USER, HOME, SHELL, TERM<br/>
<br/>
Features and example commands of designed Mini Shell:<br/>
<br/>
For help :                       help<br/>
For echo :                       echo hey there<br/>
For echo environment variable:   echo $TERM<br/>
For setting an envir. variable:  setenv TERM=vt100<br/>
For printing an envir. variable: printenv TERM<br/>
For changing the directory:      cd<br/>
For history:                     history<br/>
For piping :                     cat input.txt | wc<br/>
For input redirection :          wc -c <input.txt      <br/>
For output redirection:          ls >output.txt<br/>
For input+output redirection:    wc <input.txt >output.txt<br/>
For append:                      ls >>output.txt<br/>
For exiting:                     exit<br/>
<br/>
List of linux external commands included in  minishell :<br/>
man, which, chsh, whereis, passwd, date, cal, clear, sleep, history, apropos, exit, logout, shutdown, ls, cat, more, less, touch, cp, mv, rm, find, mkdir, cd, pwd, rmdir, chmod, grep<br/>
