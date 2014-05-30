#include "BinRelation.h"
#include "Poset.h"
#include "Node.h"

#include "Window.h"
#include "utilities.h"

#include <vector>
#include <iostream>

using namespace std;

#define STEP    100

//на входе: file - имя файла; poset - ч.у.м.
bool readPoset(const char* file, Poset& poset) {
    int elemCount, num;
    string str;
    std::set<Node> tmpSet;
    BinRelation tmpOrd;
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

    //чтение "матрицы отношений"
    for ( int i = 0; i < elemCount; i++ ) {
        f >> str; //считываем строку

        for ( int j = 0; j < elemCount; j++ ) { //цикл по столбцам
            if ( str[j] == '1' ) { //если элемент i < элемента j
                tmpOrd.insert(nodes[i], nodes[j]);
            }
        }
    }
    poset.initialize(tmpSet, tmpOrd);

    f.close();

    return true;
}

//на входе: poset - ч.у.м.; v - вектор, в который сохранятся антицепи
void toAntichains(const Poset& poset, vector< vector<Node> >& v) {
    Poset temp = poset;

    //O(n^2)
    while ( !temp.emptySet() ) {
        vector<Node> level; //накапливаем новую антицепь

        for ( Poset::iterator i = temp.begin(); i != temp.end(); ) {
            bool minimal = true; //по умолчанию, j-ый элемент - минимальный

            for ( Poset::iterator j = temp.begin(); j != temp.end(); j++ ) {
                if ( Node::compare(*i, *j) == ORD_GRT ) { //если *i > *j
                    minimal = false;
                    break;
                }
            }

            Poset::iterator t = i;
            i++;

            if ( minimal ) {
                level.push_back(*t);
                temp.remove(*t);
            }
        }

        v.push_back(level);
    }
}

void drawLatticeByAntichains(SDL_Surface* s, const vector< vector<Node> >& antichains) {

    const int X = s->w / 2;
    const int Y = s->h;

    for ( u32 i = 0; i < antichains.size() - 1; i++ ) {
        int startXi = X - (antichains[i].size() - 1) * STEP / 2;
        int startYi = Y - i * STEP;

        for ( u32 j = 0; j < antichains[i].size(); j++ ) {
            for ( u32 k = i+1; k < antichains.size(); k++ ) {
                int startXk = X - (antichains[k].size() - 1) * STEP / 2;
                int startYk = Y - k * STEP;

                for ( u32 l = 0; l < antichains[k].size(); l++ ) {
                    if ( Node::coversStrictly(antichains[k][l], antichains[i][j]) ) {
                        int x1 = startXi + STEP * j;
                        int x2 = startXk + STEP * l;

                        drawLine(s, x1, startYi, x2, startYk, 0x00ff00, 0x00ff00);

                        drawDot(s, x1, startYi, 6, 0xff0000);
                        drawDot(s, x2, startYk, 6, 0xff0000);
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
        cout << "Too few parameters!" << endl;
        return 1;
    }

    if ( !readPoset(argv[1], poset) ) {
        cout << "File reading error!" << endl;
        return 1;
    }

    toAntichains(poset, antichains);

    w.initialize(800, 600, 0, 0, "Test");

    cout << antichains[0].size() << " " << antichains[1].size() << " " << antichains[2].size() << endl;

    while ( w.isRun() ) {
        SDL_Event e;
        
        while ( SDL_PollEvent(&e) ) {
            if ( e.type == SDL_QUIT ||
                (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) ) {
                w.stop();
            }            
        }

        w.clearScreen();
        drawLatticeByAntichains(w.getScreen(), antichains);
        w.presentScreen();
    }

    return 0;
}