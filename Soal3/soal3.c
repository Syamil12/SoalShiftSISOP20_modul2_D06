#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>

int main(){
	pid_t child1,child2,child3,child4;
	int status;

	child1 = fork();
	if(child1 < 0){
		exit(EXIT_FAILURE);
	}
	if(child1 == 0){
		char *argv[] = {"mkdir", "/home/syamil/modul2/indomie", NULL};
		execv("/bin/mkdir", argv);
	}
	sleep(5);

	child2 = fork();
	if(child2 < 0){
		exit(EXIT_FAILURE);
	}
	if(child2 == 0){
		char *argv[] = {"mkdir", "/home/syamil/modul2/sedaap", NULL};
		execv("/bin/mkdir", argv);
	}
	
	child3 = fork();
	if(child3 < 0){
		exit(EXIT_FAILURE);
	}
	if(child3 == 0){	
		char *argv[] = {"unzip", "/home/syamil/modul2/jpg.zip", NULL};
		execv("/usr/bin/unzip", argv);
	}
	
	while((wait(&status)) > 0);
	DIR *dir;
	chdir("/home/syamil/modul2/jpg/");
	struct dirent *ad;
	struct stat cek;
	FILE *fptr;
	char ch[100];	
	dir = opendir(".");
	
	//if(dir == NULL){
		//printf("Directory tidak ada");
	//	exit(1);
	//}
	while((wait(&status)) > 0);
	while((ad = readdir(dir)) != NULL){
		if(strcmp(ad->d_name, ".") == 0 || strcmp(ad->d_name, "..") == 0)
  	  continue;
		child4 = fork();
		if(child4 == 0){
			if(stat(ad->d_name,&cek) == 0){
  			if(cek.st_mode & S_IFDIR){
					sprintf(ch, "/home/syamil/modul2/jpg/%s", ad->d_name);
					char *argv[] = {"mv", ch, "/home/syamil/modul2/indomie", NULL};
					execv("/bin/mv", argv);
				}else{
					while((wait(&status)) > 0);
					sprintf(ch, "/home/syamil/modul2/jpg/%s", ad->d_name);
					char *argv[] = {"mv", ch, "/home/syamil/modul2/sedaap", NULL};
					execv("/bin/mv", argv);							
					}
				}
		}
	}
	closedir(dir);
	//while(	(ad=readdir(dir)) != NULL){
		//printf(">> %s\n", ad->d_name);
	//}	
	return 0;
}

