#include "rock/application.h"

int main(int argc, char** argv) {
    rock::Application app;
    if(app.init(argc, argv)) {
        return app.run();
    }
    return 0;
}
