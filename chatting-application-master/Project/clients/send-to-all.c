void sendtoall(struct USER *me, char *msg) {
    int sent;
    struct PACKET packet;
    
    if(!isconnected) {
        fprintf(stderr, "You are not connected...\n");
        return;
    }
    
    msg[BUFFSIZE] = 0;
    
    memset(&packet, 0, sizeof(struct PACKET));
    strcpy(packet.option, "send");
    strcpy(packet.alias, me->alias);
    strcpy(packet.buff, msg);
    
    /* send request to close this connetion */
    sent = send(sockfd, (void *)&packet, sizeof(struct PACKET), 0);
}
