#include "BinRelation.h"
#include "Poset.h"
#include "Node.h"

#include "Window.h"
#include "utilities.h"

#include <vector>
#include <iostream>

using namespace std;

#define STEP_X    100 //расстояние между элементами по оси X
#define STEP_Y    110 //расстояние между элементами по оси Y
#define WIDTH     1024 //ширина окна
#define HEIGHT    768 //высота окна

//на входе: file - имя файла; poset - ч.у.м.
bool readPoset(const char* file, Poset& poset) {
    int elemCount, num;
    string str;
    std::set<Node> tmpSet; //хранит временное множество элементов
    BinRelation tmpOrd; //временное бинарное отношение
    vector<Node> nodes;

    ifstream f(file);

    if ( !f ) { //если файл не открылся, завершаем работу с ошибкой
        return false;
    }

    f >> elemCount; //считываем количество элементов множества

    //чтение множества
    for ( int i = 0; i < elemCount; i++ ) {
        f >> num; //считываем номер узла
        f >> str; //считываем имя узла

        tmpSet.insert(Node(num, str, &poset));
        nodes.push_back(Node(num, str, &poset));
    }

    //чтение матрицы отношений
    for ( int i = 0; i < elemCount; i++ ) {
        f >> str; //считываем строку

        for ( int j = 0; j < elemCount; j++ ) { //цикл по столбцам
            if ( str[j] == '1' ) { //если элемент i < элемента j
                tmpOrd.insert(nodes[i], nodes[j]);
            }
        }
    }
    poset.initialize(tmpSet, tmpOrd); //инициализация ч.у.м.а

    f.close();

    return true;
}

//на входе: poset - ч.у.м.; v - вектор, в который сохранятся антицепи
void toAntichains(const Poset& poset, vector< vector<Node> >& v) {
    Poset temp1 = poset;
    Poset temp2 = poset;

    //O(n^2)
    while ( !temp1.emptySet() ) {
        vector<Node> level; //накапливаем новую антицепь

        for ( Poset::iterator i = temp1.begin(); i != temp1.end(); ) {
            bool minimal = true; //по умолчанию i-ый элемент - минимальный

            for ( Poset::iterator j = temp2.begin(); j != temp2.end(); j++ ) {
                if ( Node::compare(*i, *j) == ORD_GRT ) { //если *i > *j
                    minimal = false; //значит, *i - не минимальный
                    break;
                }
            }

            Poset::iterator t = i;
            i++;

            if ( minimal ) { //если минимальный
                level.push_back(*t); //сохраняем в антицепь
                temp1.remove(*t); //удаляем
            }
        }

        temp2 = temp1;
        v.push_back(level); //сохраняем полученную антицепь
    }
}

void drawLatticeByAntichains(SDL_Surface* s, const vector< vector<Node> >& antichains) {
    const int X = s->w / 2; //точка отсчета по X и Y
    const int Y = s->h;

    //для каждой антицепи: находим "центр" (количество элементов * расстояние между) / 2
    for ( u32 i = 0; i < antichains.size(); i++ ) {
        const int startXi = X - (antichains[i].size() - 1) * STEP_X / 2;
        const int startYi = Y - i * STEP_Y;

        for ( u32 j = 0; j < antichains[i].size(); j++ ) {
            const int xj = startXi + j * STEP_X;

            drawDot(s, xj, startYi, 8, 0xff0000);

            for ( u32 k = i+1; k < antichains.size(); k++ ) {
                //для каждого элемента в антицепи просматриваем элементы из оставшихся антицепей
                const int startXk = X - (antichains[k].size() - 1) * STEP_X / 2;
                const int startYk = Y - k * STEP_Y;

                for ( u32 l = 0; l < antichains[k].size(); l++ ) {
                    const int xk = startXk + l * STEP_X;

                    if ( Node::coversStrictly(antichains[k][l], antichains[i][j]) ) {
                        //если какой-то элемент покрывает фиксированный, соединяем их прямой
                        drawLine(s, xj, startYi, xk, startYk, 0x00ff00);
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    Window w;
    Poset poset;
    vector< vector<Node> > antichains;

    if ( argc < 2 ) {
        cout << "Too few arguments!" << endl;
        return 1;
    }

    if ( !readPoset(argv[1], poset) ) {
        cout << "File reading error!" << endl;
        return 1;
    }
    cout << "Poset size: " << poset.sizeSet() << endl; //информация о ч.у.м.е
    cout << "Order size: " << poset.sizeOrder() << endl;

    toAntichains(poset, antichains);

    cout << "Antichains count: " << antichains.size() << endl; //Информация об антицепях
    cout << "Size of each antichain: ";
    for ( u32 i = 0; i < antichains.size(); i++ ) {
        cout << antichains[i].size() << "  ";
    } cout << endl;

    w.initialize(WIDTH, HEIGHT, "LatticeVisualizer v0.1 beta");

    while ( w.isRun() ) {
        SDL_Event e;
        
        while ( SDL_PollEvent(&e) ) {
            if ( e.type == SDL_QUIT ||
                (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) ) {
                w.stop();
                break;
            }            
        }

        w.clearScreen();
        drawLatticeByAntichains(w.getScreen(), antichains);
        w.presentScreen();
    }

    return 0;
}