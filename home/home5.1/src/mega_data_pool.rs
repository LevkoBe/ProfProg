use std::cell::RefCell;

#[derive(Debug)]
pub struct MegaDataPool<T> {
    pool: RefCell<Vec<T>>,
    used_size: RefCell<usize>,
}

#[derive(Debug)]
pub struct MegaDataPoolHandle<'a, T> {
    pool: &'a RefCell<Vec<T>>,
    item: Option<T>,
}

#[derive(Debug)]
pub struct MegaDataPoolExhausted;

impl<T: Default> MegaDataPool<T> {
    pub fn new(number_items: usize) -> Self {
        let pool = (0..number_items).map(|_| T::default()).collect();
        MegaDataPool {
            pool: RefCell::new(pool),
            used_size: RefCell::new(0),
        }
    }

    pub fn acquire(&self) -> Result<MegaDataPoolHandle<'_, T>, MegaDataPoolExhausted> {
        let item = self.pool.borrow_mut().pop().ok_or(MegaDataPoolExhausted)?;
        let next_val = *self.used_size.borrow() + 1;
        *self.used_size.borrow_mut() = next_val;
        Ok(MegaDataPoolHandle {
            pool: &self.pool,
            item: Some(item),
        })
    }

    pub fn used_size(&self) -> usize {
        *self.used_size.borrow()
    }

    pub fn release(&self, mut handle: MegaDataPoolHandle<'_, T>) {
        if let Some(item) = handle.item.take() {
            self.pool.borrow_mut().push(item);
            let next_val = *self.used_size.borrow() - 1;
            *self.used_size.borrow_mut() = next_val;
        }
    }
}

impl <'a, T> Drop for MegaDataPoolHandle<'a, T> {
    fn drop(&mut self) {
        if let Some(item) = self.item.take() {
            self.pool.borrow_mut().push(item);
        }
    }
}

impl <'a, T> std::ops::Deref for MegaDataPoolHandle<'a, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        self.item.as_ref().unwrap()
    }
}

impl <'a, T> std::ops::DerefMut for MegaDataPoolHandle<'a, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        self.item.as_mut().unwrap()
    }
}

