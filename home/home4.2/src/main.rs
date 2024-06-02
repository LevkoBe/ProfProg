
trait BaseCalculator {
    fn get_price(&self) -> f32;
    fn get_minimal_value(&self) -> f32;
    fn get_report(&self) -> String;
}

struct ConstantCalculator;

impl BaseCalculator for ConstantCalculator {
    fn get_price(&self) -> f32 {
        0.0
    }

    fn get_minimal_value(&self) -> f32 {
        0.0
    }

    fn get_report(&self) -> String {
        "Sound of silence".to_string()
    }
}

fn print_results(calculator: &dyn BaseCalculator) {
    println!("Current price: {}", calculator.get_price());
    println!("Current minimal value: {}", calculator.get_minimal_value());
    println!("Current report: {}", calculator.get_report());
}

fn main() {
    println!("Hello, world!");
    let calculator = ConstantCalculator;
    print_results(&calculator);
}
