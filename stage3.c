#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRAINEES 6
#define MAX_QUESTIONS 10
#define QUIZ_COUNT 5

typedef struct {
    int id;
    char question[256];
    char correct_answer[256];
} QuizQuestion;

typedef struct {
    int id;
    char correctness;
} QuizAnswer;

typedef struct {
    char name[50];
    char nickname[30];
    char nationality[30];
    int score;
    char pass;
} Trainee;

QuizQuestion question_bank[MAX_QUESTIONS] = {
    {1, "What is the Korean word for 'hello'?", "안녕하세요"},
    {2, "What is the Korean word for 'thank you'?", "감사합니다"},
    {3, "What is the Korean word for 'love'?", "사랑"},
    {4, "What is the Korean word for 'school'?", "학교"},
    {5, "What is the Korean word for 'friend'?", "친구"},
    {6, "What is the Korean word for 'food'?", "음식"},
    {7, "What is the Korean word for 'family'?", "가족"},
    {8, "What is the Korean word for 'music'?", "음악"},
    {9, "What is the Korean word for 'movie'?", "영화"},
    {10, "What is the Korean word for 'water'?", "물"}
};

Trainee trainees[MAX_TRAINEES] = {
    {"Jiyeon Park", "Jiyeon", "South Korea", 0, 'N'},
    {"Ethan Smith", "Ethan", "USA", 0, 'N'},
    {"Suphanan Wong", "Suphanan", "Thailand", 0, 'N'},
    {"Helena Silva", "Helena", "Brazil", 0, 'N'},
    {"Karolina Nowak", "Karolina", "Poland", 0, 'N'},
    {"Liam Wilson", "Liam", "Australia", 0, 'N'}
};

QuizAnswer answer_sheet[QUIZ_COUNT];

void isAnswer(QuizQuestion* q, char* user_ans, int index) {
    answer_sheet[index].id = q->id;
    if (strcmp(q->correct_answer, user_ans) == 0)
        answer_sheet[index].correctness = 'O';
    else
        answer_sheet[index].correctness = 'X';
}

int selectRandomTakers() {
    srand(time(NULL));
    int index;
    do {
        index = rand() % MAX_TRAINEES;
    } while (strcmp(trainees[index].nationality, "South Korea") == 0);

    printf("Welcome, %s, to the Korean quiz session!\n", trainees[index].name);
    return index;
}

void serveRandomQuiz(int trainee_index) {
    int score = 0;
    int used_ids[QUIZ_COUNT] = {0};
    printf("Quiz will start now...\n");

    for (int i = 0; i < QUIZ_COUNT; i++) {
        int qid;
        do {
            qid = rand() % MAX_QUESTIONS;
        } while (used_ids[qid % QUIZ_COUNT] != 0);
        used_ids[qid % QUIZ_COUNT] = 1;

        printf("\nQ%d: %s\nYour Answer: ", i + 1, question_bank[qid].question);
        char user_ans[256];
        fgets(user_ans, sizeof(user_ans), stdin);
        user_ans[strcspn(user_ans, "\n")] = 0; // remove newline

        isAnswer(&question_bank[qid], user_ans, i);
        if (answer_sheet[i].correctness == 'O') score += 20;
    }

    trainees[trainee_index].score = score;
    trainees[trainee_index].pass = (score >= 80) ? 'Y' : 'N';

    // Show results
    printf("\n----- Korean Quiz Result -----\n");
    for (int i = 0; i < QUIZ_COUNT; i++) {
        printf("Q%d: %c\n", answer_sheet[i].id, answer_sheet[i].correctness);
    }
    printf("Total Score: %d\n", score);
    printf("Status: %s\n", trainees[trainee_index].pass == 'Y' ? "PASS" : "FAIL");
}

void testKoreanLang() {
    int index = selectRandomTakers();
    serveRandomQuiz(index);
}

// Menu wrapper for test
int main() {
    char choice;
    while (1) {
        printf("\n==== Korean Language Training ====\n");
        printf("A. Korean Quiz\n");
        printf("Q. Quit\n");
        printf("Select option: ");
        scanf(" %c", &choice);
        getchar(); // clear newline

        switch (toupper(choice)) {
            case 'A':
                testKoreanLang();
                break;
            case 'Q':
                printf("Exiting quiz system.\n");
                return 0;
            default:
                printf("Invalid input.\n");
        }
    }
}
