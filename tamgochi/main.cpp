#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;


struct Res
{
    int food = 15, medic_kit = 15, soap = 15, toilet = 15, money = 30, toy = 15;
};


class Tamagochi{
private:
    int health = 100;
    const int max_health = 100;

    int satiety = 100;
    const int max_satiety = 100;

    int happiness = 100;
    const int max_happiness = 100;

    int clearness = 100;
    const int max_clearness = 100;

    int nat_need = 0;
    const int max_nat_need = 100;

    string Name = "";
public:
    void Change_name(string s){
        this->Name = s;
    }

    int Feed(int& i){
        if (0 <= i && i < max_satiety){
            this->satiety = min(max_satiety, satiety + i);
            return this->satiety;
        }
        return 0;
    }

    int Wash(int& i){
        if (0 <= i  && i < max_clearness){
            this->clearness = min(max_clearness, clearness + i);
            return this->clearness;
        }
        return 0;
    }

    int Make_happy(int& i){
        if (0 <= i && i < max_happiness){
            this->happiness = min(max_happiness, happiness + i);
            return this->happiness;
        }
        return 0;
    }

    int Bathroom(int& i){
        if (0 <= i && i < max_nat_need){
            this->nat_need = min(max_nat_need, nat_need + i);
            return this->nat_need;
        }
        return 0;
    }

    Tamagochi(string s) : Name{s} {}
};




class Owner{
private:
    int sanity = 100;
    const int max_sanity = 100;

    int health = 100;
    const int max_health = 100;

    int satiety = 100;
    const int max_satiety = 100;

    int happiness = 100;
    const int max_happiness = 100;

    int clearness = 100;
    const int max_clearness = 100;

    int nat_need = 0;
    const int max_nat_need = 100;
    int money = 100;

    string Name = "";
public:
    void Change_name(string s){
        this->Name = s;
    }

    int Eat(int& i){
        if (0 <= i && i < max_satiety){
            this->satiety = min(max_satiety, satiety + i);
            return this->satiety;
        }
        return 0;
    }

    int Wash(int& i){
        if (0 <= i  && i < max_clearness){
            this->clearness = min(max_clearness, clearness + i);
            return this->clearness;
        }
        return 0;
    }

    int Play_games(int& i){
        if (0 <= i && i < max_happiness){
            this->happiness = min(max_happiness, happiness + i);
            return this->happiness;
        }
        return 0;
    }

    int Bathroom(int& i){
        if (0 <= i && i < max_nat_need){
            this->nat_need = min(max_nat_need, nat_need + i);
            return this->nat_need;
        }
        return 0;
    }

    int Code(int& i){
        if (0 <= i){
            this->money += i;
            this->sanity -= 10;
            return this->money;
        }
        return 0;
    }
    int Relax(int& i){
        if (0 <= i && i < max_sanity){
            this->sanity = min(max_sanity, sanity + i);
            return this->sanity;
        }
        return 0;
    }
    Owner(string s) : Name{s} {}
};



void info(Tamagochi tam, Owner ow){
    int f = 0;
    cout<<"���� ���������\n"<<
          "1: �������: "<< ow.Eat(f)<<"\n"<<
          "2: �������: "<< ow.Wash(f)<<"\n"<<
          "3: �����: "<< ow.Bathroom(f)<<"\n"<<
          "4: ������: "<< ow.Code(f)<<"\n"<<
          "5: ��������: "<< ow.Relax(f)<<"\n"<<
          "6: �������: "<< ow.Play_games(f)<<"\n";

    cout<<"��������� ������ �������:"<<
          "1: �������: "<< tam.Feed(f)<<"\n"<<
          "2: �������: "<< tam.Wash(f)<<"\n"<<
          "3: �����: "<< tam.Bathroom(f)<<"\n"<<
          "4: �������: "<< tam.Make_happy(f)<<"\n";
}



int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<Tamagochi> Tamagochies;
    Owner Me("Masturbek");
    Tamagochi tam("Joe");
    Res res;

    for (int i = 0; i < 4; i++){
        Tamagochies.push_back(tam);
    }

    int input;

    cout<<"����� ���������� � ��������, ��� ���� ������ � ����� ����������, ��� ��� �� ����� ������ ����������)\n\n";

    while (input != 5){
        cout<<"������ ���� ���-�� ������ ��� � ��������?\n"<<
              "(1) ������ ���\n"<<
              "(2) ������ � ��������\n";

        cin>>input;

        if (input == 2){
            cout<<"��� ������ ������?\n"<<
                  "(1) ��������� ��������\n"<<
                  "(2) �������� ��������\n"<<
                  "(3) �������� � ��������\n"<<
                  "(4) ������ ��������\n";

            switch(input){
            case 1:
                cout<<"�� ��������� ��������\n";
                tam.Feed(res.food);
                break;
            case 2:
                cout<<"�� �������� �  ��������\n";
                tam.Bathroom(res.toilet);
                break;
            case 3:
                cout<<"�� �������� � ��������\n";
                tam.Make_happy(res.toy);
                break;
            case 4:
                cout<<"�� ������ ��������\n";
                tam.Wash(res.soap);
                break;
            default:
                cout<<"�������"<<endl;
                break;
            }
        info(Tamagochies[0], Me);
        }
        cin>>input;
    }
    return 0;
}
