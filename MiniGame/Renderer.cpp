#include "Renderer.h"
#include "GameManager.h"
#include <string>
#include <vector>
#include <conio.h>
#include <iostream>
#include <format>

void Renderer::SetTerminalSizeVT(int width, int height)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    // 가상 터미널 처리 모드 활성화 (VT Sequence 사용을 위해 필수)
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // VT Sequence 표준 제어 문자 출력
    // \x1b[8;세로;가로t  -> 터미널 크기를 변경하는 이스케이프 문자열입니다.
    std::cout << "\x1b[8;" << height << ";" << width << "t";
}

void Renderer::ScreenInit(GameMap* gM, GameState* gS, MapGenerator* mG, Player* pl)
{
    gameMap = gM;
    gameState = gS;
    mapGenerator = mG;
    player = pl;

    // 기존 화면 저장
    g_hOriginalScreen = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cci;

    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

    // 커서를 숨긴다.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void Renderer::ScreenClear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', GameManager::FullWidth * GameManager::FullHeight, Coor, &dw);
}

void Renderer::ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = (g_nScreenIndex + 1) % 2;
}


void Renderer::ScreenRelease()
{
    if (g_hOriginalScreen != nullptr)
    {
        SetConsoleActiveScreenBuffer(g_hOriginalScreen);
    }

    if (g_hScreen[0] != nullptr)
    {
        CloseHandle(g_hScreen[0]);
        g_hScreen[0] = nullptr;
    }

    if (g_hScreen[1] != nullptr)
    {
        CloseHandle(g_hScreen[1]);
        g_hScreen[1] = nullptr;
    }
}

void Renderer::ScreenPrint(int X, int Y, const std::string& Text)
{
    DWORD dw;
    COORD Pos = { (SHORT)X, (SHORT)Y };

    WriteConsoleOutputCharacterA(
        g_hScreen[g_nScreenIndex],
        Text.c_str(),
        (DWORD)Text.length(),
        Pos,
        &dw
    );
}

void Renderer::PrintTitle()
{
    while (true)
    {
        for (int i = 0; i < TitleAnimationFrames.size(); i++)
        {
            ScreenClear();

            for (int j = 0; j < TitleAnimationFrames[i].size(); j++)
                ScreenPrint(0, j, TitleAnimationFrames[i][j]);
            Sleep(500);
            ScreenFlipping();
        }
        int Input = NULL;
        Input = _kbhit();
        if (Input != NULL)
            break;
    }
}

void Renderer::PrintCountdown()
{
    for (int i = 0; i < CountDownNum.size(); i++)
    {
        ScreenClear();

        for (int j = 0; j < CountDownNum[i].size(); j++)
            ScreenPrint(0, j, CountDownNum[i][j]);
        Sleep(1000);
        ScreenFlipping();
    }
    Sleep(1000);
}

void Renderer::PrintGameOver(const int Level, const int Score)
{
    const std::string StringScore = "║         SCORE: " + std::format("{:06}", Score) + "               ║";
    const std::string StringLevel = "║         LEVEL: " + std::format("{:02}", Level) + "                   ║";

    while (true)
    {
        for (int i = 0; i < GameOverScreen.size(); i++)
        {
            ScreenClear();

            for (int j = 0; j < GameOverScreen[i].size(); j++)
            {
                if (j == 15)
                    ScreenPrint(0, j, StringScore);
                else if (j == 17)
                    ScreenPrint(0, j, StringLevel);
                else
                    ScreenPrint(0, j, GameOverScreen[i][j]);
            }
            Sleep(500);
            ScreenFlipping();
        }

        int Input = NULL;
        Input = _kbhit();
        if (Input != NULL)
            break;
    }
}

void Renderer::SaveMapToBuffer()
{
    int FullWidthMinusOne = GameManager::FullWidth - 1;
    int WidthPlusOne = GameManager::Width + 1;

    SaveScoreBoard();
    SaveBorderToBuffer();

    for (int i = 0; i < GameManager::Height; i++)
    {
        bool IsEdge = false;
        for (int j = 0; j < GameManager::FullWidth; j++)
        {
            IsEdge = (j == 0 || j == WidthPlusOne || j == FullWidthMinusOne) ? true : false;

            if (IsEdge) // 테두리
            {
                ScreenPrint(j, i + 1, "║");
            }
            else if (j <= GameManager::Width)
            {
                // 인게임
                char Tile = gameMap->GetGameMap()[GameManager::Height - i - 1][j];
                if (Tile == GameManager::ABlock[0])
                {
                    // 계단
                    ScreenPrint(j, i + 1, GameManager::Block);
                    j += 2;
                }
                else
                {
                    std::string tmp(1, Tile);
                    ScreenPrint(j, i + 1, tmp);
                }
            }
            else if (j > GameManager::Width)
            {
                // 스코어보드
                SaveScoreBoardToBuffer(j, i);
            }
            else
            {
                ScreenPrint(j, i + 1, &GameManager::Blank);
            }
        }
    }
}

