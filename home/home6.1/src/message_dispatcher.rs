use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use std::sync::atomic::{AtomicUsize, Ordering};
use crate::messages::Message;

type Callback = Arc<dyn Fn(Arc<dyn Message>) + Send + Sync>;

pub(crate) struct MessageDispatcher {
    subscribers: Mutex<HashMap<String, HashMap<usize, Callback>>>,
    next_id: AtomicUsize,
}

impl MessageDispatcher {
    pub fn new() -> Self {
        MessageDispatcher {
            subscribers: Mutex::new(HashMap::new()),
            next_id: AtomicUsize::new(0),
        }
    }

    pub fn subscribe(&self, message_type: &str, callback: Callback) -> usize {
        let mut subscribers = self.subscribers.lock().unwrap();
        let type_subscribers = subscribers.entry(message_type.to_string()).or_default();
        let id = self.next_id.fetch_add(1, Ordering::SeqCst);
        type_subscribers.insert(id, callback);
        id
    }

    pub fn unsubscribe(&self, message_type: &str, id: usize) {
        let mut subscribers = self.subscribers.lock().unwrap();
        if let Some(type_subscribers) = subscribers.get_mut(message_type) {
            type_subscribers.remove(&id);
        }
    }

    pub fn publish(&self, message: Arc<dyn Message>) {
        let subscribers = self.subscribers.lock().unwrap();
        if let Some(type_subscribers) = subscribers.get(message.get_type()) {
            for callback in type_subscribers.values() {
                callback(message.clone());
            }
        }
    }
}
