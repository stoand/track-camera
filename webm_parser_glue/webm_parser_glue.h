#include <webm/callback.h>
#include <webm/buffer_reader.h>
#include <webm/webm_parser.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8dx.h>

using std::uint8_t;
using std::size_t;
using std::uint64_t;
using std::vector;
using webm::Status;
using webm::FrameMetadata;
using webm::ElementMetadata;
using webm::Action;
using webm::Reader;

#define VP8_FOURCC 0x30385056

namespace webm_parser_glue
{

class GlueCallback : public webm::Callback
{
  public:
    GlueCallback();
    Status OnFrame(const FrameMetadata &, Reader *reader, std::uint64_t *bytes_remaining) override;
    vector<vpx_image_t*> images;
  private:
    vpx_codec_ctx_t codec;
};

struct WebmData
{
    webm::Status status;
    vpx_image_t **img;
    uint64_t img_count;
};

WebmData parse_webm_bytes(const std::uint8_t *buf, std::size_t buf_size);
}