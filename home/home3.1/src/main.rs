fn main() {
    let x = 1e-300;
    let y = 2e-300;
    let z = 3e-300;
    let result = magic_operation(x, y, z);
    println!("{}", result);
    println!("Hello, world!");
}

#[allow(dead_code)]
fn magic_operation(x: f64, y: f64, z: f64) -> f64 {
    let product = x * y * z;
    if product < f64::EPSILON {
        let sum = x + y + z;
        if sum < f64::EPSILON {
            return x + (y + 1.0) * (z - 1.0); 
        }
        return 1.0 / sum;
    }
    1.0 / product
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn expect_product_inverse_when_3_numbers() {
        // Arrange
        let x = 1.0;
        let y = 2.0;
        let z = 3.0;
        let product_inverse = 1.0 / (x * y * z);

        // Act
        let result = magic_operation(x, y, z);

        // Assert
        assert!(
            (result - product_inverse).abs() < f64::EPSILON,
            "Test failed! Expected the inverse of the product ({}) but got {}.", product_inverse, result
        );
    }

    #[test]
    fn expect_sum_inverse_when_zero_present() {
        // Arrange
        let x = 1.0;
        let y = 2.0;
        let z = 0.0;
        let sum_inverse = 1.0 / (x + y + z);

        // Act
        let result = magic_operation(x, y, z);

        // Assert
        assert!(
            (result - sum_inverse).abs() < f64::EPSILON,
            "Test failed! Expected the inverse of the sum ({}) but got {}.", sum_inverse, result
        );
    }

    #[test]
    fn expect_special_case_when_small_numbers() {
        // Arrange
        let x = 1e-300;
        let y = 2e-300;
        let z = 3e-300;
        let special_case_result = x + (y + 1.0) * (z - 1.0);

        // Act
        let result = magic_operation(x, y, z);

        // Assert
        assert!(
            (result - special_case_result).abs() < f64::EPSILON,
            "Test failed! Expected special case result ({}) but got {}.", special_case_result, result
        );
    }

    #[test]
    fn expect_special_case_when_zero_sum() {
        // Arrange
        let x = 0.0;
        let y = 1.0;
        let z = -1.0;
        let special_case_result = x + (y + 1.0) * (z - 1.0);

        // Act
        let result = magic_operation(x, y, z);

        // Assert
        assert!(
            (result - special_case_result).abs() < f64::EPSILON,
            "Test failed! Expected special case result ({}) but got {}.", special_case_result, result
        );
    }
}
