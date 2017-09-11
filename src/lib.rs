#[allow(dead_code)]
mod bindgen_bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

use bindgen_bindings::root::webm_parser_glue;