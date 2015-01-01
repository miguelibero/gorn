#ifndef __gorn__Data__
#define __gorn__Data__

#include <vector>
#include <memory>
#include <initializer_list>


namespace gorn
{
	class Data
	{
	private:
		std::vector<uint8_t> _mem;

	public:
		Data();
		Data(size_t size);
		Data(const void* data, size_t size);
		Data(const Data& other);
		Data(Data&& other);
        
        template<typename T>
        Data(std::initializer_list<T> list);

        template<typename T>
		Data(const std::vector<T>& data);

        template<typename T>
		Data(std::vector<T>&& data);


		uint8_t* data();
		const uint8_t* data() const;
		size_t size() const;

        static Data readFile(const std::string& path);

        friend class DataInputStream;
        friend class DataOutputStream;
	};

    template<typename T>
    Data::Data(std::initializer_list<T> list):
    _mem(reinterpret_cast<const uint8_t*>(list.begin()),
        reinterpret_cast<const uint8_t*>(list.end()))
    {
    }

    template<typename T>
	Data::Data(const std::vector<T>& data):
	_mem(reinterpret_cast<const uint8_t*>(&data.front()),
        reinterpret_cast<const uint8_t*>(&data.back()))
	{
	}

    class DataOutputStream;

    class DataInputStream
    {
	protected:
		const Data& _read_data;
		size_t _read;
	public:
		DataInputStream(const Data& data);

		size_t read(uint8_t* s, size_t n);
		size_t read(DataOutputStream& s, size_t n);
		size_t read(Data& s, size_t n);

        friend class DataStream;
    };

    class DataOutputStream
    {
    protected:
		Data& _write_data;
		mutable size_t _write;
	public:
		DataOutputStream(Data& data);

		size_t write(const uint8_t* s, size_t n);
		size_t write(const Data& s, size_t n);
		size_t write(DataInputStream& s, size_t n);

        friend class DataInputStream;
    };
}

#endif
