use indicatif::{ProgressBar, ProgressStyle};
fn main() {
    let bar = ProgressBar::new(100 * 1024 * 1024);
    bar.set_style(ProgressStyle::default_bar().template("{bar} {bytes}"));

    for _ in 0..100 {
        bar.inc(1024 * 1024);
        bar.set_message("Some message");
        std::thread::sleep(std::time::Duration::from_millis(20));
    }
    bar.finish();
}
