use flate2::read::GzDecoder;
use std::fs::File;
use tar::Archive;

fn main() -> Result<(), std::io::Error> {
    let tarball = File::open("/home/uy/.cache/lipm/download/m4-1.4.19.tar.gz")?;

    let tar = GzDecoder::new(tarball);
    let mut archive = Archive::new(tar);

    archive.unpack(".")?;

    Ok(())
}
