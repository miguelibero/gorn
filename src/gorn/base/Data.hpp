#ifndef __gorn__Data__
#define __gorn__Data__

#include <vector>
#include <memory>
#include <string>
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
        Data(const std::string& data);
		Data(const Data& other);
		Data(Data&& other);
        
        template<typename T>
        Data(std::initializer_list<T> list);

        template<typename T>
		Data(const std::vector<T>& vec);

		Data(std::vector<uint8_t>&& vec);

        Data& operator=(Data&& other);
        Data& operator=(const Data& other);

		uint8_t* ptr();
		const uint8_t* ptr() const;
        std::vector<uint8_t>& mem();
        const std::vector<uint8_t>& mem() const;
		size_t size() const;
        bool empty() const;

        bool isBinary() const;

        static Data readFile(const std::string& path);

        friend class DataInputStream;
        friend class DataOutputStream;
	};

    template<typename T>
    Data::Data(std::initializer_list<T> list)
    {
        if(list.size() > 0)
        {
            _mem = std::vector<uint8_t>(
                reinterpret_cast<const uint8_t*>(list.begin()),
                reinterpret_cast<const uint8_t*>(list.end())
            );
        }
    }

    template<typename T>
	Data::Data(const std::vector<T>& vec)
	{
        if(!vec.empty())
        {
            _mem = std::vector<uint8_t>(
                reinterpret_cast<const uint8_t*>(vec.data()),
                reinterpret_cast<const uint8_t*>(vec.data()+vec.size())
            );
        }
	}

    class DataOutputStream;

    class DataInputStream
    {
	protected:
		const Data& _data;
		size_t _read;
	public:
		DataInputStream(const Data& data);

		size_t read(uint8_t* s, size_t n);
		size_t read(DataOutputStream& s, size_t n);
		size_t read(Data& s, size_t n);
        size_t read(std::string& s, char end='\n');
        bool reachedEnd() const;
    };

    class DataOutputStream
    {
    protected:
		Data& _data;
		mutable size_t _write;

        bool fit(size_t n);
	public:
		DataOutputStream(Data& data);

		size_t write(size_t n);
		size_t write(const uint8_t* s, size_t n);
		size_t write(const Data& s, size_t n=0, size_t start=0);
		size_t write(DataInputStream& s, size_t n);
        size_t write(const std::string& s);

        template<typename T>
        size_t write(std::initializer_list<T> list);
    };

    template<typename T>
    size_t DataOutputStream::write(std::initializer_list<T> list)
    {
        return write(
            reinterpret_cast<const uint8_t*>(list.begin()),
            list.size()*sizeof(T)/sizeof(uint8_t)
        );
    }
}

#endif
