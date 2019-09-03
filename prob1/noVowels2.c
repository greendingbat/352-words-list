#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct patternNode {
	char* pattern;
	struct patternNode* next;
	struct wordNode* listHead;
};

struct wordNode {
	char* word;
	struct wordNode* nextWord;
};

char* findPattern(char*, int);
void addWord(char*, char*);

struct patternNode* head = NULL;

int main() {
	int returnCode = 0;
	int returnVal;
	char str[65];
	
	while ( (returnVal = scanf("%64s", str)) > 0) {
		char* ptr = str;
		int len = 0;	// number of non-symbol letters
		while (*ptr != '\0') {
			if ( isalpha(*ptr) && tolower(*ptr) != 'a' && tolower(*ptr) != 'e' && tolower(*ptr) != 'i' && tolower(*ptr) != 'o' && tolower(*ptr) != 'u') {
				len++;
			}
			ptr++;
		}
		char* pattern;
		if ( (pattern = findPattern(str, len)) ) {
			char* strField = malloc(sizeof(char)*strlen(str) + 1);
			strcpy(strField, str);
			char* patternField = malloc(sizeof(char)*strlen(pattern) + 1);
			strcpy(patternField, pattern);
			addWord(patternField, strField);
		}
	}
	
	struct patternNode* curr = head;
	struct wordNode* wordCurr;
	
 	while (curr != NULL) {		
		wordCurr = curr->listHead;
		while (wordCurr != NULL) {
			printf("%s ", wordCurr->word);
			wordCurr = wordCurr->nextWord;
		}
		printf("\n");
		curr = curr->next;
	} 
	
	
	
	return returnCode;
}

void addWord(char* newPattern, char* newWord) {

	if (head == NULL) {
		// List did not exist. Make new node and make it the head
		struct patternNode* newNode = malloc(sizeof(struct patternNode));
		if (newNode == NULL) {
			fprintf(stderr, "Out of memory\n");
			exit(1);
		}
		struct wordNode* newWordList = malloc(sizeof(struct wordNode));
		if (newWordList == NULL) {
			fprintf(stderr, "Out of memory\n");
			exit(1);
		}
		newWordList->word = newWord;
		newWordList->nextWord = NULL;
		newNode->pattern = newPattern;
		newNode->listHead = newWordList;
		newNode->next = NULL;

		head = newNode;

	} else {
		// List DID exist. Determine if pattern is already in list
		struct patternNode* curr = head;
		int patternFound = 0;
		while (curr != NULL) {
			if (strcmp(curr->pattern, newPattern) == 0) {
				patternFound = 1;
				break;
			}
			curr = curr->next;
		}

		if (patternFound) {
			// Pattern is already in list. Add word to wordList in that node
			struct wordNode* wordCurr = curr->listHead;
			while (wordCurr->nextWord != NULL) {

				wordCurr = wordCurr->nextWord;
			}
			struct wordNode* newWordNode = malloc(sizeof(struct wordNode));
			if (newWordNode == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(1);
			}
			newWordNode->word = newWord;
			newWordNode->nextWord = NULL;
			wordCurr->nextWord = newWordNode;
			struct wordNode* ptr = curr->listHead;
			while (ptr) {
				ptr = ptr->nextWord;
			}
		} else {
			// Pattern is NOT in list. Create new node and add it to end of list
			curr = head;
			while(curr->next != NULL) {
				curr = curr->next;
			}
			struct patternNode* newNode = malloc(sizeof(struct patternNode));
			if (newNode == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(1);
			}
			struct wordNode* newWordList = malloc(sizeof(struct wordNode));
			if (newWordList == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(1);
			}
			newWordList->word = newWord;
			newWordList->nextWord = NULL;
			newNode->pattern = newPattern;
			newNode->listHead = newWordList;
			newNode->next = NULL;
			
			curr->next = newNode;
		}
	}

}

char* findPattern(char* word, int len) {
	char* ptrWord = word;
	char* pattern = malloc(sizeof(char) * len + 1);
	if (pattern == NULL) {
			fprintf(stderr, "Out of memory\n");
			exit(1);
	}
	char* ptrPattern = pattern;
	
	while(*ptrWord != '\0') {
		if (isalpha(*ptrWord) && tolower(*ptrWord) != 'a' && tolower(*ptrWord) != 'e' && tolower(*ptrWord) != 'i' && tolower(*ptrWord) != 'o' && tolower(*ptrWord) != 'u') {
			*ptrPattern = tolower(*ptrWord);
			ptrPattern++;
		}
		ptrWord++;
	}
	if (ptrPattern == pattern) { // empty pattern
		return NULL;
	}
	*ptrPattern = '\0';
	return pattern;
	
}