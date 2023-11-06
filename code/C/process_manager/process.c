#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/resource.h>
void check_param(int argc, char *argv[]) {
	if (argc < 2) {
		printf("\033[0;31m");
		printf("chua nhap lenh\n");
		printf("\033[0m");
		exit(0);
	}
	if (strcmp(argv[1], "ps") == 0) {
		
	}
	if (strcmp(argv[1], "kill") == 0) {
		if (argc < 4) {
			printf("\033[0;31m");
			printf("chua nhap ma lenh\n");
			printf("\033[0m");
			exit(0);
		}
	}
}
void list_process(int argc, char *argv[]) {
	DIR *d;
	struct dirent *dir;
	char buffer[100], status_path[1000], process_name[100];
	int status_fd;
	d = opendir("/proc");
	printf(" %-10s%-10s\n", "ID", "Name");
	while ((dir = readdir(d)) != NULL) {
		if(isdigit(dir->d_name[0])) {
			sprintf(status_path, "/proc/%s/status", dir->d_name);
			status_fd = open(status_path, O_RDONLY);
			read(status_fd, buffer, sizeof(buffer));
			sscanf(buffer, "Name:   %s", process_name);
			printf(" %-10s%-10s\n", dir->d_name, process_name);
		}
	}
}
void kill_process(int argc, char *argv[]) {
	int process_id, kill_arg, status;
	process_id = atoi(argv[2]);
	kill_arg = atoi(argv[3]);
	status = kill(process_id, kill_arg);
	if (status == 0) {
		printf("\033[0;32m");
		printf("kill %d success\n", process_id);
		printf("\033[0m");
		exit(0);
	} else {
		printf("\033[0;31m");
		printf("kill fail\n");
		printf("\033[0m");
		exit(0);
	}
}
void setPriority(int argc, char *argv[]){
	int currentPID = atoi(argv[2]);
	int newPriority = atoi(argv[3]);

 int priority = getpriority(PRIO_PROCESS, currentPID);
  printf("%d process priority: %d\n", currentPID, priority);

  // Thiết lập độ ưu tiên cho quy trình
  int ret = setpriority(PRIO_PROCESS, currentPID, newPriority );
  if (ret != 0) {
    perror("setpriority");
    exit(EXIT_FAILURE);
  }
  printf("New process priority: %d\n", getpriority(PRIO_PROCESS, currentPID));

}
void createProcess(int argc,char *argv[]){
	pid_t childpid;
	int i=0;
	childpid = fork();
	if(childpid>=0){
	if(childpid==0){
	printf("child : pid=:%d, i+5 =%d \n", getpid(),i+5);
	}
	else {
	printf("Parent: pid =%d, i+10= %d \n", getpid(),i+10);
	}
}
else {
printf("fork error \n");
}
}
void run(int argc , char * argv[]){
char *args[10];
    int i = 0;

    // Phân tách chuỗi tham số và lưu vào mảng args
    char *token = strtok(argv[3], " ");
    while (token != NULL && i < 9) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

pid_t child_pid;
child_pid=fork();
	if(child_pid!=0){
	printf("Parent are executing..\n");
	wait(NULL);
}
	else{
        printf("child is excuting...\n");
        //printf("%s \n", *args);
	execvp(argv[2], args);
	fprintf(stderr, "an error accurred in execvp\n");
}
}


int main(int argc, char *argv[]) {
	check_param(argc, argv);

	if (strcmp(argv[1], "ps") == 0) {
		list_process(argc, argv);
	}else if (strcmp(argv[1], "kill") == 0) {
		kill_process(argc, argv);
	}else if (strcmp(argv[1], "create") == 0) {
		createProcess(argc, argv);
	}else if (strcmp(argv[1], "run") == 0) {
		run(argc, argv);
	}else if (strcmp(argv[1], "setPriority") == 0) {
		setPriority(argc, argv);
		}
	return 0;
}
