#ifndef OMI_MATCH_EVENTS_HPP_
#define OMI_MATCH_EVENTS_HPP_

#include <omi/match/paths.hpp>
#include <omi/event/dictionary.hpp>
#include <omi/event/list.hpp>
#include <omi/event/matches.hpp>

// Match inbound and outbound events

namespace omi::match {

template <typename inbound, typename outbound>
struct events {
    // Verify record id compatibility
    static_assert(event::is_matchable<inbound, outbound>, "Inbound and outbound event record must use the same id() type");

  //// Member Variables ///////////

    event::matches<inbound, outbound> matched; // Matched events
    std::vector<outbound> misses;              // Unmatched responses

  //// Construction ///////////////

    // Construct from 2 file paths (make these static, and move out of class?)
    explicit events(const std::string &inbounds, const std::string &outbounds)
      : events{ event::dictionary<inbound>::read(inbounds), event::list<outbound>::read(outbounds) } {}

    // Construct from event inputs
    explicit events(const match::paths &path)
      : events{ path.inbound.string(), path.outbound.string() } {}

    // Construct from events
    explicit events(const event::dictionary<inbound> &inbounds, const event::list<outbound> &outbounds) {
        for (const auto &response : outbounds.valids) {
            const auto trigger = inbounds.events.find(response.id());
            if (trigger != inbounds.events.end()) {
                matched.push_back(event::match<inbound, outbound>(trigger->second, response));
            } else {
                misses.push_back(response);
            }
        }
    }
};

// Stream operator
template <class inbound, class outbound>
std::ostream &operator<<(std::ostream &out, const events<inbound, outbound> &events) {
    return out << "  Matched: " << events.matched.size() << std::endl
               << "  Unmatched: " << events.misses.size() << std::endl;
}

}

#endif