// Need to be commenting


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>



#define SERVERIP "127.0.0.1"
#define SERVERPORT 8080
 
#define BUFFSIZE 1024
#define ALIASLEN 32
#define OPTLEN 16
#define LINEBUFF 2048





int isconnected, sockfd;
char option[LINEBUFF];
#include "structures.c"
struct USER me;
#include "wellcome.c"
#include "clients/send-to-alias.c"
#include "clients/send-to-all.c"
#include "clients/set-alias.c"
#include "clients/reciever.c"
#include "clients/login.c"
#include "clients/logout.c"
#include "clients/connect-with-server.c"
 
int main(int argc, char **argv) {
    int sockfd, aliaslen;
    
    memset(&me, 0, sizeof(struct USER));
    
    while(gets(option)) {
        if(!strncmp(option, "exit", 4)) {
            logout(&me);
            break;
        }
        if(!strncmp(option, "help", 4)) {
            FILE *fin = fopen("help.txt", "r");
            if(fin != NULL) {
                while(fgets(option, LINEBUFF-1, fin)) puts(option);
                fclose(fin);
            }
            else {
                fprintf(stderr, "Help file not found...\n");
            }
        }
        else if(!strncmp(option, "login", 5)) {
            char *ptr = strtok(option, " ");
            ptr = strtok(0, " ");
            memset(me.alias, 0, sizeof(char) * ALIASLEN);
            if(ptr != NULL) {
                aliaslen =  strlen(ptr);
                if(aliaslen > ALIASLEN) ptr[ALIASLEN] = 0;
                strcpy(me.alias, ptr);
            }
            else {
                strcpy(me.alias, "Anonymous");
            }
            login(&me);
        }
		else if(!strncmp(option, "file", 4)){
			char buffer[100];
			FILE *f;
			f=fopen("add.txt","r");
			fscanf(f,"%s",buffer);
			write(sockfd,buffer,100);
			printf("the file was sent successfully");
			fclose(f);
		}
        else if(!strncmp(option, "alias", 5)) {
            char *ptr = strtok(option, " ");
            ptr = strtok(0, " ");
            memset(me.alias, 0, sizeof(char) * ALIASLEN);
            if(ptr != NULL) {
                aliaslen =  strlen(ptr);
                if(aliaslen > ALIASLEN) ptr[ALIASLEN] = 0;
                strcpy(me.alias, ptr);
                setalias(&me);
            }
        }
        else if(!strncmp(option, "whisp", 5)) {
            char *ptr = strtok(option, " ");
            char temp[ALIASLEN];
            ptr = strtok(0, " ");
            memset(temp, 0, sizeof(char) * ALIASLEN);
            if(ptr != NULL) {
                aliaslen =  strlen(ptr);
                if(aliaslen > ALIASLEN) ptr[ALIASLEN] = 0;
                strcpy(temp, ptr);
                while(*ptr) ptr++; ptr++;
                while(*ptr <= ' ') ptr++;
                sendtoalias(&me, temp, ptr);
            }
        }
        else if(!strncmp(option, "send", 4)) {
            sendtoall(&me, &option[5]);
        }
        else if(!strncmp(option, "logout", 6)) {
            logout(&me);
        } else if(!strcmp(option, "clear")){
			system("clear");
			client_wellcome_message();
		}
        else fprintf(stderr, "Unknown option...\n");
    }
    return 0;
}
 

