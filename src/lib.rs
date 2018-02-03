#[macro_use]
extern crate vulkano;
#[macro_use]
extern crate vulkano_shader_derive;
extern crate vulkano_win;

extern crate winit;


#[allow(dead_code)]
mod bindgen_bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

mod webm_parser;
pub mod calc_spatial_data;
pub mod frame_renderer;