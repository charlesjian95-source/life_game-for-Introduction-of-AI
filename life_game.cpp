#include <iostream>
#include <raylib.h>
#include "config.h"
#include "menu.h"
#include "game.h"
#include "egg.h"
#include "life_map.h"

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
/*======================設置初始條件======================*/
    int mapp[map_height][map_width] = {};
    int mapp2[map_height][map_width] = {};
    int time_stop = 1; //檢測是否暫停迭代 1:迭代 -1:暫停
    int user_x = 40 , user_y = 40;
    int mode = 0;
    bool doubleMode = 0;

    Page page = Page::Menu_1;//初始化頁面
    SetTargetFPS(20);//設定frame數 太大的話會迭代太快
    InitWindow(x,y,"conway"); //設定地圖大小跟標題名稱
/*======================函數開始執行======================*/
    while(!WindowShouldClose()){
        switch(page){
            case Page::Menu_1 :{
                mode = menuPage1(page,mapp);
                if(page == Page::Egg) break;
                if(mode == 13 || mode ==100){CloseWindow(); return 0;}
                if(mode == 101){break;} //進入page2
                initMode(mapp,mode);
                page = Page::Game_1;
                doubleMode = 0;
                break;
            }
            case Page::Menu_2 :{
                mode = menuPage2(page);
                if(mode == 101){break;}
                if(mode == 100){CloseWindow(); return 0;}
                page = Page::Game_1;
                doubleMode = 1;
                break;
            }
            case Page::Game_1 :{
                user_x = 40;
                user_y = 40;
                time_stop = 1;
                gamePage1(mapp,mapp2,user_x,user_y,time_stop , doubleMode);
                page = Page::Menu_1;
                break;
            }
            case Page::Egg :{
                eggPage();
                page = Page::Menu_1;
                break;
            }
        }
    }
    CloseWindow();
}
