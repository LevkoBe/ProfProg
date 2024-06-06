use std::fs::{File, OpenOptions};
use std::io::{BufRead, BufReader, Write};
use std::error::Error;

const FILENAME: &str = "ingredients.txt";

pub struct IngredientsManager {
    filename: &'static str,
}

impl IngredientsManager {
    pub fn new() -> Self {
        IngredientsManager {
            filename: FILENAME,
        }
    }

    pub fn read_ingredients(&self) -> Result<Vec<(String, f32)>, Box<dyn Error>> {
        let file = File::open(self.filename)?;
        let reader = BufReader::new(file);
        let ingredients = reader.lines()
            .map(|line| {
                let line = line.unwrap();
                let parts: Vec<&str> = line.split_whitespace().collect();
                let ingredient = parts[0].to_string();
                let price = parts[1].parse().unwrap_or(0.0);
                (ingredient, price)
            })
            .collect::<Vec<(String, f32)>>();

        Ok(ingredients)
    }

    pub fn write_ingredients(&self, ingredients: Vec<(String, f32)>) -> Result<(), Box<dyn Error>> {
        let mut file = OpenOptions::new().write(true).truncate(true).open(self.filename)?;

        for (ingredient, price) in ingredients {
            writeln!(file, "{} {}", ingredient, price)?;
        }
        Ok(())
    }
}
