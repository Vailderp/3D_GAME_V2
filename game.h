#pragma once
#include <vaibin.h>
#include <SFML/Graphics.hpp>
#include <vector>
const float GAME_PI = acos(-1);
const float GAME_PI_180 = GAME_PI / 180;
float GAME_TORAD(float DEG) 
{ 
	return (DEG * GAME_PI_180);
}
float GAME_TODEG(float RAD)
{
	return (RAD / GAME_PI_180);
}

float di(float a, float b) // считает разницу между двумя углами
{
	float r1, r2;
	if (a > b) { r1 = a - b; r2 = b - a + 2 * GAME_PI; }
	else { r1 = b - a; r2 = a - b + 2 * GAME_PI; }
	return (r1 > r2) ? r2 : r1;
}

int _main_world_size = 32;
int _main_world_seed = 2324;
namespace game
{
	map<string, string> conf(vb::ReadConfFile("sets/conf.txt"));
	map<string, string> cmenu(vb::ReadConfFile("sets/menu.txt"));
	class POINT
	{
		public:
			float x = 0;
			float y = 0;
			POINT(float X = 0, float Y = 0)
			{
				x = X;
				y = Y;
			}
	};
	string mode(conf["mode"]);
	class SPRITECOLOR
	{
	public:
		float r = 255;
		float g = 255;
		float b = 255;
		SPRITECOLOR(float R = 255, float G = 255, float B = 255)
		{
			r = R;
			g = G;
			b = B;
		}
	};
	namespace window
	{
		//sf::RenderWindow window3(sf::VideoMode(game::window::width, game::window::height), "SFML window", sf::Style::Fullscreen, ctxsettings);
		int width(stoi(conf["window_width"]));
		const int width__2(width / 2);
		int height(stoi(conf["window_height"]));
		const int height__2(height / 2);
		const int w2size(stoi(conf["window2_size"]));
		bool w2_disable(stoi(conf["w2_disable"]));
		__int16 FPS_update_time(stoi(conf["FPS_update_time"]));
		__int16 FPS_update_time_1(stoi(conf["FPS_update_time"]) - 1);
	}

