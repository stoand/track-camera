extern crate bindgen;
extern crate gcc;

use std::env;
use std::path::PathBuf;

fn main() {

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header("webm_parser_glue/webm_parser_glue.h")
        .enable_cxx_namespaces()
        .clang_args(&["-x", "c++", "-std=c++11", "-fPIC"])
        .whitelisted_type("webm_parser_glue::WebmParser")
        .layout_tests(false)
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
        .flag("-std=c++11")
        .flag("-fPIC")
        .file("webm_parser_glue/webm_parser_glue.cc")
        .compile("webm_parser_glue");

    println!("cargo:rustc-link-lib=webm");
    println!("cargo:rustc-link-lib=vpx");
}