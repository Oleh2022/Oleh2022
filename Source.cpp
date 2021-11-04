#include <iostream>
#include "Source.h"

using namespace std;

int main(){

	bool is_dead{ false };
	unsigned short age{ 1 };
	unsigned short* ptr_age { &age };

	while (is_dead == false) {

	   display_age(ptr_age);

	   if (*ptr_age >= 0 && *ptr_age < 6){
		   choice_0_6_skills();

	   }
	   else if (*ptr_age >= 6 && *ptr_age < 12){


	   }
	   else if (*ptr_age >= 12 && *ptr_age < 18){


	   }
	   else if (*ptr_age >= 18){

	   }

	   is_dead = check_dead(ptr_age);
	   (*ptr_age)++;
	   
	}



	return 0;
}
