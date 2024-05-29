#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the Skill struct
typedef struct {
    char name[50];
    char description[200];
    int type; // 0: temporary modifier, 1: direct attack
    int duration; // duration in turns (if temporary)
    int atk_modifier;
    int def_modifier;
    int hp_modifier; // Add HP modifier
    int uses_left; // uses left for the skill
} Skill;

// Define the Character struct
typedef struct {
    char name[50];
    int hp;
    int atk;
    int def;
    Skill characteristic_attack;
    Skill skills[4];
    Skill move_history[50]; // Stack to store move history
    int history_size; // Current size of the move history stack
    int time_strike_used; // To check if "Time Strike" has been used
} Character;


// Define the Enemy struct
typedef struct {
    char name[50];
    int hp;
    int atk;
    int def;
    Skill skills[4];
} Enemy;

// Define the Option struct
typedef struct {
    char response[200];
    char narrative_before[500];
    char narrative_after[500];
    Enemy enemies[3];
} Option;

// Define the Decision struct
typedef struct {
    char question[200];
    Option options[2];
} Decision;

// Define the Scenario struct
typedef struct {
    char name[50];
    char description[1000];
    Decision decision;
} Scenario;

// Define the Node struct
typedef struct Node {
    Decision decision;
    struct Node* next;
} Node;

// Define the Queue struct
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Define a structure to represent a move
typedef struct {
    int skillIndex; // -1 for characteristic attack, 0-3 for other skills
    int atk_modifier;
} Move;

// Define the Stack structure
typedef struct StackNode {
    Move move;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;
}

// Check if the stack is empty
int isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Push a move onto the stack
void push(Stack* stack, Move move) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->move = move;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop a move from the stack
Move pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    StackNode* temp = stack->top;
    Move move = temp->move;
    stack->top = stack->top->next;
    free(temp);
    return move;
}

// Peek a move from the stack without removing it
Move peek(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->top->move;
}

Skill skillList[10];
Character characterList[3];
Scenario scenarios[5];

// Queue functions
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, Decision decision) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->decision = decision;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
}

Decision dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        exit(1);
    }
    Node* temp = q->front;
    Decision decision = temp->decision;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return decision;
}


// Initialize skills, characters, and scenarios
void initializeSkills() {
    Skill tempSkills[] = {
        // 4 skills that increase damage
        {"Power Kick (atk)", "A powerful kick that deals extra damage. (ATK +20) (Uses: 3)", 1, 0, 20, 0, 0, 3},
        {"Curve Shot (atk)", "A precise shot that bends, difficult for the opponent to dodge. (ATK +15) (Uses: 5)", 1, 0, 15, 0, 0, 5},
        {"Captain's Spirit (atk)", "A shot that has a high chance of scoring critical damage. (ATK +25) (Uses: 3)", 1, 0, 25, 0, 0, 3},
        {"Furious Strike (atk)", "A relentless strike that boosts damage significantly. (ATK +30) (Uses: 2)", 1, 0, 30, 0, 0, 2},

        // 3 skills that increase HP
        {"Healing Pass (hp)", "Restores a significant amount of stamina. (HP +20) (Uses: 3)", 0, 0, 0, 0, 20, 3},
        {"Stamina Boost (hp)", "Increases the player's stamina, restoring some HP. (HP +10) (Uses: 5)", 0, 0, 0, 0, 10, 5},
        {"Medical Assistance (hp)", "You call for quick medical assistance and boost your HP. (HP +30) (Uses: 2)", 0, 0, 0, 0, 30, 2},

        // 3 skills that increase defense
        {"Defensive Wall (def)", "Raises defense significantly for the next attack. (DEF +10 for 3 turn) (Uses: 1)", 0, 3, 0, 10, 0, 1},
        {"Power Tackle (def)", "A strong tackle that boosts defense for a few turns. (DEF +7 for 3 turns) (Uses: 2)", 0, 3, 0, 7, 0, 2},
        {"Iron Defense (def)", "Temporarily makes the defense as tough as iron, increasing defense. (DEF +5 for 3 turns) (Uses: 3)", 0, 3, 0, 5, 0, 3}
    };

    for (int i = 0; i < 10; i++) {
        skillList[i] = tempSkills[i];
    }
}




