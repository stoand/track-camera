#include "webm_parser_glue.h"

namespace webm_parser_glue
{

GlueCallback::GlueCallback()
{
    vpx_codec_dec_init(&codec, vpx_codec_vp8_dx(), NULL, 0);
}

Status GlueCallback::OnFrame(const FrameMetadata &, Reader *reader,
                             uint64_t *bytes_remaining)
{
    if (*bytes_remaining == 0)
        return Status(Status::kOkCompleted);

    auto frame = new unsigned char[*bytes_remaining];
    uint64_t total_read = 0;

    Status status;
    do
    {
        uint64_t num_actually_read;
        status = reader->Read(*bytes_remaining, frame + total_read, &num_actually_read);
        *bytes_remaining -= num_actually_read;
        total_read += num_actually_read;
    } while (status.code == Status::kOkPartial);

    if (total_read <= 1)
        return Status(Status::kOkCompleted);

    // todo - fix decoding error on a later frame
    // if (
        vpx_codec_decode(&codec, frame, (unsigned int)total_read, NULL, 0);
    // )
        // return Status(Status::kInvalidElementValue);

    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img = NULL;
    while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL)
    {
        images.push_back(img);
    }

    return status;
}

WebmData parse_webm_bytes(const uint8_t *buf, size_t buf_size)
{
    GlueCallback callback;
    auto vec = vector<uint8_t>(buf, buf + buf_size);
    webm::BufferReader buf_read(vec);
    Status status = webm::WebmParser().Feed(&callback, &buf_read);

    auto img_count = callback.images.size();
    vpx_image_t **img = new vpx_image_t*[img_count];
    std::copy(callback.images.begin(), callback.images.end(), img);
    
    return {status, img, img_count};
};
}