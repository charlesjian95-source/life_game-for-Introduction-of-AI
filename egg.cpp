#include "egg.h"
#include <raylib.h>
#include <string>

using namespace std;

/*======================EggPage設計======================*/
void eggPage(){
    const char* text = "蔡教授那麼帥應該會給我們一百分吧";
    const char* fontPath = "fonts/LXGWWenKaiMonoTC-Regular.ttf";
    const float fontSize = 360.0f;
    const double secondsPerCharacter = 0.5;
    int count = 0;
    int* codepoints = LoadCodepoints(text, &count);
    Font chineseFont = LoadFontEx(fontPath, static_cast<int>(fontSize), codepoints, count);
    const bool fontLoaded = codepoints != nullptr && count > 0 &&
                            IsFontValid(chineseFont) &&
                            chineseFont.texture.id != GetFontDefault().texture.id;
    const double startedAt = GetTime();

    while(!WindowShouldClose()){
        const bool backToMenu = IsKeyPressed(KEY_Q);
        BeginDrawing();
        ClearBackground(BLACK);
        if(fontLoaded){
            const int index = static_cast<int>((GetTime() - startedAt) / secondsPerCharacter) % count;
            int byteCount = 0;
            const char* utf8 = CodepointToUTF8(codepoints[index], &byteCount);
            const string character(utf8, byteCount);
            const Vector2 textSize = MeasureTextEx(chineseFont, character.c_str(), fontSize, 0);
            const Vector2 position = {
                (GetScreenWidth() - textSize.x) / 2.0f,
                (GetScreenHeight() - textSize.y) / 2.0f
            };
            DrawTextEx(chineseFont, character.c_str(), position, fontSize, 0, WHITE);
        }else{
            DrawText("Chinese font could not be loaded:", 100, 100, 30, WHITE);
            DrawText(fontPath, 100, 150, 20, WHITE);
        }
        DrawText("Press Q to return to menu", 40, GetScreenHeight() - 60, 24, BLUE);
        EndDrawing();
        if(backToMenu) break;
    }

    if(fontLoaded) UnloadFont(chineseFont);
    UnloadCodepoints(codepoints);
}
