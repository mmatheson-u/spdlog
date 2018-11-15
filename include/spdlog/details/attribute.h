#pragma once

#ifdef SPDLOG_SCOPED_ATTRIBUTES
#include <string>
#include <variant>

namespace spdlog {
namespace details {
struct attribute
{
using attr_val = std::variant<bool, int64_t, uint64_t, double, std::string>;
using attr_key = std::string;

attr_key key;
attr_val value;
};
} // namespace details
} // namespace spdlog
#endif // SPDLOG_SCOPED_ATTRIBUTES
