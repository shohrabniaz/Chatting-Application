int connect_with_server() {
    int newfd, err_ret;
    struct sockaddr_in serv_addr;
    struct hostent *to;
 
    /* generate address */
    if((to = gethostbyname(SERVERIP))==NULL) {
        err_ret = errno;
        fprintf(stderr, "gethostbyname() error...\n");
        return err_ret;
    }
 
    /* open a socket */
    if((newfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        err_ret = errno;
        fprintf(stderr, "socket() error...\n");
        return err_ret;
    }
 
    /* set initial values */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVERPORT);
    serv_addr.sin_addr = *((struct in_addr *)to->h_addr);
    memset(&(serv_addr.sin_zero), 0, 8);
 
    /* try to connect with server */
    if(connect(newfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
        err_ret = errno;
        fprintf(stderr, "connect() error...\n");
        return err_ret;
    }
    else {
        printf("Connected to server at %s:%d\n", SERVERIP, SERVERPORT);
        return newfd;
    }
}
