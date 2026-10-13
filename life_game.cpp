#include<iostream>
#include<cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

const int map_width = 30;
const int map_height = 30;

void showMap(int mapp[][map_width]);//展示當前的狀況
void nextGen(int mapp[][map_width]);//根據康威規則進行迭代
void buildBound(int mapp[][map_width]); //設置邊界 美觀用途

int main()
{
    int mapp[map_height][map_width] = {};
    SetConsoleOutputCP(CP_UTF8); //編碼設置為UTF-8 確保邊界符號可以正常顯示(應該可以)
/*======================設置初始條件======================*/

    mapp[10][11] = 1;
    mapp[10][14] = 1;

    mapp[11][10] = 1;

    mapp[12][10] = 1;
    mapp[12][14] = 1;

    mapp[13][10] = 1;
    mapp[13][11] = 1;
    mapp[13][12] = 1;
    mapp[13][13] = 1;

/*======================函數開始執行======================*/
    buildBound(mapp);
    while(true){
        nextGen(mapp);
        showMap(mapp);
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
    }
}
/*======================主程式結束======================*/


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
    cout << "┘";
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