#pragma once

#include <array>
#include <cstdint>
#include <linux/perf_event.h>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace perf {
class CounterConfig
{
public:
  CounterConfig(const std::uint32_t type,
                const std::uint64_t event_id,
                const std::uint64_t event_id_extension_1 = 0U,
                const std::uint64_t event_id_extension_2 = 0U) noexcept
    : _type(type)
    , _event_id(event_id)
    , _event_id_extension({ event_id_extension_1, event_id_extension_2 })
  {
  }

  ~CounterConfig() noexcept = default;

  void precise_ip(const std::uint8_t precise_ip) noexcept { _precise_ip = precise_ip; }

  [[nodiscard]] std::uint32_t type() const noexcept { return _type; }
  [[nodiscard]] std::uint64_t event_id() const noexcept { return _event_id; }
  [[nodiscard]] std::array<std::uint64_t, 2U> event_id_extension() const noexcept { return _event_id_extension; }
  [[nodiscard]] std::uint8_t precise_ip() const noexcept { return _precise_ip; }

  [[nodiscard]] bool is_auxiliary() const noexcept { return _event_id == 0x8203; }

private:
  std::uint32_t _type;
  std::uint64_t _event_id;
  std::array<std::uint64_t, 2U> _event_id_extension;
  std::uint8_t _precise_ip{ 0U };
};

class CounterResult
{
public:
  using iterator = std::vector<std::pair<std::string_view, double>>::iterator;
  using const_iterator = std::vector<std::pair<std::string_view, double>>::const_iterator;

  CounterResult() = default;
  CounterResult(CounterResult&&) noexcept = default;
  CounterResult(const CounterResult&) = default;
  explicit CounterResult(std::vector<std::pair<std::string_view, double>>&& results) noexcept
    : _results(std::move(results))
  {
  }

  ~CounterResult() = default;

  CounterResult& operator=(CounterResult&&) noexcept = default;
  CounterResult& operator=(const CounterResult&) = default;

  /**
   * Access the result of the counter or metric with the given name.
   *
   * @param name Name of the counter or metric to access.
   * @return The value, or std::nullopt of the result has no counter or value with the requested name.
   */
  [[nodiscard]] std::optional<double> get(std::string_view name) const noexcept;

  [[nodiscard]] iterator begin() { return _results.begin(); }
  [[nodiscard]] iterator end() { return _results.end(); }
  [[nodiscard]] const_iterator begin() const { return _results.begin(); }
  [[nodiscard]] const_iterator end() const { return _results.end(); }

  /**
   * Converts the result to a json-formatted string.
   * @return Result in JSON format.
   */
  [[nodiscard]] std::string to_json() const;

  /**
   * Converts the result to a CSV-formatted string.
   *
   * @param delimiter Char to separate columns (',' by default).
   * @param print_header If true, the header will be printed first (true by default).
   * @return Result in CSV format.
   */
  // [[nodiscard]] std::string to_csv(char delimiter = ',', bool print_header = true) const;
  [[nodiscard]] std::string to_csv(char delimiter = ',', bool print_header = true, std::string additional = "") const;

  /**
   * Converts the result to a table-formatted string.
   * @return Result as a table-formatted string.
   */
  [[nodiscard]] std::string to_string() const;

private:
  std::vector<std::pair<std::string_view, double>> _results;
};

class Counter
{
public:
  explicit Counter(CounterConfig config) noexcept
    : _config(config)
  {
  }

  ~Counter() noexcept = default;

  [[nodiscard]] std::uint32_t type() const noexcept { return _config.type(); }
  [[nodiscard]] std::uint64_t event_id() const noexcept { return _config.event_id(); }
  [[nodiscard]] std::array<std::uint64_t, 2U> event_id_extension() const noexcept
  {
    return _config.event_id_extension();
  }
  void precise_ip(const std::uint8_t precision) { _config.precise_ip(precision); }
  [[nodiscard]] std::uint8_t precise_ip() const noexcept { return _config.precise_ip(); }

  [[nodiscard]] perf_event_attr& event_attribute() noexcept { return _event_attribute; }
  [[nodiscard]] std::uint64_t& id() noexcept { return _id; }
  [[nodiscard]] std::uint64_t id() const noexcept { return _id; }

  void file_descriptor(const std::int64_t file_descriptor) noexcept { _file_descriptor = file_descriptor; }
  [[nodiscard]] std::int64_t file_descriptor() const noexcept { return _file_descriptor; }
  [[nodiscard]] bool is_open() const noexcept { return _file_descriptor > -1; }

  [[nodiscard]] bool is_auxiliary() const noexcept { return _config.is_auxiliary(); }

  [[nodiscard]] std::string to_string() const;

private:
  CounterConfig _config;
  perf_event_attr _event_attribute{};
  std::uint64_t _id{ 0U };
  std::int64_t _file_descriptor{ -1 };

  /**
   * Prints a name of a type (e.g., sample, branch, ...) to the stream if the type is set in the mask.
   *
   * @param stream Stream to print the name of the type on.
   * @param mask Given mask to check if the type is set.
   * @param type Type to test in the mask.
   * @param name Name to print if the type is set.
   * @param is_first Flag if this is the first printed name. If false, a separator is printed in front of the name.
   * @return True, if this was the first printed type.
   */
  static bool print_type_to_stream(std::stringstream& stream,
                                   std::uint64_t mask,
                                   std::uint64_t type,
                                   std::string&& name,
                                   bool is_first);
};
}