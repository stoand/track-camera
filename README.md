# Track Camera

## Setup

* have `gcc` installed
* install `libvpx` and `libwebm` globally

## Testing C++ Webm Glue Code

* `cd webm_parser_glue`
* `./build_test.sh`
* `./webm_parser_glue_test`
* `vlc --demux rawvideo --rawvid-fps 29.970628 --rawvid-width 1080 --rawvid-height 1920 --rawvid-chroma I420 decoded_yuv`