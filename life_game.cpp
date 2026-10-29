#include<iostream>
#include<cstdlib>
#include<thread>
#include<chrono>
#include<vector>
#include<raylib.h>
#include<string>
using namespace std;

const int map_width = 60;
const int map_height = 60;

void showMap(int mapp[][map_width]);//展示當前的狀況(已停止使用)
void nextGen(int mapp[][map_width]);//根據康威規則進行迭代
void buildBound(int mapp[][map_width]); //設置邊界 美觀用途(已停止使用)
void initMode(int mapp[][map_width]); //初始化地圖 提供各模式選擇
void loadMap(vector<string>template_map , int mapp[][map_width]);

int main()
{
    ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int mapp[map_height][map_width] = {};
    
/*======================設置初始條件======================*/
    initMode(mapp);
    const int cell_size = 20;
    const int x = map_width*cell_size;
    const int y = map_height*cell_size;
    int time_stop = 1;
    int user_x = 40 , user_y = 40;
    int user_path = 20;
    SetTargetFPS(20);//設定frame數 太大的話會迭代太快
    InitWindow(x,y,"conway");
/*======================函數開始執行======================*/
    //buildBound(mapp);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        
        if(time_stop == 1){nextGen(mapp);}
        else{DrawText("Zawarudo!", 100, 100, 50, DARKGREEN);}
        for(int i=1; i<map_width-1; i++){ //接替showMap()
            for(int j=1; j<map_height-1; j++){
                if(mapp[i][j]==1){
                    DrawRectangle(j*cell_size,i*cell_size,15,15,WHITE);
                }
            }
        }

        if(IsKeyPressed(KEY_RIGHT)) user_x+=user_path;
        if(IsKeyPressed(KEY_LEFT)) user_x-=user_path;
        if(IsKeyPressed(KEY_DOWN)) user_y+=user_path;
        if(IsKeyPressed(KEY_UP)) user_y-=user_path;
        if(IsKeyPressed(KEY_SPACE)) mapp[user_y / cell_size][user_x / cell_size] = 1;
        if(IsKeyPressed(KEY_LEFT_CONTROL)) time_stop *=-1;
        DrawRectangle(user_x,user_y,15,15,BLUE);
        EndDrawing();
    }
    CloseWindow();
}
/*======================主程式結束======================*/

/*======================初始化地圖======================*/
void initMode(int mapp[][map_width]){
    int mode_ID;
    cout << "input put mode you want";
    cout <<"=====Still Life靜態模式=====\n";
    cout << "1.Block\n" << "2.Beehive\n";
    cout <<"=====Oscillator週期震盪模式=====\n";
    cout<< "3.Blinker\n" << "4.Toad\n" << "5.Beacon\n"<< "6.Pulse\n"; 
    cout<<"=====Spaceship滑翔機=====\n";
    cout<< "7.Glider\n" << "8.LWSS\n"; 
    cout <<"=====Methuselah長壽模式=====\n";;
    cout<< "9.R-pentomino\n" << "10.Acorn\n";
    cout <<"=====Gun產生器=====\n";
    cout << "11.Gosper Glider Gun\n";
    cout << ':';
    cin >> mode_ID;

    switch(mode_ID){
    case 1: { // Block
        vector<string> template_map = {
            "OO",
            "OO"
        };
        loadMap(template_map, mapp);
        break;
    }
    case 2: { // Beehive
        vector<string> template_map = {
            ".OO.",
            "O..O",
            ".OO."
        };
        loadMap(template_map, mapp);
        break;
    }
    case 3: { // Blinker
        vector<string> template_map = {
            "OOO"
        };
        loadMap(template_map, mapp);
        break;
    }
    case 4: { // Toad
        vector<string> template_map = {
            ".OOO",
            "OOO."
        };
        loadMap(template_map, mapp);
        break;
    }
    case 5: { // Beacon
        vector<string> template_map = {
            "OO..",
            "OO..",
            "..OO",
            "..OO"
        };
        loadMap(template_map, mapp);
        break;
    }
    case 6: { // Pulsar
        vector<string> template_map = {
            "..OOO...OOO..",
            ".............",
            "O....O.O....O",
            "O....O.O....O",
            "O....O.O....O",
            "..OOO...OOO..",
            ".............",
            "..OOO...OOO..",
            "O....O.O....O",
            "O....O.O....O",
            "O....O.O....O",
            ".............",
            "..OOO...OOO.."
        };
        loadMap(template_map, mapp);
        break;
    }
    case 7: { // Glider
        vector<string> template_map = {
            ".O.",
            "..O",
            "OOO"
        };
        loadMap(template_map, mapp);
        break;
    }
    case 8: { // LWSS
        vector<string> template_map = {
            ".O..O",
            "O....",
            "O...O",
            "OOOO."
        };
        loadMap(template_map, mapp);
        break;
    }
    case 9: { // R-pentomino
        vector<string> template_map = {
            ".OO",
            "OO.",
            ".O."
        };
        loadMap(template_map, mapp);
        break;
    }
    case 10: { // Acorn
        vector<string> template_map = {
            ".O.....",
            "...O...",
            "OO..OOO"
        };
        loadMap(template_map, mapp);
        break;
    }
    case 11: { // Gosper Glider Gun
        vector<string> template_map = {
            "........................O...........",
            "......................O.O...........",
            "............OO......OO............OO",
            "...........O...O....OO............OO",
            "OO........O.....O...OO..............",
            "OO........O...O.OO....O.O...........",
            "..........O.....O.......O...........",
            "...........O...O....................",
            "............OO......................"
        };
        loadMap(template_map, mapp);
        break;
    }
    }
    
}

