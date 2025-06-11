#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAIN_MENU 3
#define NUM_TRAINING 8
#define MAX_MEMBERS 6
#define MAX_NICKNAME 20
#define TESTS 7

// Menu labels
const char *main_menu[] = {
    "Audition Management",
    "Training",
    "Debut"
};

const char *training_menu[] = {
    "Physical Strength & Knowledge",
    "Self-Management & Teamwork",
    "Language & Pronunciation",
    "Vocal",
    "Dance",
    "Visual & Image",
    "Acting & Stage Performance",
    "Fan Communication"
};

// Training results: 'P' for Pass, 'F' for Fail, '\0' = not attempted
char results[NUM_TRAINING] = {0};

// Member info
const char *milliways_members[MAX_MEMBERS][2] = {
    {"Jiyeon Park", "Jiyeon"},
    {"Ethan Smith", "Ethan"},
    {"Suphanan Wong", "Suphanan"},
    {"Helena Silva", "Helena"},
    {"Karolina Nowak", "Karolina"},
    {"Liam Wilson", "Liam"}
};

// Fitness test names
const char *fitness_tests[TESTS] = {
    "1-Mile Run (min)",
    "Speed Sprint (sec)",
    "Push-ups (min)",
    "Squats (min)",
    "Arm Strength (min)",
    "Swimming (min)",
    "Weightlifting (xBW)"
};

// Fitness data
float health_scores[MAX_MEMBERS][TESTS] = {0.0f};

// Function declarations
void handle_main_menu();
void show_main_menu();
void handle_training_menu();
void show_training_menu();
void evaluate_stage(int index);
void setHealth();
void getHealth();

int main(void) {
    handle_main_menu();
    return 0;
}

void show_main_menu() {
    printf("\n========== Magrathea Main Menu ==========\n");
    for (int i = 0; i < NUM_MAIN_MENU; i++) {
        printf("%d. %s\n", i + 1, main_menu[i]);
    }
    printf("=========================================\n");
}

void handle_main_menu() {
    char input[10];
    while (1) {
        show_main_menu();
        printf("Enter choice (or 0/Q to quit): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == 'Q' || input[0] == 'q' || input[0] == '\n') {
            printf("Exiting program.\n");
            break;
        }

        int choice = atoi(input);
        if (choice < 1 || choice > NUM_MAIN_MENU) {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("[Audition Management] - Feature pending.\n");
                break;
            case 2:
                handle_training_menu();
                break;
            case 3:
                printf("[Debut] - Feature pending.\n");
                break;
        }
    }
}

void show_training_menu() {
    printf("\n========== Training Stages ==========\n");
    for (int i = 0; i < NUM_TRAINING; i++) {
        char status = results[i];
        if (status == 'P')
            printf("%d. %s [Passed]\n", i + 1, training_menu[i]);
        else if (status == 'F')
            printf("%d. %s [Failed]\n", i + 1, training_menu[i]);
        else
            printf("%d. %s\n", i + 1, training_menu[i]);
    }
    printf("=====================================\n");
}

void handle_training_menu() {
    char input[10];

    while (1) {
        show_training_menu();
        printf("Select training stage (or 0/Q to return): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == 'Q' || input[0] == 'q' || input[0] == '\n') {
            printf("Returning to main menu.\n");
            break;
        }

        int stage = atoi(input);
        if (stage < 1 || stage > NUM_TRAINING) {
            printf("Invalid training stage.\n");
            continue;
        }

        int index = stage - 1;

        if (results[index] == 'P') {
            printf("Stage %d [%s] already completed.\n", stage, training_menu[index]);
            continue;
        }

        if (index == 1 && results[0] != 'P') {
            printf("You must complete Stage 1 before Stage 2.\n");
            continue;
        } else if (index >= 2 && (results[0] != 'P' || results[1] != 'P')) {
            printf("You must complete Stages 1 and 2 before accessing Stages 3–8.\n");
            continue;
        }

        // Special submenu for Stage 1
        if (index == 0) {
            char sub_choice[10];
            printf("\nA. Enter Fitness Data\nB. View Fitness Data\nChoose A or B: ");
            fgets(sub_choice, sizeof(sub_choice), stdin);
            if (sub_choice[0] == 'A') {
                setHealth();
            } else if (sub_choice[0] == 'B') {
                getHealth();
            } else {
                printf("Invalid option.\n");
            }
            continue;
        }

        evaluate_stage(index);
    }
}

