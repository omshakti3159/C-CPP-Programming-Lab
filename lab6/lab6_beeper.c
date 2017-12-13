#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#define SLEEP_TIME 5
#define CHECK_TIME 0.5
#define SIGCHLD_CODE 17

void sigchld_handler();

void beep(char *whoami) {
	int remains = 0;
	time_t now;
	struct tm *t;
	int nap = SLEEP_TIME;
	while (1) {
		if (remains == 0) {
			now = time(NULL);
			t = localtime(&now);
			printf("%s %02d:%02d:%02d beep!\n",
				whoami,
				t->tm_hour,
				t->tm_min,
				t->tm_sec);
			remains = sleep(nap);
		} else {
			remains = sleep(remains);
		}
	}
}

void watch(char *whoami, pid_t ppid) {
	int check_t = CHECK_TIME * 1e6;
	while (1) {
		usleep(check_t);
		if(kill(ppid, 0)) {
			printf("Parent is dead!\n");
			printf("Child (%d) becomes Parent(%d) now.\n", getpid());
			return;
		}
	}
}

void fork_child(char *whoami) {
	
}

// Handles the death of the child
void sigchld_handler() {

	char whoami[50];
	pid_t pid;
	pid_t ppid;

	ppid = getpid();

	sprintf(whoami, "Parent (%d)", ppid);
	printf("The child is killed!\n");
	printf("Trying to fork another child.\n");

	if ((pid = fork()) == -1) {
		perror("Unable to fork a child.\n");
		exit(1);
	}
	if (pid == 0) {
		printf("%s fork successfully!\n", whoami);
		sprintf(whoami, "Child (%d)", getpid());
		printf("%s starts successfully!\n", whoami);
		watch(whoami, ppid);
	}
}

int main() {
	
	char whoami[50];
	pid_t pid;
	pid_t ppid;

	ppid = getpid();

	sprintf(whoami, "Parent (%d)", ppid);
	printf("%s starts successfully!\n", whoami);

	(void)signal(SIGCHLD_CODE, sigchld_handler);

	if ((pid = fork()) == -1) {
		perror("Unable to fork a child.\n");
		exit(1);
	}
	if (pid == 0) {
		printf("%s Fork successfully!\n", whoami);
		sprintf(whoami, "Child (%d)", getpid());
		printf("%s starts successfully!\n", whoami);
		watch(whoami, ppid);
	}

	sprintf(whoami, "Parent (%d)", getpid());
	beep(whoami);
	
	
	return 0;
}