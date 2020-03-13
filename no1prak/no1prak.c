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

void exc(char *str){ 
    char *file[] = {"bash", str, NULL};
    execv("/bin/bash", file); //untuk menjalankan program
} 
//int main diisi argc, untuk menyimpan banyaknya argumen dari inputan, dan argv, untuk memisahkan antar argumen
//program akan menerima inputan sebanyak 4 argumen
//detik/* , menit/* , jam/* , dan path file.sh
int main(int argc, char *argv[]) {
    int sec, min, hour, i, sec_rn, min_rn, hour_rn;
					/*---ERROR HANDLING---*/

//untuk mengatasi argumen yang lebih/kurang dari 4
//if(argc != 4){
//	printf("tidak valid (harus 4 argumen)\n");
//        return 0;
//}
	// ubah argumen ke int sec
	if((strcmp(argv[1], "*")) == 0) sec = -1;
    	sec = atoi(argv[1]);

	// ubah argumen ke int min
	if((strcmp(argv[2], "*")) == 0) min = -1;
	min = atoi(argv[2]);

    	// ubah argumen ke int hour
	if((strcmp(argv[3], "*")) == 0) hour = -1;
	hour = atoi(argv[3]);

//untuk mengatasi argumen 1 sampai 3 yang diinput selain angka
for (i=1;i<=3;i++){
	//printf("%d",i);
	if(((*argv[i] < '0') || (*argv[i] > '9')) && *argv[i] != '*'){
		printf("tidak valid (harus angka)\n");
		return 0;
	}
}
    
// untuk mengatasi range waktu
if(sec < -1 || sec > 59 || min < -1 || min > 59 || hour < -1 || hour > 23){
        printf("tidak valid (Range waktu salah)\n");
        return 0;
}
    // ubah argumen path ke string
    char dir[100];
    strncpy(dir, argv[4], 99);
    dir[100] = '\0';

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
  	struct tm* info;
	//untuk mengambil waktu yang sedang berlangsung
  	rawtime = time(NULL);
	info = localtime(&rawtime);

        //menyimpan waktu yang sedang berlangsung
        sec_rn = info->tm_sec;
        min_rn = info->tm_min;
        hour_rn = info->tm_hour;
        
        //kondisi untuk mengecek waktu yang diinputkan 
	//sesuai dengan waktu sekarang atau *
	if((sec_rn == sec || sec == -1) &&
		(min_rn == min || min == -1) &&
           		(hour_rn == hour || hour == -1)){
                pid_t child;
                child = fork();

                int status;
		//child jalan saat = 0
                if (child == 0) exc(dir); 
                else 
                    while ((wait(&status)) > 0);
            }
        sleep(1);//delay tiap detik
    }
}

