void *client_handler(void *fd) {
    struct THREADINFO threadinfo = *(struct THREADINFO *)fd;
    struct PACKET packet;
    struct LLNODE *curr;
    int bytes, sent;
    while(1) {
        bytes = recv(threadinfo.sockfd, (void *)&packet, sizeof(struct PACKET), 0);
        if(!bytes) {
            fprintf(stderr, "Connection lost from [%d] %s...\n", threadinfo.sockfd, threadinfo.alias);
            pthread_mutex_lock(&clientlist_mutex);
            list_delete(&client_list, &threadinfo);
            pthread_mutex_unlock(&clientlist_mutex);
            break;
        }
        printf("[%d] %s %s %s\n", threadinfo.sockfd, packet.option, packet.alias, packet.buff);
        if(!strcmp(packet.option, "alias")) {
            printf("Set alias to %s\n", packet.alias);

			//saving connection time
			connect_time(packet.alias, packet.option);

            pthread_mutex_lock(&clientlist_mutex);
            for(curr = client_list.head; curr != NULL; curr = curr->next) {
                if(compare(&curr->threadinfo, &threadinfo) == 0) {
                    strcpy(curr->threadinfo.alias, packet.alias);
                    strcpy(threadinfo.alias, packet.alias);
                    break;
                }
            }
            pthread_mutex_unlock(&clientlist_mutex);
        }
        else if(!strcmp(packet.option, "whisp")) {
            int i;
            char target[ALIASLEN];
            for(i = 0; packet.buff[i] != ' '; i++); packet.buff[i++] = 0;
            strcpy(target, packet.buff);
            pthread_mutex_lock(&clientlist_mutex);
            for(curr = client_list.head; curr != NULL; curr = curr->next) {
                if(strcmp(target, curr->threadinfo.alias) == 0) {
                    struct PACKET spacket;
                    memset(&spacket, 0, sizeof(struct PACKET));
                    if(!compare(&curr->threadinfo, &threadinfo)) continue;
                    strcpy(spacket.option, "msg");
                    strcpy(spacket.alias, packet.alias);
                    strcpy(spacket.buff, &packet.buff[i]);
                    sent = send(curr->threadinfo.sockfd, (void *)&spacket, sizeof(struct PACKET), 0);
                }
            }
            pthread_mutex_unlock(&clientlist_mutex);
        }
        else if(!strcmp(packet.option, "send")) {
            pthread_mutex_lock(&clientlist_mutex);
            for(curr = client_list.head; curr != NULL; curr = curr->next) {
                struct PACKET spacket;
                memset(&spacket, 0, sizeof(struct PACKET));
                if(!compare(&curr->threadinfo, &threadinfo)) continue;
                strcpy(spacket.option, "msg");
                strcpy(spacket.alias, packet.alias);
                strcpy(spacket.buff, packet.buff);
                sent = send(curr->threadinfo.sockfd, (void *)&spacket, sizeof(struct PACKET), 0);
            }
            pthread_mutex_unlock(&clientlist_mutex);
        } else if(!strcmp(packet.option, "file")) {
			char buffer[100];
			FILE *fp;
			read(newfd,buffer,100);
			fp=fopen("add1.txt","w");
			fprintf(fp,"%s",buffer);
			printf("the file was received successfully");
			printf("the new file created is add1.txt");
			fclose(fp);
		}
        else if(!strcmp(packet.option, "exit")) {
            printf("[%d] %s has disconnected...\n", threadinfo.sockfd, threadinfo.alias);    
	    connect_time(packet.alias, packet.option); // disconected time
            pthread_mutex_lock(&clientlist_mutex);
            list_delete(&client_list, &threadinfo);
            pthread_mutex_unlock(&clientlist_mutex);
            break;
        }
        else {
            fprintf(stderr, "Garbage data from [%d] %s...\n", threadinfo.sockfd, threadinfo.alias);
        }
    }
 
    /* clean up */
    close(threadinfo.sockfd);
 
    return NULL;
}
