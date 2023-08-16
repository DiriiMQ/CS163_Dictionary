#include "Window.h"
#include <iostream>
#include "_raygui.h"
#include "core/Api.h"

int main() {
    //Window  window;
    //window.run();
    Dicts dicts;
    Api api(dicts);
    std::cout << dicts.dicts[0].Map.size() << std::endl;
    std::cout << dicts.dicts[1].Map.size() << std::endl;
    std::cout << dicts.dicts[2].Map.size() << std::endl;
    std::cout << "load in " << 1.0*clock()/CLOCKS_PER_SEC << std::endl;
    return 0;
}
