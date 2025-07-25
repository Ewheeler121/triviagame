#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define QUESTION_FILE "questions.txt"
#define ANSWER_FILE "answers.txt"
#define INITIAL_BUFFER_SIZE 4

void free_trivia_list(char **arr, int size) {
    if(arr != NULL) {
        for(int i = 0; i < size; i++) {
            free(arr[i]);
        }
        free(arr);
    }
}

int read_trivia_file(const char *filename, char ***storage) {
    int size = 0, capacity = INITIAL_BUFFER_SIZE;
    size_t length;
    char *buffer = NULL, **temp_storage, **t;
    FILE *file;

    if((file = fopen(filename, "r")) == NULL) {
        return -1;
    }
    
    temp_storage = malloc(sizeof(char *) * INITIAL_BUFFER_SIZE);
    while(getline(&buffer, &length, file) > 0) {
        if(size + 1 >= capacity) {
            capacity *= 2;
            t = realloc(temp_storage, sizeof(char *) * capacity);
            if(t == NULL) {
                //if this happens, then your FUCKED
                goto error;
            }
            temp_storage = t;
        }
        temp_storage[size++] = buffer;
        buffer = NULL;
    }
    
    fclose(file);
    *storage = temp_storage;
    return size;
error:
    for(int i = 0; i < size; i++) {
        free(temp_storage[i]);
    }
    free(temp_storage);
    fclose(file);
    return -1;
}

int main() {
    srand(time(NULL));
    char **questions, **answers;
    int s, score = 0, size = 0;

    if((size = read_trivia_file(QUESTION_FILE, &questions)) < 0) {
        fprintf(stderr, "ERROR: Incorrect file format\n");
        return -1;
    }
    
    if((s = read_trivia_file(ANSWER_FILE, &answers)) != size) {
        fprintf(stderr, "ERROR: Incorrect file format\n");
        free_trivia_list(questions, size);
        free_trivia_list(answers, s);
        return -1;
    }

    int indices[size];
    for(int i = 0; i < size; i++) {
        indices[i] = i;
    }

    //Fisher-Yates algorithm (No buffer for Swap????)
    for(int z, i = size - 1; i > 0; i--) {
        if((z = rand() % (i + 1)) != i) {
            indices[i] ^= indices[z];
            indices[z] ^= indices[i];
            indices[i] ^= indices[z];
        }
    }

    char *buffer = NULL;
    size_t l;
    for(int i = 0; i < size; i++) {
        int index = indices[i];
        printf("Q%d: %s", i + 1, questions[index]);
        if(getline(&buffer, &l, stdin) < 0) {
            break;
        }
        if(!strcasecmp(answers[index], buffer)) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong - the correct awnser: %s", answers[index]);
        }

        free(buffer);
        buffer = NULL;
    }

    printf("Your final score is... %d/%d\n", score, size);

    free_trivia_list(questions, size);
    free_trivia_list(answers, size);
    return 0;
}
