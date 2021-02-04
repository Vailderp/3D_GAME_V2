/* 3D GAME V2.0 */
/*	   GG  :)   */
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "game.h"
#include "engine.h"
#include "LAN.h"
#include <vector>
#include<Windows.h>
std::size_t received;
game::render::RAY* ray = new game::render::RAY[game::render::rays_num];
unsigned int main_time(0);
float currentTime(0);
unsigned int fps_all_val(0);

vector<game::SPRITE> sprites;

unsigned __int16 sprites_num = 0;
bool _open_LAN_started = false;
bool _connected_LAN = false;
LAN::player_was player_was;
LAN::PLAYER pl;
unsigned __int8 max_num_players = 2;



int main()
{
    game::FLOOR floor = game::FLOOR();

    //SET CONSOLE LANGUAGE 
    setlocale(LC_ALL, "Russian");
    //LAN
    sf::UdpSocket socket;
    if (game::LAN::online_mode)
    {
        if (socket.bind(game::LAN::port) != sf::Socket::Done)
        {
            cout << "Failed to bind socket on the port 2004";
        }
    }
    sf::IpAddress recipient = "192.168.0.105";
    unsigned short serverport = 2004;
    std::size_t received;
    sf::IpAddress sender;
    char _new_player[11] = "new player";
    bool _new_player_sended = false;
    LAN::new_player_num new_player_num[1];
    LAN::PLAYER myplayer;
    LAN::PLAYER players[2] = {};
    LAN::LANtime LANtime;

    for (float i = 0; i < 1; i++)
    {
        sprites.push_back(game::SPRITE(game::POINT(35 + i * cos(engine::math::toRad(i * (360 / 50) - 180)), 35 + i * sin(engine::math::toRad(i * (360 / 50) - 180))), 400, 10, i * (360 / 50) - 180, game::SPRITECOLOR(i / 10, 0.5, i / 10)));
    }



    unsigned int* _sorted_sprites = new unsigned int[sprites_num];
    float* _unsorted_sprites_length = new float[sprites_num];


    game::ingame_menu::init();
    if (game::mode == "mouse")
    {
        ShowCursor(false);
    }

    if (game::world::type == "maze")
    {
        game::world::MATRIX = engine::maze::gen(engine::seed::gen(game::world::rseed));
    }
    else if (game::world::type == "pseudo_random")
    {
        game::world::MATRIX = engine::pseudoRandomWorld::gen(engine::seed::gen(game::world::rseed));
    }

    game::walls::arr[0x00000001].initByPath("tex/minecraft_desk.png");
    game::walls::arr[0x00000001].MOD = false;
    game::walls::arr[0x00000001]._matrix.initBySize(8);

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t l = 0; l < 8; l++)
        {
            if (l % 2 == 0 || i % 2 == 0)
            {
                game::walls::arr[1]._matrix.MATRIX[i][l] = 1;
            }
        }
    }

    game::world::textures::background::initByPath("tex/sky360.jpg");

    //init SFML
    sf::ContextSettings ctxsettings;
    //ctxsettings.antialiasingLevel = 1;
    //sf::RenderWindow window2;
    sf::RenderWindow window2(sf::VideoMode(game::window::w2size, game::window::w2size), "SFML window", sf::Style::Default, ctxsettings);
    if (game::window::w2_disable)
    {
        window2.close();
    }
    sf::RenderWindow window3(sf::VideoMode(game::window::width, game::window::height), "SFML window", sf::Style::Fullscreen, ctxsettings);
    if (game::render::V_sync)
    {
        window3.setVerticalSyncEnabled(true);
    }
    sf::Image icon;
    sf::RectangleShape w2wall;
    w2wall.setSize(sf::Vector2f(game::window::w2size / game::world::size, game::window::w2size / game::world::size));
    w2wall.setFillColor(sf::Color::Blue);
    icon.loadFromFile("tex/vaivec.png");
    window3.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //SPRITES
    sf::ConvexShape convex;
    convex.setPointCount(4);

    //FLOOR
    sf::RectangleShape Floor(sf::Vector2f(game::window::width, game::window::height__2));
    Floor.setPosition(0, game::window::height__2 / 2);
    Floor.setFillColor(sf::Color(0, 150, 0));
    //FPS CONTROLLER
    sf::Clock clock;
    sf::Time Time;
    sf::Clock clock_menu;
    float LastTimeMenu = 0;
    float NewTimeMenu = 0;
    sf::Font font;
    font.loadFromFile("fonts/ob.otf");
    sf::Text FPStext;
    FPStext.setPosition(10, 10);
    FPStext.setFillColor(sf::Color(255, 0, 0, 150));
    FPStext.setCharacterSize(30);
    FPStext.setStyle(sf::Text::Bold);
    FPStext.setFont(font);
    //init player
    sf::CircleShape Player(game::player::radius);
    Player.setOrigin(sf::Vector2f(game::player::radius, game::player::radius));
    engine::FLOATPOINT spawnpoint(engine::pseudoRandomWorld::searh_spawn_point(game::world::MATRIX));
    game::player::pos.x = spawnpoint.x;
    game::player::pos.y = spawnpoint.y;

    /*SFML RAY*/
    sf::RectangleShape sfray;
    sfray.setFillColor(sf::Color::Red);

    sf::Texture tex3;
    tex3.loadFromFile("tex/boxx.jpg");

    //RAYS'S ANGLE ARRAY
    float* _rays_angles = engine::render::raycasting::_optimization_utils::angle_array_craete();
    for (unsigned int i = 0; i < game::render::rays_num; i++)
    {
        ray[i].angle = (game::player::angle - game::render::any::FOV_2) + _rays_angles[i];
    }

    while (window3.isOpen())
    {
        //FPS
        Time = clock.getElapsedTime();
        currentTime = Time.asSeconds();
        // Process events
        sf::Event event;
        while (window3.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                window3.close();
                if (!game::window::w2_disable)
                {
                    window2.close();
                }
            }
            //move
        }
        NewTimeMenu = clock_menu.getElapsedTime().asMilliseconds();
        if (NewTimeMenu - LastTimeMenu > game::_layout::delay)
        {
            LastTimeMenu = clock_menu.getElapsedTime().asMilliseconds();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (game::ingame_menu::active == false)
                {
                    game::ingame_menu::active = true;
                    if (game::mode == "mouse")
                    {
                        ShowCursor(true);
                    }
                }
                else
                {
                    game::ingame_menu::active = false;
                    if (game::mode == "mouse")
                    {
                        ShowCursor(false);
                    }
                }
            }
        }
        int mouseX = sf::Mouse::getPosition(window3).x;
        int mouseY = sf::Mouse::getPosition(window3).y;
        if (game::ingame_menu::active == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                float ss = game::player::step_speed;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    ss = game::player::step_speed * 2;
                }
                float posY = ss * sin(engine::math::toRad(game::player::angle));
                float posX = ss * cos(engine::math::toRad(game::player::angle));
                float ry = game::player::radius;
                float rx = game::player::radius;
                if (posY < 0)
                {
                    ry = -game::player::radius;
                }
                if (posX < 0)
                {
                    rx = -game::player::radius;
                }
                if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y + posY + ry)][engine::math::_getMatrixPos(game::player::pos.x + posX + rx)] == 0)
                {
                    game::player::pos.x += posX;
                    game::player::pos.y += posY;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y + ry)][engine::math::_getMatrixPos(game::player::pos.x + posX + rx)] == 0)
                {
                    game::player::pos.x += posX;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y + posY + ry)][engine::math::_getMatrixPos(game::player::pos.x + rx)] == 0)
                {
                    game::player::pos.y += posY;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                float posY = game::player::step_speed * sin(engine::math::toRad(game::player::angle));
                float posX = game::player::step_speed * cos(engine::math::toRad(game::player::angle));
                float ry = game::player::radius;
                float rx = game::player::radius;
                if (posY < 0)
                {
                    ry = -game::player::radius;
                }
                if (posX < 0)
                {
                    rx = -game::player::radius;
                }
                if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - posY - ry)][engine::math::_getMatrixPos(game::player::pos.x - posX - rx)] == 0)
                {
                    game::player::pos.x -= posX;
                    game::player::pos.y -= posY;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - ry)][engine::math::_getMatrixPos(game::player::pos.x - posX - rx)] == 0)
                {
                    game::player::pos.x -= posX;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - posY - ry)][engine::math::_getMatrixPos(game::player::pos.x - rx)] == 0)
                {
                    game::player::pos.y -= posY;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                float posY = game::player::step_speed * sin(engine::math::toRad(game::player::angle + 90));
                float posX = game::player::step_speed * cos(engine::math::toRad(game::player::angle + 90));
                float ry = game::player::radius;
                float rx = game::player::radius;
                if (posY < 0)
                {
                    ry = -game::player::radius;
                }
                if (posX < 0)
                {
                    rx = -game::player::radius;
                }
                if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - posY - ry)][engine::math::_getMatrixPos(game::player::pos.x - posX - rx)] == 0)
                {
                    game::player::pos.x -= posX;
                    game::player::pos.y -= posY;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - ry)][engine::math::_getMatrixPos(game::player::pos.x - posX - rx)] == 0)
                {
                    game::player::pos.x -= posX;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - posY - ry)][engine::math::_getMatrixPos(game::player::pos.x - rx)] == 0)
                {
                    game::player::pos.y -= posY;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                float posY = game::player::step_speed * (-cos(engine::math::toRad(game::player::angle)));
                // Исходя из формул-приведений sin(a - п/2) = - cos(a)
                float posX = game::player::step_speed * cos(engine::math::toRad(game::player::angle - 90));
                float ry = game::player::radius;
                float rx = game::player::radius;
                if (posY < 0)
                {
                    ry = -game::player::radius;
                }
                if (posX < 0)
                {
                    rx = -game::player::radius;
                }
                if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - posY - ry)][engine::math::_getMatrixPos(game::player::pos.x - posX - rx)] == 0)
                {
                    game::player::pos.x -= posX;
                    game::player::pos.y -= posY;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - ry)][engine::math::_getMatrixPos(game::player::pos.x - posX - rx)] == 0)
                {
                    game::player::pos.x -= posX;
                }
                else if (game::world::MATRIX[engine::math::_getMatrixPos(game::player::pos.y - posY - ry)][engine::math::_getMatrixPos(game::player::pos.x - rx)] == 0)
                {
                    game::player::pos.y -= posY;
                }
            }
            if (game::mode == "mouse")
            {
                int mouseVectorX = game::window::width__2 - mouseX;
                //int mouseVectorY = game::window::height__2 - mouseY;
                float arotX = -mouseVectorX * game::player::rot_speed * 0.4;
                //float arotY = -mouseVectorY * game::player::rot_speed;
                if (game::ingame_menu::active == false)
                {
                    SetCursorPos(game::window::width__2, game::window::height__2);
                }
                game::player::angle += arotX;
                for (unsigned int i = 0; i < game::render::rays_num; i++)
                {
                    ray[i].angle += arotX;
                    ray[i].cos = cos(engine::math::toRad(ray[i].angle));
                    ray[i].sin = sin(engine::math::toRad(ray[i].angle));
                    ray[i].tan = tan(engine::math::toRad(ray[i].angle));
                    ray[i].ctg = tan(engine::math::toRad(90 - ray[i].angle));
                }
            }
            else if (game::mode == "key")
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    game::player::angle -= game::player::rot_speed;
                    for (unsigned int i = 0; i < game::render::rays_num; i++)
                    {
                        ray[i].angle -= game::player::rot_speed;
                        ray[i].rad = engine::math::toRad(ray[i].angle);
                        ray[i].cos = cos(ray[i].rad);
                        ray[i].sin = sin(ray[i].rad);
                        ray[i].tan = tan(ray[i].rad);
                        ray[i].ctg = tan(engine::math::toRad(90 - ray[i].angle));
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    game::player::angle += game::player::rot_speed;
                    for (unsigned int i = 0; i < game::render::rays_num; i++)
                    {
                        ray[i].angle += game::player::rot_speed;
                        ray[i].rad = engine::math::toRad(ray[i].angle);
                        ray[i].cos = cos(ray[i].rad);
                        ray[i].sin = sin(ray[i].rad);
                        ray[i].tan = tan(ray[i].rad);
                        ray[i].ctg = tan(engine::math::toRad(90 - ray[i].angle));
                    }
                }
            }
        }

        //w clear
        window3.clear();



        //DRAW BACKGROUND
        float a;
        for (unsigned __int16 i = 0; i < game::render::rays_num; i++)
        {
            if (ray[i].angle < 0)
            {
                a = game::world::textures::background::background_FOV - abs(fmod(ray[i].angle, game::world::textures::background::background_FOV));
            }
            else
            {
                a = abs(fmod(ray[i].angle, game::world::textures::background::background_FOV));
            }
            game::world::textures::background::sprite.setTextureRect(sf::IntRect(a * game::world::textures::background::WWTEXFOV * game::world::textures::background::WWSCALE, 0, game::world::textures::background::WWSCALE, game::window::height__2));
            game::world::textures::background::sprite.setPosition(i, 0);
            window3.draw(game::world::textures::background::sprite);
        }
        
        // OLD FLOOR
        for (unsigned __int8 i = 0; i < game::render::floor_detailing; i++)
        {
            //Floor.setSize(sf::Vector2f(game::window::width, floor.wh__2__rhd));
            //Floor.setPosition(0, game::window::height__2 + floor.wh__2__rhd * i);
            //Floor.setFillColor(sf::Color(0, floor.rhd255 * i, 0));
            //window3.draw(Floor);
        }

        //FLOOR TEST :(
        /*for (unsigned int y = 0; y < game::world::size; y++)
        {
            for (unsigned int x = 0; x < game::world::size; x++)
            {
                game::_any::_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE_ distance = floor.GET_SPRITE_FROM_MATRIX(y, x).GET_VERTICAL_SPRITE_QUAD_POSITION_DISTANCE();
                game::_any::_VERTICAL_SPRITE_QUAD_POSITION_ANGLE_ sprite_angle = floor.GET_SPRITE_FROM_MATRIX(y, x).GET_VERTICAL_SPRITE_QUAD_POSITION_ANGLE(distance);
                game::_any::_VERTICAL_SPRITE_QUAD_HEIGHT_ sprite_height = floor.GET_SPRITE_FROM_MATRIX(y, x).GET_VERTICAL_SPRITE_QUAD_HEIGHT(distance);

                float distanceY0 = floor.GET_SPRITE_FROM_MATRIX(y, x).QUAD_POSITION.y0 - game::player::pos.y;
                float distanceX0 = floor.GET_SPRITE_FROM_MATRIX(y, x).QUAD_POSITION.x0 - game::player::pos.x;
                float distanceY1 = floor.GET_SPRITE_FROM_MATRIX(y, x).QUAD_POSITION.y1 - game::player::pos.y;
                float distanceX1 = floor.GET_SPRITE_FROM_MATRIX(y, x).QUAD_POSITION.x1 - game::player::pos.x;

                float distanceHx0y0 = hypot(distanceX0, distanceY0);
                float distanceHx1y0 = hypot(distanceX1, distanceY0);
                float distanceHx0y1 = hypot(distanceX0, distanceY1);
                float distanceHx1y1 = hypot(distanceX1, distanceY1);

                float posX0 = engine::math::toDeg(atan2(distanceY0, distanceX0) - atan2(distanceHx0y0 * ray[0].sin, distanceHx0y0 * ray[0].cos)) * (game::window::width / game::render::FOV);
                float posX1 = engine::math::toDeg(atan2(distanceY0, distanceX1) - atan2(distanceHx1y0 * ray[0].sin, distanceHx1y0 * ray[0].cos)) * (game::window::width / game::render::FOV);
                float posX2 = engine::math::toDeg(atan2(distanceY1, distanceX0) - atan2(distanceHx0y1 * ray[0].sin, distanceHx0y1 * ray[0].cos)) * (game::window::width / game::render::FOV);
                float posX3 = engine::math::toDeg(atan2(distanceY1, distanceX1) - atan2(distanceHx1y1 * ray[0].sin, distanceHx1y1 * ray[0].cos)) * (game::window::width / game::render::FOV);
                
                float posY0 = game::window::height__2 + (sprite_height.x0y0 / 2);
                float posY1 = game::window::height__2 + (sprite_height.x1y0 / 2);
                float posY2 = game::window::height__2 + (sprite_height.x0y1 / 2);
                float posY3 = game::window::height__2 + (sprite_height.x1y1 / 2);

                convex.setPointCount(4);
                convex.setPoint(0, sf::Vector2f(posX0, posY0));
                convex.setPoint(1, sf::Vector2f(posX1, posY1));
                convex.setPoint(3, sf::Vector2f(posX2, posY2));
                convex.setPoint(2, sf::Vector2f(posX3, posY3));
                float Clr = engine::render::walls::getWallColor(distance.x0y0);
                convex.setFillColor(sf::Color(Clr * 0.5, Clr * 1, Clr * 0.1));
                window3.draw(convex);
                if (engine::player::getINTMatrixPos().x == x && engine::player::getINTMatrixPos().y == y)
                {
                    //ЗАПОЛНИТЬ ВСЁ ЧЁРНОЕ ПРОСТРАНСТВО
                }

            }
        }*/

        //RAYCASTING
        unsigned __int8 time = 0;
        unsigned __int16 thisnumwall = 0;
        float d = 0;
        float sx = 0;
        float sy = 0;
        unsigned __int8 wallsign = 0;
        float heightWall = 0;
        for (unsigned __int16 i = 0; i < game::render::rays_num; i++)
        {
            ray[i].pos = game::player::pos;
            //engine::render::raycasting::RAYRET rayret(engine::render::raycasting::raycast_v1(ray[i].angle));
            engine::render::raycasting::RAYRET rayret(engine::render::raycasting::raycast_v2(ray[i].angle, ray[i].cos, ray[i].sin, ray[i].tan, ray[i].ctg));
            ray[i].size = rayret.hypot;
            if (rayret.matrixpos.y >= 0 && rayret.matrixpos.y < game::world::size && rayret.matrixpos.x >= 0 && rayret.matrixpos.x < game::world::size)
            {
                wallsign = game::world::MATRIX[rayret.matrixpos.y][rayret.matrixpos.x];
            }

            switch (rayret.walldir)
            {
            case 0:
                d = fmod(rayret.pos.x, game::world::wall_size) * 0.9;
                break;
            case 1:
                d = fmod(rayret.pos.y, game::world::wall_size) * 0.9;
                break;
            case 2:
                d = (game::world::wall_size - fmod(rayret.pos.x, game::world::wall_size)) * 0.9;
                break;
            case 3:
                d = (game::world::wall_size - fmod(rayret.pos.y, game::world::wall_size)) * 0.9;
            }

            if (game::walls::arr[wallsign].MOD == false)
            {
                heightWall = engine::render::walls::getWallHeight(ray[i].size, ray[i].angle);
                if (i == 840)
                {
                    //cout << heightWall << endl;
                }
                //game::walls::arr[wallsign].Rect3D.setPosition(game::render::any::Rect3Dwidth * i, game::window::height__2 - (heightWall / 2));
                //game::walls::arr[wallsign].Rect3D.setTextureRect(sf::IntRect(d * game::walls::arr[wallsign].texWallscale, 0, game::walls::arr[wallsign].texWallscale, game::walls::arr[wallsign].texHeight));
                //game::walls::arr[wallsign].Rect3D.setScale(game::walls::arr[wallsign].R3Dscale, heightWall / game::walls::arr[wallsign].texHeight);
                //float wallClr = engine::render::walls::getWallColor(ray[i].size);
                //game::walls::arr[wallsign].Rect3D.setColor(sf::Color(wallClr, wallClr, wallClr));
                //window3.draw(game::walls::arr[wallsign].Rect3D);
            }
            else if (game::walls::arr[wallsign].MOD == 'm')
            {

                switch (rayret.walldir)
                {
                case 0:
                    sx = fmod(rayret.pos.x, game::world::wall_size);
                    sy = fmod(rayret.pos.y, game::world::wall_size);
                    break;
                case 1:
                    sy = fmod(rayret.pos.y, game::world::wall_size);
                    sx = fmod(rayret.pos.x, game::world::wall_size);
                    break;
                case 2:
                    sx = fmod(rayret.pos.x, game::world::wall_size);
                    sy = fmod(rayret.pos.y, game::world::wall_size);
                    break;
                case 3:
                    sy = 0;//fmod(rayret.pos.y, game::world::wall_size);
                    sx = fmod(rayret.pos.x, game::world::wall_size);
                }

                engine::render::raycasting::RAYRET mrayret(engine::render::raycasting::wall_m_raycast_v2(
                    wallsign,
                    ray[i].cos, ray[i].sin, ray[i].tan, ray[i].ctg,
                    sx, sy
                ));
                ray[i].size = rayret.hypot + mrayret.hypot;

                heightWall = engine::render::walls::getWallHeight(ray[i].size, ray[i].angle);
                game::walls::arr[wallsign].Rect3D.setPosition(game::render::any::Rect3Dwidth * i, game::window::height__2 - (heightWall / 2));
                game::walls::arr[wallsign].Rect3D.setTextureRect(sf::IntRect(d * game::walls::arr[wallsign].texWallscale, 0, game::walls::arr[wallsign].texWallscale, game::walls::arr[wallsign].texHeight));
                game::walls::arr[wallsign].Rect3D.setScale(game::walls::arr[wallsign].R3Dscale, heightWall / game::walls::arr[wallsign].texHeight);
                float wallClr = engine::render::walls::getWallColor(ray[i].size);
                game::walls::arr[wallsign].Rect3D.setColor(sf::Color(wallClr, wallClr, wallClr));
                //window3.draw(game::walls::arr[wallsign].Rect3D);

            }
        }
        //SPRITES_DRAW OLD VERSION
        /*for (unsigned __int16 i = 0; i < sprites_num; i++)
        {
            float player_dist0 = hypot(sprites[i].pos.x - game::player::pos.x, sprites[i].pos.y - game::player::pos.y);
            float angle0 = engine::math::toDeg(acos((sprites[i].pos.x - game::player::pos.x) / player_dist0));
            if (sprites[i].pos.y - game::player::pos.y < 0)
            {
                angle0 = -angle0;
            }

            float period = engine::math::getTrigonometricPeriod(ray[0].angle);
            float ray0angle = engine::math::getAngle(ray[0].angle, period);
            //if (angle0 > ray0angle && angle0 < (ray[game::render::any::rays_num1].angle - round(ray[game::render::any::rays_num1].angle / 360) * 360))
            //{
                float spriteHeight0 = engine::render::walls::getSpriteHeight(player_dist0);
                float RadAngle0 = engine::math::toRad(angle0);
                if (player_dist0 < engine::render::sprites::raycast_v1(cos(RadAngle0), sin(RadAngle0)))
                {
                    float posX0 = (angle0 - ray0angle) * (game::window::width / game::render::FOV);
                    float posY0 = game::window::height__2 + (spriteHeight0 / 2);
                    sprites[i].sprite.setPosition(posX0, posY0);
                    float scale = abs(spriteHeight0) * 0.001;
                    sprites[i].sprite.setScale(scale, scale);
                    window3.draw(sprites[i].sprite);
                }

            //}
        }*/

        sprites_num = sprites.size();
        for (unsigned int i = 0; i < sprites_num; i++)
        {
            sprites[i].angle = engine::math::getAngle(sprites[i].angle, engine::math::getTrigonometricPeriod(sprites[i].angle));
            _unsorted_sprites_length[i] = hypot((sprites[i].pos.x + (sprites[i].radius2 * cos(engine::math::toRad(sprites[i].angle)))) - game::player::pos.x, (sprites[i].pos.y + (sprites[i].radius2 * sin(engine::math::toRad(sprites[i].angle)))) - game::player::pos.y);
            _sorted_sprites[i] = i;
        }
        for (unsigned int i = 0; i < sprites_num; i++)
        {
            for (unsigned int l = 0; l < sprites_num; l++)
            {
                if (_unsorted_sprites_length[l] < _unsorted_sprites_length[l + 1])
                {
                    swap(_unsorted_sprites_length[l], _unsorted_sprites_length[l + 1]);
                    swap(_sorted_sprites[l], _sorted_sprites[l + 1]);
                }
            }
        }
        for (unsigned int g = 0; g < sprites_num; g++)
        {
            unsigned int i = _sorted_sprites[g];
            float px1 = sprites[i].pos.x + sprites[i].radius * cos(engine::math::toRad(sprites[i].angle));
            float py1 = sprites[i].pos.y + sprites[i].radius * sin(engine::math::toRad(sprites[i].angle));
            float player_dist0 = hypot(sprites[i].pos.x - game::player::pos.x, sprites[i].pos.y - game::player::pos.y);
            float player_dist1 = hypot(px1 - game::player::pos.x, py1 - game::player::pos.y);
            float angle0 = engine::math::toDeg(acos((sprites[i].pos.x - game::player::pos.x) / player_dist0));
            float angle1 = engine::math::toDeg(acos((px1 - game::player::pos.x) / player_dist1));
            if (sprites[i].pos.y - game::player::pos.y < 0)
            {
                angle0 = -angle0;
            }
            if (py1 - game::player::pos.y < 0)
            {
                angle1 = -angle1;
            }
            float period0 = engine::math::getTrigonometricPeriod(ray[0].angle);
            float ray0angle = engine::math::getAngle(ray[0].angle, period0);
            float period1 = engine::math::getTrigonometricPeriod(ray[game::render::any::rays_num1].angle);
            float ray1angle = engine::math::getAngle(ray[game::render::any::rays_num1].angle, period1);
            float spriteHeight0 = engine::render::walls::getSpriteHeight(player_dist0);
            float RadAngle0 = engine::math::toRad(angle0);
            float spriteHeight1 = engine::render::walls::getSpriteHeight(player_dist1);
            float RadAngle1 = engine::math::toRad(angle1);
            if ((player_dist0 < engine::render::sprites::raycast_v1(cos(RadAngle0), sin(RadAngle0))) && (player_dist1 < engine::render::sprites::raycast_v1(cos(RadAngle1), sin(RadAngle1))))
            {
                float posX0 = (angle0 - ray0angle) * (game::window::width / game::render::FOV);
                float posY0 = game::window::height__2 + (spriteHeight0 / 2) + sprites[i].uplift;
                float posX1 = (angle1 - ray0angle) * (game::window::width / game::render::FOV);
                float posY1 = game::window::height__2 + (spriteHeight1 / 2) + sprites[i].uplift;

                if (angle0 - ray0angle < -180)
                {
                    posX0 = abs(angle0 - ray0angle + 360) * (game::window::width / game::render::FOV);
                }
                if (angle1 - ray0angle < -180)
                {
                    posX1 = abs(angle1 - ray0angle + 360) * (game::window::width / game::render::FOV);
                }
                if (angle0 - ray0angle > 180)
                {
                    posX0 = abs(angle0 - ray0angle - 360) * (game::window::width / game::render::FOV);
                }
                if (angle1 - ray0angle > 180)
                {
                    posX1 = abs(angle1 - ray0angle - 360) * (game::window::width / game::render::FOV);
                }
                float scale0 = abs(spriteHeight0) * 0.002;
                float scale1 = abs(spriteHeight1) * 0.002;
                


                convex.setPoint(0, sf::Vector2f(posX0, posY0));
                convex.setPoint(1, sf::Vector2f(posX0, posY0 - sprites[i].height * scale0));
                convex.setPoint(3, sf::Vector2f(posX1, posY1));
                convex.setPoint(2, sf::Vector2f(posX1, posY1 - sprites[i].height * scale1));
                float Clr = engine::render::walls::getWallColor(player_dist1);
                convex.setTexture(&tex3);
                convex.setTextureRect(sf::IntRect(0,0,100,100));
                
                sf::Transform tr = convex.getTransform();

                sf::RectangleShape sh;
                sh.setTexture(&tex3);
                //sh.setSize();

                //convex.setFillColor(sf::Color(Clr * sprites[i].color.r, Clr * sprites[i].color.g, Clr * sprites[i].color.b));
                //window3.draw(tex3, tr);
            }
        }

        if (game::ingame_menu::active)
        {
            window3.draw(game::ingame_menu::sf.shape);
            for (unsigned int i = 0; i < game::ingame_menu::buttons_num; i++)
            {
                game::ingame_menu::buttons[i].sf.shape.setPosition(sf::Vector2f(game::ingame_menu::buttons[i].pos.x, game::ingame_menu::buttons[i].pos.y));
                game::ingame_menu::buttons[i].sf.shape.setSize(sf::Vector2f(game::ingame_menu::buttons[i].width, game::ingame_menu::buttons[i].height));
                game::ingame_menu::buttons[i].sf.shape.setFillColor(sf::Color(game::ingame_menu::buttons[i].background.color.r, game::ingame_menu::buttons[i].background.color.g, game::ingame_menu::buttons[i].background.color.b));
                window3.draw(game::ingame_menu::buttons[i].sf.shape);
                game::ingame_menu::buttons[i].sf.text.setFont(font);
                game::ingame_menu::buttons[i].sf.text.setString(game::ingame_menu::buttons[i].text.text);
                game::ingame_menu::buttons[i].sf.text.setPosition(sf::Vector2f(game::ingame_menu::buttons[i].pos.x, game::ingame_menu::buttons[i].pos.y));
                game::ingame_menu::buttons[i].sf.text.setCharacterSize(game::ingame_menu::buttons[i].text.size);
                game::ingame_menu::buttons[i].sf.text.setScale(sf::Vector2f(3, 1));
                game::ingame_menu::buttons[i].sf.text.setFillColor(sf::Color(game::ingame_menu::buttons[i].text.color.r, game::ingame_menu::buttons[i].text.color.g, game::ingame_menu::buttons[i].text.color.b));
                window3.draw(game::ingame_menu::buttons[i].sf.text);
                if (engine::utils::buttons::ClsButton(mouseX, mouseY, game::ingame_menu::buttons[i].pos.x, game::ingame_menu::buttons[i].pos.y, game::ingame_menu::buttons[i].width, game::ingame_menu::buttons[i].height))
                {
                    //ONCLICK EVENTS
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if (game::ingame_menu::buttons[i].onclick_event == "exit")
                        {
                            window3.close();
                        }
                        if (game::ingame_menu::buttons[i].onclick_event == "continue")
                        {
                            game::ingame_menu::active = false;
                            ShowCursor(false);
                        }
                        if (game::LAN::online_mode)
                        {
                            if (game::ingame_menu::buttons[i].onclick_event == "openLAN")
                            {
                                if (!_open_LAN_started)
                                {
                                    system("start openlan.exe");
                                    _open_LAN_started = true;
                                }
                            }
                            if (game::ingame_menu::buttons[i].onclick_event == "connectLAN")
                            {
                                if (!_connected_LAN)
                                {
                                    _connected_LAN = true;
                                    if (!player_was.sended_my_num)
                                    {
                                        sf::Packet packet;
                                        packet << "i am new player";
                                        if (socket.send(packet, recipient, serverport) == sf::Socket::Done)
                                        {
                                            cout << "Вы успешно подключились к серверу" << endl;
                                            player_was.sended_my_num = true;
                                        }
                                        else
                                        {
                                            _connected_LAN = false;
                                            player_was.sended_my_num = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //w display
        //FPS
        Time = clock.getElapsedTime();
        float lastTime = Time.asSeconds();
        float fps = 1 / (lastTime - currentTime);
        //FPStext.setString(to_string(fps));
        fps_all_val += fps;
        if (main_time == game::window::FPS_update_time)
        {
            FPStext.setString(to_string(engine::utils::get_average_value(fps_all_val, game::window::FPS_update_time) + 1));
            main_time = 0;
            fps_all_val = 0;
        }
        window3.draw(FPStext);
        window3.display();


        main_time++;

        if (!(game::window::w2_disable))
        {
            window2.clear();
            for (unsigned __int8 y = 0; y < game::world::size; y++)
            {
                for (unsigned __int8 x = 0; x < game::world::size; x++)
                {
                    if (game::walls::arr[game::world::MATRIX[y][x]].MOD == false)
                    {
                        if (game::world::MATRIX[y][x] == 1)
                        {
                            w2wall.setPosition
                            (
                                x * game::world::wall_size,
                                y * game::world::wall_size
                            );
                            w2wall.setSize(sf::Vector2f(game::world::wall_size, game::world::wall_size));
                            window2.draw(w2wall);
                        }
                    }
                    else if (game::walls::arr[game::world::MATRIX[y][x]].MOD == 'm')
                    {
                        for (unsigned __int8 my = 0; my < game::walls::arr[game::world::MATRIX[y][x]]._matrix.MATRIX_SIZE; my++)
                        {
                            for (unsigned __int8 mx = 0; mx < game::walls::arr[game::world::MATRIX[y][x]]._matrix.MATRIX_SIZE; mx++)
                            {
                                w2wall.setPosition
                                (
                                    x * game::world::wall_size + mx * game::walls::arr[game::world::MATRIX[y][x]]._matrix.WALL_SIZE,
                                    y * game::world::wall_size + my * game::walls::arr[game::world::MATRIX[y][x]]._matrix.WALL_SIZE
                                );
                                w2wall.setSize(sf::Vector2f(game::walls::arr[game::world::MATRIX[y][x]]._matrix.WALL_SIZE, game::walls::arr[game::world::MATRIX[y][x]]._matrix.WALL_SIZE));
                                window2.draw(w2wall);
                            }
                        }
                    }
                }
            }
            Player.setPosition(game::player::pos.x, game::player::pos.y);
            window2.draw(Player);
            sfray.setPosition(game::player::pos.x, game::player::pos.y);
            for (unsigned __int16 i = 0; i < game::render::rays_num; i++)
            {
                sfray.setSize(sf::Vector2f(ray[i].size, 1));
                sfray.setRotation(ray[i].angle);
                window2.draw(sfray);
            }
            window2.display();
        }

        //LAN
        if (_connected_LAN)
        {
            if (!player_was.getted_my_num)
            {
                sf::Packet packet0;
                packet0 << "give me my num";
                if (socket.send(packet0, recipient, serverport) == sf::Socket::Done)
                {
                    sf::Packet packet1;
                    socket.receive(packet1, sender, serverport);
                    string socket_event;
                    packet1 >> myplayer.num;
                    cout << "Ваш номер: " << static_cast<unsigned int>(myplayer.num) << endl;
                    player_was.getted_my_num = true;
                }
            }
            myplayer.angle = game::player::angle;
            myplayer.x = game::player::pos.x;
            myplayer.y = game::player::pos.y;

            if (myplayer.num == 0)
            {
                cout << "Мой номер: " << myplayer.num << " . И я подаю запрос на высылание моих stats." << endl;
                sf::Packet packet1;
                packet1 << "send myplayer stats? 0";
                if (socket.send(packet1, recipient, serverport) == sf::Socket::Done)
                {
                    sf::Packet packet2;
                    if (socket.receive(packet2, sender, serverport) == sf::Socket::Done)
                    {
                        cout << "Мой номер: " << myplayer.num << " . И сервер принял запрос на высылание моих stats. Жду ответа." << endl;
                        string event2;
                        packet2 >> event2;
                        if (event2 == "send myplayer stats! 0")
                        {
                            cout << "Мой номер: " << myplayer.num << " . И сервер приказал выслать мои stats." << endl;
                            sf::Packet packet3;
                            packet3 << myplayer.num << myplayer.angle << myplayer.x << myplayer.y;
                            if (socket.send(packet3, recipient, serverport) == sf::Socket::Done)
                            {
                                cout << "Мой номер: " << myplayer.num << " . И я выслал мои stats." << endl;
                            }
                        }
                    }
                }
            }
            if (myplayer.num == 1)
            {
                cout << "Мой номер: " << myplayer.num << " . И я подаю запрос на высылание моих stats." << endl;
                sf::Packet packet6;
                packet6 << "send myplayer stats? 1";
                if (socket.send(packet6, recipient, serverport) == sf::Socket::Done)
                {
                    sf::Packet packet7;
                    if (socket.receive(packet7, sender, serverport) == sf::Socket::Done)
                    {
                        cout << "Мой номер: " << myplayer.num << " . И сервер принял запрос на высылание моих stats. Жду ответа." << endl;
                        string event7;
                        packet7 >> event7;
                        if (event7 == "send myplayer stats! 1")
                        {
                            cout << "Мой номер: " << myplayer.num << " . И сервер приказал выслать мои stats." << endl;
                            sf::Packet packet3;
                            packet3 << myplayer.num << myplayer.angle << myplayer.x << myplayer.y;
                            if (socket.send(packet3, recipient, serverport) == sf::Socket::Done)
                            {
                                cout << "Мой номер: " << myplayer.num << " . И я выслал мои stats." << endl;
                            }
                        }
                    }
                }
            }

            sf::Packet packet4;
            sf::Packet packet5;
            if (myplayer.num == 1)
            {
                packet4 << "0";
                if (socket.send(packet4, recipient, serverport) == sf::Socket::Done)
                {
                    socket.receive(packet5, sender, serverport);
                    unsigned __int8 num;
                    float angle;
                    float x;
                    float y;
                    packet5 >> num >> angle >> x >> y;
                    players[0].angle = angle;
                    players[0].x = x;
                    players[0].y = y;
                }
                cout << "Player0 angle: " << sprites[0].angle << endl;
            }
            if (myplayer.num == 0)
            {
                packet4 << "1";
                if (socket.send(packet4, recipient, serverport) == sf::Socket::Done)
                {
                    socket.receive(packet5, sender, serverport);
                    unsigned __int8 num;
                    float angle;
                    float x;
                    float y;
                    packet5 >> num >> angle >> x >> y;
                    players[1].angle = angle;
                    players[1].x = x;
                    players[1].y = y;
                }
                cout << "Player1 angle: " << sprites[1].angle << endl;
            }
            for (unsigned int i = 0; i < 2; i++)
            {
                sprites[i].angle = players[i].angle;
                sprites[i].pos.x = players[i].x;
                sprites[i].pos.y = players[i].y;
            }
        }
    }
    return false;
}
