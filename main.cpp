#include "raylib.h"

#define number_of_buttons 3
#define number_of_settings 5
#define number_of_start 4
#define number_of_pause 3

typedef enum GameScreen { Menu_Screen = 0, Settings_Screen, Start_Screen, Pause_Screen, Skills_Screen, Shop_Screen, Jobs_Screen, First_Message_Screen, Last_Message_Screen, Account_Screen, Error_Skill_Screen, Error_Shop_Screen, Error_Jobs_Screen} GameScreen;
enum { None = -1, Mathematic = 0};

int main(){

    bool CloseGame{false};
    bool PauseMenuOn{false};
    bool pop_ups_on_skills{false};

    bool do_once {true};

    int window_width  {1920};
    int window_height {1080};

    int mouse_touch {-1};
    int mouse_touch_settings {-1};
    int mouse_touch_start {-1};
    int mouse_touch_pause {-1};
    int mouse_touch_next_age {-1};
    int mouse_touch_job {-1};
    int mouse_touch_skills {-1};
    int mouse_touch_skills_error {-1};
    int mouse_touch_shop {-1};
    int mouse_touch_shop_error {-1};
    int mouse_touch_job_error {-1};
    int mouse_touch_first_message {-1};
    int mouse_touch_last_message {-1};

    int current_process {-1};
    int current_process_settings {-1};
    int current_process_start {-1};
    int current_process_pause {-1};
    int current_process_next_age {-1};
    int current_process_job {-1};
    int current_process_skills {-1};
    int current_process_skills_error {-1};
    int current_process_job_error {-1};
    int current_process_shop {-1};
    int current_process_shop_error {-1};
    int current_process_first_message {-1};
    int current_process_last_message {-1};

    short number_of_years {1};
    short max_age {GetRandomValue(10, 20)};

    int money {1000};
    int skills {0};
    int skills_touch {0};
    int math_books {0};
    int current_job {-1};

    

    Vector2 position[number_of_buttons] = {0};
    for(int i = 0; i < number_of_buttons; i++){
        position[i].x = 1750;
        position[i].y = 750 + 120*i; 
    }
    
    static const char *text[] = {"Start", "Settings", "Exit"};
    static const char *Setting_text[] = {"Graphics", "Audio", "Video", "Controls"};
    static const char *StartText[] = {"Skills", "Shop", "Job", "Account"};
    static const char *PauseMenuText[] = {"Resume", "Back to Menu", "Exit"};

    Rectangle buttons[number_of_buttons] = {0};
    Rectangle buttons_in_pause[number_of_pause] = {0};
    Rectangle buttons_in_settings[number_of_settings] = {0};
    Rectangle buttons_in_start[number_of_start] = {0};
    Rectangle button_age[1] = {0};
    Rectangle buttons_in_skill[1] = {0};
    Rectangle buttons_in_first_message[1] = {0};
    Rectangle buttons_in_last_message[1] = {0};
    Rectangle buttons_in_skill_error[1] = {0};
    Rectangle buttons_in_shop_error[1] = {0};
    Rectangle buttons_in_job_error[1] = {0};
    Rectangle buttons_in_shop[1] = {0};
    Rectangle buttons_in_job[1] = {0};

    for(int i = 0; i < number_of_buttons; i++){       
        //buttons[i] = (Rectangle){1720, (float)((window_height/1.5) + (float)((window_height/9)*i)), (float)(window_width/6.4), (float)(window_width/19.2)};
        buttons[i] = (Rectangle){1720, (float)(720 + 120*i), 300, 100};
    }

        button_age[0] = (Rectangle){1700, 900, 200, 100};

        buttons_in_pause[0] = (Rectangle){880, (float)(400 + 120*0), 300, 80};
        buttons_in_pause[1] = (Rectangle){840, (float)(400 + 120*1), 300, 80};
        buttons_in_pause[2] = (Rectangle){910, (float)(400 + 120*2), 300, 80};
    

    for(int i = 0; i < number_of_settings - 1; i++){
        buttons_in_settings[i] = (Rectangle){480, (float)(280 + 70*i), 288, 50};    
    }
    buttons_in_settings[4] = (Rectangle){1340, 180, 100, 100};

    for(int i = 0; i < number_of_start - 1; i++){
        buttons_in_start[i] = (Rectangle){0, (float)(0 + 120*i), 300, 100};
    }
    buttons_in_start[3] = (Rectangle){0, 1000, 300, 100};

    buttons_in_skill[0] = (Rectangle){410, 50, 250, 80};

    buttons_in_shop[0] = (Rectangle){410, 50, 250, 80};

    buttons_in_job[0] = (Rectangle){410, 50, 250, 80};


    buttons_in_first_message[0] = (Rectangle){1060, 670, 200, 70};

    buttons_in_last_message[0] = (Rectangle){1060, 670, 250, 70};

    buttons_in_skill_error[0] = (Rectangle){1060, 670, 250, 70};

    buttons_in_shop_error[0] = (Rectangle){1060, 670, 250, 70};

    buttons_in_job_error[0] = (Rectangle){1060, 670, 250, 70};

   

    InitWindow(window_width, window_height, "Galore");
    SetTargetFPS(60);
    ToggleFullscreen();

    Texture2D Cross = LoadTexture("Cross.png");
    Texture2D CrossAnim = LoadTexture("CrossAnim.png");
    Texture2D background = LoadTexture("MainMenu.png");
    Texture2D StartMenu2 = LoadTexture("Start_menu2.png");
    Texture2D StartMenu = LoadTexture("Start_menu.png");
    Texture2D StartMenu1 = LoadTexture("Start_menu1.png");
    Texture2D Settings = LoadTexture("Settings.png");
    Texture2D PauseMenu = LoadTexture("Pause_menu.png");
    Texture2D NextAgeBackGround = LoadTexture("Next_age_background.png");
    Texture2D ShopIcon = LoadTexture("shop.png");
    Texture2D SkillsIcon = LoadTexture("skills.png");
    Texture2D JobsIcon = LoadTexture("jobs.png");
    Texture2D StartBackground = LoadTexture("Fon3.png");

    GameScreen CurrentScreen = Menu_Screen;

//Logo
    Image Logo = LoadImage("Icon.png");
    SetWindowIcon(Logo);

   

    Vector2 start_text_position[number_of_start];
        
    start_text_position[3].x = 100;
    start_text_position[3].y = 1000;

    for(int i = 0; i < number_of_start - 1; i++){
        start_text_position[i].x = 110;
        start_text_position[i].y = (float)(40 + 120*i);
    }
    

    Vector2 pause_menu_position[number_of_pause];
    
        pause_menu_position[0].x = 897;
        pause_menu_position[0].y = (float)(400 + 120*0);
        pause_menu_position[1].x = 860;
        pause_menu_position[1].y = (float)(400 + 120*1);
        pause_menu_position[2].x = 923;
        pause_menu_position[2].y = (float)(400 + 120*2);
    

    Vector2 settings_text_position;
    settings_text_position.x = 550;
    settings_text_position.y = 215;

    Vector2 setting_buttons_position[number_of_settings - 1];
    for(int i = 0; i < number_of_settings - 1; i++){
        setting_buttons_position[i].x = 500;
        setting_buttons_position[i].y = (float)(300 + 70*i);
    }

    Vector2 years_position;
    years_position.x = 1745;
    years_position.y = 35;

    Vector2 next_age_position;
    next_age_position.x = 1730;
    next_age_position.y = 940;
    
    Vector2 years_text_position;
    years_text_position.x = 1530;
    years_text_position.y = 30;

    Vector2 skill_text_position;
    skill_text_position.x = 500;
    skill_text_position.y = 70; 

    Vector2 first_message_position;
    first_message_position.x = 610;
    first_message_position.y = 350; 

    Vector2 last_message_position;
    last_message_position.x = 610;
    last_message_position.y = 350; 

    Vector2 first_message_continue_position;
    first_message_continue_position.x = 1070;
    first_message_continue_position.y = 680;

    Vector2 last_message_continue_position;
    last_message_continue_position.x = 1070;
    last_message_continue_position.y = 680;

    Vector2 skill_error_continue_position;
    skill_error_continue_position.x = 1200;
    skill_error_continue_position.y = 680;

    Vector2 skill_error_text_position;
    skill_error_text_position.x = 610;
    skill_error_text_position.y = 350;

    Vector2 money_position;
    money_position.x = 600;
    money_position.y = 400;

    Vector2 skills_position;
    skills_position.x = 600;
    skills_position.y = 450;

    Vector2 shop_text_position;
    shop_text_position.x = 450;
    shop_text_position.y = 70;

    Vector2 job_text_position;
    job_text_position.x = 450;
    job_text_position.y = 70;

    Vector2 shop_error_continue_position;
    shop_error_continue_position.x = 1200;
    shop_error_continue_position.y = 680;

    Vector2 shop_error_text_position;
    shop_error_text_position.x = 610;
    shop_error_text_position.y = 350;

    Vector2 math_books_position;
    math_books_position.x = 600;
    math_books_position.y = 500;

    Vector2 current_job_position;
    current_job_position.x = 600;
    current_job_position.y = 550;

    Vector2 your_account_position;
    your_account_position.x = 830;
    your_account_position.y = 320;





   //Rectangle switch_audio = (Rectangle){};

    Font myfont = LoadFont("AllenoireFont.otf");

    InitAudioDevice();    
    Music music = LoadMusicStream("MainMenuSound.mp3");
    SetMusicVolume(music, 0.01); 
    PlayMusicStream(music);   

while(CloseGame == false){

// Music

//

// Mouse Logic    
switch (CurrentScreen)
{
case Menu_Screen:

UpdateMusicStream(music);
if(!IsMusicStreamPlaying(music)){
    PlayMusicStream(music);
}

for(int i = 0; i < number_of_buttons; i++){

        if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){

          mouse_touch = i;

          if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
               
            current_process = i;

          }

          break;

        }else mouse_touch = -1; 
     }

//Exit button
        if(current_process == 2){
            CloseGame = true; 
        }
//Settings
        if(current_process == 1){
            CurrentScreen = Settings_Screen;
            current_process = -1;
        }  
//Start
        if(current_process == 0){

            if(do_once == true){
                CurrentScreen = First_Message_Screen;
            }else{
                CurrentScreen = Start_Screen;
            }

            current_process = -1;
        }

    break;

case Settings_Screen:

for(int i = 0; i < number_of_settings; i++){ 

    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_settings[i])){
        
        mouse_touch_settings = i;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_settings = i;
            
        }

        break;

    }else mouse_touch_settings = -1;

}

    if(current_process_settings == 4){

    CurrentScreen = Menu_Screen;
    current_process_settings = -1;
    
    }

    break;    


