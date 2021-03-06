#ifndef OMI_LATENCY_ANALYSIS_OPTIONS_HPP_
#define OMI_LATENCY_ANALYSIS_OPTIONS_HPP_

#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/options_description.hpp>

#include <omi/program/options.hpp>
#include <omi/latency/args.hpp>
#include <omi/match/inputs.hpp>
#include <omi/utility/autotimer.hpp>

//  Options for omi latency analysis

namespace omi::latency::analysis {

struct options {

  //// Member Variables ///////////

    match::inputs files;           // Event input files
    std::string path;              // Matches list output path
    omi::period period;            // Delta time period
    bool verbose;                  // Print status to standard out
    autotimer timer;               // Program time

  //// Construction //////////////

    // Construct options from args or ini file
    template<class setting>
    explicit options(const setting &option, bool verbose) : verbose{ verbose } {
        files.inbound = option.template required<std::string>(::inbound::file::option);
        files.outbound = option.template required<std::string>(::outbound::file::option);
        period = parse::period(option.template conditional<std::string>(::delta::period::option, "microseconds"));
    }

  //// Interface ////////////////

    // Parse program args into options
    static options parse(int argc, char *argv[], const char *title = "Analysis Program Options") {
        // Declare options
        boost::program_options::options_description description(title);
        description.add_options()
            (::inbound::file::option, boost::program_options::value<std::string>(), ::inbound::file::note)
            (::outbound::file::option, boost::program_options::value<std::string>(), ::outbound::file::note)
            (::delta::period::option, boost::program_options::value<std::string>(), ::delta::period::note);

        // Read program args
        auto args = omi::program::options(argc, argv, description);
        return options{ args, args.verbose() };
    }
};

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const options &program) {
    return out << program.timer;
}

}

#endif