#include "rock/http/http_server.h"
#include "rock/log.h"

static rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

#define XX(...) #__VA_ARGS__


rock::IOManager::ptr worker;
void run() {
    g_logger->setLevel(rock::LogLevel::INFO);
    //rock::http::HttpServer::ptr server(new rock::http::HttpServer(true, worker.get(), rock::IOManager::GetThis()));
    rock::http::HttpServer::ptr server(new rock::http::HttpServer(true));
    rock::Address::ptr addr = rock::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/rock/xx", [](rock::http::HttpRequest::ptr req
                ,rock::http::HttpResponse::ptr rsp
                ,rock::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/rock/*", [](rock::http::HttpRequest::ptr req
                ,rock::http::HttpResponse::ptr rsp
                ,rock::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/rockx/*", [](rock::http::HttpRequest::ptr req
                ,rock::http::HttpResponse::ptr rsp
                ,rock::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv) {
    rock::IOManager iom(1, true, "main");
    worker.reset(new rock::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}
