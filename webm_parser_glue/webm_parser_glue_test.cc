#include "webm_parser_glue.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

using std::ifstream;
using std::ios;
using std::uint8_t;

const char *filename = "../samples/trackme.webm";

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

void vpx_img_write(const vpx_image_t *img, FILE *file)
{
    int plane;

    for (plane = 0; plane < 3; ++plane)
    {
        const unsigned char *buf = img->planes[plane];
        const int stride = img->stride[plane];
        const int w = vpx_img_plane_width(img, plane) *
                      ((img->fmt & VPX_IMG_FMT_HIGHBITDEPTH) ? 2 : 1);
        const int h = vpx_img_plane_height(img, plane);
        int y;

        for (y = 0; y < h; ++y)
        {
            fwrite(buf, 1, w, file);
            buf += stride;
        }
    }
}

static std::vector<char> read_all_bytes(char const *filename)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

TEST_CASE("Webm Parser", "[webm_parser]")
{
    std::vector<char> sample_bytes = read_all_bytes(filename);

    const std::uint8_t *i_bytes = reinterpret_cast<const std::uint8_t *>(&sample_bytes[0]);

    WebmData data = parse_webm_bytes(i_bytes, sample_bytes.size());
    FILE *outfile = fopen("decoded_yuv", "wb");
    for (int i = 0; i < data.img_count; i++) {
        vpx_image_t *img = data.img[i];
        vpx_img_write(img, outfile);
    }

    REQUIRE(data.status.completed_ok());
}
}
