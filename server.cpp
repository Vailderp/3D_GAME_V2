#include "SFML/Network.hpp"
#include "LAN.h";
#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
// IT IS THE UDP SERVER / GAFIEV VLADISLAV /

int main()
{
    setlocale(LC_ALL, "Russian");

    unsigned __int8 data[1] = { 0 };
    sf::UdpSocket socket;
    socket.bind(2004);
    // UDP socket:
    sf::IpAddress recipient = "192.168.0.105";
    unsigned short port = 2004;
    unsigned short _port2 = 2004;
    unsigned short _port = 2004;

    unsigned short playerport;
    unsigned short _playerport;

    std::size_t received;
    sf::IpAddress sender;
    sf::IpAddress _sender;

    class SOCKETPLAYER
    {
    public:
        unsigned __int16 port = 0;
        unsigned __int16 num;
    };

    unsigned __int8 players_num = 0;
    SOCKETPLAYER socketplayers[2];
    LAN::PLAYER players[2] = {};


    while (true)
    {
        sf::Packet packet;
        if (socket.receive(packet, sender, playerport) == sf::Socket::Done)
        {
            string server_event;
            packet >> server_event;

            if (server_event == "i am new player")
            {
                //packet >> playerport;
                socketplayers[players_num].num = players_num;
                socketplayers[players_num].port = playerport;
                cout << "Игрок номер " << socketplayers[players_num].num << " присоединился к игре с портом " << socketplayers[players_num].port << endl;
                players_num++;
            }

            if (server_event == "give me my num")
            {
                unsigned __int8 num0 = 0;

                for (unsigned int i = 0; i < 2; i++)
                {
                    if (socketplayers[i].port == playerport)
                    {
                        num0 = socketplayers[i].num;
                    }
                }

                sf::Packet packet0;
                packet0 << num0;
                socket.send(packet0, sender, playerport);
                cout << "Номер игрока был отправлен" << num0 << endl;
            }

            if (server_event == "send myplayer stats? 0")
            {
                sf::Packet packet1;
                packet1 << "send myplayer stats! 0";
                if (socket.send(packet1, sender, playerport) == sf::Socket::Done)
                {
                    sf::Packet packet2;
                    socket.receive(packet2, _sender, _playerport);
                    unsigned __int8 num;
                    float x;
                    float y;
                    float angle;
                    packet2 >> num >> angle >> x >> y;
                    players[0].angle = angle;
                    players[0].num = num;
                    players[0].x = x;
                    players[0].y = y;

                    //cout << "Player stats: " << " NUM: " << num << " ANGLE: " << angle << " X: " << x << " Y: " << y << endl;
                }
            }

            if (server_event == "send myplayer stats? 1")
            {
                sf::Packet packet5;
                packet5 << "send myplayer stats! 1";
                if (socket.send(packet5, sender, playerport) == sf::Socket::Done)
                {
                    sf::Packet packet6;
                    socket.receive(packet6, _sender, _playerport);
                    unsigned __int8 num;
                    float x;
                    float y;
                    float angle;
                    packet6 >> num >> angle >> x >> y;
                    players[1].angle = angle;
                    players[1].num = num;
                    players[1].x = x;
                    players[1].y = y;

                    //cout << "Player stats: " << " NUM: " << num << " ANGLE: " << angle << " X: " << x << " Y: " << y << endl;
                }
            }

            if (server_event == "0")
            {
                sf::Packet packet3;
                packet3 << players[0].num << players[0].angle << players[0].x << players[0].y;
                socket.send(packet3, sender, playerport);
            }
            if (server_event == "1")
            {
                sf::Packet packet4;
                packet4 << players[1].num << players[1].angle << players[1].x << players[1].y;
                socket.send(packet4, sender, playerport);
            }
        }
    }
	return true;
}
