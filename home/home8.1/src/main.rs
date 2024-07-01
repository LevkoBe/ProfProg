use std::fmt::Debug;

trait Product {
    fn get_coefficient(&self) -> f64;
    fn get_base_price(&self) -> f64;
}

#[derive(Debug)]
struct Milk;

impl Product for Milk {
    fn get_coefficient(&self) -> f64 {
        1.0
    }

    fn get_base_price(&self) -> f64 {
        2.0
    }
}

#[derive(Debug)]
struct Cookies;

impl Product for Cookies {
    fn get_coefficient(&self) -> f64 {
        2.0
    }

    fn get_base_price(&self) -> f64 {
        5.0
    }
}

#[derive(Debug)]
struct Pineapple;

impl Product for Pineapple {
    fn get_coefficient(&self) -> f64 {
        0.5
    }

    fn get_base_price(&self) -> f64 {
        10.0
    }
}

struct PricePresenter<const PRIORITY: usize>;

impl<const PRIORITY: usize> PricePresenter<PRIORITY> {
    fn print_total_price<T1: Product + Debug, T2: Product + Debug>(&self, obj1: &T1, obj2: &T2) {
        let total_price = PRIORITY as f64 * obj1.get_coefficient() * obj1.get_base_price()
                        + obj2.get_coefficient() * obj2.get_base_price();
        println!("Total price: {}", total_price);
    }
}

fn main() {
    let milk = Milk;
    let cookies = Cookies;
    let pineapple = Pineapple;

    let presenter = PricePresenter::<5>;
    presenter.print_total_price(&milk, &cookies);
    presenter.print_total_price(&milk, &pineapple);
    presenter.print_total_price(&cookies, &pineapple);
}
