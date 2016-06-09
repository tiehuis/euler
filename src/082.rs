// This mostly involves a way of inputting the data into this specific
// library. Implementing a graph search algorithm could be done manually,
// but what is the point, really?

extern crate petgraph;

use std::io::{self, BufReader};
use std::io::prelude::*;
use std::fs::File;

use petgraph::Graph;

/// Read a file into a vector
fn read_file(filename: &str) -> Vec<Vec<usize>> {
    let f = File::open(filename).unwrap();
    let f = BufReader::new(f);

    let mut v = vec![];
    for line in f.lines() {
        v.push(vec![]);
        for value in line.unwrap().split(',') {
            v.last_mut()
             .unwrap()
             .push(value.parse().unwrap());
        }
    }
    v
}

/// Construct a DAG that we can perform a graph search on.
fn construct_dag(values: &Vec<Vec<usize>) -> Graph<usize, ()> {
    let mut graph = Graph::<usize, ()>::new();

    // This isn't strictly a DAG, since we can not crossover paths we have
    // already crossed.
}

fn main() {
    let v = read_file("res/082_matrix.txt");

    // Construct directed graph on target data
    let d = construct_dag(&v);

    // We need to perform multiple searches (one for each start and end node
    // since we do not know exactly where we will finish). This is quicker than
    // generalizing the search algorithm itself.

    println!("{:?}", v);
}
