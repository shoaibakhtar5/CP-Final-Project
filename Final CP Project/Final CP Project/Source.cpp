#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_INVENTORY_SIZE = 5;

struct Player {
    string name;
    string playerClass;
    int health;
    int experience;
    string inventory[MAX_INVENTORY_SIZE];
    int inventorySize;
};

struct Mission {
    string name;
    int difficulty;
};

Player initializePlayer() {
    Player player;
    cout << "Enter your character's name: ";
    getline(cin, player.name);
    do {
        cout << "Choose a class \n1: Warrior\n Abilities: Karate, Battle Techniques,Mellee,Weapon Mastery\n";
        cout << "2: Witcher\n Abilities : Magic, Swordsmanship,Enhanced Senses\n";
        cout << "3 : Rogue\n Abilities : Stealth, Poison,Lockpicking and Traps\n";
        cout << "4 : Gladiator\n Abilities : Strength, Arena Combat, Leadership\n";
        cin >> player.playerClass;
        if (player.playerClass < "1" || player.playerClass > "4") {
            cout << "Please choose a class between 1 and 4.\n";
        }

    } while (player.playerClass < "1" || player.playerClass > "4");
    player.health = 100;
    player.experience = 0;
    player.inventorySize = 0;
    return player;
}

void displayPlayerInfo(const Player& player) {
    cout << "\nCharacter Information:\n";
    cout << "Name: " << player.name << "\n";
    cout << "Class: " << player.playerClass << "\n";
    cout << "Health: " << player.health << "\n";
    cout << "Experience: " << player.experience << "\n";
    cout << "Inventory:\n";
    for (int i = 0; i < player.inventorySize; ++i) {
        cout << i + 1 << ". " << player.inventory[i] << "\n";
    }
}

Mission initializemissions(int missionCount) {
    switch (missionCount) {
    case 1:
        return { "Hunt for the Goblin", 1 };
    case 2:
        return { "Retrieve the Lost Artifact", 2 };
    case 3:
        return { "Defeat the Dragon", 3 };
    default:
        return { "Unknown Mission", 0 };
    }
}

void displayMissions() {
    cout << "\nAvailable Missions:\n";
    cout << "1. Hunt for the Goblin (Difficulty: 1)\n";
    cout << "2. Retrieve the Lost Artifact (Difficulty: 2)\n";
    cout << "3. Defeat the Dragon (Difficulty: 3)\n";
}

