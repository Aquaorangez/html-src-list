/*
 ============================================================================
 Name        : MCampitelliHtmlSrcList.c
 Author      : Mick Campittelli
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 Returns the number of valid src tags

 @param str a char array of HTML source code
 @return number of tags.
 */

int countURL(char str[]);

/**
 prints each URL associated with valid src tags

 @param str a char array of HTML source code
 */
void printURL(char str[]);

/**
 Grabs valid tags and prints them in order, line by line

 @param str a char array of HTML source code
 @return the valid tags in a new char array
 */
char* tagsList(char str[]);

/**
 prints each valid tag with its frequency count.

 @param str a char array of HTML source code
 */
void printFrequencies(char str[]);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char url[BUFSIZ], buffer[BUFSIZ], str[1024 * 256], buffer2[BUFSIZ];
	FILE *file;

	strcat(url, "curl -s ");
	printf("URL:\n");

	strcat(url, fgets(buffer2, BUFSIZ, stdin));

//	test URL =	curl -s http://wfs.sbcc.edu/staff/nfguebels/web/cs137/html_src_list/simple.html"

	file = popen(url, "r");

	do {
		strcat(str, buffer);
	} while (fgets(buffer, BUFSIZ, file));

	printf("%s", "Ready\n");

	while (fgets(buffer2, BUFSIZ, stdin) != 'q') {

		if (buffer2[0] == 'c') {
			printf("%d\n", countURL(str));
		} else if (buffer2[0] == 't') {
			printf("%s", tagsList(str));
		} else if (buffer2[0] == 'u') {
			printURL(str);
		} else if (buffer2[0] == 'f') {
			printFrequencies(tagsList(str));
		} else if (buffer2[0] == 'q') {
			int countURL(char str[]);
			void printURL(char str[]);
			char* tagsList(char str[]);
			void printFrequencies( c);
			printf("%s", "Complete\n");
			break;
		}
		printf("%s", "Ready\n");
	}
	return EXIT_SUCCESS;
}

/**
 Returns the number of valid src tags

 @param str a char array of HTML source code
 @return number of tags.
 */
int countURL(char str[]) {
	char *pSrc, *pQ1;
	int count = 0;
	pSrc = strstr(str, "src=\"");

	while (pSrc) {
		pQ1 = pSrc + 1;

		//If the space before "src" isn't a space or tab, ignore it
		if (*(pSrc - 1) == ' ' || *(pSrc - 1) == '\t') {
			while (*pQ1 != '\"') {
				pQ1++;
				//takes char *str and counts the frequency of each tag. prints each pair "tag count" line by line
			}
			count++;
		}

		//set pSrc to next valid src tag, if any
		pSrc = strstr(pQ1, "src=\"");

	}
	return count;
}

/**
 prints each URL associated with valid src tags

 @param str a char array of HTML source code
 */
void printURL(char str[]) {
	char temp[BUFSIZ];
	char *pSrc, *pQ1, *pQ2;
	int count;
	pSrc = strstr(str, "src=\"");
	printf("%d\n", count);
	while (pSrc) {
		pQ1 = pSrc + 5;
		pQ2 = pQ1;

		//If the space before "src" isn't a space or tab, ignore it
		if (*(pSrc - 1) == ' ' || *(pSrc - 1) == '\t') {

			// crawl to end quotation mark,
			// count the number of characters in the URL, copy to temp array, reset count.
			while (*pQ1 != '\"') {
				count++;
				pQ1++;
			}
			strncpy(temp, pQ2, count);
			printf("%s\n", temp);
			count = 0;
			memset(temp, 0, sizeof(temp));
		}
		pSrc = strstr(pQ1, "src=\"");
	}

}

/**
 Grabs valid tags and prints them in order, line by line

 @param str a char array of HTML source code
 @return the valid tags in a new char array
 */
char* tagsList(char str[]) {
	char temp[BUFSIZ];
	char* tags;
	char *pSrc, *pQ1, *pQ2, *pQ3;
	int count;
	pSrc = strstr(str, "src=\"");
	tags = (char*) malloc(sizeof(char) * BUFSIZ);

	while (pSrc) {
		pQ1 = pSrc - 1;
		pQ3 = pSrc + 1;

		//If the space before "src" isn't a space or tab, ignore it
		if (*(pSrc - 1) == ' ' || *(pSrc - 1) == '\t') {

			// crawls backwards to opening tag '<'
			while (*pQ1 != '<') {
				pQ1--;
			}

			pQ1++;
			pQ2 = pQ1;
			// crawls to the space after the tag, incrementing the count for each character
			while (*pQ2 != ' ' && *pQ2 != '\t' && *pQ2 != '\n') {
				pQ2++;
				count++;
			}

			// checks if the tag contains any white space, newlines, and
			// tabs between the end of the tag and "src" and accounts for them by decrementing the count.
			while (*(pQ2 + 1) == ' ' || *(pQ2 + 1) == '\t' || *(pQ2 + 1) == '\n') {
				pQ2++;
				count--;
			}

			//copy to temp array, copy temp array into tags array, reset temp array.
			strncpy(temp, pQ1, count);
			strcat(temp, "\n");
			strcat(tags, temp);
			count = 0;
			memset(temp, 0, sizeof(temp));
		}
		pSrc = strstr(pQ3, "src=\"");
	}
	return tags;
}

/**
 prints each valid tag with its frequency count.

 @param str a char array of HTML source code
 */
void printFrequencies(char str[]) {

	//appends newline to end of tags file for easy splitting by delimiter
	char buffer[BUFSIZ];
	strcpy(buffer, str);
	strcat(buffer, "\n");
	char * token = strtok(buffer, "\n");

	//counts the number of tokens
	int total_line = 0, i, j;
	const char *stz;

	for (stz = str; *stz; ++stz) {
		total_line += *stz == '\n';
	}

	//initializes an array of the size of number of tags
	char *array[total_line], *temp[BUFSIZ];

	//saves each token as an array element, in order of appearance
	while (token != NULL) {
		array[i++] = token;
		token = strtok(NULL, "\n");
	}

	for (i = 0; i <= total_line + 1; i++) {
		int count = 1;
		for (j = i + 1; j <= total_line - 1; j++) {
			if (strcmp(array[i], array[j]) == 0) {
				count++;
			}

			//once loop hits end of the array, stop and print tag + count
			if (j >= total_line - 1 && strstr(temp, array[i]) == NULL) {
				printf("%s %d\n", array[i], count);
				strcat(temp, array[i]);
			}

		}
	}

	//Edge case - if the last element is the only of its kind, count is 1;
	if (strstr(temp, array[total_line - 1]) == NULL) {
		printf("%s 1\n", array[total_line - 1]);
	}
}

