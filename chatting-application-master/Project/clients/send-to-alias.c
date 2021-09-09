void sendtoalias(struct USER *me, char *target, char *msg) {
    int sent, targetlen;
    struct PACKET packet;
    
    if(target == NULL) {
        return;
    }
    
    if(msg == NULL) {
        return;
    }
    
    if(!isconnected) {
        fprintf(stderr, "You are not connected...\n");
        return;
    }
    msg[BUFFSIZE] = 0;
    targetlen = strlen(target);
    
    memset(&packet, 0, sizeof(struct PACKET));
    strcpy(packet.option, "whisp");
    strcpy(packet.alias, me->alias);
    strcpy(packet.buff, target);
    strcpy(&packet.buff[targetlen], " ");
    strcpy(&packet.buff[targetlen+1], msg);
    
    /* send request to close this connetion */
    sent = send(sockfd, (void *)&packet, sizeof(struct PACKET), 0);
}
