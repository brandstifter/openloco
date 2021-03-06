//
// Created by Thomas Brandstätter on 12/05/2018.
//

#include <driver/file.h>

#include <cassert>
#include <fstream>

namespace openloco {
namespace lang {


    void File::open(std::string& filename)
    {
        std::ifstream in(filename);
        return open(in);
    }

    void File::open(std::istream& in)
    {
        std::string line;
        while (std::getline(in, line))
            _lines.push_back(line);
    }

    void File::reset()
    {
        _lines.clear();
    }

    const std::string File::get_line(unsigned long number) const
    {
        assert (number <= _lines.size());       // error in users logic
        return _lines[number - 1];
    }

    FileStreambuffer::int_type FileStreambuffer::underflow()
    {
        if (gptr() < egptr())   // buffer not exhausted
            return traits_type::to_int_type(*gptr());

        if (_current_line >= _infile._lines.size())
            return traits_type::eof();

        std::string& line { _infile._lines[_current_line] };
        line.push_back('\n');

        char *base = &line.front();
        setg(base, base, base + line.length());

        _current_line++;
        return traits_type::to_int_type(*gptr());
    }
}}
