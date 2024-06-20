mod states;

use states::{State, Command};
use std::{io::Write, str::FromStr};

pub struct Singer {
    state: Box<dyn State>,
}

impl Singer {
    pub fn new(state: Box<dyn State>) -> Singer {
        Singer { state }
    }

    pub fn switch_state(&mut self, command: &Command) {
        self.state = self.state.switch_state(command);
    }

    pub fn sing(&self) {
        print!("~ ~ ~ ");
        self.state.sing();
    }

    pub fn is_done(&self) -> bool {
        self.state.as_any().downcast_ref::<states::ButInTheEndSong>().is_some()
    }
}

fn main() {
    println!("Hello, world!");
    let mut singer = Singer::new(Box::new(states::IntroSong));
    
    singer.sing();
    loop {
        print!(">_express_your_feelings_> ");
        std::io::stdout().flush().expect("Failed to flush stdout");

        let mut command = String::new();
        std::io::stdin().read_line(&mut command).expect("Failed to read line");

        let command = Command::from_str(command.trim()).unwrap_or(Command::Uncertain);

        singer.switch_state(&command);
        singer.sing();

        if singer.is_done() {
            break;
        }
    }
}
