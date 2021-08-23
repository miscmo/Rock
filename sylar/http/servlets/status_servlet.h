#ifndef __ROCK_HTTP_SERVLETS_STATUS_SERVLET_H__
#define __ROCK_HTTP_SERVLETS_STATUS_SERVLET_H__

#include "rock/http/servlet.h"

namespace rock {
namespace http {

class StatusServlet : public Servlet {
public:
    StatusServlet();
    virtual int32_t handle(rock::http::HttpRequest::ptr request
                   , rock::http::HttpResponse::ptr response
                   , rock::http::HttpSession::ptr session) override;
};

}
}

#endif
