#include "../include/commands.h"

int main()
{	
	char buffer[100];
	int nbytes = 100;
	char command[100];
	char exit[4];
	char pwd[3];
	char cd[2];
	char ls[2];
	char grep[4];
	char exec[4];
	char* program[20];
	char* token = NULL;
	char *commandToken = NULL;
	pid_t pid;
    int status;
	const char *invalid_characters = "./";
	const char *pipeCharacter = "|";
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Welcome to the Landy Shell\n");
	printf("\nPlease enter a command: ");
	fgets(buffer, nbytes, stdin);

	//STR CPY COMMANDS AND THINGS WE WILL CHECK FOR
	strcpy(command, buffer);
   	strcpy(exit, "exit");
   	strcpy(pwd, "pwd");
   	strcpy(cd, "cd");
   	strcpy(ls, "ls");
   	strcpy(grep, "grep");
   	strcpy(exec, "./");

   	//ERROR CHECK STR CPY
   	if (command == NULL || exit == NULL || pwd == NULL || cd == NULL || ls == NULL || grep == NULL || exec == NULL)
   	{
   		perror("\nSTRCPY DID NOT WORK\n");
   		return -1;
   	}
    
	commandToken = strtok(buffer, " \n");
	//MAKE SURE THEY INPUTED A COMMAND
	while (commandToken == NULL)
	{
		printf("\nError no commmand inserted\n");
		printf("Please enter a command: ");
		fgets(buffer, nbytes, stdin);
		commandToken = strtok(buffer, " \n");
		
	}
	if (strchr(invalid_characters, *buffer))
	{
   		commandToken = "./";
   	}

   	//SHELL EXECUTION
	while (strcmp(commandToken, exit) != 0)
	{
		token = strtok(buffer, "./ \n");
		
		//PARSE IT ONCE AND SEE IF IT HAS A PIPE |

			//SINGLE COMMAND
			
			//PRINT WORKING DIRECTORY
			if (strcmp(commandToken, pwd) == 0)
			{
				//FORK
				if ((pid = fork()) == -1) {
					  perror("fork error");
					  _exit(EXIT_FAILURE);
				}
				else if (pid == 0) 
				{ 
					if(getDirectory() != 0)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				else//PARENT PROCESS 
				{ 
					//WAIT FOR CHILD PROCESS
					if ((pid = wait(&status)) == -1)
					{
					   perror("wait error\n");
					}
		
					else 
					{   
						//CHECK STATUS
					   if (WIFSIGNALED(status) != 0)
					   {
						  printf("Child process ended because of signal %d\n",
								  WTERMSIG(status));
					   }
					   else if (WIFEXITED(status) != 0)
					   {
						 /* printf("Child process ended normally; status = %d\n",
								  WEXITSTATUS(status));*/
					   }
					   else
					   {
						  printf("Child process did not end normally\n");
					   }
					}
				}
			}


			//CHANGE DIRECTORY
			else if (strcmp(commandToken, cd) == 0)
			{
				token = strtok(NULL, " \n");
                if(moveDirectories(token) == 0)
				{
					//do nothing
				}
				else
				{
					printf("\nCD Failed\n");
					continue;
					//do not want shell to crash
				}
			}



			//LIST CONTENTS OF DIRECTORY
			else if (strcmp(commandToken, ls) == 0) 
			{
				token = strtok(NULL, " \n");
				if ((pid = fork()) == -1) {
					  perror("fork error");
					  _exit(EXIT_FAILURE);
				}
				else if (pid == 0) 
				{
					//CHILD PROCESS
					if (readDirectory(token) != 0)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				else //PARENT PROCESS
				{ 
					//WAIT FOR CHILD
					if ((pid = wait(&status)) == -1)
					{
						perror("wait error\n");
					}
		
					else 
					{ 
						//CHECK STATUS
					   if (WIFSIGNALED(status) != 0)
					   {
						  printf("Child process ended because of signal %d\n",
								  WTERMSIG(status));
					   }
					   else if (WIFEXITED(status) != 0)
					   {
						/*  printf("Child process ended normally; status = %d\n",
								  WEXITSTATUS(status));*/
					   }
					   else
					   {
						  printf("Child process did not end normally\n");
					   }
					}
				}

			}


			//EXECTUTE COMMAND
			else if (strcmp(commandToken, exec) == 0)
			{ 
				struct stat sb;
				//MAKE SURE FILE IS EXECUTABLE
				if (stat(token, &sb) == 0 && sb.st_mode & S_IXUSR){
					*program = token; 
					execute(program);
				}
				//IF ITS NOT 
				else{
					printf("NOT EXECUTABLE!\n");
				}
			}



			//GREP COMMAND
			else if (strcmp(commandToken, grep) == 0)
			{
				char* sub = NULL;
				char* filename = NULL;
				sub = strtok(NULL, " \n");
				filename = strtok(NULL, " \n");

				//FORK
				if ((pid = fork()) == -1) 
				{
					  perror("fork error");
					  _exit(EXIT_FAILURE);
				}
				else if (pid == 0) 
				{
					if (subString(sub, filename) != 0)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				else //PARENT PROCESS
				{ 
					//WAIT FOR CHILD
					if ((pid = wait(&status)) == -1)
					{
					   perror("wait error\n");
					}
		
					else 
					{
						//CHECK STATUS
					   if (WIFSIGNALED(status) != 0)
					   {
						  printf("Child process ended because of signal %d\n",
								  WTERMSIG(status));
					   }
					   else if (WIFEXITED(status) != 0)
					   {
						 /* printf("Child process ended normally; status = %d\n",
								  WEXITSTATUS(status));*/
					   }
					   else
					   {
						  printf("Child process did not end normally\n");
					   }
					}
				}
			}
			

			//EXIT 
			else if (strcmp(token, exit) == 0)
			{
				return 0;
			}
			
		
		/*else //MULTI COMMANDS
		{
			//PARSE COMMADND
			while ( token != NULL)
			{
				HERE IS WHERE I WOULD DO COMMANDS THAT CONTAIN A PARSE
				I WOULD PARSE THE STRING BASED ON THE | SO
				STR1 = THE FIRST COMMAND
				STR2 = THE SECOND COMMAND
				FORK
					I WOULD RUN STR1 THROUGH THE STRCMPS THAT I DO ABOVE TO FIND OUT WHICH COMMAND IT IS
						RETURN COMMAND ONE  RESULTS
					FORK
						RUN STR2 THOUGH STRCMPS THAT I DO ABOVE TO FIND OUT WHICH COMMAND IT IS
						PASS COMMAND 2 RESULTS FROM PASS 1
						RETURN COMMAND TWO RESULTS
					EXIT SECOND FORK
					PASS SECOND RESULTS TO STRCMP 1
					PRINT OUT COMMMAND 1 RESULTS
				EXIT FIRST FORK
			}
		}*/

		//TO GET SECOND COMMAND
		printf("Please enter a command: ");
		fgets(buffer, nbytes, stdin);
		strcpy(command, buffer);
		commandToken = strtok(command, "./ \n");
		//ERROR CHECK THEY ENTERED A COMMAND
		while (commandToken == NULL)
		{
		printf("\nError no commmand inserted\n");
		printf("Please enter a command: ");
		fgets(buffer, nbytes, stdin);
		commandToken = strtok(buffer, " \n");
		}
		if (strchr(invalid_characters, *buffer))
		{
   			commandToken = "./";
   		}
	}
	
	printf("\nEXITING\n");
	return 0;
}
