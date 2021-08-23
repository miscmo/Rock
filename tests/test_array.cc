#include "rock/rock.h"
#include "rock/ds/array.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

struct PidVid {
    PidVid(uint32_t p = 0, uint32_t v = 0)
        :pid(p), vid(v) {}
    uint32_t pid;
    uint32_t vid;

    bool operator<(const PidVid& o) const {
        return memcmp(this, &o, sizeof(o)) < 0;
    }
};

void gen() {
    rock::ds::Array<int> tmp;
    std::vector<int> vs;
    for(int i = 0; i < 10000; ++i) {
        int v = rand();
        tmp.insert(v);
        vs.push_back(v);
        ROCK_ASSERT(tmp.isSorted());
    }

    std::ofstream ofs("./array.data");
    tmp.writeTo(ofs);

    for(auto& i : vs) {
        auto idx = tmp.exists(i);
        ROCK_ASSERT(idx >= 0);
        tmp.erase(idx);
        ROCK_ASSERT(tmp.isSorted());
    }
    ROCK_ASSERT(tmp.size() == 0);
    
}

void test() {
    for(int i = 0; i < 10000; ++i) {
        ROCK_LOG_INFO(g_logger) << "i=" << i;
        std::ifstream ifs("./array.data");
        rock::ds::Array<int> tmp;
        if(!tmp.readFrom(ifs)) {
            ROCK_LOG_INFO(g_logger) << "error";
        }
        ROCK_ASSERT(tmp.isSorted());
        if(i % 100 == 0) {
            ROCK_LOG_INFO(g_logger) << "over..." << (i + 1);
        }
    }
}

int main(int argc, char** argv) {
    gen();
    test();
    return 0;
}
