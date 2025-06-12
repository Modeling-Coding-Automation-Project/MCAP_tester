"""
This module provides the MCAPTester class, a simple testing utility for validating numerical and array-based results in Python.
It is designed to facilitate the comparison of scalar values and numpy arrays with configurable tolerance, and to report failures in a clear manner.
The tester maintains an internal flag to track test failures and can raise an exception if any test fails.

Classes:
    MCAPTester:
        A utility class for performing assertions on numerical values and numpy arrays, supporting both scalar and 2D array comparisons with tolerance.
        It provides methods to check for near-equality, handle test failure reporting, and manage the test failure state.
"""
import numpy as np


class MCAPTester:
    def __init__(self):
        self.test_failed_flag = False

    def expect_near(self, actual, expected, tolerance, message):
        """
        Asserts that two values (scalars or numpy arrays) are approximately equal within a given tolerance.

        Parameters
        ----------
        actual : int, float, or np.ndarray
            The actual value to check.
        expected : int, float, or np.ndarray
            The expected value to compare against.
        tolerance : float
            The maximum allowed difference between actual and expected.
        message : str
            The message to display if the assertion fails.

        Raises
        ------
        TypeError
            If the types of actual and expected are not supported.

        Behavior
        --------
        - For scalars (int or float), checks if the absolute difference is within tolerance.
        - For numpy arrays, checks if shapes match and all elements are within tolerance using np.allclose.
        - On failure, prints the provided message and sets self.test_failed_flag to True.
        """
        if isinstance(actual, (int, float)) and isinstance(expected, (int, float)):
            if abs(actual - expected) <= tolerance:
                pass  # Do Nothing
            else:
                print(f"FAILURE: {message}")
                print()
                self.test_failed_flag = True
        elif isinstance(actual, np.ndarray) and isinstance(expected, np.ndarray):
            if actual.shape != expected.shape:
                print(f"FAILURE: {message} Shape mismatch.")
                print()
                self.test_failed_flag = True
                return

            if not np.allclose(actual, expected, atol=tolerance):
                print(f"FAILURE: {message} Element mismatch.")
                print()
                self.test_failed_flag = True
        else:
            raise TypeError("Unsupported types for expect_near.")

    def expect_near_2d(self, actual, expected, tolerance, message):
        """
        Asserts that two 2D numpy arrays are element-wise equal within a given tolerance.

        Parameters
        ----------
        actual : np.ndarray
            The actual 2D numpy array to be tested.
        expected : np.ndarray
            The expected 2D numpy array to compare against.
        tolerance : float
            The maximum allowed difference between corresponding elements.
        message : str
            Message to display in case of failure.

        Raises
        ------
        TypeError
            If either `actual` or `expected` is not a numpy array.

        Side Effects
        ------------
        - Prints a failure message and sets `self.test_failed_flag` to True if arrays differ in shape or any element exceeds the tolerance.
        - Returns immediately upon the first failure detected.
        """
        if not isinstance(actual, np.ndarray) or not isinstance(expected, np.ndarray):
            raise TypeError("Both actual and expected must be numpy arrays.")

        if actual.shape != expected.shape:
            print(f"FAILURE: {message} Shape mismatch.")
            print()
            self.test_failed_flag = True
            return

        for i in range(actual.shape[0]):
            for j in range(actual.shape[1]):
                if abs(actual[i, j] - expected[i, j]) > tolerance:
                    print(
                        f"FAILURE: {message} Element mismatch at ({i}, {j}).")
                    print()
                    self.test_failed_flag = True
                    return

    def throw_error_if_test_failed(self):
        """
        Raises a RuntimeError if the test has failed.

        Checks the 'test_failed_flag' attribute, and if it is True, raises a RuntimeError
        to indicate that the test did not pass.

        Raises:
            RuntimeError: If the test_failed_flag is set to True.
        """
        if self.test_failed_flag:
            raise RuntimeError("Test failed.")

    def reset_test_failed_flag(self):
        """
        Resets the test_failed_flag attribute to False.

        This method is typically used to clear the failure state before starting a new test or after handling a test failure.
        """
        self.test_failed_flag = False
