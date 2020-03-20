#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

//void execute(char *str){ 
//    char *script[] = {"bash", str, NULL};
//    execv("/bin/bash", script); //untuk menjalankan program
//} 
//int main diisi argc, untuk menyimpan banyaknya argumen dari inputan, dan argv, untuk memisahkan antar argumen
//program akan menerima inputan sebanyak 4 argumen
//detik/* , menit/* , jam/* , dan path file.sh
int main(int argc, char *argv[]) {
    int sec, min, hour, i, sec_rn, min_rn, hour_rn, star[4];
	/*---ERROR HANDLING---*/

	//untuk mengatasi argumen yang lebih/kurang dari 4
	if(argc != 5){
		printf("tidak valid (harus 4 argumen)\n");
        return 0;
	}
	//untuk mengatasi argumen 1 sampai 3 yang diinput selain angka
	for (i=1;i<=3;i++){
	//printf("%d",i);
	
		if(((*argv[i] < '0') || (*argv[i] > '9')) && *argv[i] != '*'){
			printf("tidak valid (harus angka)\n");
			return 0;
		}
	}
	if(*argv[1] == '*') {
		sec = -1; 
	}
	else if (*argv[1] != '*'){
		sec = atoi(argv[1]);
    	}
	if(*argv[2] == '*'){ 
		min = -1;
	}
	else if (*argv[2] != '*'){
		min = atoi(argv[2]);
    	}
	if(*argv[3] == '*'){ 
		hour = -1;
	}
	else if (*argv[3] !='*'){
		hour = atoi(argv[3]);
    	}
	// untuk mengatasi range waktu
	if(sec >= 60 || min >= 60 || hour >= 24){
        	printf("tidak valid (Range waktu salah)\n");
        	return 0;
	} 
	/*--------------------*/
    
    pid_t pid, sid;


    pid = fork();

    if (pid < 0)
      exit(EXIT_FAILURE);//error handling

    if (pid > 0) 
      exit(EXIT_SUCCESS);//error handling

    umask(0);

    sid = setsid();
    if (sid < 0)
      exit(EXIT_FAILURE);//error handling

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
	
	while (1){
  		time_t rawtime;
		time(&rawtime);
	  	struct tm* info = localtime(&rawtime);

	        //menyimpan waktu yang sedang berlangsung
	        sec_rn = info->tm_sec;
	        min_rn = info->tm_min;
	        hour_rn = info->tm_hour;
	        //kondisi untuk mengecek waktu yang diinputkan 
		//sesuai dengan waktu sekarang atau *
		if((sec_rn == sec || sec == -1) &&
			(min_rn == min || min == -1) &&
           			(hour_rn == hour || hour == -1)){
               		//printf("yoa");
			pid_t child_id;
                	child_id = fork();
                
                	if(child_id==0){
                		char *arg[] = {"bash", argv[4], NULL};
                		execv("/bin/bash", arg);
				//printf("test");
                	}
			
		}
                
        sleep(1);//delay tiap detik
    	}
}
