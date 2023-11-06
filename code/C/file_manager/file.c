#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
void check_param(int argc, char *argv[]) {
	if (argc <= 1) {
		printf("chua nhap tham so lenh\n");
		exit(0);
	}
	if (strcmp(argv[1], "ls") == 0) {

	}
	if (strcmp(argv[1], "create") == 0 || strcmp(argv[1], "remove") == 0 ||
		strcmp(argv[1], "show") == 0) {
		if (argc < 3) {
			printf("chua nhap ten file\n");
			exit(0);
		}
	}
	if (strcmp(argv[1], "copy") ==0||strcmp(argv[1],"move")==0){
		if (argc < 4){
			printf("Can nhap ten file nguon va file dich");
			exit(0);
		}
	}
	
}
void list_file(int argc, char *argv[]) {
	char dir_path[100];
	strcpy(dir_path, ".");
	DIR *d;
	struct dirent *dir;
	if (argc == 3) {
		strcpy(dir_path, argv[2]);
	}
	d = opendir(dir_path);
	if (d) {
		while ( (dir = readdir(d)) != NULL) {
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	} else {
		printf("folder khong ton tai\n");
		exit(0);
	}
}
void create_file(int argc, char *argv[]) {
char command[100];
	int fd;
	fd = open(argv[2], O_CREAT, 0666);
	if (fd == -1) {
		printf("tao file that bai\n");
		exit(0);
	} else {
          sprintf(command,"nano %s", argv[2]);
          system(command)
		printf("tao file %s thanh cong\n", argv[2]);
		exit(0);
	}
}
void copy_file(int argc, char *argv[]){
	char buffer[1024];
	int num_bytes_read;
	FILE *sourceFile, *destFile;
	sourceFile= fopen(argv[2],"rb");
	if(sourceFile==NULL){
	printf("Error opening the source file. \n");
	exit(0);
}
	destFile = fopen(argv[3],"wb");
	if(destFile==NULL){
	printf("Error opening the destination. \n");
	exit(0);
	}
	while((num_bytes_read = fread(buffer, 1, sizeof(buffer),sourceFile))>0){
	fwrite(buffer, 1, num_bytes_read, destFile);
	}
	fclose(sourceFile);
	fclose(destFile);
	printf("File copied success\n");
	
}
void remove_file(int argc, char *argv[]) {
	int status;
	status = unlink(argv[2]);
	if (status == -1) {
		printf("error delete file ! file not found\n");
		exit(0);
	} else {
		printf ("success delete file %s \n", argv[2]);
		exit(0);
	}
}
void show_file(int argc, char *argv[]) {
	int fd;
	char buffer[1000];
	fd = open(argv[2], O_RDONLY);
	if (fd == -1) {
		printf("error file not found\n");
		exit(0);
	}
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
	}
	printf("\n");
}
void move_file(int argc, char *argv[]){
	int result = rename (argv[2],argv[3]);
	if(result !=0){
		printf("Error moving the file. \n");
		exit(0);
	}
	printf("File moved success\n");
}
int main(int argc, char *argv[]) {
	check_param(argc, argv);
	if (strcmp(argv[1], "ls") == 0) {
		list_file(argc, argv);
	}
	if (strcmp(argv[1], "create") == 0) {
		create_file(argc, argv);
	}
	if (strcmp(argv[1], "remove") == 0) {
		remove_file(argc, argv);
	}
	if (strcmp(argv[1], "show") == 0) {
		show_file(argc, argv);
	}
	if(strcmp(argv[1],"copy")==0){
		copy_file(argc,argv);
	}
	if(strcmp(argv[1],"move")==0){
		move_file(argc,argv);
	}
	return 0;
}
