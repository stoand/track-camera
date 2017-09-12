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
    std::vector<char> sample_bytes = read_all_bytes(filename);

    WebmData data = parse_webm_bytes(reinterpret_cast<const std::uint8_t *>(&sample_bytes[0]), sample_bytes.size());

    REQUIRE(1 == 1);
}
}
