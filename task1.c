#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main(int ardc, char *argv[]){
 	char *input = NULL;
 	size_t n=0;
 	
 	for(; ; free(input)){	//main loop 
 	 n=0;
 	 input = NULL;
 	 printf("$ ");	//prompt
 	 n = getline(&input,&n, stdin); //get input from user
	 input[--n]=0;	//terminate the \n char
	 
	 char **paramlist = calloc(n++, sizeof(char*)); // paramlist to split the user input
	 char *token = NULL;
	 int i=0;
	 //split user input into paramlist 
	 for(token=strtok(input," "); token ;token=strtok(NULL," "))
	 	paramlist[i++] =token;

	 if(!paramlist[0]) continue;	// check if input is empty command
	 if(!strcmp(paramlist[0],"leave")) break;	//check if leave command
	
	 if(fork()==0){
	 	//child block
	 char * path = strdup(getenv("PATH")); // copy the PATH variable 
	 for(char *lib=strtok(path,":");lib;lib=strtok(NULL,":")){ 
	 	char *to_check = malloc(strlen(lib)+1+strlen(paramlist[0])+1);
	 	sprintf(to_check,"%s/%s", lib,paramlist[0]); 
	 	//printf("%s\n",to_check);
	 	execv(to_check,paramlist);
	 	free(to_check);

	 }
	 printf("command not found\n");
	 free(input);
	 free(paramlist);
	 exit(1);
	 free(path);
	 }else{
	 	//parant block
	 	int status;
	 	wait(&status);
	 }
	 free(paramlist);
 	} 
 	free(input);	
 	return 0;
}