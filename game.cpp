#include "game.h"
#include "life_map.h"
#include <raylib.h>

int user_path = 20;

/*======================gamePage1設計======================*/
void gamePage1(int mapp[][map_width],int mapp2[][map_width],int &user_x , int &user_y,int &time_stop , bool doubleMode){
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("up/down/left/right:move",300,100,20 , WHITE);
        DrawText("L-ctrl:Stop time",300,120,20 , WHITE);
        DrawText("Spcae:create(only work when time stop)",300,140,20 , WHITE);
        DrawText("Q:Back to menu",300,160,20 , WHITE);
        DrawText("L-ALT:Delete life",300,180,20 , WHITE);
        DrawText("In fact,If you create life when time moving.It will die immeditely",300,200,20 , WHITE);
        if(time_stop == 1){
            if(!doubleMode){nextGen(mapp);}
            else{nextGen(mapp,mapp2);}
        }
        else{DrawText("Zawarudo!", 450,550 , 50, DARKGREEN);}
        for(int i=1; i<map_width-1; i++){ //接替showMap()
            for(int j=1; j<map_height-1; j++){
                if(mapp[i][j]==1){
                        DrawRectangle(j*cell_size,i*cell_size,cell_size-5,cell_size-5,RED);
                }
            }
        }

        if(IsKeyPressed(KEY_RIGHT)&&user_x+2*user_path <=x) user_x+=user_path;
        if(IsKeyPressed(KEY_LEFT)&&user_x-user_path >=0) user_x-=user_path;
        if(IsKeyPressed(KEY_DOWN)&&user_y + 2*user_path <=y) user_y+=user_path;
        if(IsKeyPressed(KEY_UP)&&user_y - user_path >=0) user_y-=user_path;
        if(IsKeyPressed(KEY_SPACE)) mapp[user_y / cell_size][user_x / cell_size] = 1;
        if(IsKeyPressed(KEY_LEFT_ALT)) mapp[user_y / cell_size][user_x / cell_size] = 0;
        if(IsKeyPressed(KEY_LEFT_CONTROL)) time_stop *=-1;
        if(IsKeyPressed(KEY_Q)){EndDrawing();break;}
        DrawRectangle(user_x,user_y,cell_size-5,cell_size-5,BLUE);
        
        EndDrawing();
    }   
}

