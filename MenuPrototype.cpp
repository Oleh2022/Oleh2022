#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

void PrintglMenu(int &);
int funk (int,int &);

int main()
{
  system("color F0");
  int n {2};
  int c ;
  c = funk (n,c);
  while(TRUE){
          switch (c){
            case 1:
            cout << "   Start\n";
            break;
            case 2:
            cout << "Game Over\n";
            break;
          }
  }
  return 0;
}



int funk (int nMenu,int &input)
{
    input = 1;//устанавливаем на первый пункт меню
    PrintglMenu(input);
    while(TRUE)//бесконечный цикл
    {
        if(GetAsyncKeyState(VK_UP)){
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);// KEYEVENTF_KEYUP - Робить так щоб кнопка нажималася лише один раз. VK_UP - відповідає за стілку вверх.
            0 < input - 1 ? input = input - 1 : input = nMenu;
            PrintglMenu(input);
        }
        if(GetAsyncKeyState(VK_DOWN)){
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            input < nMenu ? input = input + 1 : input = 1;
            PrintglMenu(input);
        }
        if(GetAsyncKeyState(VK_RETURN)){
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
            Sleep(200); // Затримка при Enter
            PrintglMenu(input);
            return input;
        }
    }
}


void PrintglMenu(int &b)
{
    system("cls");
    cout << "\tMenu: " << "\n\n";
    cout << (b == 1 ? "->" : " ") << "\t Start :3\n";
    cout << (b == 2 ? "->" : " ") << "\t Exit  :3\n";

}
