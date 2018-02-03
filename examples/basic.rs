extern crate track_camera;

use track_camera::frame_renderer::FrameRenderer;

fn main() {
    // track_camera::calc_spatial_data::calc_spatial_data();
    let renderer = FrameRenderer::new(1080, 1920);
}