void initializeCharacters() {
    Character tempCharacters[] = {
        {"Messi", 125, 30, 5, {"Left Strike", "His great shooting habilities allows him to attack agresively to his opponent", 1, 0, 0, 0, 0, -1}, {}},
        {"Rakitic", 150, 20, 8, {"Technichal tackle", "His high IQ allows him to dominate all parts of the field.", 1, 0, 0, 0, 0, -1}, {}},
        {"Pique", 200, 15, 12, {"Amazing Header", "A quick and precise head hit that deals damage to the opponent, but his strong point is his strenght.", 1, 0, 0, 0, 0, -1}, {}}
    };

    for (int i = 0; i < 3; i++) {
        characterList[i] = tempCharacters[i];
    }
}

Character chooseCharacter() {
    int choice;
    printf("Choose your character:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (HP: %d, Attack: %d, Defense: %d)\n", i + 1, characterList[i].name, characterList[i].hp, characterList[i].atk, characterList[i].def);
    }
    scanf("%d", &choice);

    Character selectedCharacter = characterList[choice - 1];

    printf("You chose: %s\n", selectedCharacter.name);
    printf("HP: %d\n", selectedCharacter.hp);
    printf("Attack: %d\n", selectedCharacter.atk);
    printf("Defense: %d\n", selectedCharacter.def);
    printf("Characteristic Attack: %s - %s\n", selectedCharacter.characteristic_attack.name, selectedCharacter.characteristic_attack.description);

    return selectedCharacter;
}

void chooseSkills(Character* character) {
    int choice;
    int chosenSkills[4] = {-1, -1, -1, -1}; // Array to store chosen skill indices
    printf("Choose 4 skills from the following list:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d. %s: %s\n", i + 1, skillList[i].name, skillList[i].description);
    }

    for (int i = 0; i < 4; i++) {
        int valid = 0;
        while (!valid) {
            printf("Select skill %d: ", i + 1);
            scanf("%d", &choice);
            choice--; // Adjust for 0-based indexing
            if (choice >= 0 && choice < 10) {
                int alreadyChosen = 0;
                for (int j = 0; j < i; j++) {
                    if (chosenSkills[j] == choice) {
                        alreadyChosen = 1;
                        break;
                    }
                }
                if (!alreadyChosen) {
                    character->skills[i] = skillList[choice];
                    chosenSkills[i] = choice;
                    valid = 1;
                } else {
                    printf("You have already chosen this skill. Please select a different skill.\n");
                }
            } else {
                printf("Invalid choice. Please select a number between 1 and 10.\n");
            }
        }
    }

    printf("\033[34m");
    printf("Selected skills:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: %s (Uses left: %d)\n", character->skills[i].name, character->skills[i].description, character->skills[i].uses_left);
    }
    printf("\033[0m");
}

