void *io_handler(void *param) {
    char option[OPTLEN];
    while(scanf("%s", option)==1) {
        if(!strcmp(option, "exit")) {
            /* clean up */
            printf("Terminating server...\n");
            pthread_mutex_destroy(&clientlist_mutex);
            close(sockfd);
            exit(0);
        }
        else if(!strcmp(option, "list")) {
            pthread_mutex_lock(&clientlist_mutex);
            list_dump(&client_list);
            pthread_mutex_unlock(&clientlist_mutex);
        }
        else {
            fprintf(stderr, "Unknown command: %s...\n", option);
        }
    }
    return NULL;
}
