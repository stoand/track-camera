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
    vector<char> sample_bytes = read_all_bytes(filename);

    uint8_t *i_bytes = reinterpret_cast<uint8_t *>(&sample_bytes[0]);


    WebmParser parser;
    Status status = parser.parse(i_bytes, sample_bytes.size());

    FILE *outfile = fopen("decoded_yuv", "wb");
    for (int i = 0; i < parser.parsed_imgs.size(); i++) {
        fwrite(parser.parsed_imgs[i], 1, parser.d_w * parser.d_h, outfile);
    }
    fclose(outfile);

    REQUIRE(status.completed_ok());
}
}
