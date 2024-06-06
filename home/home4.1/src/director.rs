pub(crate) struct Director {
    ingredients_man: IngredientsManager,
    cur_pizza_type: PizzaType,
}

use crate::{builders, ingredients_manager::{self, IngredientsManager}, pizza};
use builders::{PizzaBuilder, CustomPizzaBuilder, MargaritaPizzaBuilder, PepperoniPizzaBuilder};
use std::io::{self};

pub enum PizzaType {
    Margarita,
    Pepperoni,
    Custom,
}

impl Director {
    pub fn new(cur_pizza_type: PizzaType) -> Director {
        Director {
            ingredients_man: ingredients_manager::IngredientsManager::new(),
            cur_pizza_type,
        }
    }

    #[allow(dead_code)]
    pub fn change_pizza_type(&mut self, pizza_type: PizzaType) {
        self.cur_pizza_type = pizza_type;
    }

    pub fn construct(&self) -> Option<pizza::Pizza> {
        // step 1: get the ingredients
        let mut ingredients_available = self.ingredients_man.read_ingredients().expect("No ingredients available.");
        let required_ingredients = self.required_ingredients(ingredients_available.clone());

        // step 2: check if ingredients are available
        if let Some(custom_ingredients) = self.are_available(&required_ingredients, &mut ingredients_available) {

            // step 3: write to file remaining ingredients
            self.ingredients_man.write_ingredients(ingredients_available).expect("Ingredients saving error");

            // step 4: build the pizza
            return Some(self.build(&custom_ingredients));
        }
        None
    }

    fn required_ingredients(&self, ingredients_available: Vec<(String, f32)>) -> Vec<String> {

        let get_custom_ingredients = || {
            
            println!("Choose ingredients from available:");
            for (ingredient, price) in &ingredients_available {
                print!("{}: ${:.2}, ", ingredient, price);
            }
            println!("\nEnter ingredients (separated by spaces): ");
            
            let mut input = String::new();
            io::stdin().read_line(&mut input).expect("Failed to read line");
            let input_ingredients: Vec<String> = input.trim().split_whitespace().map(String::from).collect();
            input_ingredients
        };

        match self.cur_pizza_type {
            PizzaType::Custom => get_custom_ingredients(),
            PizzaType::Margarita => MargaritaPizzaBuilder::required_ingredients(),
            PizzaType::Pepperoni => PepperoniPizzaBuilder::required_ingredients(),
        }
    }

    fn are_available(&self, required_i: &Vec<String>, available_i: &mut Vec<(String, f32)>) -> Option<Vec<(String, f32)>> {
        let mut custom_ingredients = vec![];
    
        for ingredient in required_i {
            if let Some(index) = available_i.iter().position(|(i, _)| i == ingredient) {
                // Remove the ingredient from available_i and get its price
                let (_, price) = available_i.remove(index);
                custom_ingredients.push((ingredient.clone(), price));
            } else {
                println!("Ingredient {} is not available.", ingredient);
                return None;
            }
        }
        Some(custom_ingredients)
    }

    fn build(&self, ingredients: &Vec<(String, f32)>) -> pizza::Pizza {
        match self.cur_pizza_type {
            PizzaType::Custom => {
                let mut pizza_builder = CustomPizzaBuilder::new();
                for ingredient in ingredients {
                    pizza_builder.add_ingredient(ingredient.0.as_str(), ingredient.1);
                }
                pizza_builder.build()
            }
            PizzaType::Margarita => MargaritaPizzaBuilder::new().build(),
            PizzaType::Pepperoni => PepperoniPizzaBuilder::new().build(),
        }
    }
}
