use http::header::HeaderMap;
fn main() {
    let mut headers = HeaderMap::new();
    headers.insert(
        "Content-Disposition",
        "attachment;filename=\"asdfas;df\"".parse().unwrap(),
    );

    println!("{:?}", headers);
}
