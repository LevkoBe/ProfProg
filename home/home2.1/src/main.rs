use std::{collections::HashMap, io::Write};

pub struct NameCounter {
    greetings_history: HashMap<String, i32>,
}

const GREETING_COMMAND: &str = "hello";
const DELETE_COMMAND: &str = "delete";
const SECRET_WORD_COMMAND: &str = "bread";

impl NameCounter {
    pub fn add_name(&mut self, name: &str) {
        if let Some(counter) = self.greetings_history.get_mut(name) {
            *counter += 1;
            println!("Hello again(x{}), {}!", counter, name);
        } else {
            self.greetings_history.insert(name.to_string(), 1);
            println!("Welcome, {}!", name);
        }
    }

    pub fn delete_name(&mut self, name: &str) {
        if !self.greetings_history.contains_key(name) {
            println!("No history found for {}.", name);
            return;
        }
        self.greetings_history.remove(name);
        println!("History for {} was deleted.", name)
    }

    pub fn clear_history(&mut self) {
        self.greetings_history.clear();
    }
}

fn warning_message() {
    println!("Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").")
}

fn handle_one_word(input: &str) -> bool {
    if input.to_lowercase().contains("hi") || input.to_lowercase().contains(GREETING_COMMAND) {
        println!("Hello!");
        return true
    }
    if input.to_lowercase().contains("exit") {
        return false
    }
    warning_message();
    true
}

fn handle_greeting(history: &mut NameCounter, name: &str) {
    if name.is_empty() {
        warning_message();
    } else if name == SECRET_WORD_COMMAND {
        println!("Secret word was entered. Clearing all the history...");
        history.clear_history();
    } else {
        history.add_name(name);
    }
}

fn main() {
    let mut greetings_history: NameCounter = NameCounter {
        greetings_history: HashMap::new(),
    };
    
    loop {
        let mut input = String::new();
        print!("--> ");
        std::io::stdout().flush().expect("Failed to flush stdout"); // Manually flush stdout
        std::io::stdin().read_line(&mut input).expect("Failed to read line");
        
        if !input.contains(" ") {
            let input = input.trim();
            if !handle_one_word(input) { break; }
            continue;
        }

        let (first_word, second_word) = input.split_once(" ").unwrap();
        let second_word = second_word.trim();
        if first_word.to_lowercase() == GREETING_COMMAND {
            handle_greeting(&mut greetings_history, second_word);
        } else if second_word.to_lowercase() == DELETE_COMMAND {
            greetings_history.delete_name(first_word);
        }
    }
}
