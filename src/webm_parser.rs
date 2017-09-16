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

#[test]
fn test_parse_webm() {
    let sample_bytes = include_bytes!("../samples/trackme.webm");

    let mut parser = unsafe { webm::WebmParser::new() };
    let status = unsafe { parser.parse(sample_bytes.as_ptr(), sample_bytes.len()) };
    
    let images = unsafe { parser.GetImgBuf() }.to_vec();
}