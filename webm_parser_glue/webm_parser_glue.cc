#include "webm_parser_glue.h"

using std::uint8_t;
using std::size_t;
using std::uint64_t;
using webm::Status;

namespace webm_parser_glue
{

class GlueCallback : public webm::Callback
{
  public:
    Status OnBlockEnd(const webm::ElementMetadata &metadata,
                      const webm::Block &block)
    {
        return Status(webm::Status::kOkCompleted);
    }
};

WebmData parse_webm_bytes(const uint8_t *buf, size_t buf_size)
{
    GlueCallback callback;
    webm::BufferReader buf_read(std::vector<uint8_t>(buf_size, *buf));
    Status status = webm::WebmParser().Feed(&callback, &buf_read);

    return {nullptr, 0, status};
};
}