#include "rock/http/http.h"
#include "rock/log.h"

void test_request() {
    rock::http::HttpRequest::ptr req(new rock::http::HttpRequest);
    req->setHeader("host" , "www.rock.top");
    req->setBody("hello rock");
    req->dump(std::cout) << std::endl;
}

void test_response() {
    rock::http::HttpResponse::ptr rsp(new rock::http::HttpResponse);
    rsp->setHeader("X-X", "rock");
    rsp->setBody("hello rock");
    rsp->setStatus((rock::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}

int main(int argc, char** argv) {
    test_request();
    test_response();
    return 0;
}
