use std::fmt;

#[derive(Debug)]
struct TriangleError;

#[derive(Debug)]
enum Sides {
    A,
    B,
    C,
}

impl fmt::Display for TriangleError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Invalid triangle sides")
    }
}

struct Triangle {
    a: f64,
    b: f64,
    c: f64,
}

impl Triangle {
    fn new(a: f64, b: f64, c: f64) -> Result<Triangle, TriangleError> {
        if !Triangle::is_valid(a, b, c) {
            Err(TriangleError)
        } else {
            Ok(Triangle { a, b, c })
        }
    }

    fn calculate_area(&self) -> f64 {
        let s = (self.a + self.b + self.c) / 2.0;
        (s * (s - self.a) * (s - self.b) * (s - self.c)).sqrt()
    }

    fn is_valid(a: f64, b: f64, c: f64) -> bool {
        a + b > c && a + c > b && b + c > a && a > 0.0 && b > 0.0 && c > 0.0
    }

    fn get_height_to_side(&self, side: Sides) -> f64 {
        let area = self.calculate_area();
        match side {
            Sides::A => (2.0 * area) / self.a,
            Sides::B => (2.0 * area) / self.b,
            Sides::C => (2.0 * area) / self.c,
        }
    }
}

fn main() {
    let a = 3.0;
    let b = 4.0;
    let c = 5.0;
    let is_valid = Triangle::is_valid(a, b, c);
    println!("Is valid: {}", is_valid);
    match Triangle::new(a, b, c) {
        Ok(triangle) => {
            let area = triangle.calculate_area();
            println!("Area: {}", area);
        }
        Err(error) => {
            println!("Error: {}", error);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn expect_area_6_when_sides_3_4_5() {
        // arrange
        let triangle = Triangle::new(3.0, 4.0, 5.0).unwrap();
        // act
        let area = triangle.calculate_area();
        // assert
        assert_eq!(6.0, area);
    }

    #[test]
    fn expect_area_24_when_sides_10_6_8() {
        // arrange
        let triangle = Triangle::new(10.0, 6.0, 8.0).unwrap();
        // act
        let area = triangle.calculate_area();
        // assert
        assert_eq!(24.0, area);
    }

    #[test]
    fn expect_not_triangle_when_negative_sides() {
        // arrange
        let is_triangle = Triangle::is_valid(-1.0, 2.0, 3.0);
        // assert
        assert!(!is_triangle);
    }

    #[test]
    fn expect_is_triangle_when_valid_sides() {
        // arrange
        let is_triangle = Triangle::is_valid(2.0, 3.0, 4.0);
        // assert
        assert!(is_triangle);
    }

    #[test]
    fn expect_not_triangle_when_invalid_sides() {
        // arrange
        let is_triangle = Triangle::is_valid(2.0, 3.0, 5.0);
        // assert
        assert!(!is_triangle);
    }

    #[test]
    fn expect_exception_when_invalid_sides() {
        // arrange
        let result = Triangle::new(2.0, 3.0, 5.0);
        // assert
        assert!(result.is_err());
    }

    #[test]
    fn expect_no_exception_when_valid_sides() {
        // arrange
        let result = Triangle::new(2.0, 3.0, 4.0);
        // assert
        assert!(result.is_ok());
    }

    #[test]
    fn expect_height_when_right_triangle() {
        // arrange
        let triangle = Triangle::new(3.0, 4.0, 5.0).unwrap();
        // act
        let height = triangle.get_height_to_side(Sides::A);
        // assert
        assert_eq!(height, 4.0);
    }

    #[test]
    fn expect_specific_height_when_side_a() {
        // arrange
        let triangle = Triangle::new(2.0, 2.0, 3.0).unwrap();
        // act
        let height = triangle.get_height_to_side(Sides::B);
        // assert
        assert_eq!(height, 1.984313483298443);
    }
}