Mission selectMission() {
    int MissionChoice;
    do {
        cout << "\nEnter the number of the Mission you want to play: ";
        if (!(cin >> MissionChoice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (MissionChoice == 1) {
            cout << "Mission 1: Hunt for the Goblin (Difficulty: 1) is selected.\n";
        }
        else if (MissionChoice == 2) {
            cout << "Mission 2: Retrieve the Lost Artifact (Difficulty: 2) is selected.\n";
        }
        else if (MissionChoice == 3) {
            cout << "Mission 3: Defeat the Dragon (Difficulty: 3) is selected.\n";
        }
        else {
            cout << "Please select between 1 and 3.\n";
        }
    } while (MissionChoice < 1 || MissionChoice > 3);

    return initializemissions(MissionChoice);
}

void executeStoryline(const Mission& Mission) {


    // Different stories for each quest
    if (Mission.name == "Hunt for the Goblin") {
        cout << "In the dark forests of Eldoria, goblins have been terrorizing the local villages.\n";
        cout << "Rumors suggest that their leader, Grimgor the Terrible, holds a map to hidden treasure.\n";
        cout << "Your MISSION is to hunt down Grimgor, defeat him, and recover the map!\n";

    }
    else if (Mission.name == "Retrieve the Lost Artifact") {
        cout << "Legends speak of a powerful artifact hidden deep within the Forbidden Caverns.\n";
        cout << "The artifact, known as the 'Eye of Azrath,' possesses mystical powers that can reshape reality.\n";
        cout << "Your MISSION is to brave the dangers of the caverns, retrieve the artifact, and ensure it doesn't fall into the wrong hands!\n";

    }
    else if (Mission.name == "Defeat the Dragon") {
        cout << "A mighty dragon, Drakonos the Flameheart, has awakened from centuries of slumber.\n";
        cout << "His fiery breath threatens to engulf the entire kingdom in flames.\n";
        cout << "Your MISSION is to embark on a perilous journey to the Dragon's Lair, defeat Drakonos, and save the kingdom from destruction!\n";

    }

}

void performBattle(Player& player, const Mission& Mission) {
    srand(time(0)); // Simplified seed

    int enemyDifficulty = Mission.difficulty * 2;
    int enemyHealth = 30 + rand() % (enemyDifficulty * 10);

    executeStoryline(Mission);

    cout << "\nBattle Start! You encountered a mythical creature!\n";

    while (player.health > 0 && enemyHealth > 0) {
        int playerAttack = 10 + rand() % 20;
        enemyHealth -= playerAttack;
        cout << "You dealt " << playerAttack << " damage to the creature. ";


        int creatureAttack = 2 + rand() % (enemyDifficulty * 2);
        player.health -= creatureAttack;
        cout << "The creature dealt " << creatureAttack << " damage to you.\n ";


        cout << "Your Health: " << player.health << ", Creature's Health: " << enemyHealth << "\n";
        system("pause");
    }

    if (player.health <= 0) {
        cout << "You were defeated in battle. Game Over!\n";
    }
    else {
        cout << "You defeated the creature!\n";
        player.experience += Mission.difficulty * 10;

        char increaseHealthChoice;
        do {
            cout << "Caution:If you increase your health, experience points will be deducted.\n";
            cout << "Do you want to increase your health? (y/n): ";
            cin >> increaseHealthChoice;
            if (increaseHealthChoice != 'y' && increaseHealthChoice != 'Y' && increaseHealthChoice != 'n' && increaseHealthChoice != 'N') {
                cout << "Invalid Choice. Please Select the Correct Choice.";
            }
        } while (increaseHealthChoice != 'y' && increaseHealthChoice != 'Y' && increaseHealthChoice != 'n' && increaseHealthChoice != 'N');




        if (increaseHealthChoice == 'y' || increaseHealthChoice == 'Y') {
            int experienceLoss = 20;
            if (player.experience >= experienceLoss) {
                player.health += 20;
                player.experience -= experienceLoss;
                cout << "Health increased. Your new health: " << player.health << "\n";
            }
            else {
                cout << "Not enough experience points to increase health.\n";
            }
        }

        if (Mission.name == "Hunt for the Goblin") {
            cout << "Yahoo... You got a Gold Bow. Added it to your inventory.\n";
            if (player.inventorySize < MAX_INVENTORY_SIZE) {
                player.inventory[player.inventorySize++] = "Gold Bow";
            }
            else {
                cout << "Your inventory is full. Cannot add more items.\n";
            }
        }
        else if (Mission.name == "Retrieve the Lost Artifact") {
            cout << "Yahoo... You got a Diamond Sword. Added it to your inventory.\n";
            if (player.inventorySize < MAX_INVENTORY_SIZE) {
                player.inventory[player.inventorySize++] = "Diamond Sword";
            }
            else {
                cout << "Your inventory is full. Cannot add more items.\n";
            }
        }
        else if (Mission.name == "Defeat the Dragon") {
            cout << "Yahoo... You got a Magical Stick. Added it to your inventory.\n";
            if (player.inventorySize < MAX_INVENTORY_SIZE) {
                player.inventory[player.inventorySize++] = "Magical Stick";
            }
            else {
                cout << "Your inventory is full. Cannot add more items.\n";
            }
        }
    }
}

void levelUp(Player& player) {
    int requiredExperience = 50;
    if (player.experience >= requiredExperience) {
        cout << "\nLevel Up!\n";
        player.health += 30;
        player.experience = 0;
        cout << "Health increased. Your new health: " << player.health << "\n";
    }
}

int main() {
    cout << "                       THE MAD GATE " << endl;
    cout << "        ----------------------------------------- " << endl;
    system("pause>0");
    cout << "In the moonlit realm of Eldoria, a shadowy figure emerges the legendary MEN \n";
    cout << "skilled in ancient arts.Cloaked in darkness, their mission unfolds : \n";
    cout << "to Hunt for Goblin, retrieve a lost artifact & Defeat the Dragon\n";
    cout << " and ensure it remains beyond the grasp of the lurking dangers \n";
    cout << "        ----------------------------------------- " << endl;
    system("pause");
    Player player = initializePlayer();
    int questCount = 3;
    for (int i = 0; i < questCount; i) {
        displayPlayerInfo(player);
        displayMissions();

        Mission selectedQuest = selectMission();
        performBattle(player, selectedQuest);

        if (player.health <= 0) {
            cout << "You DIED!. Game Over!\n";
            break;
        }

        levelUp(player);

        char continueChoice;
        do {
            cout << "\nDo you want to continue? (y/n): ";
            cin >> continueChoice;
            if (continueChoice != 'y' && continueChoice != 'Y' && continueChoice != 'n' && continueChoice != 'N') {
                cout << "Invalid choice. Please enter 'y' to continue or 'n' to exit.\n";
            }
        } while (continueChoice != 'y' && continueChoice != 'Y' && continueChoice != 'n' && continueChoice != 'N');

        if (continueChoice != 'y' && continueChoice != 'Y') {
            cout << "Exiting the game. Goodbye!\n";
            cout << "----------------------------------";
            cout << "----------------------------------";
            break;
        }
    }
    return 0;
}