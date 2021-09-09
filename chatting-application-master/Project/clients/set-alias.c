void setalias(struct USER *me) {
    int sent;
    struct PACKET packet;
    
    if(!isconnected) {
        fprintf(stderr, "You are not connected...\n");
        return;
    }
    
    memset(&packet, 0, sizeof(struct PACKET));
    strcpy(packet.option, "alias");
    strcpy(packet.alias, me->alias);
    
    /* send request to close this connetion */
    sent = send(sockfd, (void *)&packet, sizeof(struct PACKET), 0);
}
