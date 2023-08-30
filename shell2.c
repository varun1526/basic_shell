#include<stdio.h>
#include<readline/readline.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/history.h>
#define MAXCOM 1000
#define MAXLIST 100
#define clear() printf("\033[H\033[J")
char history_arr[MAXCOM][MAXLIST];
int history_count;
void init_shell(){
	clear();
	printf("\n\n\n\t\t**********************");
	printf("\n\n\n\t\t****** MY Shell ******");
	printf("\n\n\n\t\t**********************");
	char* username = getenv("USER");
	printf("\n\n\nUSER is: @%s ",username);
	printf("\n");
	sleep(1);
	clear();
}
void history(){
	FILE *ptr=fopen("/home/varun/Desktop/project/history.txt","rt");
	char c=getc(ptr);
	int count=1;
	if(c!=EOF){
		printf("%d ",count++);
	}
	while(c!=EOF){
		printf("%c",c);
		if(c=='\n'){
			c=getc(ptr);
			if(c!=EOF){
				printf("%d ",count++);
			}
		}
		else{
			c=getc(ptr);
		}
	}
	fclose(ptr);
}
void openHelp(){
	clear();
	printf("\n---->This shell is updation");
	printf("\n---->List of Commands: ");
	printf("\n-->cd");
	printf("\n-->ls");
	printf("\n-->exit");
	printf("\n-->piping is not allowed");
	printf("\n-->history");
	printf("\n-->delHistory");
	printf("\n-->improper space Handling");
	sleep(5);
	clear();
	return;
}
// deleting history
void delHistory(){
	FILE *ptr=fopen("/home/varun/Desktop/project/history.txt","wt");
	fclose(ptr);
	return;
}
// parsing space
void parseSpace(char *str,char **parsed){
	for(int i=0;i<MAXLIST;i++){
		parsed[i]=strsep(&str," ");
		if(parsed[i]==NULL){
			break;
		}
		if(strlen(parsed[i])==0){
			i--;
		}
	}
}
// checking if command contains pipe
int parsePipe(char* str, char** strpiped){
	if(strsep(&str,"|")){
		return 0;
	}
	return 1;
}
// own command handler
int ownCmdHandler(char **parsed){
	int NoOfOwnCmds=6,i,switchOwnArg=0;
	char* ListOwnCmds[NoOfOwnCmds];
	char* username;
	ListOwnCmds[0]="exit";
	ListOwnCmds[1]="cd";
	ListOwnCmds[2]="help";
	ListOwnCmds[3]="hello";
	ListOwnCmds[4]="history";
	ListOwnCmds[5]="delHistory";
	for(i=0;i<NoOfOwnCmds;i++){
		if(strcmp(ListOwnCmds[i],parsed[0])==0){
			switchOwnArg=i+1;
			break;
		}
	}
	if(switchOwnArg==1){
	
			printf("\nGoodbye\n");
			exit(0);
	}
	else if(switchOwnArg==2){	
		int x=chdir(parsed[1]);
		if(x==-1){
			printf("Directory doesn't exists");
		}
			return 1;
	}
	else if(switchOwnArg==3){
		openHelp();
		return 1;
	}
	else if(switchOwnArg==4){
		username=getenv("USER");
		printf("hello %s\n",username);
		return 1;
	}
	else if(switchOwnArg==5){
		history();
		return 1;
	}
	else if(switchOwnArg==6){
		delHistory();
		return 1;
	}
	else{
		return 0;
	}
}
// print Directory
void printDir(){
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	printf("\nDir: %s$ ", cwd);
}
// execute commands
void execArgs(char **parsed){
	pid_t pid=fork();
	if(pid==-1){
		printf("\n Failed forking child..");
	}
	else if(pid==0){
		if(execvp(parsed[0], parsed)<0){
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else{
		wait(NULL);
		return;
	}
}
// function to take input
int takeInput(char *str){
	char* buf;
	fflush(stdout);
	buf=readline("\n>>> ");
	if(strlen(buf)!=0){
		strcpy(str, buf);
		FILE *ptr=fopen("/home/varun/Desktop/project/history.txt","at");
		strcpy(history_arr[history_count],buf);
		fprintf(ptr,"%s\n",buf);
		fclose(ptr);
		return 0;
	}
	else{
		return 1;
	}
	
}
int processString(char* str,char** parsed){
	char* strpiped[2];
	int piped=0;
	// Checking if command contains pipe operator
	piped=parsePipe(str, strpiped);
	if(piped){
		printf("Piping is not allowed22.\n");
		return -1;
	}
	else{

		parseSpace(str,parsed);
	}
	if(ownCmdHandler(parsed)){
		return 0;
	}
	return 1;
}
// Main function
int main(){
	// Chacacter arrays to take input and parsing
	char inputString[MAXCOM],* parsedArgs[MAXLIST];
	int execFlag=0;
	// initializing shell
	init_shell();
	int size=0;
	while(1){
		// print Directory 
		printDir();
		if(takeInput(inputString)){
			continue;
		}
		// Checking if command is right if right return1
		execFlag=processString(inputString,parsedArgs);
		if(execFlag == 1){
			//execute command
			execArgs(parsedArgs);
		}
	}
	return 0;
}
