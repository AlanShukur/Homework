#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_LENGTH 512
#define EXPECTED_FIELDS 7

char judges_array[MAX_JUDGES][MAX_LENGTH];

void strip_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

void display_judge(const char *data, int index) {
    char copy[MAX_LENGTH];
    char *token;
    int field = 0;

    strncpy(copy, data, MAX_LENGTH);

    printf("[Judge %d]\n", index + 1);
    token = strtok(copy, ",");

    while (token != NULL) {
        switch (field) {
            case 0: printf("Name: %s\n", token); break;
            case 1: printf("Gender: %s\n", token); break;
            case 2: printf("Affiliation: %s\n", token); break;
            case 3: printf("Title: %s\n", token); break;
            case 4: printf("Expertise: %s\n", token); break;
            case 5: printf("Email: %s\n", token); break;
            case 6: printf("Phone: %s\n", token); break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    printf("-----------------------------------\n");
}

int main(void) {
    char project_name[100];
    int total_judges, selected_members;
    int judge_count = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry       #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    strip_newline(project_name);

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // consume newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (judge_count < total_judges) {
        char name[100], gender[20], affiliation[100], title[100], specialty[100], email[100], phone[50];

        printf("Judge %d Information:\n", judge_count + 1);

        printf(" - Name: ");
        fgets(name, sizeof(name), stdin);
        strip_newline(name);

        printf(" - Gender: ");
        fgets(gender, sizeof(gender), stdin);
        strip_newline(gender);

        printf(" - Affiliation: ");
        fgets(affiliation, sizeof(affiliation), stdin);
        strip_newline(affiliation);

        printf(" - Title: ");
        fgets(title, sizeof(title), stdin);
        strip_newline(title);

        printf(" - Expertise: ");
        fgets(specialty, sizeof(specialty), stdin);
        strip_newline(specialty);

        printf(" - Email: ");
        fgets(email, sizeof(email), stdin);
        strip_newline(email);

        printf(" - Phone: ");
        fgets(phone, sizeof(phone), stdin);
        strip_newline(phone);

        // Compose the comma-separated data
        snprintf(judges_array[judge_count], MAX_LENGTH, "%s,%s,%s,%s,%s,%s,%s",
                 name, gender, affiliation, title, specialty, email, phone);

        // Check comma count
        int commas = 0;
        const char *p = judges_array[judge_count];
        while (*p) {
            if (*p == ',') commas++;
            p++;
        }

        if (commas != EXPECTED_FIELDS - 1) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        judge_count++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    printf("\"Should we check the judge information?\" (Y/N): ");
    char answer = getchar();
    if (answer != 'Y') {
        printf("Program terminated.\n");
        return 0;
    }

    printf("\n####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");

    for (int i = 0; i < total_judges; i++) {
        display_judge(judges_array[i], i);
    }

    return 0;
}
