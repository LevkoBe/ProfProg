use crate::pizza::{Pizza, CHEESE, PEPPERONI, HAM, SAUSAGE, MUSHROOMS, ONIONS, OLIVES, PINEAPPLE, BACON, CHICKEN};

pub trait PizzaBuilder {
    fn new() -> Self where Self: Sized;
    fn add_ingredient(&mut self, ingredient: &str) -> &mut Self;
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

    fn add_ingredient(&mut self, ingredient: &str) -> &mut Self {
        match ingredient {
            CHEESE => {
                if !self.pizza.cheese {
                    self.pizza.cheese = true;
                    self.pizza.cost += 1.5;
                }
            }
            PEPPERONI => {
                if !self.pizza.pepperoni {
                    self.pizza.pepperoni = true;
                    self.pizza.cost += 2.0;
                }
            }
            HAM => {
                if !self.pizza.ham {
                    self.pizza.ham = true;
                    self.pizza.cost += 2.0;
                }
            }
            SAUSAGE => {
                if !self.pizza.sausage {
                    self.pizza.sausage = true;
                    self.pizza.cost += 1.8;
                }
            }
            MUSHROOMS => {
                if !self.pizza.mushrooms {
                    self.pizza.mushrooms = true;
                    self.pizza.cost += 1.2;
                }
            }
            ONIONS => {
                if !self.pizza.onions {
                    self.pizza.onions = true;
                    self.pizza.cost += 0.8;
                }
            }
            OLIVES => {
                if !self.pizza.olives {
                    self.pizza.olives = true;
                    self.pizza.cost += 1.0;
                }
            }
            PINEAPPLE => {
                if !self.pizza.pineapple {
                    self.pizza.pineapple = true;
                    self.pizza.cost += 1.5;
                }
            }
            BACON => {
                if !self.pizza.bacon {
                    self.pizza.bacon = true;
                    self.pizza.cost += 2.2;
                }
            }
            CHICKEN => {
                if !self.pizza.chicken {
                    self.pizza.chicken = true;
                    self.pizza.cost += 2.5;
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

    fn add_ingredient(&mut self, _ingredient: &str) -> &mut Self {
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

    fn add_ingredient(&mut self, _ingredient: &str) -> &mut Self {
        println!("Pepperoni pizza already has predefined ingredients.");
        self
    }

    fn build(self) -> Pizza {
        self.pizza
    }
}
