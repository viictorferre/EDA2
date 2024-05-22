#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h" // Include the header file containing the structs

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
