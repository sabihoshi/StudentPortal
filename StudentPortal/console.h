#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

enum ConsoleColor
{
    Black,
    Blue,
    Green,
    Aqua,
    Red,
    Purple,
    Yellow,
    White,
    Gray,
    LightBlue,
    LightGreen,
    LightAqua,
    LightRed,
    LightPurple,
    LightYellow,
    BrightWhite
};
enum class ClearType
{
    Screen,
    Line,
    Up,
    Down,
    Right,
    Left,
    EndOfLine,
    EndOfScreen,
    Color
};
enum class CursorDirection
{
    Up,
    Down,
    Right,
    Left
};
enum class ScrollDirection
{
    Screen,
    Down,
    Up
};
enum class TableCharacter
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    TopEdge,
    BottomEdge,
    LeftEdge,
    RightEdge
};
enum class GroundType
{
    Fore,
    Back
};
struct Color
{
    int R;
    int G;
    int B;
};

void PrintXY(const std::string &string, int x, int y);

std::string Repeat(char character, int repeats);

std::string Repeat(const std::string &string, int repeats);

std::string Center(const std::string &string, int length);

std::string Right(const std::string &string, int length);

std::string Left(const std::string &string, int length);

std::string Reverse(const std::string &string);

void ChangeColor(ConsoleColor color);

void ResetColor();

void SwapColors();

std::string ChangeColor(Color color, GroundType type = GroundType::Fore);

std::string ChangeColor(const std::string &string, Color color, GroundType type = GroundType::Fore);

void SetColor(Color color, GroundType type = GroundType::Fore);

COORD XY(short x, short y);

COORD XY(COORD c);

COORD XY();

COORD MoveCursor(CursorDirection direction, short amount = 1);

void Clear(ClearType type = ClearType::Screen);

COORD WriteLine();

COORD WriteLine(const std::string &string);

void SetConsoleMode(int mode);

void Pause();

void CinReset();

void PrintBorders(const COORD position, const int width, const int height);

void PrintBorders(const COORD position, std::string title, const int width, const int height);

extern bool hasCin;

inline void SetupInput(const std::string& prompt, const COORD position)
{
    XY(position);
    std::cout << prompt << "~> ";
    const auto pos = XY();

    SwapColors();
    std::cout << Repeat(" ", 30);

    XY(pos);
    MoveCursor(CursorDirection::Right);
}

template<typename T>
T Prompt(const std::string &prompt, const COORD position)
{
    while (true)
    {
        SetupInput(prompt, position);
        T input; std::cin >> input;
        hasCin = true;

        ResetColor();
        if (!std::cin)
        {
            CinReset();
            continue;
        }

        XY(position.X, position.Y + 1);
        return input;
    }
}

template<typename T>
T Prompt(const std::string &prompt)
{
    return Prompt<T>(prompt, XY());
}

template<>
inline std::string Prompt<std::string>(const std::string &prompt, const COORD position)
{
    while (true)
    {
        SetupInput(prompt, position);

        std::string input;
        if (hasCin) CinReset();
        std::getline(std::cin, input);

        ResetColor();
        if (!std::cin)
        {
            CinReset();
            continue;
        }

        ResetColor();
        XY(position.X, position.Y + 1);
        return input;
    }
}

template<>
inline std::string Prompt<std::string>(const std::string &prompt)
{
    return Prompt<std::string>(prompt, XY());
}