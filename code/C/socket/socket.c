#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
void printf_err(char *);
void printf_success(char *);
void check_param();
void tcp_list();
void udp_list();
void printf_err(char *message) {
	printf("\033[0;31m");
	printf("%s", message);
	printf("\033[0m");
}
void printf_success(char *message) {
	printf("\033[0;32m");
	printf("%s", message);
	printf("\033[0m");
}
void check_param(int argc, char *argv[]) {
	if (argc < 2) {
		printf_err("chua nhap lenh\n");
	}
	if (strcmp(argv[1], "tcp") == 0) {
	}
	if (strcmp(argv[1], "udp") == 0) {
	}
	if (strcmp(argv[1], "raw") == 0) {
	}
	if (strcmp(argv[1], "unix") == 0) {
		
	}
	if (strcmp(argv[1], "tcp6") == 0) {
	}
	if (strcmp(argv[1], "udp6") == 0) {
	}
	if (strcmp(argv[1], "raw6") == 0) {
	}
}
void tcp_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/tcp", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
void udp_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/udp", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
void raw_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/raw", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
void unix_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/unix", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
void tcp6_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/tcp6", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
void udp6_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/udp6", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
void raw6_list(int argc, char *argv[]) {
	int fd;
	char buffer[100];
	fd = open("/proc/net/raw6", O_RDONLY);
	while (read(fd, buffer, sizeof(buffer)) != 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}
int main(int argc, char *argv[]) {
	check_param(argc, argv);
	
	if (strcmp(argv[1], "tcp") == 0) {
		tcp_list(argc, argv);
	}
	if (strcmp(argv[1], "udp") == 0) {
		udp_list(argc, argv);
	}
	if (strcmp(argv[1], "raw") == 0) {
		raw_list(argc, argv);
	}
	if (strcmp(argv[1], "unix") == 0) {
		unix_list(argc, argv);
	}
	if (strcmp(argv[1], "tcp6") == 0) {
		tcp6_list(argc, argv);
	}
	if (strcmp(argv[1], "udp6") == 0) {
		udp6_list(argc, argv);
	}
	if (strcmp(argv[1], "raw6") == 0) {
		raw6_list(argc, argv);
	}
	return 0;
}