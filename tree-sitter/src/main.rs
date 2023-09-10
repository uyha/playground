use tree_sitter::{Node, Parser, Point, Tree};
use tree_sitter_eds::language;

use std::{env::current_dir, fs};

#[derive(Debug)]
struct Statement {
    key: String,
    value: String,
}

#[derive(Debug)]
struct Section {
    name: String,
    statements: Vec<Statement>,
}

fn eds_parser() -> Parser {
    let mut parser = Parser::new();
    parser.set_language(language()).expect("");
    parser
}

fn parse_eds(root_node: Node, content: &[u8]) -> Vec<Section> {
    let mut result = vec![];

    let mut cursor = root_node.walk();
    let mut current_section: Option<Section> = Option::None;

    loop {
        let kind = cursor.node().kind();
        if kind == "source_file" && !cursor.goto_first_child() {
            break;
        }
        if kind == "section" {
            if let Some(section) = current_section.take() {
                result.push(section);
            }

            if !cursor.goto_first_child() || !cursor.goto_next_sibling() {
                break;
            }
            current_section = Some(Section {
                name: cursor.node().utf8_text(content).unwrap().to_owned(),
                statements: vec![],
            });

            if !cursor.goto_next_sibling() || !cursor.goto_next_sibling() {
                break;
            }
        }
        if kind == "statement" {
            if !cursor.goto_first_child() {
                break;
            }
            let key = cursor.node().utf8_text(content).unwrap().to_owned();

            if !cursor.goto_next_sibling() || !cursor.goto_next_sibling() {
                break;
            }
            let value = cursor.node().utf8_text(content).unwrap().to_owned();

            current_section
                .as_mut()
                .unwrap()
                .statements
                .push(Statement { key, value });

            if !cursor.goto_parent() {
                break;
            }
            if !cursor.goto_next_sibling() && (!cursor.goto_parent() || !cursor.goto_next_sibling())
            {
                break;
            }
        }
    }

    result
}

fn main() {
    let mut parser = eds_parser();
    let content = fs::read_to_string("example.eds").unwrap();
    let tree = parser.parse(&content, None).unwrap();

    let node = tree.root_node();
    println!("{:?}", parse_eds(node, content.as_bytes()));
}
