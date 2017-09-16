use std::slice;

use super::bindgen_bindings::root::webm_parser_glue as webm;

impl<'a> webm::ImgBuf {
    pub fn to_vec(self) -> Vec<Vec<u8>> {
        let img_bufs = unsafe { slice::from_raw_parts(self.img_buf, self.img_buf_size) };

        img_bufs
            .into_iter()
            .map(|img_buf| {
                unsafe {
                    let size = self.d_w * (self.d_h as f64 * 1.5) as usize;
                    slice::from_raw_parts(*img_buf, size)
                }.to_vec()
            })
            .collect()
    }
}

/// Decodes a VP8 encoded `.webm` file into raw 4:2:2 YUV bytes
pub fn parse_webm_bytes(bytes: &[u8]) -> Vec<Vec<u8>> {
    let mut parser = unsafe { webm::WebmParser::new() };
    let status = unsafe { parser.parse(bytes.as_ptr(), bytes.len()) };
    
    unsafe { parser.GetImgBuf() }.to_vec()
}

#[test]
fn test_parse_webm() {
    let _ = parse_webm_bytes(include_bytes!("../samples/trackme.webm"));
}