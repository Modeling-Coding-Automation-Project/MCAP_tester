/**
 * This module provides the MCAPTester struct, a simple testing utility for validating numerical and array-based results in Rust.
 * It is designed to facilitate the comparison of scalar values and ndarray arrays with configurable tolerance, and to report failures in a clear manner.
 * The tester maintains an internal flag to track test failures and can raise a panic if any test fails.
 *
 * Structs:
 *     MCAPTester:
 *         A utility struct for performing assertions on numerical values and ndarray arrays, supporting both scalar and 2D array comparisons with tolerance.
 *         It provides methods to check for near-equality, handle test failure reporting, and manage the test failure state.
 */
use ndarray::{Array2, ArrayView2};

pub struct MCAPTester {
    test_failed_flag: bool,
}

impl MCAPTester {
    /**
     * Creates a new MCAPTester instance with test_failed_flag set to false.
     */
    pub fn new() -> Self {
        MCAPTester {
            test_failed_flag: false,
        }
    }

    /**
     * Asserts that two scalar values are approximately equal within a given tolerance.
     *
     * # Arguments
     *
     * * `actual` - The actual value to check.
     * * `expected` - The expected value to compare against.
     * * `tolerance` - The maximum allowed difference between actual and expected.
     * * `message` - The message to display if the assertion fails.
     *
     * # Behavior
     *
     * - Checks if the absolute difference is within tolerance.
     * - On failure, prints the provided message and sets self.test_failed_flag to true.
     */
    pub fn expect_near_scalar(
        &mut self,
        actual: f64,
        expected: f64,
        tolerance: f64,
        message: &str,
    ) {
        if (actual - expected).abs() <= tolerance {
            // Do nothing
        } else {
            println!("FAILURE: {}", message);
            println!();
            self.test_failed_flag = true;
        }
    }

    /**
     * Asserts that two 2D arrays are element-wise equal within a given tolerance.
     *
     * # Arguments
     *
     * * `actual` - The actual 2D array to be tested.
     * * `expected` - The expected 2D array to compare against.
     * * `tolerance` - The maximum allowed difference between corresponding elements.
     * * `message` - Message to display in case of failure.
     *
     * # Behavior
     *
     * - Checks if shapes match and all elements are within tolerance.
     * - On failure, prints the provided message and sets self.test_failed_flag to true.
     */
    pub fn expect_near(
        &mut self,
        actual: ArrayView2<f64>,
        expected: ArrayView2<f64>,
        tolerance: f64,
        message: &str,
    ) {
        if actual.shape() != expected.shape() {
            println!("FAILURE: {} Shape mismatch.", message);
            println!();
            self.test_failed_flag = true;
            return;
        }

        let mut all_close = true;
        for (a, e) in actual.iter().zip(expected.iter()) {
            if (a - e).abs() > tolerance {
                all_close = false;
                break;
            }
        }

        if !all_close {
            println!("FAILURE: {} Element mismatch.", message);
            println!();
            self.test_failed_flag = true;
        }
    }

    /**
     * Asserts that two 2D arrays are element-wise equal within a given tolerance.
     *
     * # Arguments
     *
     * * `actual` - The actual 2D array to be tested.
     * * `expected` - The expected 2D array to compare against.
     * * `tolerance` - The maximum allowed difference between corresponding elements.
     * * `message` - Message to display in case of failure.
     *
     * # Side Effects
     *
     * - Prints a failure message and sets `self.test_failed_flag` to true if arrays differ in shape or any element exceeds the tolerance.
     * - Returns immediately upon the first failure detected.
     */
    pub fn expect_near_2d(
        &mut self,
        actual: ArrayView2<f64>,
        expected: ArrayView2<f64>,
        tolerance: f64,
        message: &str,
    ) {
        if actual.shape() != expected.shape() {
            println!("FAILURE: {} Shape mismatch.", message);
            println!();
            self.test_failed_flag = true;
            return;
        }

        let rows = actual.shape()[0];
        let cols = actual.shape()[1];

        for i in 0..rows {
            for j in 0..cols {
                if (actual[[i, j]] - expected[[i, j]]).abs() > tolerance {
                    println!("FAILURE: {} Element mismatch at ({}, {}).", message, i, j);
                    println!();
                    self.test_failed_flag = true;
                    return;
                }
            }
        }
    }

    /**
     * Panics if the test has failed.
     *
     * Checks the 'test_failed_flag' attribute, and if it is true, panics
     * to indicate that the test did not pass.
     *
     * # Panics
     *
     * Panics if the test_failed_flag is set to true.
     */
    pub fn throw_error_if_test_failed(&self) {
        if self.test_failed_flag {
            panic!("Test failed.");
        }
    }

    /**
     * Resets the test_failed_flag attribute to false.
     *
     * This method is typically used to clear the failure state before starting a new test or after handling a test failure.
     */
    pub fn reset_test_failed_flag(&mut self) {
        self.test_failed_flag = false;
    }
}

impl Default for MCAPTester {
    fn default() -> Self {
        Self::new()
    }
}
