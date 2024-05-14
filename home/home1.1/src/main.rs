use std::io;

fn main() {
    println!("Enter a list of numbers separated by spaces:");

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");

    let numbers: Vec<i32> = input
        .split_whitespace()
        .filter_map(|s| s.parse().ok())
        .collect();

    let biggest_negative = numbers.iter()
        .filter(|&x| *x < 0)
        .max();

    match biggest_negative {
        Some(&num) => println!("The biggest negative number is: {}", num),
        None => println!("No negative numbers were provided."),
    }
}
