#include "webm_parser_glue.h"

namespace webm_parser_glue
{

Status WebmParser::parse(uint8_t *buf, size_t buf_size)
{
    vpx_codec_dec_init(&codec, vpx_codec_vp8_dx(), NULL, 0);

    auto vec = vector<uint8_t>(buf, &buf[buf_size - 1]);
    webm::BufferReader buf_read(vec);
    return webm::WebmParser().Feed(this, &buf_read);
}

Status WebmParser::OnFrame(const FrameMetadata &, Reader *reader,
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

    vpx_codec_decode(&codec, frame, (unsigned int)total_read, NULL, 0);

    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img = NULL;
    while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL)
    {
        OnImageParsed(img);
    }

    return status;
}

void WebmParser::OnImageParsed(vpx_image_t *img)
{
    if (parsed_imgs.empty())
    {
        d_w = img->d_w;
        d_h = img->d_h;
    }

    uint8_t *parsed_img = new uint8_t[d_w * d_h];
    parsed_imgs.push_back(parsed_img);

    for (int plane = 0; plane < 3; ++plane)
    {
        const unsigned char *plane_buf = img->planes[plane];
        const int stride = img->stride[plane];

        for (int y = 0; y < d_h; ++y)
        {
            std::copy(plane_buf, plane_buf + d_w, parsed_img);
            plane_buf += stride;
            parsed_img += d_w;
        }
    }
}
}