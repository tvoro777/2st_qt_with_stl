#pragma once

#include <vector>
#include <string>
#include <ctime>

struct DataRow {
    double freq;
    std::string time;
    std::string raw_line;
};

class CSVReader {
public:
    std::vector<DataRow> readAll(const std::string& file_path);

    std::vector<DataRow> filterByFrequencyAndTime(
        const std::vector<DataRow>& data,
        double min_freq,
        double max_freq
        );
};