void setupScenarios() {
    Scenario tempScenarios[] = {
        {
            "London",
            "You arrive to England to face Manchester City. The air is thick with tension while you arrive to the Big Ben.",
            {
                "Do you climb to the top or stay at the base of the tower?",
                {
                    {"Climb to the top", "When you reach the top, someone is already waiting for you", "No one can stop you...",
                        {{"El Kun Aguero", 80, 14, 4, {{"Boot Smash", "A powerful hit with his boot.", 1, 0, 10, 0, 0, -1}}}}}, // Weakened enemy
                    {"Stay at the base", "After some time waiting, someone finally appears...", "Next challenge...",
                        {{"The Guardian Kompany", 90, 15, 5, {{"Smashing Header", "Kompany hits you with his enormous head.", 1, 0, 15, 0, 0, -1}}}}}
                }
            }
        },
        {
            "Paris",
            "Your next challenge is PSG, this powerful team is hidden somewhere by the Eiffel Tower.",
            {
                "Do you go to the top or explore the surrounding grounds?",
                {
                    {"Go to the top", "After deciding to see the views of Paris, someone comes flying in...", "Easy...",
                        {{"Ninja Ibrahimovic", 90, 15, 7, {{"Acrobatic kick", "A damaging hit with a lot of technique.", 1, 0, 20, 0, 0, -1}}}}}, // Weakened enemy
                    {"Explore the surrounding", "When you least expect it, two big shapes appear from the dark...", "Bring them on...",
                        {{"The Soldiers Marquinhos and Thiago Silva", 100, 16, 8, {{"Combined Attack", "Together they deal a lot of damage.", 1, 0, 18, 0, 0, -1}}}}}
                }
            }
        },
        {
            "Berlin",
            "They are waiting for you in Germany, the historic Bayern Munchen are around the Berlin wall looking for you.",
            {
                "Do you investigate the West or East side of the wall?",
                {
                    {"West Side", "While wandering by the West side of the wall someone hits you from the back...", "Closer to the victory...",
                        {{"The Monster Boateng", 95, 17, 9, {{"Monster Stomp Earthquake", "With his crazy strength, he stomps on the ground creating an earthquake.", 1, 0, 12, 0, 0, -1}}}}}, // Weakened enemy
                    {"East side", "You hear laughters from far away and when you go after them...", "Another victory...",
                        {{"Ribbery and Robben Spys", 70, 15, 7, {{"Agile Dagger Strike", "With their agility, these two quickly attack you with their daggers .", 1, 0, 15, 0, 0, -1}}}}}
                }
            }
        },
        {
            "Rome",
            "The final challenge has arrived, you enter the Coliseum and thousands of people are screaming...In the middle of the battle ground is Buffon, waiting for you",
            {
                "He tells you: 'I will not let you win'. What do you wish to respond?",
                {
                    {"'May the best win'", "You are face to face with one of the most skilled warriors of all time...", "I am ready for the final step...",
                        {{"Pogba the Warrior", 80, 16, 8, {{"Elegant hit", "An elegant attack that deals lot of damage.", 1, 0, 14, 0, 0, -1}}}}}, // Weakened enemy
                    {"'This will be a piece of cake'", "Your arrogancy makes you meet the power of magic...", "I believe in myself...",
                        {{"The Magician Pirlo", 90, 18, 8, {{"Magic Potion", "This potion weakens your health by a lot.", 1, 0, 17, 0, 0, -1}}}}}

                }
            }
        },
        {
            "Final Boss",
            "After defeating his warriors, the Wise Gianluigi Buffon is your last enemy to beat and therefore be crowned Champion",
            {
                "He asks you if you are scared of him, what do you wish to say to him?",
                {
                    {"'I am ready for you", "He respects your answer but will show no mercy for you...", "Finally....",
                        {{"The Wise Gianluigi Buffon", 80, 10, 8, {{"Golden glove", "This deadly strike with his glove will cause great damage to you.", 1, 0, 14, 0, 0, -1}}}}}, // Weakened enemy
                    {"'I will retire you'", "This answer enfuriates him...", "I never doubted myself...",
                        {{"The Wise Gianluigi Buffon", 100, 20, 9, {{"Golden Glove", "This deadly strike with his glove is an even more powerful attack due to his rage against you.", 1, 0, 18, 0, 0, -1}}}}} // Weakened enemy

                }
            }
        }
    };

    for (int i = 0; i < 5; i++) { 
        scenarios[i] = tempScenarios[i];
    }
}

// Define scenario names
const char* scenario_names[] = {"London", "Paris", "Berlin", "Rome", "Final Boss"};

// Define an array of integers to track visited scenarios
int visited[5] = {0, 0, 0, 0, 0};

// Graph of scenarios: each row represents a scenario and each column indicates the connections
int scenario_graph[5][5] = {
    // London, Paris, Berlin, Rome, Final Boss
    {0, 1, 1, 0, 0}, // London
    {1, 0, 1, 0, 0}, // Paris
    {1, 1, 0, 0, 0}, // Berlin
    {0, 0, 0, 0, 1}, // Rome (must go to Final Boss)
    {0, 0, 0, 1, 0}  // Final Boss
};

void initializeStack(Stack* s) {
    s->top = NULL;
}

