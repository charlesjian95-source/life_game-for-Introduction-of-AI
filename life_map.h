#pragma once
#include "config.h"
#include <string>
#include <vector>

void initMode(int mapp[][map_width], int mode_ID);
void initMode(int mapp[][map_width],int mapp2[][map_width] , int mode_ID);
void loadMap(std::vector<std::string> template_map, int mapp[][map_width]);
void loadMap(std::vector<std::string> template_map, int mapp[][map_width],int mapp2p[][map_width]);
void nextGen(int mapp[][map_width]);
void nextGen(int mapp[][map_width],int mapp2[][map_width]);
void showMap(int mapp[][map_width]); // 終端機版本（已停止使用）
void buildBound(int mapp[][map_width]); // 原本的邊界設定（已停止使用）
