pub const FILLING_VALUE: f64 = 42.0;
pub const ARRAY_SIZE: usize = 1024;

#[derive(Debug)]
pub struct MegaData {
    small_array: Vec<f64>,
    big_array: Vec<f64>,
}

impl MegaData {
    pub fn new() -> Self {
        Self {
            small_array: vec![FILLING_VALUE; ARRAY_SIZE],
            big_array: vec![FILLING_VALUE; ARRAY_SIZE * 1024],
        }
    }

    pub fn reset(&mut self) {
        self.small_array.fill(FILLING_VALUE);
        self.big_array.fill(FILLING_VALUE);
    }
}

impl Default for MegaData {
    fn default() -> Self {
        MegaData::new()
    }
}
