use std::thread;
use std::time::Duration;

use crate::MessageDispatcher;
use crate::messages::{BlueMessage, GreenMessage, OrangeMessage};
use crate::Arc;
use rand::Rng;

pub(crate) fn generate_messages(dispatcher: Arc<MessageDispatcher>) {
    let mut rng = rand::thread_rng();

    loop {
        let message_type: u32 = rng.gen_range(1..=3);
        match message_type {
            1 => {
                let message = Arc::new(GreenMessage::new("Green".to_string(), rng.gen()));
                dispatcher.publish(message);
            }
            2 => {
                let message = Arc::new(BlueMessage::new(rng.gen::<f64>() * 1.1, rng.gen::<f64>() * 2.2));
                dispatcher.publish(message);
            }
            3 => {
                let message = Arc::new(OrangeMessage::new(
                    "Orange1".to_string(),
                    "Orange2".to_string(),
                    rng.gen(),
                    rng.gen::<f64>() * 3.3,
                ));
                dispatcher.publish(message);
            }
            _ => {}
        }
        thread::sleep(Duration::from_secs(1));
    }
}
