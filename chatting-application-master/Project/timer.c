#include <stdio.h>
void connect_time(char name[], char option[]){
	// time variable	
	time_t timer;
    char times[26];
    struct tm* tm_info;
		time(&timer);
		tm_info = localtime(&timer);
		strftime(times, 26, "%d/%m/%Y %H:%M:%S", tm_info);
		FILE *logs;
		logs = fopen("log.txt", "a");
		if(strcmp(option, "exit") == 0)
			fprintf(logs, "\nAt %s - %s is Disconnected", times, name);
		else
			fprintf(logs, "\nAt %s - %s is Connected", times, name);
		fclose(logs);
}
