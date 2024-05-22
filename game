#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SKILLS 4
#define MAX_OPTIONS 2
#define MAX_ENEMIES 4
#define MAX_SCENARIOS 4

// Define structs
typedef struct {
    char name[50];
    char description[100];
    int type; // 0 for direct attack, 1 for temporary modifier
    int duration; // Duration in turns (if temporary)
    int atk_modifier;
    int def_modifier;
    int hp_modifier;
} Skill;

typedef struct {
    char name[20];
    int hp;
    int atk;
    int def;
    Skill skills[MAX_SKILLS];
} Character;

typedef struct {
    char name[20];
    char description[300];
} Scenario;

typedef struct {
    char name[20];
    int hp;
    int atk;
    int def;
} Enemy;

typedef struct {
    char question[100];
    char options[MAX_OPTIONS][50];
    int num_options;
} Decision;

typedef struct {
    char response[50];
    char narrative_before[200];
    Enemy enemies[MAX_ENEMIES];
    char narrative_after[200];
} Option;


// Define scenarios, decisions, enemies, and options
Scenario scenarios[MAX_SCENARIOS] = {
    {"London", "FC Barcelona's journey to the Champions League begins in London, where Messi, Dani Alves, or Rakitic (player's choice) will face a 1 vs 1 combat against Manchester City to proceed to the next round."},
    {"Paris", "FC Barcelona travel to Paris, specifically to the Eiffel Tower, where they face the mighty Paris Saint-Germain. Represented by Ibrahimovic, Marquinhos, and Thiago Silva."},
    {"Berlin", "The next challenge awaits at the Berlin Wall, where Barcelona faces off against Bayern Munich. Represented by Boateng, Ribery, and Robben."},
    {"Rome", "Final battle at the Roman Coliseum. The final challenge has arrived after overcoming all previous battles, Barcelona now faces off against Juventus, the glorious Italian team."}
};

Decision decisions[MAX_SCENARIOS] = {
    {"Choose the location of the combat:", {"Big Ben", "Buckingham Palace"}, 2},
    {"Choose your action at the Eiffel Tower:", {"Climb the Eiffel Tower", "Stay at the base of the tower"}, 2},
    {"Choose your side of the Berlin Wall:", {"East side", "West side"}, 2},
    {"Choose your response to Buffon:", {"May the best win", "I will crush you"}, 2}
};

Enemy enemies[MAX_SCENARIOS][MAX_ENEMIES] = {
    {{"Kompany", 750, 25, 75}, {"Aguero", 500, 50, 25}, {""}}, // Add more enemies as needed
    {{"Ibrahimovic", 750, 75, 25}, {"Marquinhos", 1000, 25, 75}, {"Thiago Silva", 1000, 25, 75}, {""}},
    {{"Boateng", 1500, 25, 75}, {"Robben", 500, 75, 50}, {"Ribery", 500, 75, 50}, {""}},
    {{"Bonucci", 1500, 35, 90}, {"Pogba", 800, 50, 50}, {"Pirlo", 800, 50, 50}, {"Buffon", 1500, 25, 75}, {""}}
};

Option options[MAX_SCENARIOS][MAX_OPTIONS] = {
    {{"Big Ben chosen", "The combat takes place atop the Big Ben.", "Barcelona wins and proceeds to the next round."},
     {"Buckingham Palace chosen", "The combat takes place at the Buckingham Palace.", "Barcelona wins and proceeds to the next round."}},
    {{"Climb the Eiffel Tower", "Barcelona climbs the Eiffel Tower for the combat.", "Barcelona wins and proceeds to the next round."},
     {"Stay at the base of the tower", "Barcelona decides to stay at the base of the Eiffel Tower.", "Barcelona wins and proceeds to the next round."}},
    {{"East side chosen", "Barcelona chooses to battle on the east side of the Berlin Wall.", "Barcelona wins and proceeds to the next round."},
     {"West side chosen", "Barcelona chooses to battle on the west side of the Berlin Wall.", "Barcelona wins and proceeds to the next round."}},
    {{"May the best win", "Barcelona responds: May the best win.", "Barcelona wins and proceeds to the next round."},
     {"I will crush you", "Barcelona responds: I will crush you.", "Barcelona wins and proceeds to the next round."}}
};

// Define skills for each character
Skill skills[MAX_SKILLS] = {
    {"Armor", "You receive only 25 per cent of damage in the next 10 turns.", 1, 10, 0, 1.25, 0},
    {"Super Agility", "For the next 10 turns you have 25 per cent chance of dodging your opponent's attack and receive 0 damage", 1, 10, 0, 0, 0},
    {"Bandage", "+500 HP for your character", 0, 0, 0, 0, +500},
    {"Mega Attack", "Your attack will be 50 per cent more powerful", 0, 0, 1.5, 0, 0},
    {"Mirror", "Your opponent's next attack will bounce on your shield and hurt them.", 1, 1, 0, 0, 0}
};

// Define skills for Messi
Skill messi_skills[MAX_SKILLS] = {
    {"Dribble", "Increase ATK by 20% for the next 5 turns.", 1, 5, 20, 0, 0},
    {"Precision Shot", "Deal 150% damage to enemy HP.", 0, 0, 0, 1.5, 0},
    // Add more skills for Messi as needed
};

// Define skills for Dani Alves
Skill dani_alves_skills[MAX_SKILLS] = {
    {"Quick Reflexes", "Have a 30% chance to dodge enemy attacks for the next 5 turns.", 1, 5, 0, 0, 0},
    {"Defensive Stance", "Increase DEF by 30% for the next 5 turns.", 1, 5, 0, 0, 1.3},
    // Add more skills for Dani Alves as needed
};

// Define skills for Rakitic
Skill rakitic_skills[MAX_SKILLS] = {
    {"Midfield Control", "Regenerate 10% of HP for the next 5 turns.", 1, 5, 0, 0, 0.1},
    {"Strategic Pass", "Increase ATK of all allies by 10% for the next 5 turns.", 1, 5, 10, 0, 0},
    // Add more skills for Rakitic as needed
};









//Esto ni idea de com va
int main() {

    main_menu();

    // Print out initialized structs for each scenario
    for (int i = 0; i < 3; ++i) {
        printf("Scenario %d: %s\n", i + 1, scenarios[i].description);
        printf("Decision: %s\n", decisions[i].question);
        for (int j = 0; j < decisions[i].num_options; ++j) {
            printf("  Option %d: %s\n", j + 1, decisions[i].options[j]);
            printf("    Description: %s\n", options[i][j].narrative_before);
            printf("    Outcome: %s\n", options[i][j].narrative_after);
        }
        printf("\n");
    }
    return 0;
}
;