case First_Message_Screen:

    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_first_message[0])){
        
        mouse_touch_first_message = 0;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_first_message = 0;
            
        }

        break;

    }else mouse_touch_first_message = -1;

    if(current_process_first_message == 0){
        CurrentScreen = Start_Screen;
        do_once = false;
        current_process_first_message = -1; 
    }

    break;

case Start_Screen:

for(int i = 0; i < number_of_start; i++){

    StopMusicStream(music);
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_start[i])){

        mouse_touch_start = i;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_start = i;

        }

        break;

    }else mouse_touch_start = -1;
  
}
   
    if(CheckCollisionPointRec(GetMousePosition(), button_age[0])){
        
        mouse_touch_next_age = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_next_age = 0;
            break;

        }

    }else mouse_touch_next_age = -1;
   

   if(IsKeyPressed(KEY_ESCAPE)){
       PauseMenuOn = true;
       CurrentScreen = Pause_Screen;
   }
   

   if(current_process_start == 0){
        CurrentScreen = Skills_Screen;
        pop_ups_on_skills = true;
        current_process_start = -1;
    }
    
    if(current_process_start == 1){
        CurrentScreen = Shop_Screen;
        current_process_start = -1;
    }
    
    if(current_process_start == 2){
        CurrentScreen = Jobs_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 3){
        CurrentScreen = Account_Screen;
        current_process_start = -1;
    }

    if(current_process_next_age == 0){
        number_of_years++;
        skills_touch = 0;

        if(current_job == 0){
            money += 100;
        }
        current_process_next_age = -1;
    }


    if(number_of_years >= max_age){

        CurrentScreen = Last_Message_Screen;
        number_of_years = 1;
        max_age = GetRandomValue(10, 20);
        money = 0;
        skills = 0;
        skills_touch = 0;
        math_books = 0;
        current_job = -1;
    }

    break;   


