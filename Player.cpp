#include "Player.h"
#include <iostream>

void Player::set_name(std::string n) {
	name = n;
}
void Player::talk(std::string n) {
	std::cout << name << " says " << n << std::endl;
}
void Player::set_is_dead(bool n) {
	if (n == true) {
		health = 0;
		std::cout << name << " is dead" << std::endl;
	}
}
std::string Player::get_name() {
	return name;
}
int Player::get_health() {
	return health;
}
int Player::get_exp() {
	return exp;	
}
Player::Player(std::string name_val, int health_val, int exp_val) {
	name = name_val;
	health = health_val;
	exp = exp_val;
}
Player::Player(const Player& p)
	:name{ p.name }, health{ p.health }, exp{ p.exp }{
	std::cout << "Coppy called" << std::endl;
}
Player::~Player() {
	std::cout << "Destructor called" << std::endl;
}