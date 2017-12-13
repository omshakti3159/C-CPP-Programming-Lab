#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#define SLEEP_TIME 5
#define CHECK_TIME 0.5
#define SIGCHLD_CODE 17

void sigchld_handler();
char *fork_child();

void beep() {
	int remains = 0;
	time_t now;
	struct tm *t;
	int nap = SLEEP_TIME;
	while (1) {
		if (remains == 0) {
			now = time(NULL);
			t = localtime(&now);
			printf("Parent (%d) %02d:%02d:%02d beep!\n",
				getpid(),
				t->tm_hour,
				t->tm_min,
				t->tm_sec);
			remains = sleep(nap);
		} else {
			remains = sleep(remains);
		}
	}
}

void watch(pid_t ppid) {
	int check_t = CHECK_TIME * 1e6;
	while (1) {
		usleep(check_t);
		if(kill(ppid, 0)) {
			printf("Parent is dead!\n");
			printf("Child (%d) becomes Parent (%d) now.\n", 
				getpid(), getpid());
			fork_child();
			return;
		}
	}
}

char *fork_child() {

	char *whoami = (char *) malloc(sizeof(char) * 50);
	pid_t pid;
	pid_t ppid;

	ppid = getpid();

	sprintf(whoami, "Parent (%d)", ppid);

	if ((pid = fork()) == -1) {
		perror("Unable to fork a child.\n");
		exit(1);
	}
	if (pid == 0) {
		printf("%s fork successfully!\n", whoami);
		sprintf(whoami, "Child (%d)", getpid());
		printf("%s starts successfully!\n", whoami);
		watch(ppid);
	}

	return whoami;
}

// Handles the death of the child
void sigchld_handler() {

	printf("The child is killed!\n");
	printf("Trying to fork another child.\n");

	fork_child();
}

int main() {

	printf("Parent (%d) starts successfully!\n", getpid());

	(void)signal(SIGCHLD_CODE, sigchld_handler);

	char *whoami = fork_child();

	sprintf(whoami, "Parent (%d)", getpid());
	beep();
	
	
	return 0;
}