	namespace _layout
	{
		const unsigned __int16 delay = 150;
		const unsigned __int16 DISP = 10000;
		const float DISP_SCALE_W = static_cast<float>(game::window::width) / static_cast<float>(DISP);
		const float DISP_SCALE_H = static_cast<float>(game::window::height) / static_cast<float>(DISP);
		class COLOR
		{
		public:
			unsigned __int8 r = 0;
			unsigned __int8 g = 0;
			unsigned __int8 b = 0;
			unsigned __int8 a = 255;
		};
		class TEXT
		{
		public:
			string text = "";
			unsigned __int16 size = 100;
			COLOR color;

		};
		class BACKGROUND
		{
		public:
			COLOR color;
		};
		class BORDER
		{
		public:
			unsigned __int16 size = 100;
			COLOR color;
		};
		class SF
		{
		public:
			sf::Text text;
			sf::RectangleShape shape;
		};
		class BUTTON
		{
		public:
			TEXT text;
			BACKGROUND background;
			BORDER border;
			unsigned __int16 width;
			unsigned __int16 height;
			POINT pos = POINT();
			SF sf;
			string onclick_event;
		};
	}
	namespace ingame_menu
	{
		bool active = 0;
		const unsigned int buttons_num = stoi(cmenu["buttons_num"]);
		_layout::BUTTON* buttons = new _layout::BUTTON[buttons_num];
		string language = conf["language"];
		_layout::SF sf;
		void init()
		{
			sf.shape.setPosition(sf::Vector2f(0, 0));
			sf.shape.setSize(sf::Vector2f(game::window::width, game::window::height));
			sf.shape.setFillColor(sf::Color(0,0,0,100));
			for (unsigned int i = 0; i < buttons_num; i++)
			{
				//sf::Font font;
				//font.loadFromFile(cmenu[to_string(i) + ".text.font"]);
				//TEXT
				buttons[i].text.text = cmenu[to_string(i) + ".text." + language];
				buttons[i].text.size = stoi(cmenu[to_string(i) + ".text.size"]) * hypot(_layout::DISP_SCALE_W, _layout::DISP_SCALE_H);
				buttons[i].text.color = _layout::COLOR
				(
					{
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".text.color.r"])),
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".text.color.g"])),
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".text.color.b"]))
					}
				);
				//buttons[i].sf.text.setFont(font);
				//BACKGROUND
				buttons[i].background.color = _layout::COLOR
				(
					{
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".background_color.r"])),
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".background_color.g"])),
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".background_color.b"]))
					}
				);
				//BORDER
				buttons[i].border.size = stoi(cmenu[to_string(i) + ".border.size"]) * hypot(_layout::DISP_SCALE_W, _layout::DISP_SCALE_H);
				buttons[i].border.color = _layout::COLOR
				(
					{
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".border.color.r"])),
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".border.color.g"])),
						static_cast<unsigned __int8>(stoi(cmenu[to_string(i) + ".border.color.b"]))
					}
				);
				//POS
				buttons[i].width = stoi(cmenu[to_string(i) + ".width"]) * _layout::DISP_SCALE_W;
				buttons[i].height = stoi(cmenu[to_string(i) + ".height"]) * _layout::DISP_SCALE_H;
				buttons[i].pos.x = stoi(cmenu[to_string(i) + ".pos.x"]) * _layout::DISP_SCALE_W;
				buttons[i].pos.y = stoi(cmenu[to_string(i) + ".pos.y"]) * _layout::DISP_SCALE_H;
				//EVENTS
				buttons[i].onclick_event = cmenu[to_string(i) + ".onclick_event"];
			}
		}
	}

	namespace world
	{
		const string type = conf["world_type"];
		const int seed_len = 8;
		const unsigned __int8 size((stoi(conf["world_size"]) > 2 && stoi(conf["world_size"]) <= 255) ? stoi(conf["world_size"]) :_main_world_size);
		const unsigned int rseed((stoi(conf["seed"]) >= 0 && stoi(conf["seed"]) <= 4294967295) ? stoi(conf["seed"]) : _main_world_seed);
		const unsigned __int8 wall_size(game::window::w2size / size);
		string structure = "";
		namespace _any
		{
			unsigned __int16 world_len = pow(game::world::size, 2);
		}
		namespace textures
		{
			namespace background
			{
				string background = "bg.jpg";
				sf::Texture texture;
				sf::Sprite sprite;
				__int16 texWidth;
				__int16 texHeight;
				float TEXFOV;
				float WWTEXFOV;
				float FOVFOV;
				float WWSCALE;
				float SCALETEXR3D;
				unsigned __int16 background_FOV = stoi(conf["background_FOV"]);
				void initByPath (string path = background) 
				{
					texture.loadFromFile(path);
					
					sprite.setTexture(texture);
					texWidth = texture.getSize().x;
					texHeight = texture.getSize().y;
					TEXFOV = static_cast<float>(texWidth) / background_FOV;
					WWTEXFOV = static_cast<float>(game::window::width) / background_FOV;
					FOVFOV = TEXFOV * stoi(conf["FOV"]);
					game::world::textures::background::sprite.setScale(game::window::width / game::world::textures::background::FOVFOV, 1);
					WWSCALE = static_cast<float>(texWidth) / static_cast<float>(game::window::width);
					SCALETEXR3D = (static_cast<float>(game::window::width) / static_cast<float>(stoi(conf["rays_num"]))) / WWSCALE;
					sprite.setScale(SCALETEXR3D,1);
				}
			}
		}
		vector<vector<unsigned __int8>> MATRIX(game::world::size, vector<unsigned __int8> (game::world::size, 0));
	}
	namespace LAN
	{
		const bool online_mode = static_cast<bool>(stoi(conf["online_mode"]));
		unsigned __int16 port = static_cast<unsigned __int16>(stoi(conf["mysocket_port"]));
		class PLAYER
		{
		public:
			unsigned __int8 num;
		};
	}
	namespace player
	{
		POINT pos = POINT();
		float angle = 0.1;
		float step_speed = static_cast<float>(stoi(conf["player_speed_step"])) / 100;
		float rot_speed = static_cast<float>(stoi(conf["player_speed_rotation"])) / 100;
		float radius = 0;
		LAN::PLAYER LAN;
	}
	class SPRITE
	{
	private:
		void initr2(float RADIUS)
		{
			radius2 = radius / 2;
		}
	public:
		SPRITECOLOR color = SPRITECOLOR();
		POINT pos = POINT();
		float angle = 0;
		float radius = 15;
		float radius2 = radius / 2;
		float height = 0;
		float uplift = 0;
		//init
		SPRITE(POINT POS = POINT(), float HEIGHT = 0, float RADIUS = 4, float ANGLE = 0, SPRITECOLOR COLOR = SPRITECOLOR(), float UPLIFT = 0)
		{
			pos = POS;
			height = HEIGHT;
			radius = RADIUS;
			initr2(RADIUS);
			angle = ANGLE;
			color = COLOR;
			uplift = UPLIFT;
		}

	};
	
	namespace _any
	{
		class _VERTICAL_SPRITE_QUAD_POSITION_
		{
		public:
			_VERTICAL_SPRITE_QUAD_POSITION_(float X0, float X1, float Y0, float Y1) :
				x0{ X0 },
				x1{ X1 },
				y0{ Y0 },
				y1{ Y1 }
			{
			}
			float x0;
			float x1;
			float y0;
			float y1;
		};

		class _VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_
		{
		public:
			_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_(float X0Y0, float X1Y0, float X0Y1, float X1Y1) :
				x0y0{ X0Y0 },
				x1y0{ X1Y0 },
				x0y1{ X0Y1 },
				x1y1{ X1Y1 }
			{

			}
			float x0y0;
			float x1y0;
			float x0y1;
			float x1y1;
		};

		class _VERTICAL_SPRITE_QUAD_POSITION_ANGLE_
		{
		public:
			_VERTICAL_SPRITE_QUAD_POSITION_ANGLE_(float ANGLE_X0Y0, float ANGLE_X1Y0, float ANGLE_X0Y1, float ANGLE_X1Y1) :
				x0y0{ ANGLE_X0Y0 },
				x1y0{ ANGLE_X1Y0 },
				x0y1{ ANGLE_X0Y1 },
				x1y1{ ANGLE_X1Y1 }
			{

			}
			float x0y0;
			float x1y0;
			float x0y1;
			float x1y1;
		};

		class _VERTICAL_SPRITE_QUAD_HEIGHT_
		{
		public:
			_VERTICAL_SPRITE_QUAD_HEIGHT_(float X0Y0, float X1Y0, float X0Y1, float X1Y1) :
				x0y0{ X0Y0 },
				x1y0{ X1Y0 },
				x0y1{ X0Y1 },
				x1y1{ X1Y1 }
			{

			}
			float x0y0;
			float x1y0;
			float x0y1;
			float x1y1;
		};
	}

	namespace loading
	{
		const string font = "loading/font.otf";
		const string logo = "loading/logo.png";
	}
	namespace render
	{
		bool V_sync = stoi(conf["V-sync"]);
		unsigned __int8 raycasting_engine_version = static_cast<unsigned __int8>(stoi(conf["raycasting_engine_version"]));
		unsigned __int16 rays_num = stoi(conf["rays_num"]);
		float zoom = static_cast<float>(stoi(conf["zoom"])) / 100;
		__int16 FOV = stoi(conf["FOV"]);
		float FOVsin = sin(GAME_TORAD(FOV));
		float precision = 10 / static_cast<float>(stoi(conf["precision"]));
		unsigned __int8 floor_detailing(stoi(conf["floor_detailing"]));
		float shading_coefficient(static_cast<float>(stoi(conf["shading_coefficient"])) / 100000);
		unsigned __int8 render_distance = ((stoi(conf["render_distance"]) > 2 && stoi(conf["render_distance"]) <= ceil(255 / 2)) ? stoi(conf["render_distance"]) : 10);
		unsigned __int8 max_num_wall_for_ray = stoi(conf["max_num_wall_for_ray"]);
		namespace any
		{
			unsigned __int16 rays_num1 = rays_num - 1;
			float FOV_2 = float(FOV) / 2;
			const float ray_angle(float(FOV) / float(rays_num));
			const unsigned __int8 render_distance2__2 = render_distance * 2 - 2;
			const float _renderWallHeighterConst(render::rays_num / abs(2 * (tan(render::FOV) * (180 / acos(-1)))) * window::height * render::zoom);
			const float _renderFloorWidthterConst(game::window::height__2 / abs(2 * (tan(game::window::height__2) * (180 / acos(-1)))) * window::width * 8000);
			float WW___60 = 60 / static_cast<float>(game::window::width);
			float Rect3Dwidth = static_cast<float>(game::window::width) / static_cast<float>(game::render::rays_num);
		}
		class RAY
		{
			public:
				POINT pos = {0, 0};
				float angle = -180;
				float size = 0;
				float cos = 0;
				float sin = 0;
				float tan = 0;
				float ctg = 0;
				float rad = 0;
		};
	}

	class VERTICAL_SPRITE
	{
	private:
		//SFML
		string path;
		bool smooth;
		sf::Texture texture;
		sf::Sprite Rect3D;
		//3D MATH
	public:
		VERTICAL_SPRITE(POINT POSITION = POINT(), float SIZE_X = 0, float SIZE_Y = 0, float UPLIFT = 0, string PATH = "false", bool SMOOTH = false) :
			pos{ POSITION },
			size{ SIZE_X, SIZE_Y },
			uplift{ UPLIFT },
			path{ PATH },
			smooth{ SMOOTH },
			QUAD_POSITION{ _any::_VERTICAL_SPRITE_QUAD_POSITION_(POSITION.x, POSITION.x + SIZE_X, POSITION.y, POSITION.y + SIZE_Y) }
		{
			if (path != "false")
			{
				texture.loadFromFile(path);
				texture.setSmooth(smooth);
				Rect3D.setTexture(texture);
			}
			size = POINT
			(
				texture.getSize().x,
				texture.getSize().y
			);
		}

		_any::_VERTICAL_SPRITE_QUAD_POSITION_ QUAD_POSITION;
		POINT pos;
		POINT size;
		float uplift;

		_any::_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_ GET_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE()
		{
			return _any::_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_
			(
				hypot(QUAD_POSITION.x0 - game::player::pos.x, QUAD_POSITION.y0 - game::player::pos.y),
				hypot(QUAD_POSITION.x1 - game::player::pos.x, QUAD_POSITION.y0 - game::player::pos.y),
				hypot(QUAD_POSITION.x0 - game::player::pos.x, QUAD_POSITION.y1 - game::player::pos.y),
				hypot(QUAD_POSITION.x1 - game::player::pos.x, QUAD_POSITION.y1 - game::player::pos.y)
			);
		}

		_any::_VERTICAL_SPRITE_QUAD_POSITION_ANGLE_ GET_VERTICAL_SPRITE_QUAD_POSITION_ANGLE(_any::_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_ DISTANCE)
		{
			return _any::_VERTICAL_SPRITE_QUAD_POSITION_ANGLE_
			(
				GAME_TODEG(acos((QUAD_POSITION.x0 - game::player::pos.x) / DISTANCE.x0y0)) * 
				((QUAD_POSITION.y0 - game::player::pos.y < 0) ? -1 : 1),
				GAME_TODEG(acos((QUAD_POSITION.x1 - game::player::pos.x) / DISTANCE.x1y0)) *
				((QUAD_POSITION.y0 - game::player::pos.y < 0) ? -1 : 1),
				GAME_TODEG(acos((QUAD_POSITION.x0 - game::player::pos.x) / DISTANCE.x0y1)) *
				((QUAD_POSITION.y1 - game::player::pos.y < 0) ? -1 : 1),
				GAME_TODEG(acos((QUAD_POSITION.x1 - game::player::pos.x) / DISTANCE.x1y1)) * 
				((QUAD_POSITION.y1 - game::player::pos.y < 0) ? -1 : 1)
			);
		}

		_any::_VERTICAL_SPRITE_QUAD_HEIGHT_ GET_VERTICAL_SPRITE_QUAD_HEIGHT(_any::_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_ DISTANCE)
		{
			return _any::_VERTICAL_SPRITE_QUAD_HEIGHT_
			(
				game::render::any::_renderWallHeighterConst / (DISTANCE.x0y0),
				game::render::any::_renderWallHeighterConst / (DISTANCE.x1y0),
				game::render::any::_renderWallHeighterConst / (DISTANCE.x0y1),
				game::render::any::_renderWallHeighterConst / (DISTANCE.x1y1)

			);
		}

	};

	namespace walls
	{
		/*
		wall types:
		[f] - fill
		[m] - matrix
		*/
		namespace MODs
		{
			class glass
			{
			public:
				sf::Color color;
				unsigned __int8 opacity = 50;
			};
			class matrix
			{
			public:
				vector<vector<unsigned __int8>> MATRIX;
				unsigned __int8 MATRIX_SIZE;
				float WALL_SIZE;
				void initBySize(unsigned __int8 SIZE)
				{
					MATRIX = vector<vector<unsigned __int8>>(SIZE, vector<unsigned __int8>(SIZE, 0));
					MATRIX_SIZE = SIZE;
					WALL_SIZE = game::world::wall_size / MATRIX_SIZE;
				}
			};
		}

		class wall
		{
		public:
			string path;
			sf::Texture texture;
			sf::Sprite Rect3D;
			__int16 texWidth;
			__int16 texHeight;
			float texWallscale;
			float R3Dscale;
			char MOD = false;

			//MODIFICATIONS
			MODs::glass _glass;
			MODs::matrix _matrix;

			//INITIALIZATION
			void initByPath(string pathtex, unsigned __int8 MATRIX_SIZE = 0, bool smooth = false)
			{
				path = pathtex;
				texture.loadFromFile(pathtex);
				//texture.setSmooth(true);
				Rect3D.setTexture(texture);
				texWidth = texture.getSize().x;
				texHeight = texture.getSize().y;
				texWallscale = static_cast<float>(texWidth) / static_cast<float>(game::world::wall_size);
				R3Dscale = (static_cast<float>(game::window::width) / game::render::rays_num) / texWallscale;
			}
		};
		wall* arr = new wall[255];
	}

	/*class FLOOR
		{
		private:
			//SFML
			string path;
			bool smooth;
			sf::Texture texture;
			sf::Sprite Rect3D;
			POINT size;
			//3D MATH
			POINT pos;
			float size;
		public:
			FLOOR(POINT POSITION, float SIZE, string PATH = "false", bool SMOOTH = false) :
				pos{ POSITION },
				size{ SIZE },
				path{ PATH },
				smooth{ SMOOTH }
			{
				if (path != "false")
				{
					texture.loadFromFile(path);
					texture.setSmooth(smooth);
					Rect3D.setTexture(texture);
				}
				size = POINT
				(
					texture.getSize().x, 
					texture.getSize().y
				);
			}
		};*/
	
	class FLOOR
	{
	private:
		POINT pos;
		vector<vector<VERTICAL_SPRITE>> MATRIX;
	public:
		FLOOR
		(
			unsigned __int8 __VERTICAL_SPRITE_NUM = game::world::size,
			unsigned __int8 __VERTICAL_SPRITE_SIZE = game::world::wall_size,
			float X = 0,
			float Y = 0
		) :
			pos{ POINT(X,Y) }, 
			MATRIX{ vector<vector<VERTICAL_SPRITE>>( __VERTICAL_SPRITE_NUM, vector<VERTICAL_SPRITE>(__VERTICAL_SPRITE_NUM)) }
		{

			for (unsigned __int8 y = 0; y < __VERTICAL_SPRITE_NUM; y++)
			{
				for (unsigned __int8 x = 0; x < __VERTICAL_SPRITE_NUM; x++)
				{
					MATRIX[y][x] = VERTICAL_SPRITE(POINT(
						pos.y + y * __VERTICAL_SPRITE_SIZE, pos.x + x * __VERTICAL_SPRITE_SIZE),
						__VERTICAL_SPRITE_SIZE, __VERTICAL_SPRITE_SIZE, 0);
				}
			}
		}
		VERTICAL_SPRITE GET_SPRITE_FROM_MATRIX(unsigned int Y, unsigned int X)
		{
			return MATRIX[Y][X];
		}
		

	};

}
