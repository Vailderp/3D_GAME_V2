#pragma once
namespace LAN
{
	class player_was
	{
	public:
		bool sended_my_num = false;
		bool getted_my_num = false;
	};
	class new_player_num
	{
	public:
		unsigned __int8 num;
	};
	struct PLAYER
	{
	public:
		unsigned __int8 num;
		float angle;
		float x;
		float y;
	};
	class LANtime
	{
	public:
		unsigned long long Last = 0;
		unsigned long long This = 0;
	};
}
