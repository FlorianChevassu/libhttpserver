#include <cstdlib>
#include <memory>

#include <httpserver.hpp>

#define PATH "/plaintext"
#define BODY "Hello, World!"

using namespace httpserver;

class hello_world_resource : public http_resource {
	public:
        hello_world_resource(const std::shared_ptr<http_response>& resp):
            resp(resp)
        {
        }

        const std::shared_ptr<http_response> render(const http_request&) {
            return resp;
        }

    private:
        std::shared_ptr<http_response> resp;
};

int main(int argc, char** argv)
{
    webserver ws = create_webserver(atoi(argv[1]))
        .start_method(http::http_utils::THREAD_PER_CONNECTION);

    std::shared_ptr<http_response> hello = std::shared_ptr<http_response>(new string_response(BODY, 200));
    hello->with_header("Server", "libhttpserver");

    hello_world_resource hwr(hello);
    ws.register_resource(PATH, &hwr, false);

    ws.start(true);

    return 0;
}