#include <iostream>
#include <chrono>
#include <iomanip>

// Structure to hold progress tracking information
struct ProgressTracker {
    uint64_t bytesProcessed = 0;
    uint64_t totalBytes = 0;
    uint64_t bufferSize = 4096; // Buffer size for reading/writing
    std::chrono::steady_clock::time_point lastUpdateTime;
    uint64_t lastUpdateBytes = 0;
};

// Function to update progress display
void updateProgress(const ProgressTracker& tracker) {
    // Calculate elapsed time since last update
    auto now = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - tracker.lastUpdateTime);
    
    if (elapsedTime.count() > 100) { // Update at least every 100ms
        float progress = (tracker.bytesProcessed / static_cast<float>(tracker.totalBytes)) * 100.0f;
        
        // Calculate transfer speed
        uint64_t bytesSinceLast = tracker.bytesProcessed - tracker.lastUpdateBytes;
        float speed = (bytesSinceLast / 1024.0f) / (elapsedTime.count() / 1000.0f);
        
        // Calculate estimated time remaining
        float remainingTime = (tracker.totalBytes - tracker.bytesProcessed) / (bytesSinceLast / elapsedTime.count());
        
        // Display progress
        std::cout << "\rProgress: " 
                  << std::fixed << std::setprecision(2) 
                  << progress << "% "
                  << "[" << (bytesSinceLast / 1024.0f / (elapsedTime.count() / 1000.0f)) << " KB/s] "
                  << "[" << (remainingTime / 1000.0f) << " seconds remaining]";
        
        // Update last update time and bytes
        tracker.lastUpdateTime = now;
        tracker.lastUpdateBytes = tracker.bytesProcessed;
    }
}

// Function to read file with progress tracking
bool readFileWithProgress(const std::string& filePath, std::vector<uint8_t>& buffer, ProgressTracker& tracker) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filePath << std::endl;
        return false;
    }

    // Get total size of the file
    tracker.totalBytes = file.tellg();
    file.seekg(0); // Reset to beginning of file

    // Allocate buffer if not already allocated
    if (buffer.size() < tracker.bufferSize) {
        buffer.resize(tracker.bufferSize);
    }

    uint64_t bytesRead = 0;
    while (bytesRead < tracker.totalBytes) {
        // Read chunk of data
        file.read(reinterpret_cast<char*>(buffer.data()), tracker.bufferSize);
        uint64_t bytesThisRead = file.gcount();
        
        // Update progress
        bytesRead += bytesThisRead;
        tracker.bytesProcessed = bytesRead;
        updateProgress(tracker);
        
        if (bytesThisRead == 0) {
            break; // EOF reached
        }
    }

    file.close();
    return true;
}

// Function to write file with progress tracking
bool writeFileWithProgress(const std::string& filePath, const std::vector<uint8_t>& buffer, ProgressTracker& tracker) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return false;
    }

    // Set total bytes to track (assuming buffer contains all data)
    tracker.totalBytes = buffer.size();
    tracker.bytesProcessed = 0;

    uint64_t bytesWritten = 0;
    size_t offset = 0;
    
    while (bytesWritten < tracker.totalBytes) {
        // Write chunk of data
        file.write(reinterpret_cast<const char*>(buffer.data() + offset), tracker.bufferSize);
        uint64_t bytesThisWrite = file.tellp() - bytesWritten;
        
        // Update progress
        bytesWritten += bytesThisWrite;
        tracker.bytesProcessed = bytesWritten;
        offset += bytesThisWrite;
        updateProgress(tracker);
    }

    file.close();
    return true;
}

// Function to calculate checksum for data integrity verification
uint64_t calculateChecksum(const std::vector<uint8_t>& data) {
    uint64_t checksum = 0;
    for (uint8_t byte : data) {
        checksum += byte;
    }
    return checksum;
}
