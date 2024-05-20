use std::{collections::HashMap, io::Write};

// the same concerns as for the class work - it is better to have data and logic encapsulation, some named constants for commands and so on.
fn warning_message() {
    println!("Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").")
}

fn handle_one_word(input: &str) -> bool {
    if input.to_lowercase().contains("hi") || input.to_lowercase().contains("hello") {
        println!("Hello!");
    }
    else if input.to_lowercase().contains("exit") {
        return false
    }
    else {
        warning_message();
    }
    true
}

fn handle_greeting(history: &mut HashMap<String, i32>, name: &str) {
    if name.is_empty() {
        warning_message();
    }
    else if name == "bread" {
        println!("Secret word was entered. Clearing all the history...");
        history.clear();
    }
    else if let Some(counter) = history.get_mut(name) {
        *counter += 1;
        println!("Hello again(x{}), {}!", counter, name);
    }
    else {
        history.insert(name.to_string(), 1);
        println!("Welcome, {}!", name);
    }
}

fn handle_delete(history: &mut HashMap<String, i32>, name: &str) {
    if !history.contains_key(name) {
        println!("No history found for {}.", name);
        return;
    }
    history.remove(name);
    println!("History for {} was deleted.", name)
}

fn main() {
    let mut geetings_history: HashMap<String, i32> = HashMap::new();
    
    loop {
        let mut input = String::new();
        print!("--> ");
        std::io::stdout().flush().expect("Failed to flush stdout"); // Manually flush stdout
        std::io::stdin().read_line(&mut input).expect("Failed to read line");
        
        if !input.contains(" ") {
            let input = input.trim();
            if !handle_one_word(input) {
                break;
            }
            continue;
        }

        let (first_word, second_word) = input.split_once(" ").unwrap();
        let second_word = second_word.trim();
        if first_word.to_lowercase() == "hello" {
            handle_greeting(&mut geetings_history, second_word);
        }
        else if second_word.to_lowercase() == "delete" {
            handle_delete(&mut geetings_history, first_word);
        }
    }
}