case Skills_Screen:

for(int i = 0; i < number_of_start; i++){
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_start[i])){

        mouse_touch_start = i;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_start = i;

        }

        break;
    }else mouse_touch_start = -1;
  
}

if(CheckCollisionPointRec(GetMousePosition(), button_age[0])){
        
        mouse_touch_next_age = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_next_age = 0;
            break;
        }

    }else mouse_touch_next_age = -1;


for(int i = 0; i < 1; i++){
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_skill[0])){

        mouse_touch_skills = 0;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_skills = 0;

        }

        break;

    }else mouse_touch_skills= -1;
  
}


    if(current_process_start == 0){
        CurrentScreen = Start_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 1){
        CurrentScreen = Shop_Screen;
        current_process_start = -1;
    }
    
    if(current_process_start == 2){
        CurrentScreen = Jobs_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 3){
        CurrentScreen = Account_Screen;
        current_process_start = -1;
    }

    if(current_process_next_age == 0){
        number_of_years++;
        skills_touch = 0;

        if(current_job == 0){
            money += 100;
        }
        current_process_next_age = -1;
    }

    if(IsKeyPressed(KEY_ESCAPE)){
       PauseMenuOn = true;
       CurrentScreen = Pause_Screen;
    }
    
    if(number_of_years >= max_age){

        CurrentScreen = Last_Message_Screen;
        number_of_years = 1;
        max_age = GetRandomValue(10, 20);
        money = 0;
        skills = 0;
        skills_touch = 0;
        math_books = 0;
        current_job = -1;
    }

    if(current_process_skills == 0){

        if(skills_touch == 5){

            CurrentScreen = Error_Skill_Screen;
            current_process_skills = -1;
            break;
        }
        if(math_books >= 2){
    
           skills += 1 + (float)(math_books * 0.5);

        }else{

            skills++;
        }
        skills_touch++;
        current_process_skills = -1;
    }

    break;

