#include "webm_parser_glue.h"

namespace webm_parser_glue
{

int vpx_img_plane_width(const vpx_image_t *img, int plane)
{
    if (plane > 0 && img->x_chroma_shift > 0)
        return (img->d_w + 1) >> img->x_chroma_shift;
    else
        return img->d_w;
}

int vpx_img_plane_height(const vpx_image_t *img, int plane)
{
    if (plane > 0 && img->y_chroma_shift > 0)
        return (img->d_h + 1) >> img->y_chroma_shift;
    else
        return img->d_h;
}

Status WebmParser::parse(uint8_t *buf, size_t buf_size)
{
    vpx_codec_dec_init(&codec, vpx_codec_vp8_dx(), NULL, 0);

    auto vec = vector<uint8_t>(buf, buf + buf_size);
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

    size_t img_buff_size = d_w * (d_h * 1.5);
    uint8_t *parsed_img_cursor = new uint8_t[img_buff_size];

    // add the start of the parsed image cursor
    parsed_imgs.push_back(parsed_img_cursor);

    for (int plane = 0; plane < 3; ++plane)
    {
        const unsigned char *plane_cursor = img->planes[plane];
        const int stride = img->stride[plane];

        const int w = vpx_img_plane_width(img, plane) *
                      ((img->fmt & VPX_IMG_FMT_HIGHBITDEPTH) ? 2 : 1);
        const int h = vpx_img_plane_height(img, plane);

        for (int y = 0; y < h; ++y)
        {
            std::copy(plane_cursor, plane_cursor + w, parsed_img_cursor);
            plane_cursor += stride;
            parsed_img_cursor += w;
        }
    }
}
}