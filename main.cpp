#include "all_includes.h"


string orcs_names = "Orcs.txt"; // path to file with names orcs
string goblins_names = "Goblins.txt"; // path to file with names orcs

ifstream orcs; // for read from "Orcs.txt"
ifstream goblins; // for read from "Goblins.txt"

vector<string> orc_names; // dynamic array for orcs
vector<string> goblin_names; // dynamic array for goblins 

//Text Animation
void slowWrite(string s) {
	// мини анимация ввода текста
	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i];
		Sleep(50);
	}
	cout << "" << endl;
}

//Point animation
void WaitAnim() {
	for (int i = 0; i < 5; i++)
	{
		cout << ".";
		Sleep(500);
	}
} 

//Classes

class Entity {
protected:
	int Health = 100; // default value of Health
	int Damage = 10; // default value of Damage
	virtual int Attack() = 0;
};

class Character : public Entity {
public:
	int Health = Entity::Health; // Character Health
	int Damage = Entity::Damage; // Character Damage
	int Money = 0;
	int Attack() override {
		return Damage;
	}
};

class Goblin : public Entity {
public:
	string Name;
	int Health = Entity::Health - 90; // health = 10
	int Damage = Entity::Damage - 7; // damage = 3
	int Attack() override {
		return Damage;
	}
	Goblin(string name) {
		Name = name;
	}
	~Goblin() {
		cout << "Гоблин был убит." << endl;
	}
};

class Orc : public Entity {
public:
	string Name;
	int Health = Entity::Health - 65; // health = 35
	int Damage = Entity::Damage + 10; // Damage = 20
	int Attack() override {
		return Damage;
	}
	Orc(string name) {
		Name = name;
	}
};

int main() {
	orcs.open(orcs_names); // Open file with name Orcs.txt
	string s;
	if (orcs.is_open()) {
		while (getline(orcs,s)) {
			orc_names.push_back(s); // добавление имени в конец вектора
		}
	}
	s = "";
	goblins.open(goblins_names); // Open file with name Goblins.txt
	if (goblins.is_open()) {
		while (getline(goblins, s)) {
			goblin_names.push_back(s); // add in dynamic array for goblins.
		}
	}
	
	Character* character = new Character(); // Create Character in game.
	string actions; // Action character.
	bool is_work = true; // Programm status.

	

	string hi = "Welcome to the mini RPG game!\nIt was designed to show the skills of the developer.";
	slowWrite(hi);
	 hi = "Would you like to start the game?[Y/N]: ";
	Label:
	slowWrite(hi);

	cin >> actions;
	
	if ("y" == actions) {
		system("color B0");
		system("cls"); // clear console
		while (is_work) {
			if (character->Health > 0) {
				cout << "Enter any key to roll the dice:" << endl;
				string m;
				cin >> m;
				int change = 1 + rand() % 6;
				cout << "You got a number: " << change << endl;
				Sleep(1000);
				system("cls");
				cout << "Moving";
				WaitAnim();
				system("cls");
				if (change == 6) {
					int index_name_goblin = 1 + rand() % 15; // рандом от 1 числа до 15 (имя)

					Goblin* goblin = new Goblin(goblin_names[index_name_goblin]);
					cout << "You met a character: \"" << goblin->Name << "\"" << "(Goblin)" << endl;
					cout << goblin->Name << " attacked you.\nYour health is now: ";
					character->Health -= goblin->Attack();
					cout << character->Health << endl;
					cout << "Character health \"" << goblin->Name << "\" equals " << goblin->Health << endl;
					AttackG_or_Run:
					cout << "Do you want to attack him? [y/n] ";
					cin >> actions;
					system("cls");
					if ("y" == actions) {
						cout << "You attacked a goblin. " << endl;
						goblin->Health -= character->Attack();

						if (goblin->Health <= 0) {
							delete goblin;
							Sleep(2000);
							system("cls");
							continue;
						}
					}
					if ("n" == actions) {
						cout << "You decided to run away and lost 2HP" << endl;
						character->Health -= 2;
						Sleep(2000);
						system("cls");
					}
					else {
						goto AttackG_or_Run;
					}
				}

				if (change == 5) {
					int index_name_orc = 1 + rand() % 15; // рандом от 1 числа до 15 (имя)

					Orc* orc = new Orc(orc_names[index_name_orc]);
					cout << "You met a character: \"" << orc->Name << "\"" << "(Orc)" << endl;
					cout << orc->Name << " attacked you.\nYour health is now: ";
					character->Health -= orc->Attack();
					cout << character->Health << endl;
					cout << "Character health \"" << orc->Name << "\" equals " << orc->Health << endl;
					AttackO_or_Run:
					cout << "Do you want to attack him? [y/n] ";
					cin >> actions;
					system("cls");
					if ("y" == actions) {
						cout << "You attacked a orc. " << endl;
						orc->Health -= character->Attack();

						if (orc->Health <= 0) {
							delete orc;
							Sleep(2000);
							system("cls");
						}
					}
					if ("n" == actions) {
						cout << "You decided to run away and lost 10HP" << endl;
						character->Health -= 10;
						Sleep(2000);
						system("cls");
					}
					else
					{
						goto AttackO_or_Run;
					}
				}

				if (change == 4) {
					string buy;
					cout << "You met a blacksmith. He offered to upgrade your sword for 5 coins.\nDo you agree?[y/n]: " << endl;
					cin >> buy;
					if ("y" == buy) {
						character->Money -= 5;
						character->Damage += 5;
						cout << "Your sword has been upgraded. You deal 5 more damage." << endl;
					}
					if ("n" == buy) {
						cout << "You left the blacksmith." << endl;
						Sleep(2000);
						system("cls");
					}
					else {
						cout << "You did not have enough money and you left the blacksmith." << endl;
						Sleep(2000);
						system("cls");
					}
				}

				if (change == 3) {
					cout << "You met the doctor. you restored 25HP" << endl;
					character->Health += 20; 
					if (character->Health > 100) {
						character->Health = 100;
					}
				}

				if (change == 2) {
					cout << "Nobody here." << endl;
					Sleep(2000);
					system("cls");
				}

				if (change == 1) {
					cout << "You have found 10 coins." << endl;
					character->Money += 10;
					Sleep(2000);
					system("cls");
				}
			}
			if (character->Money < 0) character->Money = 0;
			else {
				system("cls");
				cout << "Your character is dead..." << endl;
				is_work = false;
			}
			
			
			
		}

	}

	if ("n" == actions) {
		cout << "You left the game." << endl;
	}
	else {
		goto Label;
	}
	
	return 0;
}