#include <unistd.h>
#include <error.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int getDirectory(void);

int moveDirectories(char* filepath);

int readDirectory(char* folder);

int subString(char* sub, char* filename);

void execute(char **argv);


//PWD
int getDirectory( void )
{
    char* cd;
    char buff[PATH_MAX + 1];

    	//GET CURRENT WORKING DIRECTORY
    	cd = getcwd( buff, PATH_MAX + 1 );
    	if( cd != NULL ) 
   		{
        	printf( "Current working directory is %s\n\n", cd );
    	}

		else 
		{                                
        	return EXIT_FAILURE;       
        }
    return EXIT_SUCCESS;
}

//CD
int moveDirectories(char* filepath)
{
		//CHANGE DIRECTORY
    	if(chdir(filepath) == 0) 
    	{
        	printf( "Directory changed to %s\n", filepath);
        	return EXIT_SUCCESS;
    	}

    	else
    	{
        	perror(filepath);
        	return EXIT_FAILURE;
    	}
    	return EXIT_SUCCESS;
}

//LS
int readDirectory(char* folder)
{
	DIR *dir;
	struct dirent *dp;

		//IF THEY WANT THE CURRENT FOLDER
		if (folder == NULL)
		{
			dir = opendir(".");
		}
		//IF THEY WANT A CERTAN FOLDER
		else
		{
			dir = opendir(folder);
		}
		while ((dp=readdir(dir)) != NULL)
		{
			if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			{
			//do nothing
			}
			else
			{
				folder = dp->d_name;
				printf("filename: \ '%s\'\n", folder);
			}
		}
	closedir(dir);
	return EXIT_SUCCESS;

}

//GREP
int subString(char* sub, char *filename)
{
	FILE *fp;
	char fline[100];
	//OPEN FILE TO READ
	fp = fopen(filename, "r");
		//CHECK FOR ALL INPUTS
		if (fp == NULL || sub == NULL)
		{
			printf("File pointer or Substring is NULL!\nCannot grep!\nPlease enter in format: grep <substring> <file name>\n");
			return EXIT_FAILURE;
		}
		//GO THROUGH EACH LINE OF FILE AND CHECK FOR SUBSTRING
		while(fgets(fline, sizeof(fline), fp))
		{
			if(strstr(fline, sub) != NULL)
			{
				printf("\nLINE= %s\n", fline);
			}
		}

	fclose(fp);

	return EXIT_SUCCESS;
}

//EXE
void execute(char** program)
{
	pid_t  pid;
     int    status;
     const char *path = *program;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execl(path, *program) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}