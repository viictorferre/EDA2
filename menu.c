#include "game.c"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "main.h" // Include the header file containing the structs

void main_menu() {
    printf("Welcome to the Game!\n");
    printf("1. Start New Game\n");
    printf("2. Configure Character\n");
    printf("3. Test Skill Selection\n");
    printf("4. Exit\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            start_new_game();
            break;
        case 2:
            configure_character();
            break;
        case 3:
            test_skill_selection();
            break;
        case 4:
            printf("Exiting the game...\n");
            return;
        default:
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
    }

    // After each action, return to the main menu
    main_menu();
}

void start_game(Character player, Enemy enemy) {
    printf("Starting combat...\n");
    
    // Main combat loop
    while (player.hp > 0 && enemy.hp > 0) {
        // Player's turn
        player_turn(&player, &enemy);

        // Check if enemy is defeated
        if (enemy.hp <= 0) {
            printf("Congratulations! You defeated the enemy.\n");
            break;
        }

        // CPU's turn
        cpu_turn(&player, &enemy);

        // Check if player is defeated
        if (player.hp <= 0) {
            printf("Game over! You were defeated by the enemy.\n");
            break;
        }
    }

    printf("Combat ended.\n");
}
void player_turn(Character *player, Enemy *enemy) {
    printf("\nPlayer's Turn\n");
    display_skills(*player);
    
    int choice;
    printf("Enter the number of the skill you want to use: ");
    scanf("%d", &choice);
    
    // Check if the choice is valid
    if (choice >= 1 && choice <= MAX_SKILLS) {
        // Apply the selected skill
        apply_skill(player, player->skills[choice - 1]);
        
        // Display updated player stats after applying the skill
        printf("\nPlayer Stats after using the skill:\n");
        printf("HP: %d\n", player->hp);
        printf("ATK: %d\n", player->atk);
        printf("DEF: %d\n", player->def);
    } else {
        printf("Invalid skill choice.\n");
    }
}



void cpu_turn(Character *player, Enemy *enemy) {
    printf("\nCPU's Turn\n");
    
    // Seed the random number generator with current time
    srand(time(NULL));
    
    // Choose a random skill index for the enemy
    int random_skill_index = rand() % MAX_SKILLS;
    
    // Apply the randomly chosen skill to the player
    apply_skill(player, enemy->skills[random_skill_index]);
    
    // Display updated player stats after applying the enemy skill
    printf("\nPlayer Stats after CPU's turn:\n");
    printf("HP: %d\n", player->hp);
    printf("ATK: %d\n", player->atk);
    printf("DEF: %d\n", player->def);
}


void apply_skill(Character *character, Skill skill) {
    // Apply the effects of the skill to the character
    if (skill.type == 0) { // Direct modifier
        character->atk += skill.atk_modifier;
        character->def += skill.def_modifier;
        character->hp += skill.hp_modifier;
    } else if (skill.type == 1) { // Temporary modifier
        printf("Applying temporary modifier: %s\n", skill.name);
        printf("Description: %s\n", skill.description);
        printf("Duration: %d turns\n", skill.duration);
    }
}

void display_skills(Character player) {
    printf("Available Skills:\n");
    for (int i = 0; i < MAX_SKILLS; i++) {
        printf("%d. %s - %s\n", i + 1, player.skills[i].name, player.skills[i].description);
    }
}

