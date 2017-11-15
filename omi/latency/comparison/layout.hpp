#ifndef OMI_LATENCY_COMPARISON_LAYOUT_HPP_
#define OMI_LATENCY_COMPARISON_LAYOUT_HPP_

#include <omi/source/write.hpp>
#include <omi/latency/comparison/configuration.hpp>
#include <omi/latency/comparison/charts.hpp>
#include <omi/latency/comparison/buttons.hpp>
#include <omi/latency/comparison/summary.hpp>
#include <omi/latency/comparison/pages.hpp>

// Generate multi-run latency comparison html report

namespace omi { 
namespace latency {
namespace comparison {

struct layout {

  //// Member Variables ///////////

    comparison::configuration options;
    match::runs runs;

  //// Methods ////////////////////

    // Write html report to path
    void write(const std::string &path) const {
        source::write(*this, path);
    }
};


// Stream operator (composes html report from layout and data) 
inline std::ostream &operator<<(std::ostream &out, const layout &report) {
    return out << html::doctype{"html"}
               << html::tag{"html"}
               << std::endl
               << html::tag{"head"}
               << html::link{"stylesheet", "text/css", report.options.css}
               << html::src{"omi.js"}
               <<   html::meta{"charset", "utf-8" }
               <<   html::title{report.options.title}
               <<   comparison::charts{report.runs} 
               << html::close{"head"}
               << html::tag{"body"}
               << html::tag{"header"}
               << html::h3{report.options.header}
               << html::close{"header"}
               << std::endl
               <<   comparison::buttons{report.runs}
               <<   comparison::summary{report.options, report.runs}
               <<   comparison::pages{report.runs}
               << html::tag{"script"}
               <<   "document.getElementById(\"defaultOpen\").click();" << std::endl
               << html::close{"script"}
               << html::close{"body"}
               << html::tag{"footer"}
               <<   html::p{"&copy; " + report.options.copyright, indent::two}
               << html::close{"footer"}
               << html::close{"html"};
}

} } }

#endif