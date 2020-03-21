# SoalShiftSISOP20_modul2_D06

Soal Shift Modul 1
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)

### 1. Soal 1
maksud dari soal no.1 ada membuat inputan seperti crontab dengan syarat argumen 1 --> detik, argumen 2 --> menit, argumen 3 --> jam, dan argumen 4 path file
```sh
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
```
dari kodingan diatas adalah memenuhi syarat mengeluarkan pesan error (error handling), program akan langsung meretur 0 jika inputan tidak sesuai, contohnya adalah jika inputan tidak sesuai kuota yang diminta, lalu jika 1 sampai 3 itu tidak berupa angka, lalu jika inputan tidak sesuai dengan syarat waktu (detik:0-59, menit:0-59, jam:0-23). selain error handling codingan diatas juga memberi kondisi jika inputan * (any value), jika user menginputkan * maka detik/menit/jam akan berubah menjadi -1, dimana akan dianggap any value. dan jika user menginputkan angka maka langsung di ubah dari argumen menjadi int melalui fungsi "atoi".

```sh
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

```
isi dari while (1) adalah untuk kegunaan daemon berjalan, dimulai dengan menbambil localtime yang sekarang, dan disimpan di integer, detik di sec_rn, menit di min_rn, jam di hour_rn, lalu terdapat kondisi pengecekan jika waktu sekarang sama dengan waktu yang diinput pada argumen maka daemon akan berjalan. jika child ==0 dimana child akan mulai, lalu menjalankan file.sh 

file.sh tersebut diisi dengan pengecekan keberhasilan program/daemon berjalan
```sh
now=`date`
#mengambil date sekarang
sc="berhasil | $now"
echo $sc >> /home/rafi/historyy.log
```
maksud dari isi file.sh ini adalah file ini akan membentuk file bertipe log dengan nama "historyy.log", si dari log tersebut adalah print berhasil dan tanggal jika daemon di jalankan sesuai dengan jam yang ada.

### 2. Soal 2
### 3. Soal 3

Pada folder Soal3 Terdapat sebuah file bernama `soal3.c`.

##### Untuk soal 3 bagian a jawabannya adalah bagian kode berikut:

```sh
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
```

**Penjelasan:**
+ Membuat proses baru dengan `child1 = fork();` dan `child2 = fork();`
+ `*argv[] = char *argv[] = {"mkdir", "/home/syamil/modul2/indomie", NULL};` Menyimpan *mkdir* pada `*argv[]` sebagai nama program dan menyimpan  `"/home/syamil/modul2/indomie", NULL` sebagai argumen pada `*argv[]`
+ Menjalankan `argv` menggunakan `execv` dengan perintah `/bin/mkdir` yang berarti membuat direktori sesuai dengan argumen pada `*argv[]`
+ `sleep(5);` Memberi jeda selama 5 detik

##### Untuk soal 3 bagian b jawabannya adalah bagian kode berikut:

```sh
child3 = fork();
	if(child3 < 0){
		exit(EXIT_FAILURE);
	}
	if(child3 == 0){	
		char *argv[] = {"unzip", "/home/syamil/modul2/jpg.zip", NULL};
		execv("/usr/bin/unzip", argv);
	}
```

**Penjelasan:**
+ Membuat proses baru dengan `child3 = fork();`
+ `*argv[] = char *argv[] = {"unzip", "/home/syamil/modul2/jpg.zip", NULL};` Menyimpan *unzip* pada `*argv[]` sebagai nama program dan menyimpan  `"/home/syamil/modul2/jpg.zip", NULL` sebagai argumen pada `*argv[]`
+ Menjalankan `argv` menggunakan `execv` dengan perintah `/usr/bin/unzip` yang berarti mengekstrak file zip

##### Untuk soal 3 bagian c jawabannya adalah bagian kode berikut:

```sh
while((wait(&status)) > 0);
	DIR *dir;
	chdir("/home/syamil/modul2/jpg/");
	struct dirent *ad;
	struct stat cek;
	FILE *fptr;
	char str[100];	
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
					sprintf(str, "/home/syamil/modul2/jpg/%s", ad->d_name);
					char *argv[] = {"mv", str, "/home/syamil/modul2/indomie", NULL};
					execv("/bin/mv", argv);
				}else{
					while((wait(&status)) > 0);
					sprintf(str, "/home/syamil/modul2/jpg/%s", ad->d_name);
					char *argv[] = {"mv", str, "/home/syamil/modul2/sedaap", NULL};
					execv("/bin/mv", argv);							
					}
				}
		}
	}
	closedir(dir);
```

**Penjelasan:**
+ `chdir("/home/syamil/modul2/jpg/");` Merubah direktori kerja
+ `dir = opendir(".");` Membuka direktori kerja sekarang dengan menyimpannya pada variabel `dir`
+ `while((ad = readdir(dir)) != NULL){ if(strcmp(ad->d_name, ".") == 0 || strcmp(ad->d_name, "..") == 0) continue;` Melakukan looping selama direktori pada variabel `dir` belum kosong, dan jika bertemu dengan folder *"."* atau *".."* looping tetap dilanjutkan
+ `if(cek.st_mode & S_IFDIR)` Mengecek apakah direktori atau bukan
+ `sprintf(ch, "/home/syamil/modul2/jpg/%s", ad->d_name);` Menyimpan nama direktori yang ditunjuk oleh pointer `ad` pada string `str`
+ `char *argv[] = {"mv", str, "/home/syamil/modul2/indomie", NULL};` Menyimpan *mv* pada `*argv[]` sebagai nama program dan menyimpan  `"/home/syamil/modul2/indomie, NULL` sebagai argumen pada `*argv[]`
+ Menjalankan `argv` menggunakan `execv` dengan perintah `/bin/mv` yang berarti memindahkan direktori yang ditunjuk pointer `ad` ke direktori indomie
+ Lalu masuk ke else jika yang ditunjuk pointer `ad` bukan folder 
+ `closedir(dir);` Menutup direktori `dir`
