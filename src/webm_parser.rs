use std::slice;

use super::bindgen_bindings::root::webm_parser_glue as webm;

impl<'a> webm::WebmData {
    pub fn get_buf(self) -> &'a [u8] {
        unsafe { slice::from_raw_parts(self.buf, self.buf_size) }
    }
}

#[test]
fn test_parse_webm() {
    let sample_bytes = include_bytes!("../samples/trackme.webm");

    let data =
        unsafe { webm::parse_webm_bytes(sample_bytes.as_ptr(), sample_bytes.len()) };

    let parsed_webm = data.get_buf();
}