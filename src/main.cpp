#include "reader_filter/reader_filter.h"
#include <iostream>

int main() {
    CSVReader reader;

    auto all_data = reader.readAll("../../sked-a25.csv");

    std::cout << "Total rows read: " << all_data.size() << std::endl;

    for (const auto& row : all_data) {
        std::cout << "Raw: freq=" << row.freq << ", time=" << row.time << std::endl;
    }

    auto filtered_data = reader.filterByFrequencyAndTime(all_data, 100.0, 500.0);

    for (const auto& row : filtered_data) {
        std::cout << "Filtered: Frequency: " << row.freq
                  << " Hz, Time: " << row.time << std::endl;
    }

    return 0;
}

