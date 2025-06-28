C, quiz-app, adaptive-learning, memory-tracker, file-handling, CLI, beginner, ATS-friendly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 100

typedef struct {
    char question[256];
    char options[4][100];
    char correct;
} Quiz;

Quiz questions[MAX_QUESTIONS];
int q_count = 0;

void loadQuestions(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf(" Could not open %s\n", filename);
        return;
    }

    while (fgets(questions[q_count].question, sizeof(questions[q_count].question), fp)) {
        for (int i = 0; i < 4; i++)
            fgets(questions[q_count].options[i], sizeof(questions[q_count].options[i]), fp);
        fscanf(fp, " %c\n", &questions[q_count].correct);
        q_count++;
    }

    fclose(fp);
}

void logMistake(Quiz q) {
    FILE *fp = fopen("mistakes.txt", "a");
    if (!fp) return;
    fprintf(fp, "%s", q.question);
    for (int i = 0; i < 4; i++)
        fprintf(fp, "%s", q.options[i]);
    fprintf(fp, "%c\n", q.correct);
    fclose(fp);
}

void quizUser() {
    int score = 0;
    for (int i = 0; i < q_count; i++) {
        printf("\n %s", questions[i].question);
        for (int j = 0; j < 4; j++)
            printf("   %s", questions[i].options[j]);

        char ans;
        printf("Your answer (A/B/C/D): ");
        scanf(" %c", &ans);

        if (ans == questions[i].correct || ans == questions[i].correct + 32) {
            printf(" Correct!\n");
            score++;
        } else {
            printf(" Wrong. Correct: %c\n", questions[i].correct);
            logMistake(questions[i]);
        }
    }
    printf(" Final Score: %d / %d\n", score, q_count);
}

int main() {
    printf(" Smart Quiz Trainer\n");

    // Load mistakes first (if any)
    loadQuestions("mistakes.txt");
    if (q_count > 0) {
        printf("Retrying past mistakes first (%d found).\n", q_count);
        quizUser();
        remove("mistakes.txt");
    }

    // Load main questions
    q_count = 0;
    loadQuestions("questions.txt");
    if (q_count == 0) {
        printf(" No questions found in questions.txt\n");
        return 1;
    }

    printf(" Starting new quiz.\n");
    quizUser();

    return 0;
}
