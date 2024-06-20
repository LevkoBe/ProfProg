use std::any::Any;
use std::str::FromStr;

pub enum Command {
    Sad,
    Fun,
    Silly,
    Dangerous,
    Uncertain,
}

#[derive(Debug)]
pub struct ParseCommandError;

impl FromStr for Command {
    type Err = ParseCommandError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s.to_lowercase().as_str() {
            "sad" => Ok(Command::Sad),
            "fun" => Ok(Command::Fun),
            "silly" => Ok(Command::Silly),
            "dangerous" => Ok(Command::Dangerous),
            _ => Ok(Command::Uncertain),
        }
    }
}

pub trait State: Any {
    fn as_any(&self) -> &dyn Any;
    fn sing(&self);
    fn switch_state(&self, command: &Command) -> Box<dyn State>;
}

pub struct IntroSong;
impl State for IntroSong {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn sing(&self) {
        println!("Ultra intro singy song!");
        println!("I'm a singer, and I'm gonna sing you a song!");
    }

    fn switch_state(&self, command: &Command) -> Box<dyn State> {
        match command {
            Command::Dangerous => Box::new(LetItBeSong),
            Command::Fun => Box::new(StarmanSong),
            Command::Sad => Box::new(ButInTheEndSong),
            Command::Uncertain => Box::new(UncertainSong),
            _ => Box::new(Self),
        }
    }
}

pub struct StarmanSong;
impl State for StarmanSong {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn sing(&self) {
        println!("Starman is singing, and he's a star!");
        println!("He's a star, and he's a starman!");
    }

    fn switch_state(&self, command: &Command) -> Box<dyn State> {
        match command {
            Command::Silly => Box::new(IntroSong),
            Command::Dangerous => Box::new(ShowMustGoOnSong),
            Command::Fun => Box::new(ButInTheEndSong),
            _ => Box::new(Self),
        }
    }
}

pub struct ShowMustGoOnSong;
impl State for ShowMustGoOnSong {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn sing(&self) {
        println!("Show must go on, show must go on!");
        println!("There might be a time when we all just have to go on!");
    }

    fn switch_state(&self, command: &Command) -> Box<dyn State> {
        match command {
            Command::Sad => Box::new(LetItBeSong),
            Command::Fun => Box::new(StarmanSong),
            _ => Box::new(Self),
        }
    }
}

pub struct LetItBeSong;
impl State for LetItBeSong {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn sing(&self) {
        println!("Let it be... Let it be!");
        println!("It doesn't matter much to me!");
    }

    fn switch_state(&self, command: &Command) -> Box<dyn State> {
        match command {
            Command::Dangerous => Box::new(IntroSong),
            Command::Silly => Box::new(ShowMustGoOnSong),
            _ => Box::new(Self),
        }
    }
}

pub struct ButInTheEndSong;
impl State for ButInTheEndSong {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn sing(&self) {
        println!("But in the end, it doesn't even matter!");
        println!("We are all just pieces of a whole!");
    }

    fn switch_state(&self, _: &Command) -> Box<dyn State> {
        Box::new(Self)
    }
}

pub struct UncertainSong;
impl State for UncertainSong {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn sing(&self) {
        println!("I'm not sure if I can sing, but let me try!");
        println!("~ ~ ~ sad, fun, silly, dangerous! ~ ~ ~");
    }

    fn switch_state(&self, _: &Command) -> Box<dyn State> {
        Box::new(IntroSong)
    }
}