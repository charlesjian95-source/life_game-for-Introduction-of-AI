#pragma once

inline constexpr int map_width = 60;
inline constexpr int map_height = 60;
inline constexpr int cell_size = 20; //細胞大小（每格像素）
inline constexpr int x = map_width * cell_size; //地圖寬度
inline constexpr int y = map_height * cell_size; //地圖高度

extern int user_path;

enum class Page{ //使用的page
    Menu_1,
    Menu_2,
    Game_1,
    Egg
};
