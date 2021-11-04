#include <iostream>
using namespace std;

int cash{ 0 };
unsigned short max_age{ 100 }, iq{ 50 };
char skills_0_6, choise_food_0_18;
void display_age(unsigned short *age_val) {
	cout << *age_val << endl;
}
void choice_0_6_skills() {
	cout << "What skill do you want to upgrade?" << endl;
	cin >> skills_0_6;

	switch (skills_0_6) {

	case 'P':
	case 'p':
		cout << "P is selected" << endl;
		iq += 20;
		break;
	}
}
void food_0_18() {

	cout << "You are hungry!! Chouse what do you want to eat?" << endl;
	cin >> choise_food_0_18;

	switch (choise_food_0_18) {

	case 'H':
	case 'h':
		cout << "You ate a hamburger. That's bad!" << endl;
		max_age -= 1;
		break;
	}

}
bool check_dead(unsigned short* age_val) {
	if (*age_val >= max_age)
		return true;
	else 
		return false;
}
