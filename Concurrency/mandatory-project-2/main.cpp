#include "concur2018.h"
#include <iostream>
#include <thread>
#include <mutex>

// Multiple threads are writing to cout/cerr at the same time -> Unclear output.
// Solution: Handle all logging via functions where logging to cout and cerr are synchronized.
// This does not affect processing speed of files, since worker threads print only when they are done with processing (success or fail).
std::mutex log_mutex;

void cout_log(std::string text) {
    log_mutex.lock();

    std::cout << text << std::endl;

    log_mutex.unlock();
}

void cerr_log(std::string text) {
    log_mutex.lock();

    std::cerr << text << std::endl;

    log_mutex.unlock();
}

char getFirstLetter(const std::string& filename) {
    // Find path separator in filename ( / or \)
    auto unix_pos = filename.find_last_of("/");
    auto win_pos = filename.find_last_of("\\");

    // No windows or unix path separators present - return first character of parameter string
    if( unix_pos == std::string::npos && win_pos == std::string::npos ) {
        return filename[0];
    }

    // Use whichever separator is not npos
    auto lastSeparatorPos = unix_pos != std::string::npos ? unix_pos : win_pos;

    // Substring from last path separators position and return substring's first character
    return filename.substr(lastSeparatorPos + 1)[0];
}

void convertFile(std::string filename, const std::vector<std::mutex*> mutexes) {
    // Select operation based on the first letter of filename.

    bool result = false;
    // select fileoperation based on the first letter of filename:
    char firstletter = getFirstLetter(filename);
    switch( firstletter ) {
    case 'C':
    {
        std::mutex* op_mutex = mutexes[concur2018::Copyright];
        op_mutex -> lock();
        try {
            result = concur2018::ProcessFile( filename, concur2018::Copyright );
        } catch(std::exception ex) {
            cerr_log("Exception while processing file " + filename);
        }
        op_mutex -> unlock();
        break;
    }
    case 'R':
    {
        std::mutex* op_mutex = mutexes[concur2018::Rotate];
        op_mutex -> lock();
        try {
            result = concur2018::ProcessFile( filename, concur2018::Rotate );
        } catch(std::exception ex) {
            cerr_log("Exception while processing file " + filename);
        }
        op_mutex -> unlock();
        break;
    }
    case 'B':
    {
        std::mutex* op_mutex = mutexes[concur2018::Border];
        op_mutex -> lock();
        try {
            result = concur2018::ProcessFile( filename, concur2018::Border );
        } catch(std::exception ex) {
            cerr_log("Exception while processing file " + filename);
        }
        op_mutex -> unlock();
        break;
    }
    case 'G':
    {
        std::mutex* op_mutex = mutexes[concur2018::Grayscale];
        op_mutex -> lock();
        try {
            result = concur2018::ProcessFile( filename, concur2018::Grayscale );
        } catch(std::exception ex) {
            cerr_log("Exception while processing file " + filename);
        }
        op_mutex -> unlock();
        break;
    }
    case 'U':
    {
        std::mutex* op_mutex = mutexes[concur2018::Unfocus];
        op_mutex -> lock();
        try {
            result = concur2018::ProcessFile( filename, concur2018::Unfocus );
        } catch(std::exception ex) {
            cerr_log("Exception while processing file " + filename);
        }
        op_mutex -> unlock();
        break;
    }
    default:
        cerr_log("Cannot process file starting with letter: " + firstletter);
        break;
    } // switch
    cout_log("Processing finished for file: " + filename + ", success: " + ( result ? "true" : "false") );
}

void processDirectory( std::string location ) {
    std::vector<std::mutex*> mutexes;

    // Mutex lock for each operation
    // Mutexes are pointers because they are passed as arguments to every worker thread.
    for(int op = concur2018::Copyright ; op <= concur2018::Unfocus; op++) {
        mutexes.push_back( new std::mutex() );
    }

    // Vector of used threads
    std::vector<std::thread> threads;

    // At this point only main thread is running so it's ok to just print to cout instead of using the synchronized log function
    std::cout << "\n" << "Starting conversion of " << location << std::endl;

    // library provides us filelist:
    concur2018::FileList files = concur2018::GetFiles( location );

    // API DOC: Thread safe with multiple files.
    // Not documented/unsure: Same operation for 2 or more files at the same time might not be threadsafe.
    // Solution: Start one thread per file, pass filename and a list of shared mutexes to each thread.
    // Shared mutexes make sure that one operation is executed only to a single file at any time.
    for( auto filename : files ) {
        threads.push_back(std::thread(convertFile, filename, mutexes));
    }

    // Wait for threads to finish working
    for( auto& thread : threads) {
        thread.join();
    }
    threads.clear();

    // delete mutexes
    for(auto* mutex : mutexes) {
        delete mutex;
    }
    mutexes.clear();

    // At this point only main thread is running so it's ok to just print to cout instead of using the synchronized log function
    std::cout << "\n" << "Ending conversion of " << location << std::endl;
}

int main()
{
    std::cerr << "\n" << "main() starting." << std::endl;

    processDirectory("inputs");

    std::cerr << "\n" << "main() ending." << std::endl;
}