/*======================迭代函數======================*/
void nextGen(int mapp[][map_width])
{
    int x[8] = {-1,0,1,1,1,0,-1,-1};
    int y[8] = {1,1,1,0,-1,-1,-1,0};

    int newMapp[map_height][map_width];

    for(int i =0; i<map_height; i++){
        for(int j=0; j<map_width; j++){
            newMapp[i][j] = mapp[i][j];
        }
    }

    for(int i = 1; i< map_height - 1; i++)
    {
        for(int j=1; j<map_width - 1;j++)
        {
            int exist_num = 0;
            for(int k=0; k<8; k++ )
            {
                if(mapp[i+x[k]][j+y[k]] == 1){
                    exist_num ++ ;
                }
                
                

            }
            if(mapp[i][j] == 0 &&  exist_num == 3)
                newMapp[i][j] = 1;
            else if(mapp[i][j] == 0)
                continue;
            if(exist_num < 2)
                newMapp[i][j] = 0;
            else if(exist_num == 2 || exist_num == 3)
                newMapp[i][j] = 1;
            else if(exist_num > 3)
                newMapp[i][j] = 0;
        }
    }

    for(int i =0; i<map_height; i++){
        for(int j=0; j<map_width; j++){
            mapp[i][j] = newMapp[i][j];
        }
    }
}


/*======================輸出地圖======================*/
void showMap(int mapp[][map_width])
{
    cout << "┌";
    for(int i=1; i< map_width-1; i++){cout <<"--";}
    cout << "┐" << '\n';
    for(int i = 1; i< map_height-1; i++)
    {   
        cout << "|";
        for(int j=1; j<map_width-1;j++)
        {
            if(mapp[i][j] == 1){
                cout << "██";
            }
            else{
                cout << "  ";
            }
        }
        cout << "|";
        cout << '\n';
    }
    cout << "└";
    for(int i=1; i< map_width-1; i++){cout << "--";}
    cout << "┘\n";
}
/*======================設置邊界======================*/
void buildBound(int mapp[][map_width]){
    for(int i=1; i<map_width-1; i++){ mapp[0][i] = -1; mapp[map_height-1][i] = -1;}
    for(int i=1; i<map_height-1; i++){ mapp[i][0] = -1; mapp[i][map_height-1] = -1;}
    mapp[0][0] = -1; 
    mapp[map_height-1][map_width-1] = -1;
    mapp[0][map_width-1] = -1;
    mapp[map_height-1][0] = -1;
}

/*======================初始化地圖(載入模板)======================*/
void loadMap(vector<string>template_map,int mapp[][map_width]){
    int height = template_map.size();
    int width = template_map[0].size();
    int h_begin = (map_height - height)/2;
    int w_begin = (map_width - width)/2;
    for(int i =0; i<height; i++){
        for(int j=0; j<width; j++){
            if(template_map[i][j] == 'O'){
                mapp[h_begin + i][w_begin + j] = 1;
            }
            
        }
    }
}