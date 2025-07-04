#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 6
#define MAX_MENTORS 8
#define MAX_COUNSEL 6
#define MAX_RESPONSES 3
#define NAME_LEN 50
#define MAX_TEXT 1024

// === Data Structures ===
typedef struct {
    int id;
    char name[NAME_LEN];
    int menteeIndex;
} Mentor;

typedef struct {
    char nickname[NAME_LEN];
    int age;
    char trauma[MAX_TEXT];
} TraumaInfo;

typedef struct {
    int id;
    char question[MAX_TEXT];
} CounselingQuestion;

typedef struct {
    char nickname[NAME_LEN];
    char question[MAX_TEXT];
    char response[101];
    int answered;
} CounselingLog;

typedef struct {
    char keyword[NAME_LEN];
    char message[MAX_TEXT];
} ArthurTrauma;

// === Globals ===
const char *milliways_nicknames[MAX_TRAINEES] = {
    "Jiyeon", "Ethan", "Suphanan", "Helena", "Karolina", "Liam"
};

int trainees[MAX_TRAINEES][2]; // [ASCII sum, ability]
Mentor mentors[MAX_MENTORS];
int mentorCount = 0;

TraumaInfo traumaList[MAX_COUNSEL];
CounselingLog counselingLogs[MAX_COUNSEL][MAX_RESPONSES];
CounselingQuestion questionBank[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

ArthurTrauma arthur = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

// === Function Prototypes ===
int parseIntMember(const char *nickname);
int getRandomAbility();
void initTrainees();
void inputMentors();
void matchMentoring();
void printMatches();
void inputTrauma();
void startCounselingSession();
void viewCounselingResults();
void handleSelfManagementMenu();
void find_easter_egg();
int isRightChar(char userChar, char binaryChar);
int isEasterEgg(const char *input);

// === Main ===
int main(void) {
    printf("Welcome to Milliways Training System\n");
    handleSelfManagementMenu();
    return 0;
}

// === Menu ===
void handleSelfManagementMenu() {
    char option[50];
    while (1) {
        printf("\n[II. Training > 2. Self-Management and Teamwork]\n");
        printf("A. Mentoring\nB. Trauma Management\nEnter name or 0 to Quit\n> ");
        fgets(option, sizeof(option), stdin);
        option[strcspn(option, "\n")] = '\0';

        if (strcmp(option, "0") == 0) break;
        else if (strcmp(option, "A") == 0 || strcmp(option, "a") == 0) {
            initTrainees();
            inputMentors();
            matchMentoring();
            printMatches();
        } else if (strcmp(option, "B") == 0 || strcmp(option, "b") == 0) {
            char sub[10];
            while (1) {
                printf("\n[Trauma Management]\n1. Input Trauma\n2. Start Counseling\n3. View Results\n0. Back\n> ");
                fgets(sub, sizeof(sub), stdin);
                if (sub[0] == '0') break;
                else if (sub[0] == '1') inputTrauma();
                else if (sub[0] == '2') startCounselingSession();
                else if (sub[0] == '3') viewCounselingResults();
                else printf("Invalid choice.\n");
            }
        } else if (strcmp(option, "Arthur") == 0) {
            find_easter_egg();
        } else {
            printf("Invalid input.\n");
        }
    }
}

// === Trainee Functions ===
int parseIntMember(const char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++)
        sum += (int)nickname[i];
    return sum;
}

int getRandomAbility() {
    return (rand() % 901) + 100;
}

void initTrainees() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_TRAINEES; i++) {
        trainees[i][0] = parseIntMember(milliways_nicknames[i]);
        trainees[i][1] = getRandomAbility();
    }
}

void inputMentors() {
    char buffer[NAME_LEN];
    mentorCount = 0;
    printf("\nEnter up to %d mentor names:\n", MAX_MENTORS);
    for (int i = 0; i < MAX_MENTORS; i++) {
        printf("Mentor %d name (blank to stop): ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) break;
        mentors[i].id = i + 1;
        strncpy(mentors[i].name, buffer, NAME_LEN);
        mentors[i].menteeIndex = -1;
        mentorCount++;
    }
}

void matchMentoring() {
    int used[MAX_MENTORS] = {0};
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int index = trainees[i][0] % mentorCount;
        int attempts = 0;
        while (used[index] && attempts < mentorCount) {
            index = (index + 1) % mentorCount;
            attempts++;
        }
        if (attempts < mentorCount) {
            mentors[index].menteeIndex = i;
            used[index] = 1;
        }
    }
}

