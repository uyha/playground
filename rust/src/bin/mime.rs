use mime;

fn main() {
    let content_disposition: mime::Mime = "attachment;filename=fzf-0.29.0-linux_amd64.tar.gz"
        .parse()
        .unwrap();

    println!("{}", content_disposition);
}
