mod pizza;
mod builders;
mod ingredients_manager;

use builders::{PizzaBuilder, CustomPizzaBuilder, MargaritaPizzaBuilder, PepperoniPizzaBuilder};
use std::io::{self, Write};

fn assemble_custom_pizza() -> pizza::Pizza {
    let mut builder = CustomPizzaBuilder::new();
    let ingredients_man = ingredients_manager::IngredientsManager::new();
    let mut ingredients_available: Vec<String> = ingredients_man.read_ingredients().expect("No ingredients available.");

    println!("Choose ingredients from available:");
    for ingredient in &ingredients_available {
        print!("{}, ", ingredient);
    }
    print!("\nEnter ingredients (separated by spaces): ");
    io::stdout().flush().expect("Failed to flush stdout");

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let mut input_ingredients: Vec<&str> = input.trim().split(' ').collect();

    input_ingredients.sort_unstable();
    input_ingredients.dedup();

    for ingredient in input_ingredients {
        if ingredients_available.contains(&ingredient.to_string()) {
            builder.add_ingredient(ingredient);
            if let Some(pos) = ingredients_available.iter().position(|x| x == ingredient) {
                ingredients_available.remove(pos);
            }
        } else {
            println!("Ingredient '{}' is not available.", ingredient);
        }
    }

    ingredients_man.write_ingredients(ingredients_available).expect("Failed to write ingredients");
    builder.build()
}


fn main() {
    println!("Hello, world!");
    println!("Choose your pizza type:");
    println!("1. Margarita");
    println!("2. Pepperoni");
    println!("3. Custom");

    let mut choice = String::new();
    io::stdin().read_line(&mut choice).expect("Failed to read line");
    let choice: usize = match choice.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Invalid input, defaulting to Custom pizza.");
            3
        }
    };

    let pizza = match choice {
        1 => MargaritaPizzaBuilder::new().build(),
        2 => PepperoniPizzaBuilder::new().build(),
        3 => assemble_custom_pizza(),
        _ => {
            println!("Invalid choice, creating a default pizza.");
            CustomPizzaBuilder::new().build()
        }
    };

    println!("Your pizza has the following ingredients: {:?}", pizza.get_ingredients());
    println!("Total cost: ${:.2}", pizza.get_cost());
}

#[cfg(test)]
mod tests {
    use super::*;
    use pizza::{CHEESE, HAM, PEPPERONI};

    #[test]
    fn test_margarita_pizza() {
        let pizza = MargaritaPizzaBuilder::new().build();
        assert_eq!(pizza.get_ingredients(), vec![CHEESE]);
        assert_eq!(pizza.get_cost(), 5.0);
    }

    #[test]
    fn test_pepperoni_pizza() {
        let pizza = PepperoniPizzaBuilder::new().build();
        assert_eq!(pizza.get_ingredients(), vec![CHEESE, PEPPERONI]);
        assert_eq!(pizza.get_cost(), 7.0);
    }

    #[test]
    fn test_custom_pizza_builder() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient(CHEESE).add_ingredient(PEPPERONI);
        let pizza = builder.build();
        assert_eq!(pizza.get_ingredients(), vec![CHEESE, PEPPERONI]);
        assert_eq!(pizza.get_cost(), 3.5);
    }

    #[test]
    fn expect_ingredients_when_they_are() {
        let ingredients_manager = ingredients_manager::IngredientsManager::new();
        let ingredients = ingredients_manager.read_ingredients().unwrap_or(vec![]);
        assert!(!ingredients.is_empty(), "Ingredients list should not be empty.");
    }

    #[test]
    fn expect_1_cheese_when_2_added() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient(CHEESE).add_ingredient(CHEESE);
        let pizza = builder.build();
        let ingredients = pizza.get_ingredients();
        assert_eq!(ingredients.iter().filter(|&&x| x == CHEESE).count(), 1, "Duplicate ingredients should be handled correctly.");
        assert_eq!(pizza.get_cost(), 1.5, "Duplicate ingredients should be handled correctly.");
    }

    #[test]
    fn expect_not_added_when_invalid_ingredient() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient("invalid_ingredient");
        let pizza = builder.build();
        let ingredients = pizza.get_ingredients();
        assert!(!ingredients.contains(&"invalid_ingredient"), "Invalid ingredients should not be added.");
    }

    #[test]
    fn expect_propper_cost_when_assemble_pizza() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient(CHEESE).add_ingredient(PEPPERONI).add_ingredient(HAM);
        let pizza = builder.build();
        assert_eq!(pizza.get_cost(), 1.5 + 2.0 + 2.0, "Cost calculation should be accurate.");
    }



}
