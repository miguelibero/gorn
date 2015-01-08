#include <gorn/base/Data.hpp>
#include <gorn/base/Exception.hpp>
#include <cstring>

namespace gorn
{
   	Data::Data()
	{
    }

	Data::Data(size_t size)
	{
		_mem.resize(size);
	}

    Data Data::readFile(const std::string& path)
    {
	    FILE *fh = nullptr;
#ifdef GORN_PLATFORM_WINDOWS
		if(fopen_s(&fh, path.c_str(), "rb") != 0)
		{
			fh = nullptr;
		}
#else
        fh = fopen(path.c_str(), "rb");
#endif
		if (fh == nullptr)
        { 
            throw Exception("Could not open file.");
        } 
        fseek(fh, 0, SEEK_END);
        size_t size = ftell(fh);
        fseek(fh, 0, SEEK_SET);
        Data data(size);
        if (size != fread(data._mem.data(), 1, size, fh)) 
        { 
            fclose(fh);
            throw Exception("Could not read file.");
        } 
        fclose(fh);
        return data;
    }

	Data::Data(const void* data, size_t size):
	_mem(reinterpret_cast<const uint8_t*>(data),
        reinterpret_cast<const uint8_t*>(data)+size)
	{
	}

    Data::Data(const std::string& data):
	_mem(data.begin(), data.end())
    {
    }

	Data::Data(const Data& other):
	_mem(other._mem)
	{
	}

	Data::Data(Data&& other):
	_mem(std::move(other._mem))
	{
	}

    Data& Data::operator=(Data&& other)
    {
        _mem = std::move(other._mem);
        return *this;
    }

    Data& Data::operator=(const Data& other)
    {
        _mem = other._mem;
        return *this;
    }

	uint8_t* Data::ptr()
	{
		return _mem.data();
	}

	const uint8_t* Data::ptr() const
	{
		return _mem.data();
	}

    std::vector<uint8_t>& Data::mem()
    {
        return _mem;
    }

    const std::vector<uint8_t>& Data::mem() const
    {
        return _mem;
    }

	size_t Data::size() const
	{
		return _mem.size();
	}

    bool Data::empty() const
    {
        return _mem.empty();
    }

    DataInputStream::DataInputStream(const Data& data):
    _data(data), _read(0)
    {
    }

	size_t DataInputStream::read(uint8_t* s, size_t n)
	{
		if(_read+n > _data.size())
		{
			n = _data.size()-_read;
		}
		memcpy(s, _data.ptr()+_read, n);
		_read += n;
		return n;
	}

	size_t DataInputStream::read(DataOutputStream& s, size_t n)
	{
		if(_read+n > _data.size())
		{
			n = _data.size()-_read;
		}
        s.write(_data.ptr()+_read, n);
		_read += n;
		return n;
	}

	size_t DataInputStream::read(Data& s, size_t n)
	{
    	if(_read+n > _data.size())
		{
			n = _data.size()-_read;
		}
        for(size_t i=0; i<n; ++i)
        {
            s._mem[i] = _data._mem[_read+i];
        }
		_read += n;
        return n;
    }

    size_t DataInputStream::read(std::string& line, char end)
    {
        size_t n = 0;
        char chr;
        while(_read+n < _data.size())
        {
            chr = _data._mem.at(_read+n);
            if(chr == end)
            {
                break;
            }
            line += chr;
            n++;
        }
		_read += n;
        return n;
    }

    bool DataInputStream::reachedEnd() const
    {
        return _read >= _data.size();
    }

    DataOutputStream::DataOutputStream(Data& data) :
    _data(data), _write(0)
    {
    }

    bool DataOutputStream::fit(size_t n)
    {
        if(_data.size() >= _write+n)
        {
            return false;
        }
        _data._mem.resize(_write+n);
        return true;
    }

    size_t DataOutputStream::write(size_t n)
    {
        fit(n);
        for(size_t i=0; i<n; ++i)
        {
            _data._mem[_write+i] = 0;
        }
        _write += n;
        return n;
    }

	size_t DataOutputStream::write(const uint8_t* s, size_t n)
	{
        fit(n);
        for(size_t i=0; i<n; ++i)
        {
            _data._mem[_write+i] = s[i];
        }
		_write += n;
		return n;
	}

	size_t DataOutputStream::write(const Data& s, size_t n, size_t start)
	{
        if(start>=s.size())
        {
            n = 0;
        }
        else if(start+n>s.size())
        {
            n = s.size()-start;
        }
        fit(n);
        for(size_t i=0; i<n; ++i)
        {
            _data._mem[_write+i] = s._mem[start+i];
        }
		_write += n;
		return n;
	}

	size_t DataOutputStream::write(DataInputStream& s, size_t n)
	{
        fit(n);
		s.read(*this, n);
		return n;
	}

    size_t DataOutputStream::write(const std::string& s)
	{
        return write(reinterpret_cast<const uint8_t*>(s.c_str()),
            s.length()*sizeof(std::string::value_type)/sizeof(uint8_t));
	}
}
