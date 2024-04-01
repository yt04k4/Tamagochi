#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace std;

int getRandomInt(int A, int B)
{
    if (A > B) { int T = A; A = B; B = T; }
    return A + rand() % (B - A + 1);
}

sf::Packet CircleShapeToPacket(sf::CircleShape cs)
{
    sf::Packet pkg;
    int type = 0;
    int x = cs.getPosition().x;
    int y = cs.getPosition().y;
    int radius = cs.getRadius();
    int r = cs.getFillColor().r;
    int g = cs.getFillColor().g;
    int b = cs.getFillColor().b;
    pkg << type << x << y << radius << r << g << b;
    return pkg;
}

sf::CircleShape PacketToCircleShape(sf::Packet pkg)
{
    sf::CircleShape cs;
    int x, y, radius, r, g, b;
    pkg >> x >> y >> radius >> r >> g >> b;
    cs.setPosition(x, y);
    cs.setRadius(radius);
    cs.setOrigin(radius, radius);
    cs.setFillColor(sf::Color(r, g, b));
    return cs;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Shapka okna");
    window.setFramerateLimit(100);
    sf::TcpSocket socket;
    socket.setBlocking(false);
    socket.connect("26.213.232.21", 55001);

    vector<sf::CircleShape>circles;
    while (window.isOpen()) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            if (evt.type == sf::Event::MouseButtonPressed) {
                int mx = evt.mouseButton.x;
                int my = evt.mouseButton.y;

                sf::CircleShape shape;
                shape.setPosition(mx, my);
                int radius = getRandomInt(30,50);
                shape.setRadius(radius);
                shape.setFillColor(sf::Color(getRandomInt(0, 255), getRandomInt(0, 255), getRandomInt(0, 255)));
                shape.setOrigin(radius, radius);
                circles.push_back(shape);

                sf::Packet pkg = CircleShapeToPacket(shape);
                socket.send(pkg);
                cout << "Package sent" << endl;
            }
        }
        sf::Packet serverPkg;
        if (socket.receive(serverPkg) == sf::Socket::Done)
        {
            cout << "You have a new incoming package" << endl;
            int type;
            serverPkg >> type;
            if (type == 0) {
                sf::CircleShape shape = PacketToCircleShape(serverPkg);
                circles.push_back(shape);
            }
        }

        window.clear();
        for (uint16_t i = 0; i < circles.size(); i++)
        {
            window.draw(circles[i]);
        }

        window.display();
    }


    return 0;
}