case Shop_Screen: 

for(int i = 0; i < number_of_start; i++){

    StopMusicStream(music);
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_start[i])){

        mouse_touch_start = i;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_start = i;

        }

        break;
    }else mouse_touch_start = -1;
  
}

if(CheckCollisionPointRec(GetMousePosition(), button_age[0])){
        
        mouse_touch_next_age = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_next_age = 0;
            break;
        }

    }else mouse_touch_next_age = -1;



for(int i = 0; i < 1; i++){
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_shop[0])){

        mouse_touch_shop = 0;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_shop = 0;

        }

        break;

    }else mouse_touch_shop= -1;
  
}    


    if(current_process_start == 0){
        CurrentScreen = Skills_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 1){
        CurrentScreen = Start_Screen;
        current_process_start = -1;
    }
    
    if(current_process_start == 2){
        CurrentScreen = Jobs_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 3){
        CurrentScreen = Account_Screen;
        current_process_start = -1;
    }

    if(current_process_next_age == 0){
        number_of_years++;
        skills_touch = 0;

        if(current_job == 0){
            money += 100;
        }
        current_process_next_age = -1;
    }

    if(IsKeyPressed(KEY_ESCAPE)){
       PauseMenuOn = true;
       CurrentScreen = Pause_Screen;
    }

   if(number_of_years >= max_age){

        CurrentScreen = Last_Message_Screen;
        number_of_years = 1;
        max_age = GetRandomValue(10, 20);
        money = 0;
        skills = 0;
        skills_touch = 0;
        math_books = 0;
        current_job = -1;
    }

    if(current_process_shop == 0){

        if(money >= 100){

            money -= 100;
            math_books++;
            current_process_shop = -1;

        }else{

            CurrentScreen = Error_Shop_Screen;
            current_process_shop = -1;
        }
    }
    
    break;


