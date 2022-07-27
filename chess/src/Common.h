#pragma once

#ifdef CHESS_GAME_DLL
#define CHESS_API __declspec(dllexport)
#else
#define CHESS_API __declspec(dllimport)
#endif

