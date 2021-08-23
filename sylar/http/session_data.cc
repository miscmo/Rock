#include "session_data.h"
#include "rock/util.h"

namespace rock {
namespace http {

SessionData::SessionData(bool auto_gen)
    :m_lastAccessTime(time(0)) {
    if(auto_gen) {
        std::stringstream ss;
        ss << rock::GetCurrentUS() << "|" << rand() << "|" << rand() << "|" << rand();
        m_id = rock::md5(ss.str());
    }
}

void SessionData::del(const std::string& key) {
    rock::RWMutex::WriteLock lock(m_mutex);
    m_datas.erase(key);
}

bool SessionData::has(const std::string& key) {
    rock::RWMutex::ReadLock lock(m_mutex);
    auto it = m_datas.find(key);
    return it != m_datas.end();
}

void SessionDataManager::add(SessionData::ptr info) {
    rock::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getId()] = info;
}

SessionData::ptr SessionDataManager::get(const std::string& id) {
    rock::RWMutex::ReadLock lock(m_mutex);
    auto it = m_datas.find(id);
    if(it != m_datas.end()) {
        it->second->setLastAccessTime(time(0));
        return it->second;
    }
    return nullptr;
}

void SessionDataManager::check(int64_t ts) {
    uint64_t now = time(0) - ts;
    std::vector<std::string> keys;
    rock::RWMutex::ReadLock lock(m_mutex);
    for(auto& i : m_datas) {
        if(i.second->getLastAccessTime() < now) {
            keys.push_back(i.first);
        }
    }
    lock.unlock();
    for(auto& i : keys) {
        del(i);
    }
}

void SessionDataManager::del(const std::string& id) {
    rock::RWMutex::WriteLock lock(m_mutex);
    m_datas.erase(id);
}

}
}
