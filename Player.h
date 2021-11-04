#pragma once
#include <string>

class Player
{
private:
	std::string name;
	int health;
	int exp;
	bool dead = false;

public:
	void set_name(std::string n);
	std::string get_name();
	int get_health();
	int get_exp();
	void talk(std::string n);
	void set_is_dead(bool n);

	Player(std::string name_val = "Unknown", int health_val = 100, int exp_val = 0);
	Player(const Player& p);
	~Player(); 
	
};

