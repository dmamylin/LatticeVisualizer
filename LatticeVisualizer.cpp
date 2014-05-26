#include "Set.h"
#include "BinRelation.h"
#include "Poset.h"
#include "LatticeNode.h"

int main() {
    Poset<LatticeNode> poset;

    readPoset("test.lat", poset);

    return 0;
}