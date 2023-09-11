use tree_sitter::{Node, Parser, Tree, TreeCursor};
use tree_sitter_eds::language;

use std::fs;

#[derive(Debug)]
pub struct EDS {
    content: String,
    tree: Tree,
}

impl EDS {
    pub fn parse(content: &str) -> Option<EDS> {
        let mut parser = Parser::new();
        parser.set_language(language()).ok()?;

        Some(EDS {
            content: content.to_owned(),
            tree: parser.parse(content, None)?,
        })
    }
}

#[derive(Debug)]
pub struct EDSNode<'a> {
    pub content: &'a str,
    pub node: Node<'a>,
}
pub struct EDSIterator<'a> {
    content: &'a str,
    cursor: TreeCursor<'a>,
}

impl<'a> IntoIterator for &'a EDS {
    type Item = EDSNode<'a>;
    type IntoIter = EDSIterator<'a>;

    fn into_iter(self) -> Self::IntoIter {
        Self::IntoIter {
            content: &self.content,
            cursor: self.tree.walk(),
        }
    }
}

fn parse_section_name<'a>(content: &'a str, cursor: &mut TreeCursor<'a>) -> Option<EDSNode<'a>> {
    if cursor.goto_first_child()
        && cursor.goto_next_sibling()
        && cursor.node().kind() == "section_name"
    {
        let node = cursor.node();
        let content = cursor.node().utf8_text(content.as_bytes()).ok()?;

        return Some(EDSNode { content, node });
    }
    None
}

fn parse_statement<'a>(content: &'a str, cursor: &mut TreeCursor<'a>) -> Option<EDSNode<'a>> {
    if cursor.goto_next_sibling() && cursor.node().kind() == "statement" {
        let node = cursor.node();
        let content = cursor.node().utf8_text(content.as_bytes()).ok()?;

        return Some(EDSNode { content, node });
    }
    None
}

impl<'a> Iterator for EDSIterator<'a> {
    type Item = EDSNode<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        let kind = self.cursor.node().kind();
        let cursor = &mut self.cursor;

        if kind == "source_file" && cursor.goto_first_child() {
            return self.next();
        } else if cursor.node().kind() == "section" {
            return parse_section_name(self.content, cursor);
        } else if kind == "section_name" {
            if cursor.goto_next_sibling() {
                if let Some(node) = parse_statement(self.content, cursor) {
                    return Some(node);
                } else if cursor.goto_parent() && cursor.goto_next_sibling() {
                    return self.next();
                }
            }
        } else if kind == "statement" {
            if let Some(node) = parse_statement(self.content, cursor) {
                return Some(node);
            }
            if cursor.goto_parent()
                && cursor.goto_next_sibling()
                && cursor.node().kind() == "section"
            {
                return parse_section_name(self.content, cursor);
            }
        }
        None
    }
}

fn main() {
    let content = fs::read_to_string("example.eds").unwrap();
    let eds = EDS::parse(&content).unwrap();

    for node in eds.into_iter() {
        println!("{:?}", node);
    }
}
