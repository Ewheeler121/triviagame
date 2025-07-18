#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 100
#define MAX_LINE 500

char *questions[MAX_QUESTIONS];
char *answers[MAX_QUESTIONS];
int question_count = 0;

void load_file(const char *filename, char *array[], int *count) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		exit (1);
	}

	char buffer[MAX_LINE];
	while (fgets(buffer, sizeof(buffer), file)) {
		buffer[strcspn(buffer, "\n")] = '\0';
		array[*count] = malloc(strlen(buffer) + 1);
		strcpy(array[*count], buffer);
		(*count)++;
	}

	fclose(file);
}

void free_memory(char *array[], int count) {
	for (int i = 0; i < count; i++) {
		free(array[i]);
	}
}

int main() {
	srand(time(NULL));

	// This little bit here loads the questions and answers
	load_file("questions.txt", questions, &question_count);
	int answer_count = 0;
	load_file("answers.txt", answers, &answer_count);

	if (question_count != answer_count) {
		fprintf(stderr, "Mismatch between the number of questions and answers - please fix this!\n");
		return 1;
	}

	// Random question order
	int indices[MAX_QUESTIONS];
	for (int i = 0; i < question_count; i++) {
		indices[i] = i;
	}

	//Shuffle the indices using the Fisher-Yates algorithm
	for (int i = question_count -1; i > 0; i--) {
		int z = rand() % (i + 1);
		int temp = indices[i];
		indices[i] = indices[z];
		indices[z] = temp;
	}

	int score = 0;
	char user_input[MAX_LINE];

	for (int i = 0; i < question_count; i++) {
		int q_idx = indices[i];
		printf("Q%d: %s\n> ", i + 1, questions[q_idx]);
		fgets(user_input, sizeof(user_input), stdin);
		user_input[strcspn(user_input, "\n")] = '\0';

		// Bonus question
		if (strcasecmp(questions[q_idx], "What is the air-speed velocity of an unladen swallow ???") == 0) {
			if (strcasecmp(user_input, "African or European?") == 0) {
				printf("I don't know that! *gets cast into the Gorge of Eternal Peril*\n");
				printf("You win the game! You may continue your quest for the Holy Grail!\n");
				break;
			} else {
				printf("Wrong! You were cast into the Gorge of Eternal Peril - try the next question.\n");
				continue;
			}
		}

		// All other questions
		if (strcasecmp(user_input, answers[q_idx]) == 0) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Wrong - the correct answer: %s\n", answers[q_idx]);
		}
	}

	printf("\nYour final score is... %d/%d\n", score, question_count);

	free_memory(questions, question_count);
	free_memory(answers, answer_count);

	return 0;
}
