use std::io::{self};

use director::PizzaType;

mod pizza;
mod builders;
mod ingredients_manager;
mod director;

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
    let director = match choice {
        1 => director::Director::new(PizzaType::Margarita),
        2 => director::Director::new(PizzaType::Pepperoni),
        _ => director::Director::new(PizzaType::Custom),
    };

    if let Some(pizza) = director.construct() {
        println!("Your pizza has the following ingredients: {:?}", pizza.get_ingredients());
        println!("Total cost: ${:.2}", pizza.get_cost());
    } else {
        println!("Sorry, we could not make a pizza for you.");
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use builders::{CustomPizzaBuilder, PizzaBuilder};
    use director::Director;
    use pizza::{CHEESE, HAM, PEPPERONI};

    #[test]
    fn test_margarita_pizza() {
        let pizza = Director::new(PizzaType::Margarita).construct().unwrap();
        
        assert_eq!(pizza.get_ingredients(), vec![CHEESE]);
        assert_eq!(pizza.get_cost(), 5.0);
    }

    #[test]
    fn test_pepperoni_pizza() {
        let pizza = Director::new(PizzaType::Pepperoni).construct().unwrap();
        
        assert_eq!(pizza.get_ingredients(), vec![CHEESE, PEPPERONI]);
        assert_eq!(pizza.get_cost(), 7.0);
    }

    #[test]
    fn test_custom_pizza_builder() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient(CHEESE, 1.5).add_ingredient(PEPPERONI, 2.0);
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
        builder.add_ingredient(CHEESE, 1.5).add_ingredient(CHEESE, 1.5);
        let pizza = builder.build();
        let ingredients = pizza.get_ingredients();
        
        assert_eq!(ingredients.iter().filter(|&&x| x == CHEESE).count(), 1, "Duplicate ingredients should be handled correctly.");
        assert_eq!(pizza.get_cost(), 1.5, "Duplicate ingredients should be handled correctly.");
    }

    #[test]
    fn expect_not_added_when_invalid_ingredient() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient("invalid_ingredient", 1.1);
        let pizza = builder.build();
        let ingredients = pizza.get_ingredients();
        
        assert!(!ingredients.contains(&"invalid_ingredient"), "Invalid ingredients should not be added.");
    }

    #[test]
    fn expect_propper_cost_when_assemble_pizza() {
        let mut builder = CustomPizzaBuilder::new();
        builder.add_ingredient(CHEESE, 1.5).add_ingredient(PEPPERONI, 2.0).add_ingredient(HAM, 2.0);
        let pizza = builder.build();
        
        assert_eq!(pizza.get_cost(), 1.5 + 2.0 + 2.0, "Cost calculation should be accurate.");
    }

    #[test]
    fn expect_less_ingredients_when_director_used_them() {
        let initial_quantity = ingredients_manager::IngredientsManager::new().read_ingredients().unwrap_or(vec![]).len();
        Director::new(PizzaType::Pepperoni).construct();
        let final_quantity = ingredients_manager::IngredientsManager::new().read_ingredients().unwrap_or(vec![]).len();
        
        assert!(final_quantity < initial_quantity, "Ingredients should be removed from the inventory.");
    }


}