// Modified combat function
void combat(Character* player, Enemy* enemy) {
    srand(time(NULL));
    printf("\n--- Combat Start! ---\n");
    printf("%s vs %s\n", player->name, enemy->name);

    int temp_def = 0; // Temporary defense boost
    int def_duration = 0; // Duration of the temporary defense boost
    int turn_count = 1; // Initialize turn count
    Stack move_stack;
    initializeStack(&move_stack);

    while (player->hp > 0 && enemy->hp > 0) {
        printf("\n--- Turn %d ---\n", turn_count); // Display turn count

        int player_choice;
        printf("\033[34m");
        printf("\nYour turn! Choose an action:\n");
        printf("1. %s (Characteristic Attack)\n", player->characteristic_attack.name);
        for (int i = 0; i < 4; i++) {
            printf("%d. %s (Uses left: %d)\n", i + 2, player->skills[i].name, player->skills[i].uses_left);
        }
        if (!player->time_strike_used) {
            printf("6. Time Strike (Special Move that duplicates the damage of the last attack)\n");
        }
        scanf("%d", &player_choice);

        int player_damage = 0;
        if (player_choice == 1) {
            player_damage = player->atk + player->characteristic_attack.atk_modifier - enemy->def;
            printf("\033[0;32m");
            printf("You used %s!\n", player->characteristic_attack.name);
            player->move_history[player->history_size++] = player->characteristic_attack; // Store move in history

            // Push the move onto the stack
            Move move = { .skillIndex = -1, .atk_modifier = player->characteristic_attack.atk_modifier };
            push(&move_stack, move);

        } else if (player_choice == 6 && !player->time_strike_used) {
            if (!isStackEmpty(&move_stack)) {
                Move last_move = pop(&move_stack); // Get the last move
                player_damage = 2 * (player->atk + last_move.atk_modifier - enemy->def); // Double the power
                printf("\033[0;32m");
                printf("You used Time Strike (Double Power)!\n");
                player->time_strike_used = 1; // Mark "Time Strike" as used
            } else {
                printf("No moves in history to execute Time Strike.\n");
                continue;
            }
        } else {
            Skill* chosen_skill = &player->skills[player_choice - 2];
            if (chosen_skill->uses_left > 0) {
                if (chosen_skill->type == 0 && chosen_skill->def_modifier > 0) { // Defense skill
                    temp_def = chosen_skill->def_modifier;
                    def_duration = chosen_skill->duration;
                    printf("\033[0;32m");
                    printf("You used %s and increased your defense by %d for %d turns!\n", chosen_skill->name, chosen_skill->def_modifier, chosen_skill->duration);
                } else if (chosen_skill->hp_modifier > 0) { // Healing skill
                    player->hp += chosen_skill->hp_modifier;
                    printf("\033[0;32m");
                    printf("You used %s and healed %d HP!\n", chosen_skill->name, chosen_skill->hp_modifier);
                } else { // Attack skill
                    player_damage = player->atk + chosen_skill->atk_modifier - enemy->def;
                    printf("\033[0;32m");
                    printf("You used %s!\n", chosen_skill->name);
                    player->move_history[player->history_size++] = *chosen_skill; // Store move in history

                    // Push the move onto the stack
                    Move move = { .skillIndex = player_choice - 2, .atk_modifier = chosen_skill->atk_modifier };
                    push(&move_stack, move);
                }
                chosen_skill->uses_left--;
            } else {
                printf("You can't use that skill anymore!\n");
                continue;
            }
        }

        if (player_damage > 0) {
            enemy->hp -= player_damage;
            printf("You dealt %d damage to %s.\n", player_damage, enemy->name);
        } else {
            printf("Your attack was too weak to cause any damage.\n");
        }

        if (enemy->hp <= 0) {
            printf("%s is defeated!\n", enemy->name);
            break;
        }

        printf("\033[0;31m");
        printf("\nEnemy's turn!\n");

        int enemy_choice = rand() % 5;
        int enemy_damage = 0;
        Skill* enemy_skill;
        if (enemy_choice == 0) {
            enemy_damage = enemy->atk + enemy->skills[0].atk_modifier - (player->def + temp_def);
            enemy_skill = &enemy->skills[0];
        } else {
            enemy_skill = &enemy->skills[enemy_choice];
            enemy_damage = enemy->atk + enemy_skill->atk_modifier - (player->def + temp_def);
        }

        printf("%s attacked you!\n", enemy->name);

        if (enemy_damage > 0) {
            player->hp -= enemy_damage;
            printf("%s dealt %d damage to you.\n", enemy->name, enemy_damage);
        } else {
            printf("%s's attack was too weak to cause any damage.\n", enemy->name);
        }

        if (player->hp <= 0) {
            printf("You are defeated!\n");
            break;
        }

        if (def_duration > 0) {
            def_duration--;
            if (def_duration == 0) {
                temp_def = 0;
                printf("Your defense boost has worn off.\n");
            }
        }

        printf("\033[0m");
        printf("\n%s HP: %d\n", player->name, player->hp);
        printf("%s HP: %d\n", enemy->name, enemy->hp);

        turn_count++; // Increment turn count
    }
}


