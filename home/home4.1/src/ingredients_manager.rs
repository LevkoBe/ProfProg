use std::fs::File;
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

    pub fn read_ingredients(&self) -> Result<Vec<String>, Box<dyn Error>> {
        let file = File::open(self.filename)?;
        let reader = BufReader::new(file);
        let ingredients = reader.lines().collect::<Result<Vec<_>, _>>()?;
        Ok(ingredients)
    }

    pub fn write_ingredients(&self, ingredients: Vec<String>) -> Result<(), Box<dyn Error>> {
        let mut file = File::create(self.filename)?;
        for ingredient in ingredients {
            writeln!(file, "{}", ingredient)?;
        }
        Ok(())
    }
}
