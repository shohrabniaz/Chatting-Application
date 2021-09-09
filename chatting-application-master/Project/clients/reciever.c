void *receiver(void *param) {
    int recvd;
    struct PACKET packet;
    
    printf("Waiting here [%d]...\n", sockfd);
    while(isconnected) {
        
        recvd = recv(sockfd, (void *)&packet, sizeof(struct PACKET), 0);
        if(!recvd) {
            fprintf(stderr, "Connection lost/kick from server...\n");
            isconnected = 0;
            close(sockfd);
            break;
        }
        if(recvd > 0) {
            printf("[%s]: %s\n", packet.alias, packet.buff);
        }
        memset(&packet, 0, sizeof(struct PACKET));
    }
    return NULL;
}