// Menu function
void showMenu() {
    int choice;
    printf("\033[0m");
    printf("Welcome to the The Champions League Battle!\n");
    printf("This is a role play game, that means that every desicion that you make during the game will influence to the difficulty of the game.\n");
    printf("In this game it is about winning the 2015 Champions League with FC Barcelona, to do this you will have to defeat all the rivals that get in your way.\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            playGame();
            break;
        case 2:
            printf("Thank you for playing! Goodbye.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please select again.\n");
            showMenu();
            break;
    }
}

// Play game function
void playGame() {
    initializeSkills();
    initializeCharacters();
    setupScenarios();

    Character player = chooseCharacter();
    chooseSkills(&player);

    int currentScenarioIndex = -1;  // -1 means no scenario chosen yet
    int visitedCount = 0;

    // First scenario selection
    printf("Choose your first scenario:\n");
    printf("1. London\n2. Paris\n3. Berlin\n");
    int initialChoice;
    scanf("%d", &initialChoice);
    currentScenarioIndex = initialChoice - 1;
    visited[currentScenarioIndex] = 1;
    visitedCount++;

    while (currentScenarioIndex != 4) { // 4 is Final Boss index
        Scenario currentScenario = scenarios[currentScenarioIndex];
        Decision currentDecision = currentScenario.decision;

        printf("\033[0m");
        printf("\n--- Scenario: %s ---\n", currentScenario.name);
        printf("%s\n", currentScenario.description);

        printf("\n%s\n", currentDecision.question);
        printf("1. %s\n", currentDecision.options[0].response);
        printf("2. %s\n", currentDecision.options[1].response);

        int choice;
        scanf("%d", &choice);
        Option selectedOption = currentDecision.options[choice - 1];

        printf("%s\n", selectedOption.narrative_before);
        combat(&player, &selectedOption.enemies[0]);
        printf("%s\n", selectedOption.narrative_after);

        if (player.hp <= 0) {
            printf("Game Over. You have been defeated.\n");
            break;
        }

        // Check if we need to transition to Rome or Final Boss
        if (visitedCount == 3) { // If all three initial scenarios are visited
            currentScenarioIndex = 3; // Transition to Rome
            visited[currentScenarioIndex] = 1;
            visitedCount++;
        } else if (currentScenarioIndex == 3) { // If already in Rome
            currentScenarioIndex = 4; // Transition to Final Boss
        } else {
            // Select next scenario
            printf("\033[0m");
            printf("Choose your next scenario:\n");
            for (int i = 0; i < 4; i++) {
                if (!visited[i] && scenario_graph[currentScenarioIndex][i]) {
                    printf("%d. %s\n", i + 1, scenario_names[i]);
                }
            }
            
            int nextScenarioChoice;
            while (1) {
                scanf("%d", &nextScenarioChoice);
                nextScenarioChoice--;  // Adjust for 0-based index
                
                // Check if the choice is valid
                if (nextScenarioChoice >= 0 && nextScenarioChoice < 4 && !visited[nextScenarioChoice] && scenario_graph[currentScenarioIndex][nextScenarioChoice]) {
                    break; // Valid choice, exit the loop
                } else {
                    printf("Invalid choice. Please choose a valid scenario:\n");
                    for (int i = 0; i < 4; i++) {
                        if (!visited[i] && scenario_graph[currentScenarioIndex][i]) {
                            printf("%d. %s\n", i + 1, scenario_names[i]);
                        }
                    }
                }
            }

            currentScenarioIndex = nextScenarioChoice;
            visited[currentScenarioIndex] = 1;
            visitedCount++;
        }
    }

    if (player.hp > 0 && currentScenarioIndex == 4) {
        // Final Boss encounter
        Scenario finalBossScenario = scenarios[4];
        Decision finalDecision = finalBossScenario.decision;

        printf("\033[0m");
        printf("\n--- Final Boss: %s ---\n", finalBossScenario.name);
        printf("%s\n", finalBossScenario.description);

        printf("\n%s\n", finalDecision.question);
        printf("1. %s\n", finalDecision.options[0].response);
        printf("2. %s\n", finalDecision.options[1].response);

        int choice;
        scanf("%d", &choice);
        Option selectedOption = finalDecision.options[choice - 1];

        printf("%s\n", selectedOption.narrative_before);
        combat(&player, &selectedOption.enemies[0]);
        printf("%s\n", selectedOption.narrative_after);

        if (player.hp > 0) {
            printf("Congratulations! You have defeated the final boss and won the game!\n");
        } else {
            printf("Game Over. You have been defeated by the final boss.\n");
        }
    }
}

int main() {
    showMenu();
    return 0;
}