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

  void throw_error_if_test_failed() {
    if (this->_test_failed_flag) {
      throw std::runtime_error("Test failed.");
    }
  }

  void reset_test_failed_flag() { this->_test_failed_flag = false; }

protected:
  bool _test_failed_flag = false;
};

} // namespace Tester

#endif // MCAP_TESTER_HPP
