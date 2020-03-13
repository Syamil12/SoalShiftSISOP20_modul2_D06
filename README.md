# SoalShiftSISOP20_modul2_D06

Soal Shift Modul 1
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)

### 1. Soal 1
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
