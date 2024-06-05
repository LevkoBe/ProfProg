
mod mega_data;
mod mega_data_pool;
mod tests;

use crate::mega_data::MegaData;
use crate::mega_data_pool::MegaDataPool;

fn main() {
    let pool = MegaDataPool::new(5);
    let mut mega_data_handle = pool.acquire().unwrap();
    let used_size = pool.used_size();
    println!("Used size: {}", used_size);
    *mega_data_handle = MegaData::new();

    mega_data_handle.reset();
    println!("handle reset");
    
    pool.release(mega_data_handle);
    println!("handle released");
}
