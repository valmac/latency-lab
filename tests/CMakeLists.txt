# Latency lab regression tests
add_executable(tests ${OMI_DIR}/test/main.cpp
  analysis/percentiles.cpp
  analysis/statistics.cpp
  collection/calculate.cpp
  collection/percentile.cpp
  match/timestamps.cpp
  types/period.cpp
  types/sequence.cpp
  types/timestamp.cpp)
target_link_libraries(tests ${Boost_LIBRARIES})
add_test(NAME tests COMMAND tests)
