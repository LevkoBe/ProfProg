pub const CHEESE: &str = "cheese";
pub const PEPPERONI: &str = "pepperoni";
pub const HAM: &str = "ham";
pub const SAUSAGE: &str = "sausage";
pub const MUSHROOMS: &str = "mushrooms";
pub const ONIONS: &str = "onions";
pub const OLIVES: &str = "olives";
pub const PINEAPPLE: &str = "pineapple";
pub const BACON: &str = "bacon";
pub const CHICKEN: &str = "chicken";

pub struct Pizza {
    pub cheese: bool,
    pub pepperoni: bool,
    pub ham: bool,
    pub sausage: bool,
    pub mushrooms: bool,
    pub onions: bool,
    pub olives: bool,
    pub pineapple: bool,
    pub bacon: bool,
    pub chicken: bool,
    pub cost: f32,
}

impl Pizza {
    pub fn new() -> Self {
        Pizza {
            cheese: false,
            pepperoni: false,
            ham: false,
            sausage: false,
            mushrooms: false,
            onions: false,
            olives: false,
            pineapple: false,
            bacon: false,
            chicken: false,
            cost: 0.0,
        }
    }

    pub fn get_ingredients(&self) -> Vec<&str> {
        let mut ingredients = Vec::new();
        if self.cheese { ingredients.push(CHEESE); }
        if self.pepperoni { ingredients.push(PEPPERONI); }
        if self.ham { ingredients.push(HAM); }
        if self.sausage { ingredients.push(SAUSAGE); }
        if self.mushrooms { ingredients.push(MUSHROOMS); }
        if self.onions { ingredients.push(ONIONS); }
        if self.olives { ingredients.push(OLIVES); }
        if self.pineapple { ingredients.push(PINEAPPLE); }
        if self.bacon { ingredients.push(BACON); }
        if self.chicken { ingredients.push(CHICKEN); }
        ingredients
    }

    pub fn get_cost(&self) -> f32 {
        self.cost
    }
}
