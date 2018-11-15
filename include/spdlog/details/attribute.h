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

template <typename L>
class scoped_attribute
{
public:
    scoped_attribute(std::shared_ptr<L> logger, details::attribute&& attr) : logger_(std::move(logger))
    {
        logger_->push_attribute(std::move(attr));
    }

    ~scoped_attribute()
    {
        logger_->pop_attribute();
    }

private:
    std::shared_ptr<L> logger_;
};
} // namespace details
} // namespace spdlog
#endif // SPDLOG_SCOPED_ATTRIBUTES

#define CONCAT(x, y) x##y
#define CONCAT2(x, y) CONCAT(x, y)
#define ANONYMOUS_VAR(str) CONCAT2(str, __LINE__)
#define SCOPED_ATTRIBUTE_TO_LOGGER(...) \
    spdlog::details::scoped_attribute ANONYMOUS_VAR(_scoped_attribute)(__VA_ARGS__);
#define SCOPED_ATTRIBUTE(...) SCOPED_ATTRIBUTE_TO_LOGGER(spdlog::default_logger(), __VA_ARGS__)

