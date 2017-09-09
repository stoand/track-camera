#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

use std::io::Read;
use std::fs::File;

pub fn asdf() {
    print!("asdf called");
}