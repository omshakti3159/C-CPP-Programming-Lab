#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

#define SLEEP_TIME 5
#define CHECK_TIME 0.5

void fork_child();

pid_t parent_pid;
pid_t child_pid;

// Beeps
void beep() {
	int remains = 0;
	time_t now;
	struct tm *t;
	int nap = SLEEP_TIME;
	while (1) {
		if (remains == 0) {
			now = time(NULL);
			t = localtime(&now);
			printf("------ Parent (%d) %02d:%02d:%02d beep!\n",
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

// Watches the father every 0.5 sec
void watch(pid_t ppid) {
	int check_t = CHECK_TIME * 1e6;
	while (1) {
		usleep(check_t);
		if(kill(ppid, 0)) {
			printf("! Parent is dead!\n");
			printf("! Child (%d) becomes Parent (%d) now.\n", 
				getpid(), getpid());

			child_pid = parent_pid = getpid();

			fork_child();
			return;
		}
	}
}

// Forks a child
void fork_child() {

	pid_t pid;
	pid_t ppid;

	ppid = getpid();

	if ((pid = fork()) == -1) {
		perror("> Unable to fork a child.\n");
		exit(1);
	}
	if (pid == 0) {
		printf("> Parent (%d) fork successfully!\n", ppid);
		printf("> Child (%d) starts successfully!\n", getpid());

		parent_pid = ppid;
		child_pid = getpid();

		watch(ppid);
	}
	else {
		child_pid = pid;
	}

}

// Handles SIGCHLD signal
void sigchld_handler(int sig) {

	wait(NULL);

	printf("! Child is killed!\n");
	printf("! Trying to fork another child.\n");

	fork_child();
}

// Handles SIGTRAP signal
void signtrap_handler(int sig) {
	printf("!!! PROCESS (%d) EXIT.\n", getpid());
	// kill(0, SIGKILL);

	if (getpid() == parent_pid) {
		// printf("child_pid = %d\n", child_pid);
		kill(child_pid, SIGKILL);
	} else {
		kill(parent_pid, SIGKILL);
	}

	exit(0);
}

int main() {

	printf("> Parent (%d) starts successfully!\n", getpid());

	(void)signal(SIGCHLD, sigchld_handler);
	(void)signal(SIGTRAP, signtrap_handler);

	child_pid = parent_pid = getpid();

	fork_child();

	beep();
	
	
	return 0;
}