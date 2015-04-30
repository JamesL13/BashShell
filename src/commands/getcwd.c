#include "../../include/commands.h"



char* getDirectory(void){
	
	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)size)) != NULL){
		ptr = getcwd(buf, (size_t)size);
	}
	else{
		perror("\nCould not get working directory!\n");
	}
	return ptr;
}
