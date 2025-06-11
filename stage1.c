#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAIN_MENU 3
#define NUM_TRAINING 8

// One-dimensional arrays for menu entries
char *main_menu[] = {
    "Audition Management",
    "Training",
    "Debut"
};

char *training_menu[] = {
    "Physical Strength & Knowledge",         // Stage 1
    "Self-Management & Teamwork",            // Stage 2
    "Language & Pronunciation",              // Stage 3
    "Vocal",                                 // Stage 4
    "Dance",                                 // Stage 5
    "Visual & Image",                        // Stage 6
    "Acting & Stage Performance",            // Stage 7
    "Fan Communication"                      // Stage 8
};

// One-dimensional array for storing training results: 'P', 'F', or '\0'
char results[NUM_TRAINING] = {0};

// Function declarations
void show_main_menu();
void handle_main_menu();
void show_training_menu();
void handle_training_menu();
void evaluate_stage(int index);

int main(void) {
    handle_main_menu();
    return 0;
}

// Display and handle main menu
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
                printf("[Audition Management] - Function not yet implemented.\n");
                break;
            case 2:
                handle_training_menu();
                break;
            case 3:
                printf("[Debut] - Function not yet implemented.\n");
                break;
        }
    }
}

// Show main menu
void show_main_menu() {
    printf("\n========== Magrathea Main Menu ==========\n");
    for (int i = 0; i < NUM_MAIN_MENU; i++) {
        printf("%d. %s\n", i + 1, main_menu[i]);
    }
    printf("=========================================\n");
}

// Handle training menu logic
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

        // Prevent reselection
        if (results[index] == 'P') {
            printf("Stage %d [%s] already completed.\n", stage, training_menu[index]);
            continue;
        }

        // Enforce sequential order
        if (index == 1 && results[0] != 'P') {
            printf("You must complete Stage 1 before Stage 2.\n");
            continue;
        } else if (index >= 2 && (results[0] != 'P' || results[1] != 'P')) {
            printf("You must complete Stages 1 and 2 before accessing Stages 3–8.\n");
            continue;
        }

        evaluate_stage(index);
    }
}

// Show training menu
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

// Handle evaluation for a stage
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
