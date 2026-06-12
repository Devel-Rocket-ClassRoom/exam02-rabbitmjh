#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <format>

enum class ConsoleColor
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

class GameMap;
class GameState;
class MapGenerator;
class Player;

class Renderer
{
private:
    const ConsoleColor BorderColor = ConsoleColor::DARKGRAY;    // 테두리 색깔
    const ConsoleColor PlayerColor = ConsoleColor::YELLOW;  // 플레이어 색깔
    const ConsoleColor NormalColor = ConsoleColor::WHITE;       // 기본 색깔
    const ConsoleColor NormalStair = ConsoleColor::LIGHTGRAY;   // 기본 계단 색깔

	int g_nScreenIndex = 0;
    HANDLE g_hScreen[2] = { nullptr, nullptr };
	HANDLE g_hOriginalScreen = nullptr;

	GameMap* gameMap;
    GameState* gameState;
    MapGenerator* mapGenerator;
    Player* player;
    
    const int ShakeOffsetX = 1;
    const int ShakeOffsetY = 1;
    bool IsShaking = false;

	// 카운트 다운 애니메이션
    const std::vector<std::vector<std::string>> CountDownNum =
    {
        {
            "╔═════════════════════════════════════╗",
            "║                                     ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║                                     ║",
            "║                                     ║",
            "╚═════════════════════════════════════╝"
        },
        {
            "╔═════════════════════════════════════╗",
            "║                                     ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║                          ████       ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║       ████                          ║",
            "║       ████                          ║",
            "║       ████                          ║",
            "║       ████                          ║",
            "║       ████                          ║",
            "║       ████                          ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║                                     ║",
            "║                                     ║",
            "╚═════════════════════════════════════╝"
        },
        {
            "╔═════════════════════════════════════╗",
            "║                                     ║",
            "║                 ████                ║",
            "║                █████                ║",
            "║               ██████                ║",
            "║              ███████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║                 ████                ║",
            "║       ███████████████████████       ║",
            "║       ███████████████████████       ║",
            "║                                     ║",
            "║                                     ║",
            "╚═════════════════════════════════════╝"
        }
    };
	// 타이틀 애니메이션
    const std::vector<std::vector<std::string>> TitleAnimationFrames = {
        // 프레임 1: 오른쪽을 바라보며 대기 (- PRESS 켜짐)
        {
            R"(╔═════════════════════════════════════╗)", // 01
            R"(║                                     ║)", // 02
            R"(║ ___  _  _  ___ ___ _  _ ___ ___ ___ ║)", // 03
            R"(║  |   |\ |  |__  |  |\ |  |   |  |__ ║)", // 04
            R"(║ _|_  | \|  |    |  | \| _|_  |  |__ ║)", // 05
            R"(║                                     ║)", // 06
            R"(║ ____ ___  __  _  ____  ____         ║)", // 07
            R"(║ [__   |  |__| |  |__/  [__          ║)", // 08
            R"(║ ___]  |  |  | |  |  \  ___]         ║)", // 09
            R"(║                                     ║)", // 10
            R"(║                                     ║)", // 11
            R"(║                                     ║)", // 12
            R"(║                                     ║)", // 13
            R"(║                 ███                 ║)", // 14
            R"(║                     O               ║)", // 15
            R"(║                    /|\              ║)", // 16
            R"(║                    / >              ║)", // 17
            R"(║                    ███              ║)", // 18
            R"(║                                     ║)", // 19
            R"(║     - PRESS ANY KEY TO START -      ║)", // 20
            R"(╚═════════════════════════════════════╝)"  // 21
        },

        // 프레임 2: 왼쪽으로 방향 전환 (문구 꺼짐)
        {
            R"(╔═════════════════════════════════════╗)", // 01
            R"(║                                     ║)", // 02
            R"(║ ___  _  _  ___ ___ _  _ ___ ___ ___ ║)", // 03
            R"(║  |   |\ |  |__  |  |\ |  |   |  |__ ║)", // 04
            R"(║ _|_  | \|  |    |  | \| _|_  |  |__ ║)", // 05
            R"(║                                     ║)", // 06
            R"(║ ____ ___  __  _  ____  ____         ║)", // 07
            R"(║ [__   |  |__| |  |__/  [__          ║)", // 08
            R"(║ ___]  |  |  | |  |  \  ___]         ║)", // 09
            R"(║                                     ║)", // 10
            R"(║                                     ║)", // 11
            R"(║                                     ║)", // 12
            R"(║                                     ║)", // 13
            R"(║                    ███              ║)", // 14
            R"(║                  O                  ║)", // 15
            R"(║                 /|\                 ║)", // 16
            R"(║                 < \                 ║)", // 17
            R"(║                 ███                 ║)", // 18
            R"(║                                     ║)", // 19
            R"(║                                     ║)", // 20
            R"(╚═════════════════════════════════════╝)"  // 21
        }
    };
	// 게임 오버 애니메이션
    const std::vector<std::vector<std::string>> GameOverScreen = {
        {
        R"(╔═════════════════════════════════════╗)", // 01
        R"(║                                     ║)", // 02
        R"(║         ____ ____ _  _ ____         ║)", // 03
        R"(║         | __ |__| |\/| |___         ║)", // 04
        R"(║         |__] |  | |  | |___         ║)", // 05
        R"(║                                     ║)", // 06
        R"(║         ____ _  _ ____ ____         ║)", // 07
        R"(║         |  | |  | |___ |__/         ║)", // 08
        R"(║         |__|  \/  |___ |  \         ║)", // 09
        R"(║                                     ║)", // 10
        R"(║                                     ║)", // 11
        R"(║                                     ║)", // 12
        R"(║                                     ║)", // 13
        R"(║                                     ║)", // 14
        R"(║                                     ║)", // 15
        R"(║                                     ║)", // 16
        R"(║                                     ║)", // 17
        R"(║                                     ║)", // 18
        R"(║                                     ║)", // 19
        R"(║                                     ║)", // 20
        R"(╚═════════════════════════════════════╝)"  // 21
        },
        {
        R"(╔═════════════════════════════════════╗)", // 01
        R"(║                                     ║)", // 02
        R"(║         ____ ____ _  _ ____         ║)", // 03
        R"(║         | __ |__| |\/| |___         ║)", // 04
        R"(║         |__] |  | |  | |___         ║)", // 05
        R"(║                                     ║)", // 06
        R"(║         ____ _  _ ____ ____         ║)", // 07
        R"(║         |  | |  | |___ |__/         ║)", // 08
        R"(║         |__|  \/  |___ |  \         ║)", // 09
        R"(║                                     ║)", // 10
        R"(║                                     ║)", // 11
        R"(║                                     ║)", // 12
        R"(║                                     ║)", // 13
        R"(║                                     ║)", // 14
        R"(║                                     ║)", // 15
        R"(║                                     ║)", // 16
        R"(║                                     ║)", // 17
        R"(║                                     ║)", // 18
        R"(║                                     ║)", // 19
        R"(║     - PRESS ANY KEY TO CLOSE  -     ║)", // 20
        R"(╚═════════════════════════════════════╝)"  // 21
        }
    };

