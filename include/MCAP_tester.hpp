/**
 * @file MCAP_tester.hpp
 * @brief Provides the Tester::MCAPTester class template for unit testing
 * numerical values and containers.
 *
 * This header defines the Tester namespace containing the MCAPTester class
 * template, which offers a set of utility functions for verifying the numerical
 * closeness of scalar values, vectors, arrays, and nested containers. The class
 * is designed to facilitate automated testing by providing expect_near methods
 * that compare actual and expected results within a specified tolerance,
 * reporting failures and tracking test status.
 *
 * @class Tester::MCAPTester
 * @brief A template class for performing near-equality checks on scalars and
 * containers in unit tests.
 *
 * The MCAPTester class template provides overloaded expect_near methods for
 * comparing single values, std::vector, std::array, and nested containers. It
 * tracks test failures and can throw an exception if any test fails, supporting
 * robust and automated test workflows.
 */

#ifndef MCAP_TESTER_HPP
#define MCAP_TESTER_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Tester {

template <typename T> class MCAPTester {
public:
  MCAPTester() : _test_failed_flag(false) {}

  /**
   * @brief Checks if the actual value is within a specified tolerance of the
   * expected value.
   *
   * If the absolute difference between actual and expected is greater than the
   * given tolerance, this function prints a failure message and sets the
   * internal test failed flag.
   *
   * @tparam T Type of the values to compare (should support arithmetic
   * operations).
   * @param actual The actual value to check.
   * @param expected The expected value to compare against.
   * @param tolerance The maximum allowed difference between actual and
   * expected.
   * @param message The message to display if the check fails.
   */
  void expect_near(T actual, T expected, T tolerance,
                   const std::string &message) {
    if (std::abs(actual - expected) <= tolerance) {
      /* Do Nothing. */
    } else {
      std::cout << "FAILURE: " << message << std::endl;
      std::cout << std::endl;
      this->_test_failed_flag = true;
    }
  }

  /**
   * @brief Checks if two vectors are element-wise equal within a given
   * tolerance.
   *
   * Compares each element of the `actual` vector to the corresponding element
   * in the `expected` vector. If all elements are within the specified
   * `tolerance`, the function does nothing. If a size mismatch or an element
   * exceeds the tolerance, it prints a failure message, sets the internal test
   * failed flag, and returns.
   *
   * @tparam T Numeric type of the vector elements.
   * @param actual The vector of actual values to check.
   * @param expected The vector of expected values to compare against.
   * @param tolerance The maximum allowed difference between corresponding
   * elements.
   * @param message The message to display in case of failure.
   */
  void expect_near(const std::vector<T> actual, const std::vector<T> expected,
                   T tolerance, const std::string &message) {
    if (actual.size() != expected.size()) {
      std::cout << "FAILURE: " << message << " Size mismatch." << std::endl;
      std::cout << std::endl;
      this->_test_failed_flag = true;
      return;
    }

    for (size_t i = 0; i < actual.size(); i++) {
      if (std::abs(actual[i] - expected[i]) <= tolerance) {
        /* Do Nothing. */
      } else {
        std::cout << "FAILURE: " << message << " Element mismatch."
                  << std::endl;
        std::cout << std::endl;
        this->_test_failed_flag = true;
        return;
      }
    }
  }

  /**
   * @brief Checks if two std::array objects are element-wise near each other
   * within a given tolerance.
   *
   * This function compares each element of the input arrays `actual` and
   * `expected`. If the absolute difference between corresponding elements is
   * greater than the specified `tolerance`, the function prints a failure
   * message, sets the test failed flag, and returns early. Otherwise, it
   * continues checking all elements.
   *
   * @tparam N The size of the arrays to compare.
   * @param actual The array containing actual values.
   * @param expected The array containing expected values.
   * @param tolerance The maximum allowed difference between corresponding
   * elements.
   * @param message The message to display in case of a mismatch.
   */
  template <std::size_t N>
  void expect_near(const std::array<T, N> &actual,
                   const std::array<T, N> &expected, T tolerance,
                   const std::string &message) {
    for (std::size_t i = 0; i < N; ++i) {
      if (std::abs(actual[i] - expected[i]) <= tolerance) {
        /* Do Nothing. */
      } else {
        std::cout << "FAILURE: " << message << " Element mismatch."
                  << std::endl;
        std::cout << std::endl;
        this->_test_failed_flag = true;
        return;
      }
    }
  }

  /**
   * @brief Compares two 2D vectors element-wise and checks if all corresponding
   * elements are within a specified tolerance.
   *
   * This function iterates over the elements of the provided 2D vectors
   * `actual` and `expected`. If the sizes of the vectors or their sub-vectors
   * do not match, or if any corresponding elements differ by more than the
   * specified `tolerance`, the function prints a failure message, sets the
   * internal test failed flag, and returns early.
   *
   * @tparam T The numeric type of the elements in the vectors.
   * @param actual The actual 2D vector of values to be tested.
   * @param expected The expected 2D vector of values to compare against.
   * @param tolerance The maximum allowed difference between corresponding
   * elements.
   * @param message A custom message to display in case of failure.
   */
  void expect_near(const std::vector<std::vector<T>> actual,
                   const std::vector<std::vector<T>> expected, T tolerance,
                   const std::string &message) {
    if (actual.size() != expected.size()) {
      std::cout << "FAILURE: " << message << " Size mismatch." << std::endl;
      std::cout << std::endl;
      this->_test_failed_flag = true;
      return;
    }

    for (size_t i = 0; i < actual.size(); i++) {
      if (actual[i].size() != expected[i].size()) {
        std::cout << "FAILURE: " << message << " Size mismatch. " << std::endl;
        std::cout << std::endl;
        this->_test_failed_flag = true;
        return;
      }

      for (size_t j = 0; j < actual[i].size(); j++) {
        if (std::abs(actual[i][j] - expected[i][j]) <= tolerance) {
          /* Do Nothing. */
        } else {
          std::cout << "FAILURE: " << message << " Element mismatch."
                    << std::endl;
          std::cout << std::endl;
          this->_test_failed_flag = true;
          return;
        }
      }
    }
  }

  template <std::size_t M, std::size_t N>
  void expect_near(const std::array<std::array<T, N>, M> &actual,
                   const std::array<std::array<T, N>, M> &expected, T tolerance,
                   const std::string &message) {
    for (std::size_t i = 0; i < M; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        if (std::abs(actual[i][j] - expected[i][j]) <= tolerance) {
          /* Do Nothing. */
        } else {
          std::cout << "FAILURE: " << message << " Element mismatch."
                    << std::endl;
          std::cout << std::endl;
          this->_test_failed_flag = true;
          return;
        }
      }
    }
  }

  /**
   * @brief Throws a std::runtime_error if the test has failed.
   *
   * This method checks the internal _test_failed_flag. If the flag is set to
   * true, it throws a std::runtime_error with the message "Test failed.".
   *
   * @throws std::runtime_error if the test has failed.
   */
  void throw_error_if_test_failed() {
    if (this->_test_failed_flag) {
      throw std::runtime_error("Test failed.");
    }
  }

  /**
   * @brief Resets the test failed flag to indicate that no test failure has
   * occurred.
   *
   * This method sets the internal _test_failed_flag to false, clearing any
   * previous test failure state.
   */
  void reset_test_failed_flag() { this->_test_failed_flag = false; }

protected:
  bool _test_failed_flag = false;
};

} // namespace Tester

#endif // MCAP_TESTER_HPP
