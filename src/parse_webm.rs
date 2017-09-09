use super::webm;

pub fn parse_webm() {
    println!("parsing webm");
    let action = webm::Action::kRead;

    let parser = unsafe { webm::WebmParser::new() };
}