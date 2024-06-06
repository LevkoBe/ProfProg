use std::io::{self, BufRead};
use std::sync::{Mutex, Arc};
use lazy_static::lazy_static;
use std::thread;
use std::time::Duration;

const SLEEP_TIME: u8 = 1;
const INPUT_WORDS_NUMBER: u8 = 5;
const FILE_WORDS_NUMBER: u8 = 3;
const FILE_NAME: &str = "configuration.txt";

struct Phraser {
    file_words: Vec<(String, String)>,
}

impl Phraser {
    fn new() -> Self {
        Self {
            file_words: Self::read_from_file(),
        }
    }

    fn read_from_file() -> Vec<(String, String)> {
        let mut file_words = Vec::new();
        let file = std::fs::File::open(FILE_NAME).expect("Unable to open file");
        let reader = std::io::BufReader::new(file);
        for line in reader.lines() {
            let line = line.expect("Unable to read line");
            let mut words = line.split_whitespace();
            if let (Some(first), Some(second)) = (words.nth(1), words.next()) {
                file_words.push((first.to_string(), second.to_string()));
            }
        }

        if file_words.len() != FILE_WORDS_NUMBER as usize {
            panic!("The file is not correct!");
        }

        file_words
    }

    fn get_words(&self, number_of_letter: u8) -> (String, String) {
        if number_of_letter < ('l' as u8) {
            return self.file_words[0].clone();
        } else if number_of_letter < ('p' as u8) {
            return self.file_words[1].clone();
        } else {
            return self.file_words[2].clone();
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_akpreword_akpostword_when_between_a_k() {
        let phraser = Phraser::new();
        let word = "abc";
        if let Some(first_char) = word.chars().next() {
            let ascii_value = first_char as u8;
            let (first, second) = phraser.get_words(ascii_value);
            assert_eq!(first, "AKPreword");
            assert_eq!(second, "AKPostword");
        } else {
            panic!("The word is empty!");
        }
    }

    #[test]
    fn expect_lopreword_lopostword_when_between_l_o() {
        let phraser = Phraser::new();
        let word = "lmn";
        if let Some(first_char) = word.chars().next() {
            let ascii_value = first_char as u8;
            let (first, second) = phraser.get_words(ascii_value);
            assert_eq!(first, "l_o_preword");
            assert_eq!(second, "l_o_postword");
        } else {
            panic!("The word is empty!");
        }
    }

    #[test]
    fn expect_pzpreword_pzpostword_when_between_p_z() {
        let phraser = Phraser::new();
        let word = "pqr";
        if let Some(first_char) = word.chars().next() {
            let ascii_value = first_char as u8;
            let (first, second) = phraser.get_words(ascii_value);
            assert_eq!(first, "p-z-preword");
            assert_eq!(second, "p-z-postword");
        } else {
            panic!("The word is empty!");
        }
    }
}

lazy_static! {
    static ref PHRASER_INSTANCE: Arc<Mutex<Phraser>> = Arc::new(Mutex::new(Phraser::new()));
}

fn main() {
    let mut words = Vec::new();
    println!("Enter {} words:", INPUT_WORDS_NUMBER);
    for _ in 0..INPUT_WORDS_NUMBER {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        words.push(input.trim().to_string());
    }

    let mut threads = Vec::new();

    for word in words {
        let phraser_instance = Arc::clone(&PHRASER_INSTANCE);
        threads.push(thread::spawn(move || {
            let phraser = phraser_instance.lock().unwrap();
            if let Some(first_char) = word.chars().next() {
                thread::sleep(Duration::from_secs(SLEEP_TIME.into()));
                let ascii_value = first_char as u8;
                let (first, second) = phraser.get_words(ascii_value);
                println!("{} - {} - {}", first, word, second);
            } else {
                println!("Thread: {} - The word is empty!", word);
            }
        }));
    }

    for thread in threads {
        thread.join().expect("Thread failed to join");
    }
}
