use crate::pizza::{Pizza, CHEESE, PEPPERONI, HAM, SAUSAGE, MUSHROOMS, ONIONS, OLIVES, PINEAPPLE, BACON, CHICKEN};

pub trait PizzaBuilder {
    fn required_ingredients() -> Vec<String>;
    fn new() -> Self where Self: Sized;
    fn add_ingredient(&mut self, ingredient: &str, price: f32) -> &mut Self;
    fn build(self) -> Pizza;
}

pub struct CustomPizzaBuilder {
    pizza: Pizza,
}

impl PizzaBuilder for CustomPizzaBuilder {
    fn new() -> Self {
        CustomPizzaBuilder {
            pizza: Pizza::new(),
        }
    }

    fn required_ingredients() -> Vec<String> {
        vec![]
    }

    fn add_ingredient(&mut self, ingredient: &str, price: f32) -> &mut Self {
        match ingredient {
            CHEESE => {
                if !self.pizza.cheese {
                    self.pizza.cheese = true;
                    self.pizza.cost += price;
                }
            }
            PEPPERONI => {
                if !self.pizza.pepperoni {
                    self.pizza.pepperoni = true;
                    self.pizza.cost += price;
                }
            }
            HAM => {
                if !self.pizza.ham {
                    self.pizza.ham = true;
                    self.pizza.cost += price;
                }
            }
            SAUSAGE => {
                if !self.pizza.sausage {
                    self.pizza.sausage = true;
                    self.pizza.cost += price;
                }
            }
            MUSHROOMS => {
                if !self.pizza.mushrooms {
                    self.pizza.mushrooms = true;
                    self.pizza.cost += price;
                }
            }
            ONIONS => {
                if !self.pizza.onions {
                    self.pizza.onions = true;
                    self.pizza.cost += price;
                }
            }
            OLIVES => {
                if !self.pizza.olives {
                    self.pizza.olives = true;
                    self.pizza.cost += price;
                }
            }
            PINEAPPLE => {
                if !self.pizza.pineapple {
                    self.pizza.pineapple = true;
                    self.pizza.cost += price;
                }
            }
            BACON => {
                if !self.pizza.bacon {
                    self.pizza.bacon = true;
                    self.pizza.cost += price;
                }
            }
            CHICKEN => {
                if !self.pizza.chicken {
                    self.pizza.chicken = true;
                    self.pizza.cost += price;
                }
            }
            _ => (),
        }
        self
    }
    
    fn build(self) -> Pizza {
        self.pizza
    }
}

pub struct MargaritaPizzaBuilder {
    pizza: Pizza,
}

impl PizzaBuilder for MargaritaPizzaBuilder {
    fn new() -> Self {
        let mut pizza = Pizza::new();
        pizza.cheese = true;
        pizza.cost = 5.0;
        MargaritaPizzaBuilder { pizza }
    }

    fn required_ingredients() -> Vec<String> {
        vec![CHEESE.to_string()]
    }

    fn add_ingredient(&mut self, _ingredient: &str, _price: f32) -> &mut Self {
        println!("Margarita pizza already has predefined ingredients.");
        self
    }

    fn build(self) -> Pizza {
        self.pizza
    }
}

pub struct PepperoniPizzaBuilder {
    pizza: Pizza,
}

impl PizzaBuilder for PepperoniPizzaBuilder {
    fn new() -> Self {
        let mut pizza = Pizza::new();
        pizza.cheese = true;
        pizza.pepperoni = true;
        pizza.cost = 7.0;
        PepperoniPizzaBuilder { pizza }
    }

    fn required_ingredients() -> Vec<String> {
        vec![CHEESE.to_string(), PEPPERONI.to_string()]
    }

    fn add_ingredient(&mut self, _ingredient: &str, _price: f32) -> &mut Self {
        println!("Pepperoni pizza already has predefined ingredients.");
        self
    }

    fn build(self) -> Pizza {
        self.pizza
    }
}
