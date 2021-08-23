#include "rock/uri.h"
#include <iostream>

int main(int argc, char** argv) {
    //rock::Uri::ptr uri = rock::Uri::Create("http://www.rock.top/test/uri?id=100&name=rock#frg");
    //rock::Uri::ptr uri = rock::Uri::Create("http://admin@www.rock.top/test/中文/uri?id=100&name=rock&vv=中文#frg中文");
    rock::Uri::ptr uri = rock::Uri::Create("http://admin@www.rock.top");
    //rock::Uri::ptr uri = rock::Uri::Create("http://www.rock.top/test/uri");
    std::cout << uri->toString() << std::endl;
    auto addr = uri->createAddress();
    std::cout << *addr << std::endl;
    return 0;
}
