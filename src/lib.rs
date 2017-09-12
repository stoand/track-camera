#[allow(dead_code)]
mod bindgen_bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

mod webm_parser;