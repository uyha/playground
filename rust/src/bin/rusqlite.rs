use rusqlite::{params, Connection, Result};
use std::path::PathBuf;

#[derive(Debug)]
struct Person {
    id: i32,
    name: String,
    data: PathBuf,
}

fn main() -> Result<()> {
    let conn = Connection::open_in_memory()?;

    conn.execute(
        "CREATE TABLE person (
                  id              INTEGER PRIMARY KEY,
                  name            TEXT NOT NULL,
                  data            TEXT
                  )",
        [],
    )?;
    let me = Person {
        id: 0,
        name: "Steven".to_string(),
        data: std::env::current_dir().unwrap(),
    };
    conn.execute(
        "INSERT INTO person (name, data) VALUES (?1, ?2)",
        params![me.name, me.data.to_string_lossy()],
    )?;

    let mut stmt = conn.prepare("SELECT id, name, data FROM person")?;
    let person_iter = stmt.query_map([], |row| {
        let data: String = row.get(2)?;
        Ok(Person {
            id: row.get(0)?,
            name: row.get(1)?,
            data: data.into(),
        })
    })?;

    for person in person_iter {
        println!("Found person {:?}", person.unwrap());
    }
    Ok(())
}
