mod message_dispatcher;
mod messages;
pub mod message_generator;

use core::time::Duration;
use std::sync::Arc;
use std::thread;
use message_dispatcher::MessageDispatcher;
use message_generator::generate_messages;

fn main() {
    let dispatcher = Arc::new(MessageDispatcher::new());

    let green_subscriber_id = dispatcher.subscribe("GreenMessage", Arc::new(move |message| {
        println!("Received GreenMessage: {}", message);
    }));

    let _blue_subscriber_id = dispatcher.subscribe("BlueMessage", Arc::new(move |message| {
        println!("Received BlueMessage: {}", message);
    }));

    let orange_subscriber_id = dispatcher.subscribe("OrangeMessage", Arc::new(move |message| {
        println!("Received OrangeMessage: {}", message);
    }));

    let generator_dispatcher = dispatcher.clone();
    let handle1 = thread::spawn(move || {
        generate_messages(generator_dispatcher);
    });

    let generator_dispatcher = dispatcher.clone();
    let handle2 = thread::spawn(move || {
        generate_messages(generator_dispatcher);
    });

    thread::sleep(Duration::from_secs(5));

    dispatcher.unsubscribe("GreenMessage", green_subscriber_id);
    // dispatcher.unsubscribe("BlueMessage", _blue_subscriber_id);
    dispatcher.unsubscribe("OrangeMessage", orange_subscriber_id);

    handle1.join().unwrap();
    handle2.join().unwrap();
}