case Jobs_Screen:

    for(int i = 0; i < number_of_start; i++){

    StopMusicStream(music);
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_start[i])){

        mouse_touch_start = i;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_start = i;

        }

        break;
    }else mouse_touch_start = -1;
  
}

if(CheckCollisionPointRec(GetMousePosition(), button_age[0])){
        
        mouse_touch_next_age = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_next_age = 0;
            break;
        }

    }else mouse_touch_next_age = -1;



for(int i = 0; i < 1; i++){
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_job[0])){

        mouse_touch_job = 0;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_job = 0;

        }

        break;

    }else mouse_touch_job= -1;
  
}    


    if(current_process_start == 0){
        CurrentScreen = Skills_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 1){
        CurrentScreen = Shop_Screen;
        current_process_start = -1;
    }
    
    if(current_process_start == 2){
        CurrentScreen = Start_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 3){
        CurrentScreen = Account_Screen;
        current_process_start = -1;
    }

    if(current_process_next_age == 0){
        number_of_years++;
        skills_touch = 0;

        if(current_job == 0){
            money += 100;
        }
        current_process_next_age = -1;
    }
    if(IsKeyPressed(KEY_ESCAPE)){
       PauseMenuOn = true;
       CurrentScreen = Pause_Screen;
    }

    if(number_of_years >= max_age){

        CurrentScreen = Last_Message_Screen;
        number_of_years = 1;
        max_age = GetRandomValue(10, 20);
        money = 0;
        skills = 0;
        skills_touch = 0;
        math_books = 0;
        current_job = -1;
    }

    if(current_process_job == 0){
        
        if(skills == 5){
           current_job = 0;
        }else{
            CurrentScreen = Error_Jobs_Screen;
        }

        current_process_job = -1;
    }


    break;    


case Account_Screen:

for(int i = 0; i < number_of_start; i++){

    StopMusicStream(music);
    
    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_start[i])){

        mouse_touch_start = i;

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_start = i;

        }

        break;
    }else mouse_touch_start = -1;
  
}

if(CheckCollisionPointRec(GetMousePosition(), button_age[0])){
        
        mouse_touch_next_age = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_next_age = 0;
            break;
        }

    }else mouse_touch_next_age = -1;


    if(current_process_start == 0){
        CurrentScreen = Skills_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 1){
        CurrentScreen = Shop_Screen;
        current_process_start = -1;
    }
    
    if(current_process_start == 2){
        CurrentScreen = Jobs_Screen;
        current_process_start = -1;
    }

    if(current_process_start == 3){
        CurrentScreen = Start_Screen;
        current_process_start = -1;
    }

    if(current_process_next_age == 0){
        number_of_years++;
        skills_touch = 0;

        if(current_job == 0){
            money += 100;
        }
        current_process_next_age = -1;
    }

    if(current_process_next_age == 0){
        number_of_years++;
        skills_touch = 0;

        if(current_job == 0){
            money += 100;
        }
        current_process_next_age = -1;
    }

    if(IsKeyPressed(KEY_ESCAPE)){
       PauseMenuOn = true;
       CurrentScreen = Pause_Screen;
    }

    if(number_of_years >= max_age){

        CurrentScreen = Last_Message_Screen;
        number_of_years = 1;
        max_age = GetRandomValue(10, 20);
        money = 0;
        skills = 0;
        skills_touch = 0;
    }


    break;

