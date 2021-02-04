#pragma once
#include "game.h"
#include <SFML/Graphics.hpp>
#include <vector>
typedef vector<vector<unsigned __int8>> __matrix8;
namespace engine
{
	class FLOATPOINT
	{
		public:
			float x;
			float y;
	};
	class INTPOINT
	{
	public:
		int x;
		int y;
	};
	class SHORTPOINT 
	{
	public:
		short x;
		short y;
	};
	class __INT16POINT
	{
	public:
		unsigned __int16 x;
		unsigned __int16 y;
	};
	class __INT8POINT
	{
		public:
			unsigned __int8 x;
			unsigned __int8 y;
	};
	class FLOATBUFFER
	{
		private:
			unsigned __int32 _time = 0;
		public:
			map<int, FLOATPOINT> points;
			void add_point(float x, float y)
			{
				points[_time].x = x;
				points[_time].y = y;
				_time++;
			}
			bool exist_point(float x, float y)
			{
				for (size_t i = 0; i < points.size(); i++)
				{
					if (points[i].x == x && points[i].x == y)
					{
						return true;
					}
				}
				return false;
			}
			void clearRAM()
			{
				for (size_t i = 0; i < points.size(); i++)
				{
					points.erase(i);
				}
			}
	};
	class INTBUFFER
	{
	private:
		unsigned int _time = 0;
	public:
		map<int, INTPOINT> points;
		void add_point(int x, int y)
		{
			points[_time].x = x;
			points[_time].y = y;
			_time++;
		}
		bool exist_point(int x, int y)
		{
			for (size_t i = 0; i < points.size(); i++)
			{
				if (points[i].x == x && points[i].x == y)
				{
					return true;
				}
			}
			return false;
		}
		void clearRAM()
		{
			for (size_t i = 0; i < points.size(); i++)
			{
				points.erase(i);
			}
		}
	};
	namespace utils
	{
		namespace sorts
		{
			short* short_bubble_increase(short* n, short len)
			{
				for (unsigned int i = 0; i < len; i++)
				{
					for (unsigned int l = 0; l < len; l++)
					{
						if (n[l - 1] > n[l])
						{ 
							swap(n[l - 1], n[l]);
						}
					}
				}
				return n;
			}
			float* float_bubble_increase(float* n, float len)
			{
				for (unsigned int i = 0; i < len; i++)
				{
					for (unsigned int l = 0; l < len; l++)
					{
						if (n[l - 1] > n[l])
						{
							swap(n[l - 1], n[l]);
						}
					}
				}
				return n;
			}
		}
		__matrix8 create__matrix8(unsigned __int8 y, unsigned __int8 x)
		{
			return __matrix8(y, vector<unsigned __int8>(x, 0));
		}
		inline unsigned int get_average_value(unsigned int allsum, unsigned __int16 len)
		{
			return round(allsum / len);
		}
		inline float FloatDeNULL(float n)
		{
			return n + 0.000000001;
		}
		namespace buttons
		{
			inline bool ClsButton(unsigned int mouseX, unsigned int mouseY, unsigned int buttonX, unsigned int buttonY, unsigned int buttonW, unsigned int buttonH)
			{
				if (mouseX > buttonX)
				{
					if (mouseX < buttonX + buttonW)
					{
						if (mouseY > buttonY)
						{
							if (mouseY < buttonY + buttonH)
							{
								return true;
							}
						}
					}
				}
				return false;
			}
		}
	}
	namespace pseudoRandomWorld
	{
		vector<vector<unsigned __int8>> gen(int seed)
		{
			vector<vector<unsigned __int8>> MATRIX(game::world::size, vector<unsigned __int8>(game::world::size, 0));
			if (to_string(seed).length() == game::world::seed_len)
			{
				string str_seed = to_string(seed);
				short buffer_seed[game::world::seed_len]{};
				for (size_t i = 0; i < game::world::seed_len; i++)
				{
					buffer_seed[i] = (str_seed[i] - '0');
					buffer_seed[i] += 2;
				}
				int x = 0;
				int y = 0;
				unsigned __int8 time = 0;
				for (size_t i = 0; i < game::world::seed_len; i++)
				{
					for (size_t l = 0; l < game::world::seed_len; l++)
					{
						for (size_t o = 0; o < pow(game::world::size, 2) / pow(game::world::seed_len, 2); o++)
						{
							if (o % 2 == 0)
							{
								if (x % (buffer_seed[i] + buffer_seed[l]) == 0)
								{
									MATRIX[y][x] = 1;
								}
								else if ((buffer_seed[i]) % (buffer_seed[l] + x) == 0)
								{
									MATRIX[y][x] = 1;
								}
							}
							else if (o % 2 != 0)
							{
								if ((x + buffer_seed[i]) % (buffer_seed[l]) == 0)
								{
									MATRIX[y][x] = 1;
								}
								else if ((y + buffer_seed[i]) % (buffer_seed[l] + x) == 0)
								{
									MATRIX[y][x] = 1;
								}
							}
							else
							{
								if (x % (buffer_seed[i] + buffer_seed[l]) == 0)
								{
									MATRIX[y][x] = 1;
								}
							}
							x++;
							if (time >= game::world::size)
							{
								x = 0;
								y++;
							}
							time++;
						}
					}
				}
				for (size_t y = 0; y < game::world::size; y++)
				{
					for (size_t x = 0; x < game::world::size; x++)
					{
						if (y == 0)
						{
							MATRIX[y][x] = 1;
						}
						else if (y == static_cast<unsigned long long>(game::world::size) - 1)
						{
							MATRIX[y][x] = 1;
						}
						else if (x == 0)
						{
							MATRIX[y][x] = 1;
						}
						else if (x == static_cast<unsigned long long>(game::world::size) - 1)
						{
							MATRIX[y][x] = 1;
						}
					}
				}
				return MATRIX;
			}
			else
			{
				for (size_t y = 0; y < game::world::size; y++)
				{
					for (size_t x = 0; x < game::world::size; x++)
					{
						if (y == 0)
						{
							MATRIX[y][x] = 1;
						}
						else if (y == static_cast<unsigned long long>(game::world::size) - 1)
						{
							MATRIX[y][x] = 1;
						}
						else if (x == 0)
						{
							MATRIX[y][x] = 1;
						}
						else if (x == static_cast<unsigned long long>(game::world::size) - 1)
						{
							MATRIX[y][x] = 1;
						}
					}
				}
				return MATRIX;
			}
			return MATRIX;
		}
		FLOATPOINT searh_spawn_point(vector<vector<unsigned __int8>> MATRIX)
		{
			for (int x = 0; x < game::world::size; x++)
			{
				for (int y = 0; y < game::world::size; y++)
				{
					if (MATRIX[y][x] == 0)
					{
						return FLOATPOINT
						(
							{
								static_cast<float>(y * game::world::wall_size + (game::world::wall_size / 2)),
								static_cast<float>(x * game::world::wall_size + (game::world::wall_size / 2))
							}
						);
					}
				}
			}
			return FLOATPOINT
			(
				{
					0,
					0
				}
			);
		}
	}
	namespace maze
	{
		namespace ___utils
		{
			/*DUALPOINT*/
			class DUALINTPOINT 
			{
			public:
				INTPOINT P1;
				INTPOINT P2;
			};
			/*DIRECTION SEARCH*/
			class DIRPOINT
			{
			public:
				INTPOINT pos;
				char dir;
				bool fnd = false;
			};
			DIRPOINT search_dirpoint(INTBUFFER _walls_buff, string structure)
			{
				int __sdpY(0);
				int __sdpX(0);
				DIRPOINT dirp;
				for (size_t i = 0; i < _walls_buff.points.size(); i++)
				{
					//0
					__sdpY = _walls_buff.points[i].y - 1;
					__sdpX = _walls_buff.points[i].x;
					if (__sdpY > 0)
					{
						if (__sdpY < game::world::size - 1)
						{
							if (__sdpX > 0)
							{
								if (__sdpX < game::world::size - 1)
								{
									if (structure
										[
											static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>
											(__sdpY)*game::world::size + __sdpX
										] != 'z')
									{
										if (structure
											[
												(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY) - 1)
												* game::world::size + __sdpX
											] != 'z')
										{
											if (structure
												[
													(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY))
													* game::world::size + (static_cast<unsigned long long>(__sdpX) + 1)
												] != 'z')
											{
												if (structure
													[
														(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY))
														* game::world::size + (static_cast<unsigned long long>(__sdpX) - 1)
													] != 'z')
												{
													dirp.dir = '0';
													dirp.pos = INTPOINT
													(
														{
															__sdpX,
															__sdpY
														}
													);
													dirp.fnd = true;
												}
											}
										}
									}
								}
							}
						}
					}
					//1
					__sdpY = _walls_buff.points[i].y + 1;
					__sdpX = _walls_buff.points[i].x;
					if (__sdpY > 0)
					{
						if (__sdpY < game::world::size - 1)
						{
							if (__sdpX > 0)
							{
								if (__sdpX < game::world::size - 1)
								{
									if (structure
										[
											static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>
											(__sdpY)*game::world::size + __sdpX
										] != 'z')
									{
										if (structure
											[
												(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY) + 1)
												* game::world::size + __sdpX
											] != 'z')
										{
											if (structure
												[
													(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY))
													* game::world::size + (static_cast<unsigned long long>(__sdpX) + 1)
												] != 'z')
											{
												if (structure
													[
														(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY))
														* game::world::size + (static_cast<unsigned long long>(__sdpX) - 1)
													] != 'z')
												{
													dirp.dir = '1';
													dirp.pos = INTPOINT
													(
														{
															__sdpX,
															__sdpY
														}
													);
													dirp.fnd = true;
												}
											}
										}
									}
								}
							}
						}
					}
					//2
					__sdpY = _walls_buff.points[i].y;
					__sdpX = _walls_buff.points[i].x - 1;
					if (__sdpY > 0)
					{
						if (__sdpY < game::world::size - 1)
						{
							if (__sdpX > 0)
							{
								if (__sdpX < game::world::size - 1)
								{
									if (structure
										[
											static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY)
											* game::world::size + __sdpX
										] != 'z')
									{
										if (structure
											[
												(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY) - 1)
												* game::world::size + __sdpX
											] != 'z')
										{
											if (structure
												[
													(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY) + 1)
													* game::world::size + (__sdpX)
												] != 'z')
											{
												if (structure
													[
														(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY))
														* game::world::size + (static_cast<unsigned long long>(__sdpX) - 1)
													] != 'z')
												{
													dirp.dir = '2';
													dirp.pos = INTPOINT
													(
														{
															__sdpX,
															__sdpY
														}
													);
													dirp.fnd = true;
												}
											}
										}
									}
								}
							}
						}
					}
					//3
					__sdpY = _walls_buff.points[i].y;
					__sdpX = _walls_buff.points[i].x + 1;
					if (__sdpY > 0)
					{
						if (__sdpY < game::world::size - 1)
						{
							if (__sdpX > 0)
							{
								if (__sdpX < game::world::size - 1)
								{
									if (structure
										[
											static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY)
											* game::world::size + __sdpX
										] != 'z')
									{
										if (structure
											[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY) - 1)
											* game::world::size + __sdpX
											] != 'z')
										{
											if (structure
												[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY) + 1)
												* game::world::size + (__sdpX)
												] != 'z')
											{
												if (structure
													[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__sdpY))
													* game::world::size + (static_cast<unsigned long long>(__sdpX) + 1)
													] != 'z')
												{
													dirp.dir = '3';
													dirp.pos = INTPOINT
													(
														{
															__sdpX,
															__sdpY
														}
													);
													dirp.fnd = true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
				return dirp;
			}
		};
		__matrix8 gen(int seed)
		{
			__matrix8 MATRIX = engine::utils::create__matrix8(game::world::size, game::world::size);
			//Переделать из string в MATRIX;
			sf::RenderWindow loadwind(sf::VideoMode
			(
				400,
				200
			), "SFML window");
			sf::Font font;
			font.loadFromFile(game::loading::font);
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(65);
			text.setPosition(130, 85);
			sf::Text text2;
			text2.setFont(font);
			text2.setCharacterSize(45);
			text2.setPosition(5, 5);
			text2.setString("MAZE GENERATION");
			sf::Texture tex;
			tex.loadFromFile(game::loading::logo);
			sf::Sprite logo;
			logo.setTexture(tex);
			logo.setScale
			(
				static_cast<float>(400) / tex.getSize().x,
				static_cast<float>(200) / tex.getSize().y
			);
			text.setString("100%");
			loadwind.draw(logo);
			loadwind.draw(text);
			loadwind.display();
			string structure = "";
			//INIT STRUCTURE WORLD
			for (size_t i = 0; i < pow(game::world::size, 2); i++)
			{
				structure += ' ';
			}
			//_PRE
			bool _gened(false);
			INTPOINT _maze_points
			(
				{
					int(game::world::size / 2),
					int(game::world::size / 2)
				}
			);
			string __pre_bin_dirseed(vb::DecToBin(seed));
			string __pre_decseed(to_string(seed));
			//DIRECTION SEED
			string dirseed("");
			/*UNPACKING DIRSEED*/
			int _unpack_time(1);
			for (short i = 0; i < __pre_bin_dirseed.length(); i++)
			{
				for (short l = 0; l < __pre_decseed.length(); l++)
				{
					dirseed += to_string
					(
						(
							(
								(__pre_bin_dirseed[i] - '0') *
								(__pre_decseed[l] - '0') +
								(i % (l + 1)) +
								(_unpack_time % ((i % (l + 1)) + 1))
								)
							+ abs
							(
								(__pre_decseed[dirseed[__pre_decseed[int(__pre_decseed.length() / 2)] - '0'] - '0'] - '0') +
								((dirseed[int(__pre_decseed.length() /
									((dirseed.length() /
										(__pre_decseed.length() + 1) + 1)))] - '0'))
							)
							)
						% 4
					);
					_unpack_time++;
				}
			}
			INTBUFFER _walls_buff;
			_walls_buff.add_point(_maze_points.x, _maze_points.y);
			structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + _maze_points.x] = 'z';
			int _maze_time(0);
			int ___fornum = pow(game::world::size, 2) / 10;
			for (size_t i = 0; i < ___fornum; i++)
			{
				loadwind.clear();
				text.setString(to_string(int(float(i) / float(___fornum) * 100)) + "%");
				loadwind.draw(logo);
				loadwind.draw(text);
				loadwind.draw(text2);
				loadwind.display();
				___utils::DIRPOINT dirp(___utils::search_dirpoint(_walls_buff, structure));
				if (dirp.fnd == false)
				{
					break;
				}
				_maze_points.x = dirp.pos.x;
				_maze_points.y = dirp.pos.y;
				_walls_buff.add_point(_maze_points.x, _maze_points.y);
				structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + _maze_points.x] = 'z';
				for (short i = 0; i < dirseed.length(); i++)
				{
					if (dirseed[i] == '0')
					{
						if (_maze_points.y - 1 > 0)
						{
							if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(_maze_points.y) - 1) * game::world::size + _maze_points.x] != 'z') //main
							{
								int __mpY = _maze_points.y - 1;
								int __mpX = _maze_points.x;
								if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY) - 1) * game::world::size + __mpX] != 'z')
								{
									if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY)) * game::world::size + (static_cast<unsigned long long>(__mpX) + 1)] != 'z')
									{
										if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY)) * game::world::size + (static_cast<unsigned long long>(__mpX) - 1)] != 'z')
										{
											_maze_points.y--;
											structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + _maze_points.x] = 'z';
											_walls_buff.add_point(_maze_points.x, _maze_points.y);
										}
									}
								}
							}
						}
					}
					else if (dirseed[i] == '1')
					{
						if (_maze_points.y + 1 < game::world::size - 1)
						{
							if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(_maze_points.y) + 1) * game::world::size + _maze_points.x] != 'z')
							{
								int __mpY = _maze_points.y + 1;
								int __mpX = _maze_points.x;
								if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY)) * game::world::size + (static_cast<unsigned long long>(__mpX) + 1)] != 'z')
								{
									if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY)) * game::world::size + (static_cast<unsigned long long>(__mpX) - 1)] != 'z')
									{
										if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY) + 1) * game::world::size + (__mpX)] != 'z')
										{
											_maze_points.y++;
											structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + _maze_points.x] = 'z';
											_walls_buff.add_point(_maze_points.x, _maze_points.y);
										}
									}
								}
							}
						}
					}
					else if (dirseed[i] == '2')
					{
						if (_maze_points.x - 1 > 0)
						{
							if (structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + (static_cast<unsigned long long>(_maze_points.x) - 1)] != 'z')
							{
								int __mpY = _maze_points.y;
								int __mpX = _maze_points.x - 1;
								if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY) - 1) * game::world::size + (__mpX)] != 'z')
								{
									if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY) + 1) * game::world::size + (__mpX)] != 'z')
									{
										if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY)) * game::world::size + (static_cast<unsigned long long>(__mpX) - 1)] != 'z')
										{
											_maze_points.x--;
											structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + _maze_points.x] = 'z';
											_walls_buff.add_point(_maze_points.x, _maze_points.y);
										}
									}
								}
							}
						}
					}
					else if (dirseed[i] == '3')
					{
						if (_maze_points.x + 1 < game::world::size - 1)
						{
							if (structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + (static_cast<unsigned long long>(_maze_points.x) + 1)] != 'z')
							{
								int __mpY = _maze_points.y;
								int __mpX = _maze_points.x + 1;
								if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY) + 1) * game::world::size + (__mpX)] != 'z')
								{
									if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY) - 1) * game::world::size + (__mpX)] != 'z')
									{
										if (structure[(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(__mpY)) * game::world::size + (static_cast<unsigned long long>(__mpX) + 1)] != 'z')
										{
											_maze_points.x++;
											structure[_maze_points.y * static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(game::world::size) + _maze_points.x] = 'z';
											_walls_buff.add_point(_maze_points.x, _maze_points.y);
										}
									}
								}
							}
						}
					}
					if (_maze_time == dirseed.length())
					{
						_maze_time = 0;
					}
					_maze_time++;
				}
			}
			structure[0] = ' ';
			for (size_t i = 0; i < pow(game::world::size, 2); i++)
			{
				if (structure[i] == 'z')
				{
					structure[i] = ' ';
				}
				else if (structure[i] == ' ')
				{
					structure[i] = 'z';
				}
			}
			_walls_buff.clearRAM();
			for (size_t y = 0; y < game::world::size; y++)
			{
				for (size_t x = 0; x < game::world::size; x++)
				{
					if (structure[y * game::world::size + x] == 'z')
					{
						MATRIX[y][x] = 1;
					}
					else
					{
						MATRIX[y][x] = 0;
					}
				}
			}
			return MATRIX;
		}
		/*Компьютер ищет старт и финиш в лабиринте с самым длинным путём*/
		___utils::DUALINTPOINT getMatrixStartFinishPoint()
		{
			/*Функция вернём дуалпоинт - поинты старта и финиша*/
			___utils::DUALINTPOINT dualpoint
			(
				{
					INTPOINT
					(
						{
							0,
							0
						}
					), 
					INTPOINT
					(
						{
							0,
							0
						}
					)
				}
			);
			/*Список возможных стартов / финишов*/
			map<unsigned int, unsigned int> SFmap;
			unsigned int SFnum = 0;
			/*Поиск возможных стартов / финишов*/
			for (size_t i = game::world::size; i < (game::world::structure.length() - game::world::size); i++)
			{
				
				if (game::world::structure[i] == ' ')
				{
					if 
					(
						(
							game::world::structure[i - game::world::size] != ' ' 
													&&
							game::world::structure[i + game::world::size] != ' '
													&&
							game::world::structure[i + 1] != ' '
													&&
							game::world::structure[i - 1] == ' '
						)
													||
						(
							game::world::structure[i - game::world::size] != ' '
													&&
							game::world::structure[i + game::world::size] != ' '
													&&
							game::world::structure[i - 1] != ' '
													&&
							game::world::structure[i + 1] == ' '
						)
													||
						(
							game::world::structure[i - game::world::size] != ' '
													&&
							game::world::structure[i + 1] != ' '
													&&
							game::world::structure[i - 1] != ' '
													&&
							game::world::structure[i + game::world::size] == ' '
						)
													||
						(
							game::world::structure[i + game::world::size] != ' '
													&&
							game::world::structure[i + 1] != ' '
													&&
							game::world::structure[i - 1] != ' '
													&&
							game::world::structure[i - game::world::size] == ' '
						)
					)	
					{
						SFmap[SFnum] = i;
						SFnum++;
					}
					/*SCRIPT*/
					for (unsigned __int32 i = 0; i < SFmap.size() / 2; i++)
					{
						unsigned int _main_SF_n = SFmap[i];
					}
				}
			}
			return dualpoint;
		}
	}
	namespace seed
	{
		int gen(int rand_seed, int type = 8)
		{
			if (type == 8)
			{
				srand(rand_seed);
				int random = 10000000 * (fmod(rand(), 9.9999932));
				while (random < 10000000 || random > 99999999)
				{
					random = 10000000 * (fmod(rand(), 9.999993));
				}
				return random;
			}
		}
	}
	namespace math
	{
		/*CONSTS*/
		const float PI = acos(-1);
		const float PI_180 = acos(-1) / 180;
		const float RAD90 = 90 * PI_180;
		/*FUNC*/
		inline float toDeg(float rad)
		{
			return rad / PI_180;
		}
		inline float getTrigonometricPeriod(float angle)
		{
			return round(angle / 360);
		}
		inline float getAngle(float angle, float period)
		{
			return angle - period * 360;
		};
		unsigned __int8 _getMatrixPos(__int16 pos)
		{
			return pos / game::world::wall_size;
		}

		inline unsigned __int8 _getTileMatrixPos(__int16 pos, float tile)
		{
			return pos / tile;
		}

		inline float toRad(float dg)
		{
			return dg * PI_180;
		}
		INTPOINT getINTW2MatrixPos(int x, int y)
		{
			return INTPOINT
			(
				{
					static_cast<int>(x * game::world::wall_size),
					static_cast<int>(y * game::world::wall_size)
				}
			);
		}
		FLOATPOINT getFLOATW2MatrixPos(float x, float y)
		{
			return FLOATPOINT
			(
				{
					x  * game::world::wall_size,
					y  * game::world::wall_size
				}
			);
		}
		INTPOINT getINTMatrixPos(int x, int y)
		{
			return INTPOINT
			(
				{
					int(x / game::world::wall_size),
					int(y / game::world::wall_size)
				}
			);
		}
		SHORTPOINT getSHORTMatrixPos(short x, short y)
		{
			return SHORTPOINT
			(
				{
					short(x / (game::window::w2size / game::world::size)),
					short(y / (game::window::w2size / game::world::size))
				}
			);
		}
		FLOATPOINT getFLOATMatrixPos(float x, float y)
		{
			return FLOATPOINT
			(
				{
					x / (game::window::w2size / game::world::size),
					y / (game::window::w2size / game::world::size)
				}
			);
		}
		int getNumInWorldStructFromW2pos(float x, float y)
		{
			//return y * 
		}
	}
	namespace player
	{
		INTPOINT getINTMatrixPos()
		{
			return INTPOINT
			(
				{
					int(game::player::pos.x / (game::window::w2size / game::world::size)),
					int(game::player::pos.y / (game::window::w2size / game::world::size))
				}
			);
		}
		FLOATPOINT getFLOATMatrixPos()
		{
			return FLOATPOINT
			(
				{
					game::player::pos.x / (game::window::w2size / game::world::size),
					game::player::pos.y / (game::window::w2size / game::world::size)
				}
			);
		}
		INTPOINT getW2MatrixPos()
		{
			return INTPOINT
			(
				{
					int(game::player::pos.x / (game::window::w2size / game::world::size) * game::world::wall_size),
					int(game::player::pos.y / (game::window::w2size / game::world::size) * game::world::wall_size)
				}
			);
		}
		float getRadAngle()
		{
			return math::toRad(game::player::angle);
		}
	}
	/*RENDER ENGINE*/
	namespace render
	{
		vector<game::render::RAY> ray(game::render::rays_num);
		namespace raycasting
		{
			namespace _optimization_utils
			{
				float* angle_array_craete()
				{
					float* aa = new float[game::render::rays_num];
					for (size_t i = 0; i < game::render::rays_num; i++)
					{
						aa[i] = i * game::render::any::ray_angle;
					}
					return aa;
				}
				unsigned __int8 _getMatrixPos(__int16 pos)
				{
					return pos / game::world::wall_size;
				}
				unsigned __int8 _getMatrixPos_m(__int16 pos, unsigned __int8 matrix_num)
				{
					return pos / game::walls::arr[matrix_num]._matrix.WALL_SIZE;
				}
			}
			enum WALLDIRENUM
			{

			};
			class RAYRET
			{
			public:
				__INT8POINT matrixpos;
				FLOATPOINT pos;
				float hypot;
				unsigned __int8 walldir;
			};
			namespace _vars
			{
				float vA = 0;
				float vB = 0;
				float vcx = 0;
				float vcy = 0;
				float vcxm = 0;
				float vAA = 0;
				float vBB = 0;
				float hA = 0;
				float hB = 0;
				float hcx = 0;
				float hcy = 0;
				float hcym = 0;
				float hAA = 0;
				float hBB = 0;
				float hypot = 0;
				int jx = 0;
				int jy = 0;
				RAYRET* LENRAYBUFF = new RAYRET[game::render::any::render_distance2__2];
				

				/*opimization*/
			}
			//VARS
			namespace vars
			{
				class cls_walls_class
				{
				public:
					__INT16POINT matrixpos;
					unsigned __int16 matrixnum;
				};
			}
			namespace _any_utils
			{
				bool check_cls_walls_arr(unsigned __int16 j, vars::cls_walls_class * _cls_walls, unsigned __int8 size = 0)
				{
					for (unsigned __int8 i = 0; i < size; i++)
					{
						if (j == _cls_walls[i].matrixnum)
						{
							return false;
						}
					}
					return true;
				}
			}
			RAYRET raycast_v1(float rayangle)
			{
				float cosA = cos(engine::math::toRad(rayangle));
				float sinA = sin(engine::math::toRad(rayangle));
				for (float l = 0; l < game::world::size; l += game::render::precision)
				{
					float cx = player::getFLOATMatrixPos().x + l * cosA;
					float cy = player::getFLOATMatrixPos().y + l * sinA;
					if (game::world::MATRIX[int(cy)][int(cx)] == 1)
					{
						engine::FLOATPOINT clspos = engine::FLOATPOINT({ cx * game::world::wall_size, cy * game::world::wall_size });
						return RAYRET
						(
							{
								__INT8POINT
								(
									{
										static_cast<unsigned __int8>(cx),
										static_cast<unsigned __int8>(cy)
									}
								),
								clspos,
								hypot(clspos.x - player::getFLOATMatrixPos().x, clspos.y - player::getFLOATMatrixPos().y)
							}
						);
						break;
					}
				}
			}
			//http://ndspaces.narod.ru/math/tabltrig.files/trig1.jpg
			inline RAYRET raycast_v2(float degrayangle, float cosDegAngle, float sinDegAngle, float tanrayangle, float tanrayangle__90)
			{
				unsigned __int8 time = 0;
				float radedangle = math::toRad(degrayangle);
				/*
					0
				_________
				|		|
				|		|
			3	|		|	1
				|_______|
					2
				*/
				if (cosDegAngle > 0 && sinDegAngle > 0)
				{
					//Ver
					_vars::vA = game::world::wall_size - (game::player::pos.x - engine::player::getINTMatrixPos().x * game::world::wall_size);
					_vars::vB = _vars::vA * tanrayangle;
					_vars::vcx = game::player::pos.x + _vars::vA;
					_vars::vcy = game::player::pos.y + _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 3;
							time++;
						}
					}
					_vars::vAA = game::world::wall_size;
					_vars::vBB = _vars::vAA * tanrayangle;

					//Hor
					_vars::hB = game::world::wall_size - (game::player::pos.y - engine::player::getINTMatrixPos().y * game::world::wall_size);
					_vars::hA = _vars::hB * tanrayangle__90;
					_vars::hcx = game::player::pos.x + _vars::hA;
					_vars::hcy = game::player::pos.y + _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 2;
							time++;
						}
					}
					_vars::hBB = game::world::wall_size;
					_vars::hAA = _vars::hBB * tanrayangle__90;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx += _vars::vAA;
						_vars::vcy += _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::world::MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 3;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx += _vars::hAA;
						_vars::hcy += _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 2;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				else if (cosDegAngle < 0 && sinDegAngle > 0)
				{
					//Ver
					_vars::vA = game::player::pos.x - engine::player::getINTMatrixPos().x * game::world::wall_size;
					_vars::vB = _vars::vA * tanrayangle;
					_vars::vcx = game::player::pos.x - _vars::vA;
					_vars::vcy = game::player::pos.y - _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 1;
							time++;
						}
					}
					_vars::vAA = game::world::wall_size;
					_vars::vBB = _vars::vAA * tanrayangle;

					//Hor
					_vars::hB = game::world::wall_size - (game::player::pos.y - engine::player::getINTMatrixPos().y * game::world::wall_size);
					_vars::hA = _vars::hB * tanrayangle__90;
					_vars::hcx = game::player::pos.x + _vars::hA;
					_vars::hcy = game::player::pos.y + _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 2;
							time++;
						}
					}
					_vars::hBB = game::world::wall_size;
					_vars::hAA = _vars::hBB * tanrayangle__90;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx -= _vars::vAA;
						_vars::vcy -= _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::world::MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 1;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx += _vars::hAA;
						_vars::hcy += _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 2;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				else if (cosDegAngle > 0 && sinDegAngle < 0)
				{
					//Ver
					_vars::vA = game::world::wall_size - (game::player::pos.x - engine::player::getINTMatrixPos().x * game::world::wall_size);
					_vars::vB = _vars::vA * tanrayangle;
					_vars::vcx = game::player::pos.x + _vars::vA;
					_vars::vcy = game::player::pos.y + _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 3;
							time++;
						}
					}
					_vars::vAA = game::world::wall_size;
					_vars::vBB = _vars::vAA * tanrayangle;

					//Hor
					_vars::hB = game::player::pos.y - engine::player::getINTMatrixPos().y * game::world::wall_size;
					_vars::hA = _vars::hB * tanrayangle__90;
					_vars::hcx = game::player::pos.x - _vars::hA;
					_vars::hcy = game::player::pos.y - _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.1);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 0;
							time++;
						}
					}
					_vars::hBB = game::world::wall_size;
					_vars::hAA = _vars::hBB * tanrayangle__90;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx += _vars::vAA;
						_vars::vcy += _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::world::MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 3;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx -= _vars::hAA;
						_vars::hcy -= _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.1);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 0;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				else if (cosDegAngle < 0 && sinDegAngle < 0)
				{
					//Ver
					_vars::vA = game::player::pos.x - engine::player::getINTMatrixPos().x * game::world::wall_size;
					_vars::vB = _vars::vA * tanrayangle;
					_vars::vcx = game::player::pos.x - _vars::vA;
					_vars::vcy = game::player::pos.y - _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 1;
							time++;
						}
					}
					_vars::vAA = game::world::wall_size;
					_vars::vBB = _vars::vAA * tanrayangle;

					//Hor
					_vars::hB = game::player::pos.y - engine::player::getINTMatrixPos().y * game::world::wall_size;
					_vars::hA = _vars::hB * tanrayangle__90;
					_vars::hcx = game::player::pos.x - _vars::hA;
					_vars::hcy = game::player::pos.y - _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.1);
					if (_vars::jx < game::world::size && _vars::jy < game::world::size)
					{
						if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 0;
							time++;
						}
					}
					_vars::hBB = game::world::wall_size;
					_vars::hAA = _vars::hBB * tanrayangle__90;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx -= _vars::vAA;
						_vars::vcy -= _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::world::MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - game::player::pos.x, _vars::vcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 1;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx -= _vars::hAA;
						_vars::hcy -= _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.01);
						if (_vars::jx < game::world::size && _vars::jy < game::world::size)
						{
							if (game::world::MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - game::player::pos.x, _vars::hcy - game::player::pos.y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 0;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				//MAIN RAYRET
				return RAYRET();

			}

			RAYRET wall_m_raycast_v2(unsigned __int8 matrix_num, float cos_angle, float sin_angle, float tan_angle, float ctg_angle, float start_pos_x, float start_pos_y)
			{
				unsigned __int16 time = 0;
				unsigned __int8 hvx = _optimization_utils::_getMatrixPos(start_pos_x);
				unsigned __int8 hvy = _optimization_utils::_getMatrixPos(start_pos_y);
				if (game::walls::arr[matrix_num]._matrix.MATRIX[hvy][hvx] == 1)
				{
					_vars::LENRAYBUFF[time].pos.x = hvx;
					_vars::LENRAYBUFF[time].pos.y = hvy;
					_vars::LENRAYBUFF[time].hypot = hypot(hvx - start_pos_x, hvy - start_pos_y);
					_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
					_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
					_vars::LENRAYBUFF[time].walldir = 3;
					return _vars::LENRAYBUFF[time];
				}
				/*
					0
				_________
				|		|
				|		|
			3	|		|	1
				|_______|
					2
				*/
				if (cos_angle > 0 && sin_angle > 0)
				{
					//Ver
					_vars::vA = game::walls::arr[matrix_num]._matrix.WALL_SIZE - (start_pos_x - _optimization_utils::_getMatrixPos_m(start_pos_x, matrix_num) *game::walls::arr[matrix_num]._matrix.WALL_SIZE);
					_vars::vB = _vars::vA * tan_angle;
					_vars::vcx = start_pos_x + _vars::vA;
					_vars::vcy = start_pos_y + _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 3;
							time++;
						}
					}
					_vars::vAA = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::vBB = _vars::vAA * tan_angle;

					//Hor
					_vars::hB = game::walls::arr[matrix_num]._matrix.WALL_SIZE - (start_pos_y - _optimization_utils::_getMatrixPos_m(start_pos_y, matrix_num) * game::walls::arr[matrix_num]._matrix.WALL_SIZE);
					_vars::hA = _vars::hB * ctg_angle;
					_vars::hcx = start_pos_x + _vars::hA;
					_vars::hcy = start_pos_y + _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 2;
							time++;
						}
					}
					_vars::hBB = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::hAA = _vars::hBB * ctg_angle;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx += _vars::vAA;
						_vars::vcy += _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 3;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx += _vars::hAA;
						_vars::hcy += _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 2;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				else if (cos_angle < 0 && sin_angle > 0)
				{
					//Ver
					_vars::vA = start_pos_x - engine::player::getINTMatrixPos().x * game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::vB = _vars::vA * tan_angle;
					_vars::vcx = start_pos_x - _vars::vA;
					_vars::vcy = start_pos_y - _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 1;
							time++;
						}
					}
					_vars::vAA = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::vBB = _vars::vAA * tan_angle;

					//Hor
					_vars::hB = game::walls::arr[matrix_num]._matrix.WALL_SIZE - (start_pos_y - _optimization_utils::_getMatrixPos_m(start_pos_y, matrix_num) * game::walls::arr[matrix_num]._matrix.WALL_SIZE);
					_vars::hA = _vars::hB * ctg_angle;
					_vars::hcx = start_pos_x + _vars::hA;
					_vars::hcy = start_pos_y + _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 2;
							time++;
						}
					}
					_vars::hBB = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::hAA = _vars::hBB * ctg_angle;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx -= _vars::vAA;
						_vars::vcy -= _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 1;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx += _vars::hAA;
						_vars::hcy += _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 2;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				else if (cos_angle > 0 && sin_angle < 0)
				{
					//Ver
					_vars::vA = game::walls::arr[matrix_num]._matrix.WALL_SIZE - (start_pos_x - engine::player::getINTMatrixPos().x * game::walls::arr[matrix_num]._matrix.WALL_SIZE);
					_vars::vB = _vars::vA * tan_angle;
					_vars::vcx = start_pos_x + _vars::vA;
					_vars::vcy = start_pos_y + _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 3;
							time++;
						}
					}
					_vars::vAA = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::vBB = _vars::vAA * tan_angle;

					//Hor
					_vars::hB = start_pos_y - _optimization_utils::_getMatrixPos_m(start_pos_y, matrix_num) * game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::hA = _vars::hB * ctg_angle;
					_vars::hcx = start_pos_x - _vars::hA;
					_vars::hcy = start_pos_y - _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.1);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 0;
							time++;
						}
					}
					_vars::hBB = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::hAA = _vars::hBB * ctg_angle;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx += _vars::vAA;
						_vars::vcy += _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 3;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx -= _vars::hAA;
						_vars::hcy -= _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.1);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 0;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				else if (cos_angle < 0 && sin_angle < 0)
				{
					//Ver
					_vars::vA = start_pos_x - _optimization_utils::_getMatrixPos_m(start_pos_x, matrix_num) * game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::vB = _vars::vA * tan_angle;
					_vars::vcx = start_pos_x - _vars::vA;
					_vars::vcy = start_pos_y - _vars::vB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 1;
							time++;
						}
					}
					_vars::vAA = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::vBB = _vars::vAA * tan_angle;

					//Hor
					_vars::hB = start_pos_y - _optimization_utils::_getMatrixPos_m(start_pos_y, matrix_num) * game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::hA = _vars::hB * ctg_angle;
					_vars::hcx = start_pos_x - _vars::hA;
					_vars::hcy = start_pos_y - _vars::hB;
					_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
					_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.1);
					if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
					{
						if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
						{
							_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
							_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
							_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
							_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
							_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
							_vars::LENRAYBUFF[time].walldir = 0;
							time++;
						}
					}
					_vars::hBB = game::walls::arr[matrix_num]._matrix.WALL_SIZE;
					_vars::hAA = _vars::hBB * ctg_angle;
					//RAY LEN SEARCHER
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::vcx -= _vars::vAA;
						_vars::vcy -= _vars::vBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::vcx - 0.1);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::vcy);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								//cout << (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1) << endl;
								_vars::LENRAYBUFF[time].pos.x = _vars::vcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::vcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::vcx - start_pos_x, _vars::vcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 1;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (unsigned __int8 i = 0; i < game::render::any::render_distance2__2; i++)
					{
						_vars::hcx -= _vars::hAA;
						_vars::hcy -= _vars::hBB;
						_vars::jx = _optimization_utils::_getMatrixPos(_vars::hcx);
						_vars::jy = _optimization_utils::_getMatrixPos(_vars::hcy - 0.01);
						if (_vars::jx < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE && _vars::jy < game::walls::arr[matrix_num]._matrix.MATRIX_SIZE)
						{
							if (game::walls::arr[matrix_num]._matrix.MATRIX[_vars::jy][_vars::jx] == 1)
							{
								_vars::LENRAYBUFF[time].pos.x = _vars::hcx;
								_vars::LENRAYBUFF[time].pos.y = _vars::hcy;
								_vars::LENRAYBUFF[time].hypot = hypot(_vars::hcx - start_pos_x, _vars::hcy - start_pos_y);
								_vars::LENRAYBUFF[time].matrixpos.x = _vars::jx;
								_vars::LENRAYBUFF[time].matrixpos.y = _vars::jy;
								_vars::LENRAYBUFF[time].walldir = 0;
								time++;
								break;
							}
						}
						else
						{
							break;
						}
					}
					//SORT BUFFER
					unsigned __int8 ft = time;
					for (unsigned __int8 i = 0; i < ft; i++)
					{
						for (unsigned __int8 l = 0; l < ft; l++)
						{
							if (_vars::LENRAYBUFF[l].hypot > _vars::LENRAYBUFF[l + 1].hypot)
							{
								swap(_vars::LENRAYBUFF[l], _vars::LENRAYBUFF[l + 1]);
								break;
							}
						}
					}
					return _vars::LENRAYBUFF[0];
				}
				//MAIN RAYRET
				return RAYRET();

			}
		}
		namespace walls
		{
			inline float getWallHeight(float raysize, float angle)
			{
				return game::render::any::_renderWallHeighterConst / (raysize * cos(math::toRad(angle - game::player::angle) / 1.05));
			}
			inline float getWallColor(float raysize)
			{
				return  255 / (1 + pow(raysize, 2) * game::render::shading_coefficient);
			}
			inline float getSpriteHeight(float raysize)
			{
				return game::render::any::_renderWallHeighterConst / raysize;
			}
			namespace _optimization_utils
			{
				inline unsigned __int8 _getMatrixPos(__int16 pos, float wall_size)
				{
					return pos / wall_size;
				}
			}
		}
		namespace floor 
		{
			class RAY3DRET
			{
			public:
				float hypot = 0;
			};

			//FLOOR'S RAY-TRACER
			float traceRAY3D(float player_offset_y, float player_offset_x)
			{
				return hypot(player_offset_y, player_offset_x);
			}
		}

		namespace sprites
		{
			float raycast_v1(float cosA, float sinA)
			{
				for (float l = 0; l < game::window::w2size; l += game::render::precision)
				{
					float cx = game::player::pos.x + l * cosA;
					float cy = game::player::pos.y + l * sinA;
					if (game::world::MATRIX[engine::math::_getMatrixPos(cy)][engine::math::_getMatrixPos(cx)] != 0)
					{
						return hypot(game::player::pos.x - cx, game::player::pos.y - cy);
					}
				}
			}

		}
	}
}
