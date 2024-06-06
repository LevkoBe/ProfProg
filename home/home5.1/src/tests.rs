#[cfg(test)]
mod tests {
    use crate::{mega_data::MegaData, mega_data_pool::MegaDataPool};

    #[test]
    fn expect_used_size_when_acquiring() {
        // Arrange
        let pool: MegaDataPool<MegaData> = MegaDataPool::new(5);
        let mut expected_size = 0;

        // Act
        for _ in 0..5 {
            pool.acquire().unwrap();
            expected_size += 1;

            // Assert
            assert_eq!(pool.used_size(), expected_size);
        }
    }

    #[test]
    fn expect_exception_when_exhausted() {
        // Arrange
        let pool: MegaDataPool<MegaData> = MegaDataPool::new(5);

        // Act
        let mut acquired = Vec::new();
        for _ in 0..5 {
            acquired.push(pool.acquire().unwrap());
        }

        assert!(pool.acquire().is_err());
    }

    #[test]
    fn expect_no_exception_when_similar_to_exhausted() {
        // Arrange
        let pool: MegaDataPool<MegaData> = MegaDataPool::new(5);

        // Act
        for _ in 0..42 {
            pool.acquire().unwrap();
        } // 42 is a magical number ;)

        assert!(pool.acquire().is_ok());
    }


    #[test]
    fn expect_used_size_when_releasing() {
        // Arrange
        let pool: MegaDataPool<MegaData> = MegaDataPool::new(5);
        let mut acquired = Vec::new();
        for _ in 0..5 {
            acquired.push(pool.acquire().unwrap());
        }
        let mut expected_size = 5;

        // Act
        for data in acquired {
            pool.release(data);

            // Assert
            expected_size -= 1;
            assert_eq!(pool.used_size(), expected_size);
        }
    }

    #[test]
    fn expect_used_size_when_acquired_again() {
        // Arrange
        let pool: MegaDataPool<MegaData> = MegaDataPool::new(5);
        let expected_size = 5;
        let mut acquired = Vec::new();
        for _ in 0..5 {
            acquired.push(pool.acquire().unwrap());
        }

        // Act & Assert
        for data in acquired {
            pool.release(data);
            pool.acquire().unwrap();
            assert_eq!(pool.used_size(), expected_size);
        }
    }}