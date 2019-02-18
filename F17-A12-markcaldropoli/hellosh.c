/* hellosh.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
	char line[1024];
	int pid, i, spaces, output_loc, output_file, cmd_one, cmd_two, run_cmd_two, exec_cmd_two, status;
	char *args[] = {&line, 0};
	char *temp;

	while(1) {
		memset(&line[0], '\0', sizeof(line));
		memset(&args[0], 0, sizeof(args));

		spaces = 0;
		output_loc = 0;
		output_file = 0;
		cmd_one = 0;
		cmd_two = 0;
		run_cmd_two = 0;
		exec_cmd_two = 0;
		status = 0;

		printf("Hello!!>");
		if(!fgets(line, 1023, stdin)) break;

		if(strcmp(line, "exit\n") == 0) break;

		for(i = 0; i< strlen(line); i++) {
			if(line[i] == '\n') line[i] = '\0';
		}

		temp = strtok(line, " ");
		while(temp) {
			if(strchr(">\0", *temp)) {
				args[spaces++] = NULL;
				output_loc = spaces;
			} else if(strcmp("&&", temp) == 0) {
				args[spaces++] = NULL;
				cmd_two = spaces;
				cmd_one = 1;
			} else if(strcmp(";", temp) == 0) {
				args[spaces++] = NULL;
				run_cmd_two = spaces;
				cmd_one = 0;
			} else args[spaces++] = temp;

			temp = strtok(NULL, " ");
		}

		args[++spaces] = NULL;

		if(0) RUN: exec_cmd_two = 1;

		pid = fork();

		if(pid == 0) {
			if(output_loc) {
				output_file = open(args[output_loc], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				dup2(output_file, 1);
			}

			/* This is the child */
			execvp(line, args);
			fprintf(stderr, "Hello!!: %s\n", strerror(errno));
			exit(errno);
		} else {
			/* This is the parent */
			if(cmd_two && exec_cmd_two == 0) {
				if(waitpid(pid, &status, 0) == -1) {
					perror("waitpid failure");
					return EXIT_FAILURE;
				}

				if((WEXITSTATUS(status) == 0 && cmd_one == 1) || cmd_one == 0) {
					for(i = run_cmd_two; i < spaces; i++) args[i-run_cmd_two] = args[i];
					args[i] = NULL;
					strcpy(line, args[0]);
					goto RUN;
				}
			}
			else wait(NULL);
		}
	}
	return 0;
}