case Error_Skill_Screen:

 if(CheckCollisionPointRec(GetMousePosition(), buttons_in_skill_error[0])){
        
        mouse_touch_skills_error = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_skills_error = 0;
            break;

        }

    }else mouse_touch_skills_error = -1;


    if(current_process_skills_error == 0){
        CurrentScreen = Start_Screen;
        current_process_skills_error = -1;
    }
     
    

    break;


case Error_Shop_Screen:

    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_shop_error[0])){
            
            mouse_touch_shop_error = 0;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

                current_process_shop_error = 0;
                break;

            }

        }else mouse_touch_shop_error = -1;


        if(current_process_shop_error == 0){
            CurrentScreen = Start_Screen;
            current_process_shop_error = -1;
        }


    break;

case Error_Jobs_Screen:

    if(CheckCollisionPointRec(GetMousePosition(), buttons_in_job_error[0])){
            
            mouse_touch_job_error = 0;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

                current_process_job_error = 0;
                break;

            }

        }else mouse_touch_job_error = -1;


        if(current_process_job_error == 0){
            CurrentScreen = Start_Screen;
            current_process_job_error = -1;
        }

    

    break;    

case Pause_Screen:

    for(int i = 0; i < number_of_pause; i++){
        if(CheckCollisionPointRec(GetMousePosition(), buttons_in_pause[i])){
        
            mouse_touch_pause = i;

            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

                current_process_pause = i;
            
            }

            break;

    }else mouse_touch_pause = -1;
}

   if(current_process_pause == 0){
       PauseMenuOn = false;
       CurrentScreen = Start_Screen;
       current_process_pause = -1;
   }

   if(current_process_pause == 1){
       CurrentScreen = Menu_Screen;
       PauseMenuOn = false;
       pop_ups_on_skills = false;
       current_process_pause = -1;
   }

   if(current_process_pause == 2){
       CloseGame = true;
       current_process_pause = -1;
   }

    break; 

case Last_Message_Screen: 

 if(CheckCollisionPointRec(GetMousePosition(), buttons_in_last_message[0])){
        
        mouse_touch_last_message = 0;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            current_process_last_message = 0;
            break;

        }

    }else mouse_touch_last_message = -1;

    if(current_process_last_message == 0){
        CurrentScreen = Menu_Screen;
        current_process_last_message = -1;
    }
    do_once = true;

    

    break;


default: break;
}