void printMatches() {
    printf("\n======= Mentoring Matches =======\n");
    for (int i = 0; i < mentorCount; i++) {
        if (mentors[i].menteeIndex != -1) {
            int t = mentors[i].menteeIndex;
            printf("Trainee #%d (%s | Ability: %d) -> Mentor #%d (%s)\n",
                   t + 1, milliways_nicknames[t], trainees[t][1],
                   mentors[i].id, mentors[i].name);
        } else {
            printf("Mentor #%d (%s) has no mentee.\n", mentors[i].id, mentors[i].name);
        }
    }
    printf("=================================\n");
}

// === Trauma & Counseling ===
void inputTrauma() {
    char name[NAME_LEN], desc[MAX_TEXT];
    while (1) {
        printf("Enter nickname (or '0' to return): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if (strcmp(name, "0") == 0) break;

        int found = -1;
        for (int i = 0; i < MAX_COUNSEL; i++)
            if (strcmp(name, milliways_nicknames[i]) == 0)
                found = i;

        found != -1
            ? (printf("Enter trauma for %s: ", name),
               fgets(desc, sizeof(desc), stdin),
               desc[strcspn(desc, "\n")] = '\0',
               strcpy(traumaList[found].nickname, name),
               traumaList[found].age = 18 + found,
               strcpy(traumaList[found].trauma, desc),
               printf("Trauma recorded for %s.\n", name))
            : printf("Nickname not found.\n");
    }
}

void startCounselingSession() {
    char name[NAME_LEN];
    printf("\nAvailable members for counseling:\n");
    for (int i = 0; i < MAX_COUNSEL; i++)
        if (strlen(traumaList[i].trauma) > 0)
            printf("- %s\n", traumaList[i].nickname);

    printf("Enter nickname (or '0' to cancel): ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strcmp(name, "0") == 0) return;

    int index = -1;
    for (int i = 0; i < MAX_COUNSEL; i++)
        if (strcmp(traumaList[i].nickname, name) == 0)
            index = i;

    if (index == -1) {
        printf("Nickname not found or no trauma recorded.\n");
        return;
    }

    srand((unsigned int)time(NULL));
    int used[5] = {0};
    int count = 0;

    while (count < MAX_RESPONSES) {
        int q = rand() % 5;
        if (used[q]) continue;
        used[q] = 1;

        if (counselingLogs[index][count].answered) {
            count++;
            continue;
        }

        printf("Q%d: %s\n> ", questionBank[q].id, questionBank[q].question);
        fgets(counselingLogs[index][count].response, 101, stdin);
        counselingLogs[index][count].response[strcspn(counselingLogs[index][count].response, "\n")] = '\0';

        if (strlen(counselingLogs[index][count].response) == 0 || strlen(counselingLogs[index][count].response) > 100) {
            printf("Invalid response. Try again.\n");
            continue;
        }

        strcpy(counselingLogs[index][count].nickname, name);
        strcpy(counselingLogs[index][count].question, questionBank[q].question);
        counselingLogs[index][count].answered = 1;
        count++;
    }

    printf("Counseling session completed for %s.\n", name);
}

void viewCounselingResults() {
    char name[NAME_LEN];
    printf("\nCompleted sessions:\n");
    for (int i = 0; i < MAX_COUNSEL; i++)
        if (counselingLogs[i][0].answered)
            printf("- %s\n", counselingLogs[i][0].nickname);

    printf("Enter nickname to view results: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int index = -1;
    for (int i = 0; i < MAX_COUNSEL; i++)
        if (strcmp(traumaList[i].nickname, name) == 0)
            index = i;

    if (index == -1) {
        printf("Nickname not found.\n");
        return;
    }

    printf("\nNickname: %s\nAge: %d\nTrauma: %s\n",
           traumaList[index].nickname,
           traumaList[index].age,
           traumaList[index].trauma);

    for (int j = 0; j < MAX_RESPONSES; j++) {
        if (counselingLogs[index][j].answered) {
            printf("Q: %s\nA: %s\n", counselingLogs[index][j].question, counselingLogs[index][j].response);
        }
    }
}

// === Easter Egg ===
void find_easter_egg() {
    printf("\n<<Arthur's Easter Egg>>\n");
    int len = strlen(arthur.keyword);
    char reversed[NAME_LEN];
    char input[NAME_LEN];
    for (int i = 0; i < len; i++) {
        unsigned char c = arthur.keyword[len - 1 - i];
        reversed[i] = c;
        printf("Char %d binary: ", i + 1);
        for (int j = 7; j >= 0; j--)
            printf("%d", (c >> j) & 1);
        printf("\n");
    }

    printf("Enter the characters from above in order: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (isEasterEgg(input)) {
        printf("##Easter Egg Discovered!$$\n%s\n", arthur.message);
    } else {
        printf("Incorrect. Returning to menu.\n");
    }
}

int isRightChar(char userChar, char binaryChar) {
    return (int)userChar == (int)binaryChar;
}

int isEasterEgg(const char *input) {
    return strcmp(input, arthur.keyword) == 0;
}
