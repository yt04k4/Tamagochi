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
    cout<<"Ваше состояние\n"<<
          "1: Сытость: "<< ow.Eat(f)<<"\n"<<
          "2: Чистота: "<< ow.Wash(f)<<"\n"<<
          "3: Нужда: "<< ow.Bathroom(f)<<"\n"<<
          "4: Деньги: "<< ow.Code(f)<<"\n"<<
          "5: Рассудок: "<< ow.Relax(f)<<"\n"<<
          "6: Счастье: "<< ow.Play_games(f)<<"\n";

    cout<<"Состояние вашего питомца:"<<
          "1: Сытость: "<< tam.Feed(f)<<"\n"<<
          "2: Чистота: "<< tam.Wash(f)<<"\n"<<
          "3: Нужда: "<< tam.Bathroom(f)<<"\n"<<
          "4: Счастье: "<< tam.Make_happy(f)<<"\n";
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

    cout<<"Добро пожаловать в Тамагочи, это игра только в альфа разработке, так что не будте строги пожалуйста)\n\n";

    while (input != 5){
        cout<<"Будете сами что-то делать или с тамагочи?\n"<<
              "(1) Сделаю сам\n"<<
              "(2) Сделаю с тамагочи\n";

        cin>>input;

        if (input == 2){
            cout<<"Что хотите делать?\n"<<
                  "(1) Покормить тамагочи\n"<<
                  "(2) Выгулять тамагочи\n"<<
                  "(3) Поиграть с тамагочи\n"<<
                  "(4) Помыть тамагочи\n";

            switch(input){
            case 1:
                cout<<"Вы покормили тамагочи\n";
                tam.Feed(res.food);
                break;
            case 2:
                cout<<"Вы погуляли с  тамагочи\n";
                tam.Bathroom(res.toilet);
                break;
            case 3:
                cout<<"Вы поиграли с тамагочи\n";
                tam.Make_happy(res.toy);
                break;
            case 4:
                cout<<"Вы помыли тамагочи\n";
                tam.Wash(res.soap);
                break;
            default:
                cout<<"Мисклик"<<endl;
                break;
            }
        info(Tamagochies[0], Me);
        }
        cin>>input;
    }
    return 0;
}
