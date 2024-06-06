struct LegacyCalculator {
    mega_delta: f32,
    mega_multiplier: f32,
}

impl LegacyCalculator {
    const STRANGE_VAL1: f32 = 6.0;
    const STRANGE_VAL2: f32 = 13.0;

    fn new(mega_delta: f32, mega_multiplier: f32) -> Self {
        LegacyCalculator {
            mega_delta,
            mega_multiplier,
        }
    }

    fn calculate_price_part1(&self) -> f32 {
        Self::STRANGE_VAL1 - self.mega_delta
    }

    fn calculate_price_part2(&self) -> f32 {
        Self::STRANGE_VAL2 * self.mega_multiplier + 1.0 - self.mega_delta
    }

    fn get_our_the_most_and_minimal_value(&self) -> f32 {
        self.mega_delta * self.mega_multiplier
    }

    fn get_some_document_representation(&self) -> String {
        format!(
            "The man {:.1} who sold the {:.1} world",
            Self::STRANGE_VAL1 - self.mega_delta,
            self.mega_multiplier * Self::STRANGE_VAL2
        )
    }
}

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
        "Sound of Silence".to_string()
    }
}

struct MyCoolCalculator {
    coef1: f32,
    coef2: f32,
    coef3: f32,
}

impl MyCoolCalculator {
    const VAL1: f32 = 12.0;
    const VAL2: f32 = 3.0;
    const VAL3: f32 = 0.05;

    fn new(coef1: f32, coef2: f32, coef3: f32) -> Self {
        MyCoolCalculator { coef1, coef2, coef3 }
    }
}

impl BaseCalculator for MyCoolCalculator {
    fn get_price(&self) -> f32 {
        self.coef1 * Self::VAL1 + self.coef2 * Self::VAL2 - self.coef3 * Self::VAL3
    }

    fn get_minimal_value(&self) -> f32 {
        (self.coef1 * Self::VAL1).min(self.coef2 * Self::VAL2)
    }

    fn get_report(&self) -> String {
        format!("Some1 {}, another2 {:.3}, and3 {:.2}", self.coef1, self.coef2, self.coef3 * Self::VAL2)
    }
}

struct MegaAdapter {
    legacy_calculator: LegacyCalculator,
}

impl BaseCalculator for MegaAdapter {
    fn get_price(&self) -> f32 {
        self.legacy_calculator.calculate_price_part1() + self.legacy_calculator.calculate_price_part2()
    }

    fn get_minimal_value(&self) -> f32 {
        self.legacy_calculator.get_our_the_most_and_minimal_value()
    }

    fn get_report(&self) -> String {
        self.legacy_calculator.get_some_document_representation()
    }
}

fn print_results(calculator: &dyn BaseCalculator) {
    println!("Current price: {}", calculator.get_price());
    println!("Current minimal value: {}", calculator.get_minimal_value());
    println!("Current report: {}", calculator.get_report());
}

fn main() {
    let cool_calculator = MyCoolCalculator::new(6.0, 12.1, 3.2);
    print_results(&cool_calculator);
    
    let constant_calculator = ConstantCalculator;
    print_results(&constant_calculator);
    
    let adapted_legacy_calculator = MegaAdapter {
        legacy_calculator: LegacyCalculator::new(1.34, 5.4)};
    print_results(&adapted_legacy_calculator);
}
