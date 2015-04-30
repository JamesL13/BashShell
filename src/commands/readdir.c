#include "../../include/commands.h"
#include <dirent.h>

//NEED A STRUCT ACCORDING TO OPENGROUP
struct direct *readdir(DIR *dir);

int readdir_r(DIR *restrict dir, struct direct *restrict entry, struct direct **restrict result);


void readDirectory(char *directory)
{
//EXACT CODE FROM OPEN SHIFT
	DIR *dirp;
	struct direct *dp;

	if ((dirp = opendir(".")) == NULL)
	{
		perror("Could not open '.'");
		return;
	}

	do {
		 errno = 0;
        if ((dp = readdir(dirp)) != NULL) {
            if (strcmp(dp->d_name, directory) != 0)
                continue;


            (void) printf("found %s\n", directory);
            (void) closedir(dirp);
                return;


        }
    } while (dp != NULL);


    if (errno != 0)
        perror("error reading directory");
    else
        (void) printf("failed to find %s\n", directory);
    (void) closedir(dirp);
    return;
}