void configure_character() {
    // Display character options for the player to choose from
    printf("Choose Your Character:\n");
    printf("1. Messi\n");
    printf("2. Dani Alves\n");
    printf("3. Rakitic\n");

    int choice;
    printf("Enter the number of the character you want to play as: ");
    scanf("%d", &choice);

    Character player;

    // Initialize player character based on the chosen character
    switch (choice) {
        case 1:
            player = (Character){"Messi", 1000, 100, 50, {skills[0][0], skills[0][1], skills[0][2], skills[0][3]}};
            break;
        case 2:
            player = (Character){"Dani Alves", 1200, 80, 70, {skills[1][0], skills[1][1], skills[1][2], skills[1][3]}};
            break;
        case 3:
            player = (Character){"Rakitic", 800, 120, 40, {skills[2][0], skills[2][1], skills[2][2], skills[2][3]}};
            break;
        default:
            printf("Invalid choice. Defaulting to Messi.\n");
            player = (Character){"Messi", 1000, 100, 50, {skills[0][0], skills[0][1], skills[0][2], skills[0][3]}};
            break;
    }

    // Display current character stats
    printf("\nSelected Character:\n");
    printf("Name: %s\n", player.name);
    printf("HP: %d\n", player.hp);
    printf("ATK: %d\n", player.atk);
    printf("DEF: %d\n", player.def);
}

void test_skill_selection(){
    // Display available skills for testing
    printf("\nAvailable Skills for Testing:\n");
    for (int i = 0; i < MAX_SKILLS; i++) {
        printf("%d. %s - %s\n", i + 1, player.skills[i].name, player.skills[i].description);
    }

    // Select a skill for testing
    printf("\nEnter the number of the skill you want to test: ");
    scanf("%d", &choice);

    // Apply the selected skill to the player character
    if (choice >= 1 && choice <= MAX_SKILLS) {
        apply_skill(&player, player.skills[choice - 1]);

        // Display updated player stats after applying the skill
        printf("\nPlayer Stats after Testing:\n");
        printf("HP: %d\n", player.hp);
        printf("ATK: %d\n", player.atk);
        printf("DEF: %d\n", player.def);
    } else {
        printf("Invalid skill choice.\n");
    }
}
void exit_game() {
    printf("Exiting game...\n");
    exit(0);
}

=======
#define MAX_SKILLS 50
#define MAX_WEAPONS 10
#define MAX_EQUIPPED_SKILLS 4
#define MAX_EQUIPPED_WEAPONS 1
#define ENEMIES 4
#define OPTIONS 5


int initial_menu(Character Player) {
    int choice;

    while (choice != 4) {
        printf("\nWelcome to the Game Menu:\n");
        printf("1. Start a New Game\n");
        printf("2. Configure Character\n");
        printf("3. Test Skill Selection System\n");
        printf("4. Exit\n");
        
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                start_game(Player); // Call start_game function
                break;
            case 2:
                configure_character(Player); // Call configure_character function
                break;
            case 3:
                test_skills(Player); // Call test_skills function
                break;
            case 4:
                exit_game(); // Call exit_game function
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 4.\n");
        }
    }
    return 0;
}

void start_game(Character Player1) {
    printf("Starting new game...\n");
    Player1 = create_character(Player1); // Assign the result of create_character to Player1
}

bool character_exists(Character player) {
    return strcmp(player.name, "") != 0;
}

Character create_character(Character new_character) {
    printf("Enter your character's name (up to 20 characters): ");
    scanf("%s", new_character.name);
    new_character.hp = 0;
    new_character.atk = 0;
    new_character.def = 0;
    return new_character;
}

void configure_character(Character player) {
    int choice;
    if(character_exists(player) == false){
        printf("Dear player, since you don't have a character we will have first to create one\n");
        player = create_character(player);   
    }
    else{
        while (choice != 3){
            printf("Welcome to the character configuration where you can manage your habilities or manage your weapons!\n");
            printf("1. Habilities inventory \n 2. Weapon inventory \n 3. Go back to menu \n");
            printf("Enter your choice (1-3): ");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                    choose_and_equip_skills(&player);
                    break;
                case 2:
                    choose_and_equip_weapon(&player); 
                    break;
                case 3:
                    break;
                default:
                    printf("Invalid choice. Please enter a number from 1 to 4.\n");
            }
        }
    }
}

void test_skills(Character player) {
    printf("Testing skill selection system...\n");
}

void exit_game() {
    printf("Exiting game...\n");
    exit(0);
}
