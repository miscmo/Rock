#ifndef __ROCK_NS_NAME_SERVER_MODULE_H__
#define __ROCK_NS_NAME_SERVER_MODULE_H__

#include "rock/module.h"
#include "ns_protocol.h"

namespace rock {
namespace ns {

class NameServerModule;
class NSClientInfo {
friend class NameServerModule;
public:
    typedef std::shared_ptr<NSClientInfo> ptr;
private:
    NSNode::ptr m_node;
    std::map<std::string, std::set<uint32_t> > m_domain2cmds;
};

class NameServerModule : public RockModule {
public:
    typedef std::shared_ptr<NameServerModule> ptr;
    NameServerModule();

    virtual bool handleRockRequest(rock::RockRequest::ptr request
                        ,rock::RockResponse::ptr response
                        ,rock::RockStream::ptr stream) override;
    virtual bool handleRockNotify(rock::RockNotify::ptr notify
                        ,rock::RockStream::ptr stream) override;
    virtual bool onConnect(rock::Stream::ptr stream) override;
    virtual bool onDisconnect(rock::Stream::ptr stream) override;
    virtual std::string statusString() override;
private:
    bool handleRegister(rock::RockRequest::ptr request
                        ,rock::RockResponse::ptr response
                        ,rock::RockStream::ptr stream);
    bool handleQuery(rock::RockRequest::ptr request
                        ,rock::RockResponse::ptr response
                        ,rock::RockStream::ptr stream);
    bool handleTick(rock::RockRequest::ptr request
                        ,rock::RockResponse::ptr response
                        ,rock::RockStream::ptr stream);

private:
    NSClientInfo::ptr get(rock::RockStream::ptr rs);
    void set(rock::RockStream::ptr rs, NSClientInfo::ptr info);

    void setQueryDomain(rock::RockStream::ptr rs, const std::set<std::string>& ds);

    void doNotify(std::set<std::string>& domains, std::shared_ptr<NotifyMessage> nty);

    std::set<rock::RockStream::ptr> getStreams(const std::string& domain);
private:
    NSDomainSet::ptr m_domains;

    rock::RWMutex m_mutex;
    std::map<rock::RockStream::ptr, NSClientInfo::ptr> m_sessions;

    /// sessoin 关注的域名
    std::map<rock::RockStream::ptr, std::set<std::string> > m_queryDomains;
    /// 域名对应关注的session
    std::map<std::string, std::set<rock::RockStream::ptr> > m_domainToSessions;
};

}
}

#endif
