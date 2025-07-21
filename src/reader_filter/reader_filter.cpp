#include "reader_filter.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

std::vector<DataRow> CSVReader::readAll(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open file");

    std::string buffer((std::istreambuf_iterator<char>(file)), {});
    std::vector<DataRow> result; DataRow row; size_t start = 0, col = 0; bool skip = false, header = true;

    for (size_t i = 0; i <= buffer.size(); i++) {
        if (i == buffer.size() || buffer[i] == '\n' || buffer[i] == ';') {
            if (i > start) {
                if (col == 1) try { row.freq = std::stod(buffer.substr(start, i - start)); } catch(...) { skip = true; }
                else if (col == 2) row.time = buffer.substr(start, i - start);
            }
            if (buffer[i] == '\n') {
                if (!header && !skip && col > 1) result.push_back(row);
                row = DataRow(); col = 0; skip = false; header = false;
            }
            start = i + 1; col++;
        }
    }
    return result;
}

std::vector<DataRow> CSVReader::filterByFrequencyAndTime(
    const std::vector<DataRow>& data,
    double min_freq,
    double max_freq
    ) {
    std::vector<DataRow> filtered;

    std::time_t now = std::time(nullptr);
    std::tm utc_tm = *std::localtime(&now);
    int current_minutes = utc_tm.tm_hour * 60 + utc_tm.tm_min;

    for (const auto& row : data) {
        if (row.freq < min_freq || row.freq > max_freq)
            continue;

        const std::string& time_str = row.time;
        if (time_str == "0000-2400") {
            filtered.push_back(row);
            continue;
        }

        if (time_str.size() != 9 || time_str[4] != '-') {
            continue;
        }

        int start_h = std::stoi(time_str.substr(0,2));
        int start_m = std::stoi(time_str.substr(2,2));
        int end_h = std::stoi(time_str.substr(5,2));
        int end_m = std::stoi(time_str.substr(7,2));

        int start_minutes = start_h * 60 + start_m;
        int end_minutes = end_h * 60 + end_m;

        bool in_interval = false;
        if (start_minutes <= end_minutes) {
            in_interval = (start_minutes <= current_minutes && current_minutes <= end_minutes);
        } else {
            in_interval = (current_minutes >= start_minutes || current_minutes <= end_minutes);
        }

        if (in_interval) {
            filtered.push_back(row);
        }
    }

    return filtered;
}


