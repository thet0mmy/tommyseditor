#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

unsigned int linenum;
int lastline;
int dr;
char buf[250][99];
char rbuf[99];
char cmd;
char welcome[99] = "welcome to tommy's editor. check out :help.";

int edit(int argc, char *argv[])
{
	while (1<2) {
		printf("%x : ",linenum);
		dr = 0;
		fgets(rbuf, 99, stdin);

		if (strcmp(rbuf,":eq\r") == 0) {
			return 0;
		}

		if (strcmp(rbuf,":lb\n") == 0) {
			printf("lastline=%i\n",lastline);
			for (int lbf = 0; lbf < lastline; lbf++) {
				printf("%x -> %s",lbf,buf[lbf]);
			}
			dr = 1;
		}

		if (strcmp(rbuf,":help\n") == 0) {
	printf("\n:eq = quit   :lb = list buffer\n");
	printf(":bg = beginning of buffer\n");
	printf(":ed = end of buffer\n");
	printf(":up = move one line up\n");
	printf(":dn = move one line down\n");
	printf("\n:wb = write buffer to file\n");
	printf(":op = open file to buffer\n\n");
	printf("writing is buggy, be careful!\n");
	printf("type to add stuff to the buffer.\n");
	printf("buffer lines must not start with a colon.\n");
			dr = 1;
		}

		if (strcmp(rbuf,":go\n") == 0) {
			int *jumpline;
			scanf("%i",jumpline);
			linenum = *jumpline-1;
			dr = 1;
		}

		if (strcmp(rbuf,":bg\n") == 0) {
			linenum = 0;			
			dr = 1;
		}

		if (strcmp(rbuf,":ed\n") == 0) {
			linenum = lastline;
			dr = 1;
		}

		if (strcmp(rbuf,":md\n") == 0) {
			linenum = lastline/2;
			dr = 1;
		}

		if (strcmp(rbuf,":up\n") == 0) {
			linenum--;
			dr = 1;
		}

		if (strcmp(rbuf,":dn\n") == 0) {
			linenum++;
			dr = 1;
		}

		if (strcmp(rbuf,":wb\n") == 0) {
			char fname[30];
			if (argc<2) {
				printf("no filename specified at cmdline\n");
				printf("enter filename to save as: ");
				scanf("%s",fname);
				linenum--;
			}
			else {
				strcpy(fname,argv[1]);
			}
			FILE *savefile = fopen(fname, "w");
			char savefix[99];
			printf("Lastline=%x\n",lastline);
			strcpy(savefix, buf[lastline-1]);
			for (int wrbuf=0; wrbuf < lastline; wrbuf++) {
				fprintf(savefile,"%s",buf[wrbuf]);
			}
			fclose(savefile);
			strcpy(buf[lastline-1],savefix);
			printf("saved buffer.");
			dr = 1;
			
		}

		if (strcmp(rbuf,":op\n") == 0) {
			char fname[30];
			int rlinenum = 0;
			char line[102];

			lastline = 0;
			linenum = 0;

			printf("enter filename to open: ");
			fgets(fname,30,stdin);
			fname[strlen(fname)-1] = '\0';
			FILE *openf = fopen(fname,"r");
			if (openf == NULL) {
				printf("fp is null, opening failed.\n");
			}
			while (!feof(openf)) {
				fgets(line,99,openf);
				for (int debug = 0; debug < strlen(line)+1; debug++) {
					printf("%x ",line[debug]);
				}
				printf("\n");
				if (line[1] != 0) {
					int llen = strlen(line);
					line[100] = '\n';
					line[101] = '\0';
					strcpy(buf[rlinenum],line);
					if (rlinenum+1 > lastline) {
						lastline = rlinenum + 1;
					}
					rlinenum++;
				}
			}
			linenum = 0;
			dr = 1;
		}

		if (dr == 0) {
			if (rbuf[0] != ':') {
				strcpy(buf[linenum],rbuf);
				linenum++;
			}
			else {
				printf("that's not a command. see :help\n");
			}
		}


		if (linenum > lastline) { lastline = linenum; }
	}
	return 1;
}

int main(int argc, char *argv[])
{
	printf("%s\n",welcome);
	for (int dispmsg=1; dispmsg < strlen(welcome) - (time(0) % strlen(welcome)); dispmsg++) {
		printf("%x ",welcome[dispmsg]);
	}
	printf("\n");
	void *m = malloc(sizeof(buf));
	edit(argc, argv);
}
