#pragma once

#include <string>
#include <cstdint>

namespace nix::hash_decode {

/**
 * @brief The extra bits decoded, for formats like base64 where encoded-characters-per-byte is not an integer
 * for base16, always bit_count=0 and data=0
 */
struct TrailingBits {
    uint8_t bit_count = 0;
    uint8_t data = 0;
};

/**
 * @brief How many padding characters (base64 '=') are missing. Always MissingPadding::Correct for other formats
 */
enum struct MissingPadding : uint8_t {
    Correct = 0,
    OneMore = 1,
    TwoMore = 2,
};

/**
 * @brief the result of decoding a HashFormat to bytes. The main result is in hash_bytes, and the rest indicates bad input data
 */
struct Result {
    std::string hash_bytes;
    // if parse_finished_at == s.size(), then all is well
    size_t parse_finished_at;
    TrailingBits trailing = TrailingBits();
    MissingPadding padding = MissingPadding::Correct;

    bool bad_parse_finished_at(const std::string_view& s);

    bool bad_trailing();

    bool bad_padding();

    std::string warn_if_bad(const std::string_view& s);
};

} // namespace nix::hash_decode


