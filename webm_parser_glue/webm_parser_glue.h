// #include <webm/file_reader.h>
// #include <webm/status.h>
#include <webm/callback.h>
#include <webm/buffer_reader.h>
#include <webm/webm_parser.h>

namespace webm_parser_glue
{

struct WebmData
{
    uint8_t *buf;
    size_t buf_size;
    webm::Status status;
};

WebmData parse_webm_bytes(const std::uint8_t *buf, std::size_t buf_size);
}