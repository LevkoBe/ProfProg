use std::io::{self, Write, BufRead};

fn input_valid_filename() -> String {
    loop {
        let mut filename = String::new();
        io::stdin().read_line(&mut filename).expect("Failed to read line");
        let filename = filename.trim().to_string();
        if filename.ends_with(".txt") {
            return filename;
        } else {
            println!("Filename must end with \".txt\"");
            print!("Please provide correct file name: ");
            io::stdout().flush().expect("Failed to flush stdout");
        }
    }
}

fn input_valid_color() -> String {
    loop {
        let mut color = String::new();
        io::stdin().read_line(&mut color).expect("Failed to read line");
        let color = color.trim().to_string();
        let color_split = color.split(",").collect::<Vec<_>>();
        if color_split.len() != 3 {
            println!("Invalid color format. Please enter in format \"R,G,B\" where R, G, and B are integers between 0 and 255.");
            print!("Please, enter your favorite color (format \"0,0,0\"): ");
            io::stdout().flush().expect("Failed to flush stdout");
            continue;
        }
        let valid_color = color_split.iter().all(|c| c.trim().parse::<u8>().is_ok());
        if valid_color {
            return color;
        }
        println!("Invalid color format. Please enter in format \"R,G,B\" where R, G, and B are integers between 0 and 255.");
        print!("Please, enter your favorite color (format \"0,0,0\"): ");
        io::stdout().flush().expect("Failed to flush stdout");
    }
}

fn input_unfavorite_color() -> Option<String> {
    println!("Do you want to specify an unfavorite color? (y/n)");
    loop {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        match input.trim().to_lowercase().as_str() {
            "y" => {
                println!("Please, enter the unfavorite color (format \"0,0,0\"): ");
                io::stdout().flush().expect("Failed to flush stdout");
                let color = input_valid_color();
                return Some(color);
            }
            "n" => return None,
            _ => {
                println!("Invalid input. Please enter 'y' or 'n'.");
                continue;
            }
        }
    }
}

fn ask_user() -> (String, String, String, Option<String>) {
    print!("Please, enter the name of the file with the image: ");
    io::stdout().flush().expect("Failed to flush stdout");
    let filename = input_valid_filename();

    print!("Please, enter your favorite color (format \"0,0,0\"): ");
    io::stdout().flush().expect("Failed to flush stdout");
    let favorite_color = input_valid_color();

    print!("Please, enter the output file name: ");
    io::stdout().flush().expect("Failed to flush stdout");
    let output_filename = input_valid_filename();

    let unfavorite_color = input_unfavorite_color();

    (filename, favorite_color, output_filename, unfavorite_color)
}

struct Image {
    array: [[String; 16]; 16],
    favorite_color: String,
}

impl Image {
    fn new() -> Image {
        Image {
            array: Default::default(),
            favorite_color: String::new(),
        }
    }

    fn fill_in_array(&mut self, x: usize, y: usize, color: String, unfavorite_color: Option<&String>) {
        if let Some(uf_color) = unfavorite_color {
            if color == *uf_color {
                self.array[x][y] = self.favorite_color.clone();
                return;
            }
        }
        if color.eq(&self.favorite_color) {
            self.array[x][y] = self.favorite_color.clone();
            if x > 0 { self.array[x - 1][y] = color.clone(); }
            if y > 0 { self.array[x][y - 1] = color.clone(); }
        } else {
            self.array[x][y] = color;
        }
    }

    fn write_file(&self, filename: &str) {
        let mut file = std::fs::File::create(filename).unwrap_or_else(|err| {
            eprintln!("Failed to create file {}: {}", filename, err);
            std::process::exit(1);
        });
        for i in 0..16 {
            for j in 0..16 {
                write!(file, "{} ", self.array[i][j]).unwrap_or_else(|err| {
                    eprintln!("Failed to write to file {}: {}", filename, err);
                    std::process::exit(1);
                });
            }
            writeln!(file).unwrap_or_else(|err| {
                eprintln!("Failed to write to file {}: {}", filename, err);
                std::process::exit(1);
            });
        }
        println!("Image saved to {}", filename);
    }

    fn read_file(&mut self, filename: &str, unfavorite_color: Option<&String>) {
        let file = std::fs::File::open(filename).unwrap_or_else(|err| {
            eprintln!("Failed to open file {}: {}", filename, err);
            std::process::exit(1);
        });
        let reader = std::io::BufReader::new(file);
        for (i, line) in reader.lines().enumerate() {
            let line = line.unwrap_or_else(|err| {
                eprintln!("Failed to read line from file {}: {}", filename, err);
                std::process::exit(1);
            });
            for (j, color) in line.split_whitespace().enumerate() {
                self.fill_in_array(i, j, color.to_string(), unfavorite_color);
            }
        }
    }
}

fn main() {
    let mut image = Image::new();
    let (i_filename, fav_color, o_filename, unfav_color) = ask_user();

    image.favorite_color = fav_color;
    image.read_file(&i_filename, unfav_color.as_ref());
    image.write_file(&o_filename);
}
