#include "rock/email/email.h"
#include "rock/email/smtp.h"

void test() {
    rock::EMail::ptr email = rock::EMail::Create(
            "user@163.com", "passwd",
            "hello world", "<B>hi xxx</B>hell world", {"564628276@qq.com"});
    rock::EMailEntity::ptr entity = rock::EMailEntity::CreateAttach("rock/rock.h");
    if(entity) {
        email->addEntity(entity);
    }

    entity = rock::EMailEntity::CreateAttach("rock/address.cc");
    if(entity) {
        email->addEntity(entity);
    }

    auto client = rock::SmtpClient::Create("smtp.163.com", 465, true);
    if(!client) {
        std::cout << "connect smtp.163.com:25 fail" << std::endl;
        return;
    }

    auto result = client->send(email, true);
    std::cout << "result=" << result->result << " msg=" << result->msg << std::endl;
    std::cout << client->getDebugInfo() << std::endl;
    //result = client->send(email, true);
    //std::cout << "result=" << result->result << " msg=" << result->msg << std::endl;
    //std::cout << client->getDebugInfo() << std::endl;
}

int main(int argc, char** argv) {
    rock::IOManager iom(1);
    iom.schedule(test);
    iom.stop();
    return 0;
}
