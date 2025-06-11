#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAIN_MENU 3
#define NUM_TRAINING 8
#define MAX_MEMBERS 6
#define MAX_NICKNAME 20
#define TESTS 7
#define DAYS 6

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

char results[NUM_TRAINING] = {0};

const char *milliways_members[MAX_MEMBERS][2] = {
    {"Jiyeon Park", "Jiyeon"},
    {"Ethan Smith", "Ethan"},
    {"Suphanan Wong", "Suphanan"},
    {"Helena Silva", "Helena"},
    {"Karolina Nowak", "Karolina"},
    {"Liam Wilson", "Liam"}
};

const char *fitness_tests[TESTS] = {
    "1-Mile Run (min)",
    "Speed Sprint (sec)",
    "Push-ups (min)",
    "Squats (min)",
    "Arm Strength (min)",
    "Swimming (min)",
    "Weightlifting (xBW)"
};

float health_scores[MAX_MEMBERS][TESTS] = {0.0f};

const char *days_of_week[DAYS] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

const char *exercise_types[] = {
    "Cardio: Running, Cycling, Fast Walking",
    "Full-body Strength: Push-ups, Squats",
    "Lower-body Strength: Leg Press, Leg Curl",
    "Upper-body Strength: Pull-ups, Chin-ups",
    "Core Strength: Plank, Crunches"
};

char member_routine[MAX_MEMBERS][DAYS][100] = {{{0}}};

// Function declarations
void show_main_menu();
void handle_main_menu();
void show_training_menu();
void handle_training_menu();
void evaluate_stage(int index);
void setHealth();
void getHealth();
void setExerciseRoutine();
void getExerciseRoutine();
void print_member_list();

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
            case 1: printf("[Audition Management] - Feature pending.\n"); break;
            case 2: handle_training_menu(); break;
            case 3: printf("[Debut] - Feature pending.\n"); break;
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

        if (index == 0) {
            char sub_choice[10];
            printf("\nA. Enter Fitness Data\nB. View Fitness Data\nC. Set Basic Workout Routine\nD. View Basic Workout Routine\nChoose A-D: ");
            fgets(sub_choice, sizeof(sub_choice), stdin);

            switch (sub_choice[0]) {
                case 'A': setHealth(); break;
                case 'B': getHealth(); break;
                case 'C': setExerciseRoutine(); break;
                case 'D': getExerciseRoutine(); break;
                default: printf("Invalid option.\n");
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
    if (choice[0] != 'Y') return;

    printf("Did you complete the training and pass the certification? (P/F): ");
    fgets(result, sizeof(result), stdin);
    if (result[0] == 'P' || result[0] == 'F') {
        results[index] = result[0];
        printf("Result saved for Stage %d [%s]: %c\n", index + 1, training_menu[index], result[0]);
    } else {
        printf("Invalid input. Result not saved.\n");
    }
}

void print_member_list() {
    printf("\n=========== Milliways Members ===========\n");
    for (int i = 0; i < MAX_MEMBERS; i++)
        printf("%d. %s (%s)\n", i + 1, milliways_members[i][0], milliways_members[i][1]);
    printf("=========================================\n");
}

void setHealth() {
    printf("========== Enter Fitness Data ==========\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        char input[256];
        printf("Enter 7 test results for %s (%s), comma-separated:\n> ", milliways_members[i][0], milliways_members[i][1]);
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
        getchar();

        if (test_index < 1 || test_index > TESTS) {
            printf("Invalid test number.\n");
            return;
        }

        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(milliways_members[i][1], nickname) == 0) {
                printf("%s (%s): %s = %.2f\n", milliways_members[i][0], nickname,
                       fitness_tests[test_index - 1],
                       health_scores[i][test_index - 1]);
                return;
            }
        }
        printf("Member not found.\n");
    }
}

void setExerciseRoutine() {
    int core_used[MAX_MEMBERS] = {0};
    char input[100];
    print_member_list();
    printf("Enter member number to assign routine: ");
    fgets(input, sizeof(input), stdin);
    int index = atoi(input) - 1;

    if (index < 0 || index >= MAX_MEMBERS) {
        printf("Invalid member index.\n");
        return;
    }

    for (int d = 0; d < DAYS; d++) {
        int cardio = 0, strength = 0;
        char selected[100] = "";
        printf("\nDay: %s\n", days_of_week[d]);
        for (int i = 0; i < 5; i++) {
            printf("%d. %s\n", i + 1, exercise_types[i]);
        }

        while (1) {
            printf("Select exercise (0 to finish): ");
            fgets(input, sizeof(input), stdin);
            int choice = atoi(input);

            if (choice == 0) {
                if (!cardio || !strength) {
                    printf("Each day must include at least 1 cardio and 1 strength/core exercise.\n");
                    continue;
                }
                break;
            }

            if (choice < 1 || choice > 5) {
                printf("Invalid choice. Try again.\n");
                continue;
            }

            if (choice == 5 && core_used[index]) {
                printf("Core exercises can only be used once per week.\n");
                continue;
            }

            // Prevent duplicate entries
            if (strstr(selected, exercise_types[choice - 1]) != NULL) {
                printf("Exercise already selected.\n");
                continue;
            }

            strcat(selected, exercise_types[choice - 1]);
            strcat(selected, "; ");

            if (choice == 1) cardio = 1;
            else strength = 1;
            if (choice == 5) core_used[index] = 1;
        }

        strcpy(member_routine[index][d], selected);
    }

    printf("\nWorkout routine saved successfully for %s.\n", milliways_members[index][1]);
}

void getExerciseRoutine() {
    print_member_list();
    printf("Enter member number to view routine: ");
    char input[10];
    fgets(input, sizeof(input), stdin);
    int index = atoi(input) - 1;

    if (index < 0 || index >= MAX_MEMBERS) {
        printf("Invalid member index.\n");
        return;
    }

    printf("\n===== Workout Routine for %s (%s) =====\n", milliways_members[index][0], milliways_members[index][1]);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s\n", days_of_week[d],
               strlen(member_routine[index][d]) > 0 ? member_routine[index][d] : "(No routine set)");
    }
}
