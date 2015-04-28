#include "../../include/commands.h"

//THIS FUNCTION IS TO CHANGE DIRECTORIES FROM PASSED IN CHOICE
void moveDirectories(char *directory)
{
	//LOOKED AT OPEN GROUP, NOT SURE WHY RET IS USED AT THE MOMENT
	int ret;
	ret = chdir (directory);
	if (ret == -1)
	{
		perror("\nYour change directories failed\n");
	}
	else
	{
		printf("\nIt worked\n");
	}
}