    std::vector<std::string> ScoreBoard;    // 스코어보드 저장
public:
    void SetTerminalSizeVT(int width, int height) const; // 콘솔 창 크기 조절 함수
	void ScreenInit(GameMap* gM, GameState* gS, MapGenerator* mG, Player* pl);      // 더블 버퍼링 버퍼 생성
	void ScreenClear() const;     // 더블 버퍼링 화면 초기화
	void ScreenFlipping();  // 더블 버퍼링 화면 전환
	void ScreenRelease();   // 더블 버퍼링 버퍼 해제
	void ScreenPrint(int X, int Y, const std::string& Text, ConsoleColor Color) const;   // 더블 버퍼링 출력값 버퍼에 저장
	void PrintTitle();      // 타이틀 출력
	void PrintCountdown();	// 카운트다운 출력
	void PrintGameOver(const int Level, const int Score);   // 게임오버 출력
    void SaveMapToBuffer();       // 버퍼에 게임 화면 저장
    void SaveBorderToBuffer() const;      // 버퍼에 맨위, 맨아래줄 그리기
    void SaveScoreBoardToBuffer(int y, int x, ConsoleColor Color);  // 버퍼에 스코어보드 그리기
    void SavePlayerToBuffer();      // 버퍼에 플레이어 그리기
    void ClearPlayerPosition(int y, int x); // 버퍼에 플레이어가 있던 자리 공백으로
    void SaveScoreBoard();  // ScoreBoard 벡터에 스코어보드 저장
    ConsoleColor SetTimeTextColor() const;    // 시간 비율로 숫자 텍스트 색깔 지정
    void StartScreenShake();        // 화면 흔들림 시작
    void StopScreenShake();         // 화면 흔들림 해제, 범위 밖으로 벗어난 것들 빈칸으로
};