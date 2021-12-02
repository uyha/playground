use std::path::PathBuf;
fn main() {
    let path: PathBuf = [PathBuf::from("/test"), PathBuf::from("test")]
        .into_iter()
        .collect();

    println!("{:?}", path);
}
