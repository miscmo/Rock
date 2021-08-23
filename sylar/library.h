#ifndef __ROCK_LIBRARY_H__
#define __ROCK_LIBRARY_H__

#include <memory>
#include "module.h"

namespace rock {

class Library {
public:
    static Module::ptr GetModule(const std::string& path);
};

}

#endif
