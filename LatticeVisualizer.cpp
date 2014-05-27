#include "Set.h"
#include "BinRelation.h"
#include "Poset.h"
#include "LatticeNode.h"

#include "Window.h"
#include "utilities.h"

#include <vector>

using namespace std;

void toAntichains(const Poset<LatticeNode>& poset, vector< vector<LatticeNode> >& v) {
    Poset<LatticeNode> temp = poset;

    //O(n^2)
    while ( !temp.empty() ) {
        vector<LatticeNode> level; //накапливаем новый этаж

        for ( typename Poset<LatticeNode>::iterator i = poset.begin(); i != poset.end(); i++ ) {
            bool minimal = true;

            for ( typename Poset<LatticeNode>::iterator j = temp.begin(); j != temp.end(); j++ ) {
                if ( *i > *j ) {
                    minimal = false;
                }
            }

            if ( minimal ) {
                level.push_back(i->getData());
                temp.remove(*i);
            }
        }

        v.push_back(level);
    }
}

int main() {
    Window w;
    Poset<LatticeNode> poset;
    vector< vector<LatticeNode> > antichains;

    if ( !readPoset("test.lat", poset) ) {
        cout << "File reading error!" << endl;
        return 1;
    }

    toAntichains(poset, antichains);

    cout << antichains.size() << endl;

    w.initialize(800, 600, 0, 0, "Test");

    while ( w.isRun() ) {
        SDL_Event e;
        
        while ( SDL_PollEvent(&e) ) {
            if ( e.type == SDL_QUIT ||
                (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) ) {
                w.stop();
            }            
        }

        w.clearScreen();

        const int step = 100;
        const int X = 400;
        const int Y = 500;

        drawLine(w.getScreen(), X, Y, X - step, Y - step, 0xff0000, 0xff0000);
        drawLine(w.getScreen(), X, Y, X, Y - step, 0xff0000, 0xff0000);
        drawLine(w.getScreen(), X, Y, X + step, Y - step, 0xff0000, 0xff0000);

        drawLine(w.getScreen(), X - step, Y - step, X, Y - 2*step, 0xff0000, 0xff0000);
        drawLine(w.getScreen(), X, Y - step, X, Y - 2*step, 0xff0000, 0xff0000);
        drawLine(w.getScreen(), X + step, Y - step, X, Y - 2*step, 0xff0000, 0xff0000);

        /*for ( int i = 0; i < antichains.size() - 1; i++ ) {
            for ( int j = 0; j < antichains[i].size(); j++ ) {
                for ( int k = 0; k < antichains[i+1].size(); k++ ) {
                    drawLine(w.getScreen(), X - step*j , Y - step*j, 
                        X - step*k, Y - step*k, 0xff0000, 0xff0000);
                }
            }
        }*/

        w.presentScreen();
    }

    return 0;
}