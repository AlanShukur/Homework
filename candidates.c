#include <stdio.h>
#include <stdlib.h>

#define CANDIDATES 6

// Each candidate has 11 fields
#define FIELDS 11

char *member_info[CANDIDATES][FIELDS] = {
    {"Jiyeon Park", "20060415", "F", "jiyeon@outlook.com", "South Korea", "18.5", "Dance", "Composition", "0", "ENFJ", "A passionate and creative dancer and composer ready to pursue dreams together."},
    {"Ethan Smith", "20050822", "M", "ethan@outlook.com", "USA", "21.2", "Vocal", "Lyric Writing", "2", "ISTP", "A vocalist with a rich voice and songwriting skills, eager to share K-POP’s charm worldwide."},
    {"Suphanan Wong", "20040105", "F", "suphanan@outlook.com", "Thailand", "19.0", "Dance", "Lyric Writing", "4", "INFJ", "Aspiring to move hearts with dynamic dance and emotional lyrics, becoming part of the Hallyu wave from Thailand."},
    {"Helena Silva", "20070310", "F", "helena@outlook.com", "Brazil", "20.8", "Vocal", "Composition & Lyric Writing", "1", "ENFP", "A versatile singer from Brazil who wants to inspire through both music and lyrics."},
    {"Karolina Nowak", "20060918", "F", "karolina@outlook.com", "Poland", "17.9", "Dance", "Composition", "2", "ISFP", "A composer and dancer from Poland, eager to convey emotions through music."},
    {"Liam Wilson", "20061108", "M", "liam@outlook.com", "Australia", "20.1", "Dance", "Composition & Lyric Writing", "3", "ENTJ", "A passionate dancer and composer from Australia, determined to share his unique music through K-POP."}
};

int calculate_age(char dob[]) {
    int birth_year = (dob[0]-'0')*1000 + (dob[1]-'0')*100 + (dob[2]-'0')*10 + (dob[3]-'0');
    return 2025 - birth_year;
}

const char* topik_level(const char *level) {
    if (level[0] == '0') return "Native";
    return level;
}

int main(void)
{
    char group_name[100];
    int i;

    // Bonus Feature: Read group name using getchar
    printf("####################################\n");
    printf("    Audition Candidate Data Entry   \n");
    printf("####################################\n");
    printf("Enter audition group name: ");

    int index = 0;
    char ch;
    while ((ch = getchar()) != '\n' && index < 99) {
        group_name[index++] = ch;
    }
    group_name[index] = '\0';

    printf("\nWelcome to the %s Audition System!\n\n", group_name);

    // Print the results
    printf("####################################\n");
    printf("    Audition Candidate Data Review  \n");
    printf("####################################\n");
    printf("Group: %s\n", group_name);
    printf("==========================================================================================================\n");
    printf("Name            | Age | DOB      | Gender | Email                  | Nationality   | BMI  | Primary | Secondary               | TOPIK  | MBTI\n");
    printf("==========================================================================================================\n");

    for (i = 0; i < CANDIDATES; i++) {
        int age = calculate_age(member_info[i][1]);
        printf("%-15s | %-3d | %-8s | %-6s | %-22s | %-13s | %-4s | %-7s | %-22s | %-6s | %-4s\n",
               member_info[i][0], age, member_info[i][1], member_info[i][2],
               member_info[i][3], member_info[i][4], member_info[i][5],
               member_info[i][6], member_info[i][7], topik_level(member_info[i][8]),
               member_info[i][9]);

        printf("----------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", member_info[i][10]);
        printf("----------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
