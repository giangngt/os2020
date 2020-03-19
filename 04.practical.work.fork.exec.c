#include <unistd.h>
#include <stdio.h>

int main() {
	printf("Main before fork()\n");
	int pid = fork();
	if (pid == 0){
		printf("This is a child after fork()\n");
		printf("Launching ps -ef \n");
		char *args[] = {"/bin/ps", "-ef", NULL};
		execvp("/bin/ps", args);
		return 0;
	}
	else {
		printf("This is a parent after fork(), child is %d\n", pid);
		printf("Launching free -h \n");
		char *bruh[] = {"free", "-h", NULL};
		execvp("free", bruh);
		return 0;
	}
}
