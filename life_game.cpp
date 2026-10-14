#include<iostream>
#include<cstdlib>
#include <thread>
#include <chrono>
//#include <windows.h>
using namespace std;

const int map_width = 100;
const int map_height = 100;

void showMap(int mapp[][map_width]);//展示當前的狀況
void nextGen(int mapp[][map_width]);//根據康威規則進行迭代
void buildBound(int mapp[][map_width]); //設置邊界 美觀用途
void initMode(int mapp[][map_width]); //初始化地圖 提供各模式選擇

int main()
{
    int mapp[map_height][map_width] = {};
    //SetConsoleOutputCP(CP_UTF8); //編碼設置為UTF-8 確保邊界符號可以正常顯示(應該可以)
/*======================設置初始條件======================*/
    /*
    mapp[10][11] = 1;
    mapp[10][14] = 1;

    mapp[11][10] = 1;

    mapp[12][10] = 1;
    mapp[12][14] = 1;

    mapp[13][10] = 1;
    mapp[13][11] = 1;
    mapp[13][12] = 1;
    mapp[13][13] = 1;
    */
    initMode(mapp);

/*======================函數開始執行======================*/
    buildBound(mapp);
    while(true){
        nextGen(mapp);
        showMap(mapp);
        this_thread::sleep_for(chrono::milliseconds(500));
        //system("cls");
    }
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
    case 1:
        mapp[48][48] = 1;
        mapp[48][49] = 1;
        mapp[49][49] = 1;
        mapp[49][48] = 1;
        break;
    case 2:
        mapp[48][49] = 1;
        mapp[48][50] = 1;
        mapp[49][48] = 1;
        mapp[49][51] = 1;
        mapp[50][49] = 1;
        mapp[50][50] = 1;
        break;
    case 3:
        mapp[48][48] = 1;
        mapp[48][49] = 1;
        mapp[48][50] = 1;
        break;
    case 4:
        mapp[48][49] = 1;
        mapp[48][50] = 1;
        mapp[48][51] = 1;
        mapp[49][48] = 1;
        mapp[49][49] = 1;
        mapp[49][50] = 1;
        break;
    case 5:
        mapp[48][48] = 1;
        mapp[48][49] = 1;
        mapp[49][48] = 1;
        mapp[49][49] = 1;
        mapp[50][50] = 1;
        mapp[50][51] = 1;
        mapp[51][50] = 1;
        mapp[51][51] = 1;
        break;
    case 6:
        mapp[48][50] = 1;
        mapp[48][51] = 1;
        mapp[48][52] = 1;
        mapp[48][56] = 1;
        mapp[48][57] = 1;
        mapp[48][58] = 1;

        mapp[50][48] = 1;
        mapp[50][53] = 1;
        mapp[50][55] = 1;
        mapp[50][60] = 1;

        mapp[51][48] = 1;
        mapp[51][53] = 1;
        mapp[51][55] = 1;
        mapp[51][60] = 1;

        mapp[52][48] = 1;
        mapp[52][53] = 1;
        mapp[52][55] = 1;
        mapp[52][60] = 1;

        mapp[53][50] = 1;
        mapp[53][51] = 1;
        mapp[53][52] = 1;
        mapp[53][56] = 1;
        mapp[53][57] = 1;
        mapp[53][58] = 1;

        mapp[55][50] = 1;
        mapp[55][51] = 1;
        mapp[55][52] = 1;
        mapp[55][56] = 1;
        mapp[55][57] = 1;
        mapp[55][58] = 1;

        mapp[56][48] = 1;
        mapp[56][53] = 1;
        mapp[56][55] = 1;
        mapp[56][60] = 1;

        mapp[56][48] = 1;
        mapp[56][53] = 1;
        mapp[56][55] = 1;
        mapp[56][60] = 1;

        mapp[56][48] = 1;
        mapp[56][53] = 1;
        mapp[56][55] = 1;
        mapp[56][60] = 1;

        mapp[58][50] = 1;
        mapp[58][51] = 1;
        mapp[58][52] = 1;
        mapp[58][56] = 1;
        mapp[58][57] = 1;
        mapp[58][58] = 1;
        break;
    case 7:
        mapp[40][41] = 1;
        mapp[41][42] = 1;
        mapp[42][40] = 1;
        mapp[42][41] = 1;
        mapp[42][42] = 1;
        break;
    case 8:
        mapp[45][66] = 1;
        mapp[45][69] = 1;
        mapp[46][65] = 1;
        mapp[47][65] = 1;
        mapp[47][69] = 1;
        mapp[48][65] = 1;
        mapp[48][66] = 1;
        mapp[48][67] = 1;
        mapp[48][68] = 1;
        break;
    case 9:
        mapp[48][49] = 1;
        mapp[48][50] = 1;
        mapp[49][48] = 1;
        mapp[49][49] = 1;
        mapp[50][49] = 1;
        break;
    case 10:
        mapp[48][46] = 1;
        mapp[49][48] = 1;
        mapp[50][45] = 1;
        mapp[50][46] = 1;
        mapp[50][49] = 1;
        mapp[50][50] = 1;
        mapp[50][51] = 1;
        break;
    case 11:
        break;
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