//Drawing
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (CurrentScreen)
    {

    case Menu_Screen:

        DrawTexture(background, 0, 0, WHITE);

        for(int i = 0; i < number_of_buttons; i++){
            DrawRectangleRec(buttons[i], BLANK);
            DrawTextEx(myfont, text[i], position[i], (i == mouse_touch) ? 35 : 30, 0.0, PURPLE);
        }
        
        break;

    case First_Message_Screen:
        
        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        DrawTexture(PauseMenu, 585, 290, WHITE);
        DrawTextEx(myfont, "You were born in the city_name. This is the land\n of big opportunities where you can become\n whoever you want. Want to be a scientist who\n will discover something new or the the soldier\n who will fight for the freedom of his land? Lets\n see what way your fate has prepared for you.", first_message_position, 30, 0, PURPLE);

        
        

        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }
        DrawRectangleRec(buttons_in_first_message[0], BLANK);
        DrawTextEx(myfont, "Let's start", first_message_continue_position, (mouse_touch_first_message == 0) ? 35 : 30, 0, PURPLE);
        
        
        break;    

    case Start_Screen:

        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);
        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }

        break;


    case Skills_Screen: 

        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        DrawTexture(StartMenu2, 300, 0, WHITE);

                
        DrawRectangleRec(buttons_in_skill[0], BLANK);
        DrawTextEx(myfont, "Math", skill_text_position,(mouse_touch_skills == 0) ? 35 : 30, 0, PURPLE);

        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }



        break;   


    case Error_Skill_Screen:

    DrawTexture(StartBackground, 0, 0, WHITE);
    DrawTexture(StartMenu, 1420, 0, WHITE);
    DrawTexture(StartMenu1, 0, 0, WHITE);
    DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

    DrawTexture(SkillsIcon, 205, 22, WHITE);
    DrawTexture(ShopIcon, 205, 145, WHITE);
    DrawTexture(JobsIcon, 205, 263, WHITE);
        
    DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
    DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
    DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

    //DrawTexture(StartMenu2, 300, 0, WHITE);

    DrawTexture(PauseMenu, 585, 290, WHITE);

    DrawTextEx(myfont, "You have already reached your limit.\nTry again in the next year.", skill_error_text_position, 30, 0, PURPLE);

    DrawRectangleRec(buttons_in_skill_error[0], BLANK);

    DrawTextEx(myfont, "Ok", skill_error_continue_position, (mouse_touch_skills_error == 0) ? 35 : 30, 0, PURPLE);

    for(int i = 0; i < number_of_start; i++){
        DrawRectangleRec(buttons_in_start[i], BLANK);
        DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
    }

       
     

    break;    




    case Error_Jobs_Screen:

    DrawTexture(StartBackground, 0, 0, WHITE);
    DrawTexture(StartMenu, 1420, 0, WHITE);
    DrawTexture(StartMenu1, 0, 0, WHITE);
    DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

    DrawTexture(SkillsIcon, 205, 22, WHITE);
    DrawTexture(ShopIcon, 205, 145, WHITE);
    DrawTexture(JobsIcon, 205, 263, WHITE);
        
    DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
    DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
    DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

    DrawTexture(PauseMenu, 585, 290, WHITE);

    DrawTextEx(myfont, "You don't have enough skills to get this job.", skill_error_text_position, 30, 0, PURPLE);

    DrawRectangleRec(buttons_in_job_error[0], BLANK);

    DrawTextEx(myfont, "Ok", skill_error_continue_position, (mouse_touch_job_error == 0) ? 35 : 30, 0, PURPLE);

    for(int i = 0; i < number_of_start; i++){
        DrawRectangleRec(buttons_in_start[i], BLANK);
        DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
    }

    break;


    case Shop_Screen: 


        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        DrawTexture(StartMenu2, 300, 0, WHITE);

                
        DrawRectangleRec(buttons_in_shop[0], BLANK);
        DrawTextEx(myfont, "Math book", shop_text_position, (mouse_touch_shop == 0) ? 35 : 30, 0, PURPLE);
       
        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }


        break;   


    case Error_Shop_Screen:


        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
            
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        DrawTexture(PauseMenu, 585, 290, WHITE);

        DrawTextEx(myfont, "You don't have enough money.", skill_error_text_position, 30, 0, PURPLE);

        DrawRectangleRec(buttons_in_shop_error[0], BLANK);

        DrawTextEx(myfont, "Ok", shop_error_continue_position, (mouse_touch_shop_error == 0) ? 35 : 30, 0, PURPLE);

        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }
        

        break;     

    case Jobs_Screen: 

        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        DrawTexture(StartMenu2, 300, 0, WHITE);

                
        DrawRectangleRec(buttons_in_job[0], BLANK);

        DrawTextEx(myfont, "Mathematic", job_text_position, (mouse_touch_job == 0) ? 35 : 30, 0, PURPLE);
       
        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }


        break;        


    case Account_Screen:
         
        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);

        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);

        DrawTexture(PauseMenu, 585, 290, WHITE);
        DrawTextEx(myfont, "Your Account", your_account_position, 40, 0, PURPLE);
        DrawTextEx(myfont, TextFormat("Money: %d$", money), money_position, 30, 0, PURPLE);
        DrawTextEx(myfont, TextFormat("Math: %d", skills), skills_position, 30, 0, PURPLE);
        DrawTextEx(myfont, TextFormat("Math books: %d", math_books), math_books_position, 30, 0, PURPLE);
        DrawTextEx(myfont,  (current_job == 0) ? "Job: Mathematic" : "Job: None", current_job_position, 30, 0, PURPLE);


        for(int i = 0; i < number_of_start; i++){
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }


        break;    
        
    case Settings_Screen:

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(Settings, 480, 180, WHITE);
        DrawTextEx(myfont,"Settings", settings_text_position, 40, 0 , PURPLE);
        

        if(mouse_touch_settings == 4) DrawTexture(CrossAnim, 1363, 202, WHITE);
        else DrawTexture(Cross, 1365, 205, WHITE);
        
        for(int i = 0; i < number_of_settings; i++){
            DrawRectangleRec(buttons_in_settings[i], BLANK);
        }

        for(int i = 0; i < 4; i++){
            DrawTextEx(myfont, Setting_text[i], setting_buttons_position[i], (i == mouse_touch_settings) ? 35 : 30, 0, PURPLE);
        }

        for(int i = 0; i < number_of_buttons; i++){ 
            DrawRectangleRec(buttons[i], BLANK);
            DrawTextEx(myfont, text[i], position[i], (i == mouse_touch) ? 35 : 30, 0.0, PURPLE);
        }

        break;

    case Pause_Screen:

        DrawTexture(StartBackground, 0, 0, WHITE);
        DrawTexture(StartMenu, 1420, 0, WHITE);
        DrawTexture(StartMenu1, 0, 0, WHITE);
        DrawTexture(NextAgeBackGround, 1670, 918, WHITE);
        DrawTexture(SkillsIcon, 205, 22, WHITE);
        DrawTexture(ShopIcon, 205, 145, WHITE);
        DrawTexture(JobsIcon, 205, 263, WHITE);
        
        DrawTextEx(myfont, TextFormat("%d", number_of_years), years_position, 35, 0, PURPLE);
        DrawTextEx(myfont, "Your age: ", years_text_position, 40, 0, PURPLE);
        DrawTextEx(myfont, "Next age", next_age_position, (mouse_touch_next_age == 0) ? 43 : 40, 0, PURPLE);
         
        if(PauseMenuOn){

            DrawTexture(PauseMenu, 585, 290, WHITE);
            

            for(int i = 0; i < number_of_pause; i++){
                DrawRectangleRec(buttons_in_pause[i], BLANK);
                DrawTextEx(myfont, PauseMenuText[i], pause_menu_position[i], (mouse_touch_pause == i) ? 35 : 30, 0, PURPLE);
            }
            
        }

        for(int i = 0; i < number_of_start; i++){
            
            DrawRectangleRec(buttons_in_start[i], BLANK);
            DrawTextEx(myfont, StartText[i], start_text_position[i], (i == mouse_touch_start) ? 35 : 30, 0, PURPLE);
        }

        break;

    case Last_Message_Screen: 


        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(PauseMenu, 585, 290, WHITE);

        DrawRectangleRec(buttons_in_last_message[0], BLANK);
        DrawTextEx(myfont, TextFormat("Age %d\n Well, that's the end. I can't say if the story was\n good or not. It was your story and only you can\n judge it. So, let's see the result of this way of life: ", max_age), last_message_position, 30, 0, PURPLE);
        DrawTextEx(myfont, "Back to menu", last_message_continue_position, (mouse_touch_last_message == 0) ? 35 : 30, 0, PURPLE);

        break;
    

    default: break;
    }
    EndDrawing();
}

// Unload and Close
    UnloadTexture(background);
    UnloadTexture(Cross);
    UnloadTexture(StartMenu);
    UnloadTexture(StartMenu1);
    UnloadTexture(StartMenu2);
    UnloadTexture(Settings);
    UnloadTexture(PauseMenu);
    UnloadTexture(JobsIcon);
    UnloadTexture(ShopIcon);
    UnloadTexture(SkillsIcon);
    UnloadTexture(NextAgeBackGround);
    UnloadTexture(StartBackground);
    UnloadMusicStream(music);

    CloseAudioDevice();      
    CloseWindow(); 
   
    return 0;
}
