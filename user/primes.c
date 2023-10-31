#include "kernel/types.h"
#include "user/user.h"

void sieve(int fd){
	
	int prime = -1;

	if(read(fd, &prime, sizeof(int)) == 0){
		exit(0);
	}
	
	printf("prime %d\n", prime);

	int p[2];
	pipe(p);
	int pid = fork();
	int num;
	if(pid > 0){
		close(p[0]);
		while(read(fd, &num, sizeof(int)) != 0){
			if(num % prime != 0){
				write(p[1], &num, sizeof(int));
			}
		}
		close(p[1]);
		wait(0);
	}
	else if(pid == 0){
		close(p[1]);
		sieve(p[0]);
		close(p[0]);
	}
}

int main(){
	
	int p[2];

	pipe(p);

	for(int i=2; i<=35; i++){
		if(write(p[1], &i, sizeof(int)) != sizeof(int)){
			fprintf(2, "can't write\n");
			exit(1);
		}	
	}

	close(p[1]);
	sieve(p[0]);
	close(p[0]);

	return 0;
}
