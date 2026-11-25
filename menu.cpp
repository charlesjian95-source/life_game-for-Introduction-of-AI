#include "menu.h"
#include <raylib.h>

/*======================主程式結束======================*/
int menuPage2(Page &page){
    /*===============設置文字大小、間距、位置等等===============*/
    const int x =400;
    const int y = 300, d = 40; //d是間距
    const int size = 40;
    const int button_x = x-50; 
    int button_y = y;

    /*===============選單===============*/
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Conway's life game" , 325 , 100 , 60 , WHITE);
        DrawText("Double mode",x,y-2*d, 50 , WHITE);
        if(IsKeyPressed(KEY_LEFT)){page = Page::Menu_1;return 101;}
        EndDrawing();
    }
    return 100; //結束
}

/*======================MenuPage設計======================*/
int menuPage1(Page &page , int mapp[][map_width]){ //待完成
    /*===============設置文字大小、間距、位置等等===============*/
    const int x =400;
    const int y = 300, d = 40; //d是間距
    const int size = 40;
    const int button_x = x-50; 
    int button_y = y;
    int egg = 0;
    const int eggKeys[] = {KEY_C, KEY_S, KEY_E, KEY_THREE, KEY_TWO, KEY_SIX};
    /*===============選單===============*/
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
           
        DrawText("Single Mode" , x , y-2*d , 50 , WHITE);
        DrawText("1.Block" , x , y+0*d  , size , WHITE);
        DrawText("2.Beehive" , x , y+1*d  , size , WHITE);
        DrawText("3.Blinker" , x , y+2*d  , size , WHITE);
        DrawText("4.Toad" , x , y+3*d  , size , WHITE);
        DrawText("5.Beacon" , x , y+4*d  , size , WHITE);
        DrawText("6.Pulse" , x , y+5*d  , size , WHITE);
        DrawText("7.Glider" , x , y+6*d  , size , WHITE);
        DrawText("8.LWSS" , x , y+7*d  , size , WHITE);
        DrawText("9.R-pentomin" , x, y+8*d  , size , WHITE);
        DrawText("10.Acorn" , x , y+9*d  , size , WHITE);
        DrawText("11.Gosper Glider Gun" , x , y+10*d  , size , WHITE);
        DrawText("12.VOID" , x , y+11*d  , size , WHITE);
        DrawText("QUIT" , x , y+12*d  , size , WHITE);
        DrawText("use up/down to move arrow" , x-100 ,y+13*d ,size , BLUE );
        DrawText("use Space to choose mode" , x-100 ,y+14*d ,size , BLUE );
        DrawText("use RIGHT to enter double mode" , x-100 , y+15*d , size , BLUE);

        /*===============操作===============*/
        if(IsKeyPressed(KEY_UP) && button_y>y)button_y-=d;
        else if(IsKeyPressed(KEY_UP))button_y = y+12*d;

        if(IsKeyPressed(KEY_DOWN) && button_y<y+12*d)button_y+=d;
        else if(IsKeyPressed(KEY_DOWN))button_y = y;

        if(IsKeyPressed(KEY_SPACE)){EndDrawing(); return((button_y-y)/size+1);}

        if(IsKeyPressed(KEY_RIGHT)){EndDrawing(); page = Page::Menu_2; return 101;} //切換到page2

        DrawText("->", button_x , button_y,size , BLUE);

        int key = 0;
        while((key = GetKeyPressed()) != 0){
            // Accept both the number row and the numeric keypad.
            if(key >= KEY_KP_0 && key <= KEY_KP_9)
                key = KEY_ZERO + (key - KEY_KP_0);
            if(key == eggKeys[egg]) ++egg;
            else egg = (key == KEY_C) ? 1 : 0;
            if(egg == 6) break;
        }
        EndDrawing();
        if(egg == 6){
            page = Page::Egg;
            return 0;
        } 
    }
    return 100;
}
