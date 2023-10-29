#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	if(argc <= 1){
		exit(0);
	}

	if(argc > 2){
		fprintf(2, "sleep: too many args: %d\n", argc-1);
		exit(1);
	}

	int n = atoi(argv[1]);
	sleep(n);

	exit(0);
}
