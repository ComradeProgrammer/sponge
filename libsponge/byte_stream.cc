#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`
template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t _capacity) : capacity(_capacity), buffer() {
    // DUMMY_CODE(capacity);
}

ByteStream::~ByteStream() {}

size_t ByteStream::write(const string &data) {
    // DUMMY_CODE(data);
    // return {};
    if (capacity <= buffer.size()) {
        return 0;
    }
    size_t limit = capacity - buffer.size();
    size_t accept = 0;
    for (; accept < limit && accept < data.size(); accept++) {
        buffer.push_back(data[accept]);
        writeCount++;
    }
    return accept;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    // DUMMY_CODE(len);
    // return {};
    stringstream ss;
    size_t i = 0;
    for (auto itr = buffer.begin(); itr != buffer.end(); itr++) {
        if (i >= len) {
            break;
        }
        ss << *itr;
    }
    return ss.str();
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (buffer.size() == 0) {
            break;
        }
        buffer.pop_front();
        readCount++;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    // DUMMY_CODE(len);
    // return {};
    stringstream ss;
    for (size_t i = 0; i < len; i++) {
        if (buffer.size() == 0) {
            break;
        }
        char c = buffer.front();
        buffer.pop_front();
        ss << c;
        readCount++;
    }
    return ss.str();
}

void ByteStream::end_input() { stop = true; }

bool ByteStream::input_ended() const { return stop; }

size_t ByteStream::buffer_size() const { return buffer.size(); }

bool ByteStream::buffer_empty() const { return buffer.empty(); }

bool ByteStream::eof() const {
    if (buffer.size() == 0 && stop) {
        return true;
    }
    return false;
}

size_t ByteStream::bytes_written() const { return writeCount; }

size_t ByteStream::bytes_read() const { return readCount; }

size_t ByteStream::remaining_capacity() const { return capacity - buffer.size(); }
