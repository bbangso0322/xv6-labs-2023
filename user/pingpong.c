#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){

	int p1[2];
	int p2[2];

	if(argc > 1){
		fprintf(2, "pingpong: args are unnecessary\n");
		exit(1);
	}

	pipe(p1);
	pipe(p2);

	int pid = fork();
	char buf[5];

	if(pid == 0){
		close(p1[1]);
		close(p2[0]);

		if(read(p1[0], buf, 5) < 0){
			fprintf(2, "pingpong: can't read\n");
			exit(1);
		}
		else{
			printf("%d: received %s\n", getpid(), buf);
		}
		close(p1[0]);

		if(write(p2[1], "pong", 5) != 5){
			fprintf(2, "pingpong: can't write\n");	
			exit(1);
		}

		
		close(p2[1]);
	}
	else if(pid > 0){
		close(p2[1]);
		close(p1[0]);

		if(write(p1[1], "ping", 5) != 5){
			fprintf(2, "pingpong: can't write\n");	
			exit(1);
		}
		close(p1[1]);

		if(read(p2[0], buf, 5) < 0){
			fprintf(2, "pingpong: can't read\n");
			exit(1);
		}
		else{
			printf("%d: received %s\n", getpid(), buf);
		}
		
		close(p2[0]);
	}
	else{
		fprintf(2, "pingpong: fork fail\n");
		exit(1);
	}

	exit(0);
}
