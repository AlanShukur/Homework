#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 6
#define MAX_MENTORS 8
#define NAME_LEN 50

// Trainee data [nickname ASCII sum, ability]
int trainees[MAX_TRAINEES][2];

// Milliways members
const char *milliways_nicknames[MAX_TRAINEES] = {
    "Jiyeon", "Ethan", "Suphanan", "Helena", "Karolina", "Liam"
};

// Mentor struct
typedef struct {
    int id;
    char name[NAME_LEN];
    int menteeIndex;  // index into trainees[]
} Mentor;

Mentor mentors[MAX_MENTORS];
int mentorCount = 0;

// === Function Prototypes ===
int parseIntMember(const char *nickname);
int getRandomAbility();
void initTrainees();
void inputMentors();
void matchMentoring();
void printMatches();

// === Main Menu Handler (sample menu entry point) ===
void handleSelfManagementMenu() {
    char option[10];
    while (1) {
        printf("\n[Self-Management and Teamwork]\n");
        printf("A. Mentoring\n0. Back\nSelect option: ");
        fgets(option, sizeof(option), stdin);

        if (option[0] == '0') break;
        if (option[0] == 'A') {
            initTrainees();
            inputMentors();
            matchMentoring();
            printMatches();
        } else {
            printf("Invalid option.\n");
        }
    }
}

// === Convert nickname to ASCII sum ===
int parseIntMember(const char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

// === Generate random ability score ===
int getRandomAbility() {
    return (rand() % 901) + 100;  // 100–1000
}

// === Initialize trainees' ASCII sum + random ability ===
void initTrainees() {
    srand(time(NULL));
    for (int i = 0; i < MAX_TRAINEES; i++) {
        trainees[i][0] = parseIntMember(milliways_nicknames[i]);  
        trainees[i][1] = getRandomAbility();                       
    }
}

// === Input mentors ===
void inputMentors() {
    char buffer[NAME_LEN];
    printf("\nEnter up to %d mentor names:\n", MAX_MENTORS);
    for (int i = 0; i < MAX_MENTORS; i++) {
        printf("Mentor %d name (leave blank to stop): ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) break;

        mentors[i].id = i + 1;
        strncpy(mentors[i].name, buffer, NAME_LEN);
        mentors[i].menteeIndex = -1;  // Not yet matched
        mentorCount++;
    }
}

// === Match each trainee to a mentor (1:1 if possible) ===
void matchMentoring() {
    int used[MAX_MENTORS] = {0};  // Prevent double assignment

    for (int i = 0; i < MAX_TRAINEES; i++) {
        int ascii_sum = trainees[i][0];
        int index = ascii_sum % mentorCount;

        
        int tries = 0;
        while (used[index] && tries < mentorCount) {
            index = (index + 1) % mentorCount;
            tries++;
        }

        if (tries == mentorCount) {
            printf("Error: Could not match trainee %d due to mentor overflow.\n", i);
            continue;
        }

        mentors[index].menteeIndex = i;
        used[index] = 1;
    }
}

// === Output matching results ===
void printMatches() {
    printf("\n======= Mentoring Matches =======\n");
    for (int i = 0; i < mentorCount; i++) {
        if (mentors[i].menteeIndex != -1) {
            int t = mentors[i].menteeIndex;
            printf("Trainee #%d (%s)  ->  Mentor #%d (%s)\n",
                   t + 1, milliways_nicknames[t], mentors[i].id, mentors[i].name);
        } else {
            printf("Mentor #%d (%s) has no mentee assigned.\n", mentors[i].id, mentors[i].name);
        }
    }
    printf("=================================\n");
}

int main() {
    handleSelfManagementMenu();
    return 0;
}
