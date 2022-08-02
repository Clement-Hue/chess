#pragma once
#include "pch.h"
#include <algorithm>
#include <array>
#include "game/Square.h"
#include "game/Constants.h"

template <typename T, typename Color>
void is_in_board(const Square& square )
{
	EXPECT_EQ(typeid(square.get_piece()->get_color()), typeid(Color)) << "Invalid piece color";
	EXPECT_TRUE( dynamic_cast<T*>(square.get_piece()) ) << "Invalid type of piece";
}


template <int NbIndex,typename T>
void has_squares(const std::array<T, NB_SQUARES>& list, const int (&indexes)[NbIndex])
{
	for (int8_t i = 0; i<NB_SQUARES; ++i)
	{
		if (std::find(std::begin(indexes), std::end(indexes), i) != std::end(indexes))
		{
			EXPECT_TRUE(list[i]) << "square " << +i << " is not in list";
		} else
		{
			EXPECT_FALSE(list[i]) << "square " << +i << " is in list";
		}
	}
}
