/************** SERVER STRUCTERS *********************/
struct PACKET {
    char option[OPTLEN]; // instruction
    char alias[ALIASLEN]; // client's alias
    char buff[BUFFSIZE]; // payload
};
 
struct THREADINFO {
    pthread_t thread_ID; // thread's pointer
    int sockfd; // socket file descriptor
    char alias[ALIASLEN]; // client's alias
};
 
struct LLNODE {
    struct THREADINFO threadinfo;
    struct LLNODE *next;
};
 
struct LLIST {
    struct LLNODE *head, *tail;
    int size;
};

/****************** CLIENTS STRUCTURES ******************/
struct USER {
        int sockfd; // user's socket descriptor
        char alias[ALIASLEN]; // user's name
};
