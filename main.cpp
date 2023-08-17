#include "Window.h"
#include <iostream>
#include "_raygui.h"
#include "core/Api.h"

int main() {
    Dicts dicts;
    Api api(dicts);
    Window window(&api);
    window.run();
    return 0;
}
