# Requires libwebm to be installed globally
# as well as catch - https://github.com/philsquared/Catch/blob/master/docs/tutorial.md

clang++ -O0 -std=c++14 webm_parser_glue_test.cc webm_parser_glue.cc -lwebm -o webm_parser_glue_test && ./webm_parser_glue_test