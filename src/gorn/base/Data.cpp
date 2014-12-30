#include <gorn/base/Data.hpp>
#include <cstring>
#include <streambuf>

namespace gorn
{
   	Data::Data()
	{
    }

	Data::Data(size_t size)
	{
		_mem.resize(size);
	}

    Data::Data(std::istream& stream)
    {
        stream.seekg(0, stream.end);
        size_t size = stream.tellg();
        stream.seekg(0, stream.beg);
        _mem.resize(size);
        stream.read(reinterpret_cast<char*>(_mem.data()), size);
    }

	Data::Data(const uint8_t* data, size_t size):
	_mem(data, data+size)
	{
	}

	Data::Data(const std::vector<uint8_t>& data):
	_mem(data)
	{
	}

	Data::Data(std::vector<uint8_t>&& data):
	_mem(std::move(data))
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

    void Data::resize(size_t size)
    {
        _mem.resize(size);
    }

	uint8_t* Data::data()
	{
		return _mem.data();
	}

	const uint8_t* Data::data() const
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
		memcpy(s, _read_data.data()+_read, n);
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
