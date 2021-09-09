#include <stdio.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
void server_wellcome_message(){
	system("clear");
	printf(ANSI_COLOR_RED "######################################################\n");
	printf("#                Xenon Server Admin UI               #\n");
	printf("######################################################\n\n\n" ANSI_COLOR_RESET);
}

void client_wellcome_message(){
	system("clear");
	printf(ANSI_COLOR_RED "######################################################\n");
	printf("#                Wellcome to Xenon Server            #\n");
	printf("#                 Xenon Server Client UI             #\n");
	printf("######################################################\n\n\n" ANSI_COLOR_RESET);
}
