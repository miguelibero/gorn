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

	Data::Data(const Data& other):
	_mem(other._mem)
	{
	}

	Data::Data(Data&& other):
	_mem(std::move(other._mem))
	{
	}

	uint8_t* Data::ptr()
	{
		return _mem.data();
	}

	const uint8_t* Data::ptr() const
	{
		return _mem.data();
	}

	size_t Data::size() const
	{
		return _mem.size();
	}

    DataInputStream::DataInputStream(const Data& data):
    _read_data(data), _read(0)
    {
    }

	size_t DataInputStream::read(uint8_t* s, size_t n)
	{
		if(_read+n > _read_data.size())
		{
			n = _read_data.size()-_read;
		}
		memcpy(s, _read_data.ptr()+_read, n);
		_read += n;
		return n;
	}

	size_t DataInputStream::read(DataOutputStream& s, size_t n)
	{
		if(_read+n > _read_data.size())
		{
			n = _read_data.size()-_read;
		}
		s._write_data._mem.insert(s._write_data._mem.begin()+s._write,
			_read_data._mem.begin()+_read,
            _read_data._mem.begin()+_read+n);
		_read += n;
		s._write += n;
		return n;
	}

	size_t DataInputStream::read(Data& s, size_t n)
	{
    	if(_read+n > _read_data.size())
		{
			n = _read_data.size()-_read;
		}
        s._mem.insert(s._mem.end(),
            _read_data._mem.begin()+_read,
            _read_data._mem.begin()+_read+n);
		_read += n;
        return n;
    }

    DataOutputStream::DataOutputStream(Data& data) :
    _write_data(data), _write(0)
    {
    }

	size_t DataOutputStream::write(const uint8_t* s, size_t n)
	{
		_write_data._mem.insert(
            _write_data._mem.begin()+_write, s, s+n);
		_write += n;
		return n;
	}

	size_t DataOutputStream::write(const Data& s, size_t n)
	{
        if(n>s.size())
        {
            n = s.size();
        }
   		_write_data._mem.insert(_write_data._mem.begin()+_write,
            s._mem.begin(), s._mem.begin()+n);
		_write += n;
		return n;
	}

	size_t DataOutputStream::write(DataInputStream& s, size_t n)
	{
		s.read(*this, n);
		return n;
	}
}
