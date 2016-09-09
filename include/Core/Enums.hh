#ifndef ARCADE_EVENT_HH
# define ARCADE_EVENT_HH

namespace arcade
{
	enum Events
	{
		UP, DOWN, LEFT, RIGHT, CLOSE, LIB_UP, LIB_DOWN, GAME_UP, GAME_DOWN, RESTART_GAME, MENU
	};

	enum Type
	{
		NONE, SBOX, BBOX, SCIRCLE, BCIRCLE, TRIANGLE
	};
}

#endif //ARCADE_EVENT_HH
