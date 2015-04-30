#include "../../include/commands.h"
#include <string.h>

char* buffer [100];

void main ()
{
	scanf("%c", buffer);
	do
	{
		const char s[2] = "|";
		char *token;
		//CPY STRING TO TOKEN INCASE THERE IS A | SO WE DONT LOSE THE COMMAND WHEN PARSING IT
		strcpy(token, buffer);

		//PARSE IT ONCE AND SEE IF IT HAS AND |
		token = strok(str,s);
		if (token == NULL)
		{
			//SINGLE COMMAND
			//POSSIBLY ALSO PARSE BY SPACE HERE TO GET COMMAND AND THEN ARGUEMENTS FOR EACH COMMAND?
			if (buffer == 'pwd')
			{
				getDirectory();
			}
			else if (buffer == 'cd')
			{
				moveDirectoryies(buffer);
			}
			else if (buffer == 'ls') //NEED TO CHECK FOR ls <file> MAYBE ALSO PARSE BY A SPACE?
			{
				changeDirectory(buffer);
			}
			else if (buffer = 'exec*') //NEED TO GET THE OUTPUT SO MAYBE ALSO PARSE BY A SPACE WHEN IN THE SINGLE COMMAND FOR LOOP?
		}
		else //MULTI COMMANDS
		{
			//PARSE COMMADN
			while ( token != NULL)
			{

			}
		}
		
	}while (buffer != 'exit')
	

	/*while they do not exit
		check through there input command
		parse command
		if command has no pipes
			if else loop of commands
			run single command
		else
			parse commands and run 1 at a time
			run multiple commands pass output between commands
	*/
}