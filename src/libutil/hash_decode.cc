#include "nix/util/hash_decode.hh"
#include "nix/util/logging.hh"

namespace nix::hash_decode {

bool Result::bad_parse_finished_at(const std::string_view& s) {
    return parse_finished_at < s.size();
}

bool Result::bad_trailing() {
    return trailing.data != 0;
}

bool Result::bad_padding() {
    return padding != MissingPadding::Correct;
}

std::string Result::warn_if_bad(const std::string_view& s) {
    if (bad_parse_finished_at(s)) {
        warn("Hash '%s' has extraneous data after: '%s'", s.substr(0, parse_finished_at), s.substr(parse_finished_at));
    } else if (bad_padding()) {
        warn("Hash '%s' is missing '=' padding");
    } else if (bad_trailing()) {
        warn("Hash '%s' has non-zero padding bits");
    }
    return hash_bytes;
}

} // namespace nix::hash_decode
