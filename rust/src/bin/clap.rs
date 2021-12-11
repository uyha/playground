use clap::{App, Arg, SubCommand};

fn main() {
    let matches = App::new("clap")
        .version("1.0")
        .author("Uy Ha <hchanuy@gmail.com>")
        .arg(
            Arg::with_name("help")
                .short("h")
                .long("help")
                .help("Print this message"),
        )
        .get_matches();
    println!("{}", matches.is_present("help"));
}
