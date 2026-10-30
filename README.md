# 康威生命遊戲｜Conway's Game of Life

使用 **C++17** 與 [raylib](https://www.raylib.com/) 製作的康威生命遊戲，提供圖形選單、11 種初始圖案，以及暫停和手動放置細胞的功能。本專案為人工智慧導論課程的實作練習。

## 下載與執行

**[下載最新版 Windows 64 位元遊戲包](https://github.com/charlesjian95-source/life_game-for-Introduction-of-AI/releases/latest/download/Conway-Windows-x64.zip)** · [查看 Release](https://github.com/charlesjian95-source/life_game-for-Introduction-of-AI/releases/latest)

1. 下載 `Conway-Windows-x64.zip`。
2. 對 ZIP 按右鍵，選擇「全部解壓縮」。
3. 開啟解壓縮後的 `Conway` 資料夾。
4. 執行 `life_game.exe`。

遊玩不需要安裝 VS Code、MSYS2 或編譯器。請保留整個資料夾的內容：

```text
Conway/
├── life_game.exe
├── libraylib.dll
├── glfw3.dll
├── libgcc_s_seh-1.dll
├── libstdc++-6.dll
├── libwinpthread-1.dll
├── README.txt
└── licenses/
```

**請下載 Release 的完整遊戲包，不要只下載儲存庫裡的 `.exe`，也不要直接在 ZIP 裡執行。** EXE 和 DLL 必須放在同一個資料夾。分享給朋友時，請傳整個 ZIP 或上方的下載連結。

## 操作方式

使用前請將輸入法切換到 **英數模式（英／ENG）**，避免 SPACE 被中文輸入法攔截。

### 選單

| 按鍵 | 功能 |
| --- | --- |
| ↑／↓ | 移動箭頭、選擇模式 |
| SPACE | 進入選取的模式；選取 QUIT 時結束程式 |
| ESC／視窗右上角 × | 結束程式 |

### 遊戲畫面

| 按鍵 | 功能 |
| --- | --- |
| ↑／↓／←／→ | 移動藍色游標，一次一格 |
| 左 Ctrl | 暫停／繼續演化 |
| SPACE | 將游標所在的格子設為活細胞 |
| Q | 返回選單 |
| ESC／視窗右上角 × | 結束程式 |

建議先按左 Ctrl 暫停，再放置細胞並移開藍色游標觀察。演化進行時也能放細胞，但孤立細胞通常會在下一代死亡；藍色游標也會遮住同一位置的白色細胞。

重新選擇模式會清空地圖並載入新的圖案；目前游標位置與暫停狀態會保留。

## 內建模式

| 編號 | 模式 | 類型與特徵 |
| --- | --- | --- |
| 1 | Block | 靜態圖案 |
| 2 | Beehive | 靜態圖案 |
| 3 | Blinker | 週期 2 的振盪器 |
| 4 | Toad | 週期 2 的振盪器 |
| 5 | Beacon | 週期 2 的振盪器 |
| 6 | Pulsar | 週期 3 的振盪器；選單顯示為 Pulse |
| 7 | Glider | 滑翔機 |
| 8 | LWSS | 輕型太空船 |
| 9 | R-pentomino | 長時間演化的初始圖案 |
| 10 | Acorn | 長時間演化的初始圖案 |
| 11 | Gosper Glider Gun | 持續產生滑翔機的圖案 |

## 生命遊戲規則

每一格只有存活與死亡兩種狀態，以周圍八格作為鄰居。所有細胞根據同一代的狀態，一起計算下一代：

- 活細胞有 2 或 3 個活鄰居時繼續存活。
- 活細胞少於 2 個或多於 3 個活鄰居時死亡。
- 死細胞恰好有 3 個活鄰居時誕生。

這套規則也記為 **B3/S23**。圖案碰到邊界不會自動反彈，而是依鄰居狀態繼續演化。

## 開發與編譯

目前的 Windows 建置使用 MSYS2 UCRT64、GCC 與 raylib。原始碼位於 [`life_game.cpp`](life_game.cpp)。

### 安裝依賴

安裝 [MSYS2](https://www.msys2.org/) 後，開啟 **MSYS2 UCRT64** 終端機，更新套件：

```bash
pacman -Syu
```

若更新過程要求關閉終端機，依指示關閉，再重新開啟 UCRT64 繼續更新。完成後安裝編譯器和 [raylib UCRT64 套件](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-raylib)：

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib
```

### 編譯程式

在 UCRT64 終端機切換至專案根目錄，執行：

```bash
g++ -std=c++17 -O2 life_game.cpp -o life_game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
./life_game.exe
```

若使用 VS Code，請讓 C++ 擴充功能使用 UCRT64 的 `g++.exe`，並在建置工作或 Code Runner 的編譯指令中加入上述連結參數。MSYS2 安裝於預設位置時，編譯器路徑為 `C:/msys64/ucrt64/bin/g++.exe`。

自行編譯的 EXE 若要帶到其他電腦，也需要附上相依 DLL；直接使用 Release 遊戲包即可取得已整理好的執行檔與 DLL。

## 常見問題

### 找不到 libraylib.dll 或 libgcc_s_seh-1.dll

請重新下載上方的 Release 遊戲包並完整解壓縮，確認五個 DLL 與 `life_game.exe` 位於同一層。儲存庫的「Code → Download ZIP」是原始碼壓縮檔，不是完整遊戲包。

### 按 SPACE 沒有反應

先點進遊戲視窗，再將輸入法切換成英數模式（英／ENG）。中文輸入法可能先攔截空白鍵，讓遊戲收不到輸入。

### 放了細胞卻看不到

先暫停演化，再放置細胞並移開藍色游標。孤立細胞在持續演化時會死亡，而游標會蓋住所在位置的細胞。

### 長壽模式很快就不再明顯變化

目前地圖為 **60 × 60**，邊界會改變圖案的演化結果。因此 R-pentomino、Acorn 等模式不一定呈現無限平面上的完整演化過程。

## 目前限制

- 地圖固定為 60 × 60，每格 20 像素，視窗大小為 1200 × 1200。
- 地圖不採用左右、上下相接的環繞邊界。
- 最外圈（列或行索引為 0、59）不會繪製或更新，但目前游標仍能到達並放入細胞。請在內部格子操作，避免產生看不見且持續影響鄰居的邊界細胞。
- 新增模板時，`loadMap()` 尚未驗證空模板、每列長度或過大尺寸。請使用大小一致的字串，並將圖案寬、高限制在 58 格以內，保留外圈。

## 使用的函式庫

- [raylib](https://www.raylib.com/)：視窗、鍵盤輸入與圖形繪製。
- Windows Release 附有 raylib、GLFW、GCC 執行所需的 DLL；第三方授權文字位於遊戲包的 `licenses/` 資料夾。
