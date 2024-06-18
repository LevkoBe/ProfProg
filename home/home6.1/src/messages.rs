use std::fmt;

pub trait Message: fmt::Display {
    fn get_type(&self) -> &'static str;
}

pub struct GreenMessage {
    message: String,
    counter: i32,
}

impl GreenMessage {
    pub fn new(message: String, counter: i32) -> Self {
        GreenMessage { message, counter }
    }
}

impl fmt::Display for GreenMessage {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} {}", self.message, self.counter)
    }
}

impl Message for GreenMessage {
    fn get_type(&self) -> &'static str {
        "GreenMessage"
    }
}

pub struct BlueMessage {
    value1: f64,
    value2: f64,
}

impl BlueMessage {
    pub fn new(value1: f64, value2: f64) -> Self {
        BlueMessage { value1, value2 }
    }
}

impl fmt::Display for BlueMessage {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} {}", self.value1, self.value2)
    }
}

impl Message for BlueMessage {
    fn get_type(&self) -> &'static str {
        "BlueMessage"
    }
}

pub struct OrangeMessage {
    string1: String,
    string2: String,
    integer: i32,
    double_value: f64,
}

impl OrangeMessage {
    pub fn new(string1: String, string2: String, integer: i32, double_value: f64) -> Self {
        OrangeMessage {
            string1,
            string2,
            integer,
            double_value,
        }
    }
}

impl fmt::Display for OrangeMessage {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} {} {} {}", self.string1, self.string2, self.integer, self.double_value)
    }
}

impl Message for OrangeMessage {
    fn get_type(&self) -> &'static str {
        "OrangeMessage"
    }
}
