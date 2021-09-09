void login(struct USER *me) {
    int recvd;
    if(isconnected) {
        fprintf(stderr, "You are already connected to server at %s:%d\n", SERVERIP, SERVERPORT);
        return;
    }
    sockfd = connect_with_server();
    if(sockfd >= 0) {
        isconnected = 1;
        me->sockfd = sockfd;
        if(strcmp(me->alias, "Anonymous")) setalias(me);
        printf("Logged in as %s\n", me->alias);
        printf("Receiver started [%d]...\n", sockfd);
	
	client_wellcome_message();
        struct THREADINFO threadinfo;
        pthread_create(&threadinfo.thread_ID, NULL, receiver, (void *)&threadinfo);
 
    }
    else {
        fprintf(stderr, "Connection rejected...\n");
    }
}
