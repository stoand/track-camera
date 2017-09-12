extern crate bindgen;
extern crate gcc;

use std::env;
use std::path::PathBuf;

fn main() {

    println!("cargo:rustc-link-lib=webm");

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header("webm_parser_glue/webm_parser_glue.h")
        .enable_cxx_namespaces()
        .clang_args(&["-x", "c++", "-std=c++14"])
        .whitelisted_function("webm_parser_glue::parse_webm_bytes")
        .generate()
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_dir.join("bindings.rs"))
        .expect("Couldn't write bindings!");
        
    // build webm parser glue c++ code
    gcc::Build::new()
        .cpp(true)
        .file("webm_parser_glue/webm_parser_glue.cc")
        .compile("webm_parser_glue");
}