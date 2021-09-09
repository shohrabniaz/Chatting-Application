
//Backdoor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define IP "127.0.0.1"
#define PORT 8080
#define BACKLOG 10
#define CLIENTS 10
#define BUFFSIZE 1024
#define ALIASLEN 32
#define OPTLEN 16

#define BLACKLIST "127.0.0.1"

#include "structures.c"

int compare(struct THREADINFO *a, struct THREADINFO *b) {
    return a->sockfd - b->sockfd;
}
 
#include "servers/listing.c"
 
int sockfd, newfd;
/****** Structure variables *****/
struct THREADINFO thread_info[CLIENTS];
struct LLIST client_list;
pthread_mutex_t clientlist_mutex;

#include "timer.c"
#include "wellcome.c"
#include "servers/client-handler.c"
#include "servers/io-handler.c"
#include "servers/cipher.c"
 
int main(int argc, char **argv) {
	// socket variable
    int err_ret, sin_size;
    struct sockaddr_in serv_addr, client_addr;
    pthread_t interrupt;
    char *password = "Caeyqpot";
 
    /* initialize linked list */
    list_init(&client_list);
 
    /* initiate mutex */
    pthread_mutex_init(&clientlist_mutex, NULL);
 
    /* open a socket */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        err_ret = errno;
        fprintf(stderr, "socket() failed...\n");
        return err_ret;
    }
 
    /* set initial values */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    memset(&(serv_addr.sin_zero), 0, 8);
 
    /* bind address with socket */
    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
        err_ret = errno;
        fprintf(stderr, "bind() failed...\n");
        return err_ret;
    }
 
    /* start listening for connection */
    if(listen(sockfd, BACKLOG) == -1) {
        err_ret = errno;
        fprintf(stderr, "listen() failed...\n");
        return err_ret;
    }
 
    /* initiate interrupt handler for IO controlling */
    server_wellcome_message();
    // Password Encrypting by Vigenere Cipher
    char pass[50];
    printf("Please enter password: ");
    scanf("%s", pass);
    if(strcmp(cipher(pass), password) == 0){
	    if(pthread_create(&interrupt, NULL, io_handler, NULL) != 0) {
		err_ret = errno;
		fprintf(stderr, "pthread_create() failed...\n");
		return err_ret;
	    }
	 
	    /* keep accepting connections */
	    printf("Starting socket listener...\n");
	    while(1) {
		sin_size = sizeof(struct sockaddr_in);
			char *check_ip;
	       	if((newfd = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t*)&sin_size)) == -1) {
		    err_ret = errno;
		    fprintf(stderr, "accept() failed...\n");
		    return err_ret;
		}

			//Check Black List
			check_ip = inet_ntoa(client_addr.sin_addr);
		if(strcmp(check_ip, BLACKLIST) == 0) {
				printf("%s is refused!", check_ip);
			    close(newfd);
			} else {
		    if(client_list.size == CLIENTS) {
		        fprintf(stderr, "Connection full, request rejected...\n");
		        continue;
		    }
		    printf("Connection requested received...\n");
		    struct THREADINFO threadinfo;
		    threadinfo.sockfd = newfd;
		    strcpy(threadinfo.alias, "Anonymous");
		    pthread_mutex_lock(&clientlist_mutex);
		    list_insert(&client_list, &threadinfo);
		    pthread_mutex_unlock(&clientlist_mutex);
		    pthread_create(&threadinfo.thread_ID, NULL, client_handler, (void *)&threadinfo);
			
		}
	    }
	 
	    return 0;
	} else {
	printf("You entered wrong password!\n");
	return 0;
}
}