void evaluate_stage(int index) {
    char choice[10], result[10];

    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(choice, sizeof(choice), stdin);
    if (choice[0] != 'Y') {
        printf("Returning to training menu.\n");
        return;
    }

    printf("Did you complete the training and pass the certification? (P/F): ");
    fgets(result, sizeof(result), stdin);
    if (result[0] == 'P' || result[0] == 'F') {
        results[index] = result[0];
        printf("Result saved for Stage %d [%s]: %c\n", index + 1, training_menu[index], result[0]);
    } else {
        printf("Invalid input. Result not saved.\n");
    }
}

void setHealth() {
    printf("========== Enter Fitness Data ==========\n");

    for (int i = 0; i < MAX_MEMBERS; i++) {
        char input[256];
        printf("Enter 7 test results for %s (%s), comma-separated:\n", 
               milliways_members[i][0], milliways_members[i][1]);
        printf("Format: Run, Sprint, PushUps, Squats, ArmStrength, Swim, Weightlifting\n> ");
        fgets(input, sizeof(input), stdin);

        char *token = strtok(input, ",");
        int count = 0;
        while (token != NULL && count < TESTS) {
            health_scores[i][count++] = atof(token);
            token = strtok(NULL, ",");
        }

        if (count != TESTS) {
            printf("Invalid number of inputs. Please re-enter for %s.\n", milliways_members[i][1]);
            i--;
        }
    }

    printf("All fitness data recorded successfully.\n");
}

void getHealth() {
    char option[10];
    printf("\nView Options:\n");
    printf("A. View All Fitness Data\n");
    printf("B. View Data for One Member\n");
    printf("C. View One Test for One Member\n");
    printf("Choose A/B/C: ");
    fgets(option, sizeof(option), stdin);

    if (option[0] == 'A') {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\n%s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
            for (int j = 0; j < TESTS; j++) {
                printf("  %s: %.2f\n", fitness_tests[j], health_scores[i][j]);
            }
        }
    } else if (option[0] == 'B') {
        char nickname[MAX_NICKNAME];
        printf("Enter member nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = '\0';

        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(milliways_members[i][1], nickname) == 0) {
                printf("\n%s (%s):\n", milliways_members[i][0], nickname);
                for (int j = 0; j < TESTS; j++) {
                    printf("  %s: %.2f\n", fitness_tests[j], health_scores[i][j]);
                }
                return;
            }
        }
        printf("Member not found.\n");
    } else if (option[0] == 'C') {
        char nickname[MAX_NICKNAME];
        int test_index;
        printf("Enter member nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = '\0';

        printf("Select Test (1–7):\n");
        for (int i = 0; i < TESTS; i++) {
            printf("%d. %s\n", i + 1, fitness_tests[i]);
        }
        printf("> ");
        scanf("%d", &test_index);
        getchar(); // consume newline

        if (test_index < 1 || test_index > TESTS) {
            printf("Invalid test number.\n");
            return;
        }

        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(milliways_members[i][1], nickname) == 0) {
                printf("%s (%s): %s = %.2f\n", 
                       milliways_members[i][0], nickname,
                       fitness_tests[test_index - 1],
                       health_scores[i][test_index - 1]);
                return;
            }
        }
        printf("Member not found.\n");
    } else {
        printf("Invalid option.\n");
    }
}
