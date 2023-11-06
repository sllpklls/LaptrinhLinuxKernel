   #define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
       #include <arpa/inet.h>
       #include <sys/socket.h>
       #include <netdb.h>
	#include <string.h>
       #include <ifaddrs.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <linux/if_link.h>
	void check_param(int argc, char *argv[]) {
	if (argc < 2) {
		printf("chua nhap lenh\n");
		exit(0);
	}
	}
	void setup ( int argc, char *argv[]){
	char command[50];
	if (strcmp(argv[3],"up") ==0){
	sprintf(command,"ifconfig %s up", argv[2]);
	}else if (strcmp(argv[3],"down")==0){
	sprintf(command,"ifconfig %s down",argv[2]);	
	}else{
	printf("Chi nhap lenh up hoac down ");
	exit(0);
	}
	system(command);
	
}
       void list_network(int argc, char *argv[])
       {
           struct ifaddrs *ifaddr;
           int family, s;
           char host[NI_MAXHOST];

           if (getifaddrs(&ifaddr) == -1) {
               perror("getifaddrs");
               exit(EXIT_FAILURE);
           }
           /* Walk through linked list, maintaining head pointer so we
              can free list later. */
           for (struct ifaddrs *ifa = ifaddr; ifa != NULL;
                    ifa = ifa->ifa_next) {
               if (ifa->ifa_addr == NULL)
                   continue;
               family = ifa->ifa_addr->sa_family;
               /* Display interface name and family (including symbolic
                  form of the latter for the common families). */

               printf("%-8s %s (%d)\n",
                      ifa->ifa_name,
                      (family == AF_PACKET) ? "AF_PACKET" :
                      (family == AF_INET) ? "AF_INET" :
                      (family == AF_INET6) ? "AF_INET6" : "???",
                      family);

               /* For an AF_INET* interface address, display the address. */

               if (family == AF_INET || family == AF_INET6) {
                   s = getnameinfo(ifa->ifa_addr,
                           (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                 sizeof(struct sockaddr_in6),
                           host, NI_MAXHOST,
                           NULL, 0, NI_NUMERICHOST);
                   if (s != 0) {
                       printf("getnameinfo() failed: %s\n", gai_strerror(s));
                       exit(EXIT_FAILURE);
                   }

                   printf("\t\taddress: <%s>\n", host);

               } else if (family == AF_PACKET && ifa->ifa_data != NULL) {
                   struct rtnl_link_stats *stats = ifa->ifa_data;

                   printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                          "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                          stats->tx_packets, stats->rx_packets,
                          stats->tx_bytes, stats->rx_bytes);
               }
           }

           freeifaddrs(ifaddr);
           exit(EXIT_SUCCESS);
       }
int main (int argc , char *argv[]){
	check_param(argc,argv);
	if (strcmp(argv[1],"setup")==0){
		setup(argc,argv);
	}
	if(strcmp(argv[1],"list")==0){
	list_network(argc,argv);
	}
	return 0;
}
