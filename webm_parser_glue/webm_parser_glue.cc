#include "webm_parser_glue.h"

using std::uint8_t;
using std::size_t;
using std::uint64_t;
using webm::Status;
using webm::FrameMetadata;
using webm::Reader;

namespace webm_parser_glue
{

class GlueCallback : public webm::Callback
{
//   public:
//     Status OnFrame(const FrameMetadata &metadata, Reader *reader,
//                    std::uint64_t *bytes_remaining)
//     {
//         return Status(webm::Status::kOkCompleted);
//     }
};

WebmData parse_webm_bytes(const uint8_t *buf, size_t buf_size)
{
    GlueCallback callback;
    auto vec = std::vector<uint8_t>(buf, buf + buf_size);
    webm::BufferReader buf_read(vec);
    Status status = webm::WebmParser().Feed(&callback, &buf_read);

    return {nullptr, 0, status};
};
}