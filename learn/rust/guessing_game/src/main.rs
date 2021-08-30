use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("GUESS THE NUMBER");


    let secret_number = rand::thread_rng().gen_range(0..100);

    loop {

        println!("please input your guess:");

        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(s) => {
                println!("error: {}", s);
                continue;
            },
        };

        println!("you guess: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("too small"),
            Ordering::Equal => {
                println!("right");
                break;
            },
            Ordering::Greater => println!("too big!"),
        }
    }

    println!("secret number: {}", secret_number);
}