void Renderer::SaveBorderToBuffer()
{
    int WidthPlusOne = GameManager::Width + 1;

    std::string Header;
    Header += "╔";
    ScreenPrint(0, 0, "╔");
    for (int i = 1; i < GameManager::FullWidth - 1; i++)
    {
        ScreenPrint(i, 0, (i != WidthPlusOne ? "═" : "╦"));
        Header += (i != WidthPlusOne ? "═" : "╦");
    }
    ScreenPrint(GameManager::FullWidth - 1, 0, "╗");
    Header += "╗";

    std::string Footer;
    Footer += "╚";
    ScreenPrint(0, GameManager::FullHeight - 1, "╚");
    for (int i = 1; i < GameManager::FullWidth - 1; i++)
    {
        ScreenPrint(i, GameManager::FullHeight - 1, (i != WidthPlusOne ? "═" : "╩"));
        Footer += (i != WidthPlusOne ? "═" : "╩");
    }
    ScreenPrint(GameManager::FullWidth - 1, GameManager::FullHeight - 1, "╝");
    Footer += "╝";
}

void Renderer::SaveScoreBoardToBuffer(int x, int y)
{
    std::string tmp(1, ScoreBoard[GameManager::Height - y - 1][x - GameManager::Width - 2]);
    ScreenPrint(x, y + 1, tmp);
}

void Renderer::SavePlayerToBuffer()
{
    gameMap->SetGameMap(player->GetPlayerY() + 2, player->GetPlayerX(), 'O');
    gameMap->SetGameMap(player->GetPlayerY() + 1, player->GetPlayerX() - 1, '/');
    gameMap->SetGameMap(player->GetPlayerY() + 1, player->GetPlayerX(), '|');
    gameMap->SetGameMap(player->GetPlayerY() + 1, player->GetPlayerX() + 1, '\\');
    if (player->GetPlayerDir() == Player::Dir::Idle)
    {
        gameMap->SetGameMap(player->GetPlayerY(), player->GetPlayerX() - 1, '/');
        gameMap->SetGameMap(player->GetPlayerY(), player->GetPlayerX() + 1, '\\');
    }
    else if (player->GetPlayerDir() == Player::Dir::Left)
    {
        gameMap->SetGameMap(player->GetPlayerY(), player->GetPlayerX() - 1, '<');
        gameMap->SetGameMap(player->GetPlayerY(), player->GetPlayerX() + 1, '\\');
    }
    else if (player->GetPlayerDir() == Player::Dir::Right)
    {
        gameMap->SetGameMap(player->GetPlayerY(), player->GetPlayerX() - 1, '/');
        gameMap->SetGameMap(player->GetPlayerY(), player->GetPlayerX() + 1, '>');
    }
}

void Renderer::ClearPlayerPosition(int y, int x)
{
    for (int i = y; i <= y + 2; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            gameMap->SetGameMap(i, j, GameManager::Blank);
        }
    }
}

void Renderer::SaveScoreBoard()
{
    ScoreBoard.clear();
    std::string StringScore = "SCORE: " + std::format("{:06}", gameState->Score);
    std::string StringLevel = "LEVEL: " + std::format("{:02}", gameState->Level);
    while (StringScore.size() < GameManager::ScoreBoardWidth + 2)
        StringScore += GameManager::Blank;
    while (StringLevel.size() < GameManager::ScoreBoardWidth + 2)
        StringLevel += GameManager::Blank;

    ScoreBoard.push_back(StringScore);
    ScoreBoard.push_back(StringLevel);
    int tmp = GameManager::Height - 3;
    for (int i = 0; i < tmp; i++)
    {
        std::string s;
        for (int j = 0; j < GameManager::ScoreBoardWidth; j++)
            s += GameManager::Blank;

        ScoreBoard.push_back(s);
    }

    std::string StringTime = "TIME: " + std::format("{:.2f}", gameState->CurrentTime);
    while (StringTime.size() < GameManager::ScoreBoardWidth + 2)
        StringTime += GameManager::Blank;
    ScoreBoard.push_back(StringTime);
}

