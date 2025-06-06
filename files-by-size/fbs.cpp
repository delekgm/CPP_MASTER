#include <iostream>
#include <filesystem>
#include <map>
#include <string>

namespace fs = std::filesystem;

// Helper function to format sizes
std::string format_size(uintmax_t size, bool human_readable) {
    if(!human_readable) return std::to_string(size) + "bytes";

    constexpr uintmax_t KB = 1024;
    constexpr uintmax_t MB = KB * 1024;
    constexpr uintmax_t GB = MB * 1024;

    if(size >= GB) {
        return std::to_string(size / GB) + " GB";
    } else if (size >= MB) {
        return std::to_string(size / MB) + " MB";
    } else if (size >= KB) {
        return std::to_string(size / KB) + " KB";
    } else {
        return std::to_string(size) + " bytes";
    }
 }

 // Template function to process files using any iterator type
template <typename DirectoryIterator>
void process_files(const fs::path& folder_path, std::map<std::string, uintmax_t>& file_sizes, bool include_hidden) {
    size_t file_count = 0;
    size_t processed_count = 0;

    // First, count total files
    for (const auto& entry : DirectoryIterator(folder_path)) {
        if (fs::is_regular_file(entry.path())) {
            ++file_count;
        }
    }

    // Process files and show progress
    for (const auto& entry : DirectoryIterator(folder_path)) {
        try {
            // Skip symbolic links to avoid infinite recursion
            if(fs::is_symlink(entry.path())) {
                std::cout << "Skipping symbolic link: " << entry.path() << std::endl;
                continue;
            }

            if (fs::is_regular_file(entry.path())) {
                std::string filename = entry.path().filename().string();

                // Skip hidden files unless --include-hidden is set
                if (!include_hidden && !filename.empty() && filename[0] == '.') {
                    continue;
                }

                std::string extension = entry.path().extension().string();
                uintmax_t file_size = fs::file_size(entry.path());
                file_sizes[extension] += file_size;
                ++processed_count;

                // Show progress every 10 files
                if (processed_count % 10 == 0 || processed_count == file_count) {
                    std::cout << "Processed " << processed_count << " of " << file_count << " files..." << std::endl;
                }

            }

        } catch (const std::exception& e) {
            std::cerr << "Error processing: " << entry.path() << " - " << e.what() << std::endl;
            continue;
        }
    }
}

// Function to parse arguments
std::tuple<std::filesystem::path, bool, bool, bool> parse_arguments(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("Usage: folder_scanner <folder_path> [--recursive] [--human-readable] [--include-hidden]");
    }

    std::filesystem::path folder_path = argv[1];
    bool recursive = false;
    bool human_readable = false;
    bool include_hidden = false;

    // Parse optional arguments
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--recursive") {
            recursive = true;
        } else if (arg == "--human-readable") {
            human_readable = true;
        } else if (arg == "--include-hidden") {
            include_hidden = true;
        } else {
            throw std::invalid_argument("Unknown argument: " + arg);
        }
    }

    return {folder_path, recursive, human_readable, include_hidden};
}

int main(int argc, char* argv[])
{
    try {
        auto [folder_path, recursive, human_readable, include_hidden] = parse_arguments(argc, argv);

        if (!fs::exists(folder_path) || !fs::is_directory(folder_path))
        {
            std::cerr << "Error: Invalid folder path." << std::endl;
            return 1;
        }

        // Map to store total sizes for each file type
        std::map<std::string, uintmax_t> file_sizes;

        // Use the appropriate iterator
        if (recursive) {
            process_files<fs::recursive_directory_iterator>(folder_path, file_sizes, include_hidden);
        } else {
            process_files<fs::directory_iterator>(folder_path, file_sizes, include_hidden);
        }

        // Print results
        std::cout << "File type sizes in folder: " << folder_path << std::endl;
        for(const auto &[extension, total_size] : file_sizes) {
            std::cout << (extension.empty() ? "[no extension]" : extension) << ": " << format_size(total_size, human_readable) << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// #include <iostream>
// #include <fstream>
// #include <thread>
// #include <chrono>

// int main() {
//     std::ofstream file("output.txt");
//     std::cout << "Hello\n"; // Buffered; won't immediately appear in output.txt
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     std::cout << "After sleep";
//     file.flush();    // Now "Hello" is written to output.txt
//     return 0;
// }

    // std::cout << "Files in folder: " << folder_path << std::endl;

    // for (const auto& entry : fs::directory_iterator(folder_path)) 
    // {
    //     if (fs::is_regular_file(entry.path())) {
    //         std::cout << entry.path().filename() << std::endl;
    //     }
    // }