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
using webm::Info;

#define VP8_FOURCC 0x30385056

namespace webm_parser_glue
{

int vpx_img_plane_width(const vpx_image_t *img, int plane);
int vpx_img_plane_height(const vpx_image_t *img, int plane);

class WebmParser : public webm::Callback
{
public:
  WebmParser() = default;
  Status parse(const uint8_t *buf, size_t buf_size);
  Status OnFrame(const FrameMetadata &, Reader *reader, std::uint64_t *bytes_remaining) override;

  vector<uint8_t *> parsed_imgs;
  size_t d_w = 0;
  size_t d_h = 0;

private:
  void OnImageParsed(vpx_image_t *img);
  vpx_codec_ctx_t codec;
};

WebmParser init_parser();
}