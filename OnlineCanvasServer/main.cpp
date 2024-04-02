#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

using namespace std;

int main()
{
    QSqlDatabase obj_db = QSqlDatabase::addDatabase("QSQLITE");

    if(QFile::exists("objects.db")){
        obj_db.setDatabaseName("objects.db");
        obj_db.open();
        qDebug()<< "ok";
    }
    else{
        qDebug()<< "not ok";
    }

    QSqlQuery query(obj_db);

    sf::TcpListener listener;
    listener.setBlocking(false);
    listener.listen(55001);

    sf::SocketSelector selector;
    vector<sf::TcpSocket*> clients;

    selector.add(listener);
    while (true)
    {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done) {
                    clients.push_back(client);
                    selector.add(*client);
                    QString q = "SELECT x, y, radius, r, g, b FROM Circles";
                    query.exec(q);
                    while (query.next()) {
                        sf::Packet pkgj;
                        pkgj << 0;
                        for (int i = 0; i < 6; ++i){
                            pkgj << query.value(i).toInt();
                        }
                        client->send(pkgj);
                    }
                    cout << "New connection from: " << client->getRemoteAddress() << endl;
                    cout << "Connections: " << clients.size() << endl;
                }
            }
            else {
                for (uint16_t i = 0; i < clients.size(); i++)
                {
                    sf::TcpSocket& client = *(clients[i]);
                    if (selector.isReady(client)) {
                        sf::Packet pkg;
                        sf::Socket::Status status = client.receive(pkg);
                        if (status == sf::Socket::Done) {
                            int type, x, y, radius, r, g, b, height, width;
                            pkg >> type;
                            if(type == 0){
                                pkg >> x >> y >> radius >> r >> g >> b;
                                QString msg = "INSERT INTO Circles (x, y, radius, r, g, b) VALUES (" + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(radius) + ", " + QString::number(r) + ", " + QString::number(g) + ", " + QString::number(b) + ");";
                                query.exec(msg);
                                obj_db.commit();

                                cout << "Received from client #" << i << ":" << endl;
                                cout << "Type: " << type << endl;
                                cout << "X: " << x << endl;
                                cout << "Y: " << y << endl;
                                cout << "Radius: " << radius << endl;
                                cout << "Color: " << r << ", " << g << ", " << b << endl;
                                cout << endl;
                            }
                            else if(type == 1){
                                pkg >> x >> y >> height >> width >> r >> g >> b;
                                QString msg = "INSERT INTO Rectangles (x, y, height, width, r, g, b) VALUES (" + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(height) + ", " + QString::number(width) + ", " + QString::number(r) + ", " + QString::number(g) + ", " + QString::number(b) + ");";
                                query.exec(msg);
                                obj_db.commit();

                                cout << "Received from client #" << i << ":" << endl;
                                cout << "Type: " << type << endl;
                                cout << "X: " << x << endl;
                                cout << "Y: " << y << endl;
                                cout << "Height: " << height << endl;
                                cout << "Width: " << width << endl;
                                cout << "Color: " << r << ", " << g << ", " << b << endl;
                                cout << endl;
                            }
                            for (uint16_t j = 0; j < clients.size(); j++)
                            {
                                if (i != j) {
                                    clients[j]->send(pkg);
                                }
                            }
                        }
                        else if (status == sf::Socket::Disconnected) {
                            selector.remove(client);
                            clients.erase(clients.begin() + i);
                            cout << "Client #" << i << " disconnected" << endl;
                            i--;
                            if (clients.size() == 0){
                                QString msg = "DELETE FROM Circles";
                                query.exec(msg);
                                obj_db.commit();
                            }
                        }
                        else if (status == sf::Socket::Error) {
                            cout << "Error while receiving package" << endl;
                        }
                        else {
                            cout << "No data " << rand() % 25 << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
