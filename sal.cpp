#include <stdio.h>
#include <time.h>
#include <malloc.h>
#define sal_active

// The Simple Addons Library is under the MIT license as described below.

/*
MIT License

Copyright (c) 2021 CowMan999

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// The Simple Addons Library, A Lightweight Replacement For The Standard C++ Library.
namespace sal 
{

    // simple wrapper for c-style array
    template<typename T, int S> class array
    {
        private:
            T m_array[S];

        public:

            // operators
            T& operator[](int pos)
            {
                return m_array[pos];
            }

            bool operator==(array<T, S> other)
            {
                bool isequal = 1;
                for (int i = 0; i < S; i++)
                {
                    if(other[i] != m_array[i])
                    {
                        isequal = 0;
                    }
                }

                return isequal;
            }

            bool operator!=(array<T, S> other)
            {
                bool isequal = 1;
                for (int i = 0; i < S; i++)
                {
                    if(other[i] != m_array[i])
                    {
                        isequal = 0;
                    }
                }

                return !isequal;
            }

            // functions
            T at(int pos)
            {
                return m_array[pos];
            }

            int size()
            {
                return S;
            }

    };

    // more complex dynamic array implementation
    template<typename T> class dynamic_array
    {
        private:
            long long m_size{};
            T* m_data;
            int m_size_element = sizeof(*m_data);
            long long m_cap{1};

            void resize()
            {
                m_cap = m_cap+5;
                T* tmp = (T*)realloc(m_data, m_cap*m_size_element);

                m_data = tmp;
            }

        public:
            dynamic_array()
            {
                // allocate memory for one element 
                m_data = (T*)malloc(m_size_element);
            }

            ~dynamic_array()
            {
                // free data
                free(m_data);
            }

            void push(T val)
            {
                if(m_size >= m_cap)
                {
                    resize();
                }
                m_data[m_size++] = val;
            }

            int pop()
            {
                return m_data[--m_size];
            }

            T& operator[](int pos)
            {
                return m_data[pos];
            }

            T& at(int pos)
            {
                return m_data[pos];
            }

            bool operator==(dynamic_array<T> other)
            {
                bool isequal = 1;
                for (int i = 0; i < other.size(); i++)
                {
                    if(other[i] != m_data[i])
                    {
                        isequal = 0;
                    }
                }

                return isequal;
            }

            bool operator!=(dynamic_array<T> other)
            {
                bool isequal = 1;
                for (int i = 0; i < other.size(); i++)
                {
                    if(other[i] != m_data[i])
                    {
                        isequal = 0;
                    }
                }

                return !isequal;
            }

            int size()
            {
                return m_size;
            }

    };

    // basic string class
    class string
    {
        private:
            char* m_string;
            long long m_size{};
            int m_size_element = sizeof(char);
            long long m_cap{1};

            void resize()
            {
                m_cap += 32;
                char* tmp = (char*) realloc(m_string, m_size_element*m_cap);
                m_string = tmp;
            }

            int size_c_style_str(const char* c_str)
            {
                int size_c_str = -1;
                while(1)
                {
                    size_c_str++;
                    if(c_str[size_c_str] == '\0')
                    {
                        break;
                    }

                }
                return size_c_str;
            }


        public:
            string()
            {
                // allocate some space
                m_string = (char*) malloc(m_size_element /* Just one, hopefully... */);
            }

            string(const char* data)
            {
                // allocate some space
                m_string = (char*) malloc(m_size_element /* Just one, hopefully... */);
                append(data);
            }

            ~string()
            {
                free(m_string);
            }

            void resize(int size)
            {
                if(m_cap <= size)
                {
                    m_cap = size+3;
                }
                char* tmp = (char*) realloc(m_string, m_size_element*m_cap);
                m_string = tmp;
            }

            void push(char data)
            {
                if(m_size >= m_cap)
                {
                    resize();
                }
                m_string[m_size++] = data;
            }

            char pop()
            {
                return m_string[m_size--];
            }

            char& operator[](int pos)
            {
                return m_string[pos];
            }

            char& at(int pos)
            {
                return m_string[pos];
            }

            void operator=(const char* data)
            {
                int size_c_str = size_c_style_str(data);

                m_size = 0;

                for(int i = 0; i < size_c_str; i++)
                {
                    push(data[i]);
                }
                
            }


            void operator+=(const char* data)
            {
                int size_c_str = size_c_style_str(data);

                for(int i = 0; i < size_c_str; i++)
                {
                    push(data[i]);
                }
                
            }

            void append(const char* data)
            {
                int size_c_str = size_c_style_str(data);


                for(int i = 0; i < size_c_str; i++)
                {
                    push(data[i]);
                }
                
            }

            void append(char data)
            {
                push(data);
            }

            const char* c_str()
            {
                return m_string;
            }

            int size()
            {
                return m_size;
            }

            // comparsons
            bool operator==(sal::string data)
            {
                bool isequal = 1;
                if(data.size() != this->size())
                {
                    return 0;
                }
                for (long long i = 0; i < data.size(); i++)
                {
                    if (m_string[i] != data[i])
                    {
                        isequal = 0;
                    }
                    
                }

                return isequal;
                
            }

            bool operator!=(sal::string data)
            {
                bool isequal = 1;
                if(data.size() != this->size())
                {
                    return 1;
                }
                for (long long i = 0; i < data.size(); i++)
                {
                    if (m_string[i] != data[i])
                    {
                        isequal = 0;
                    }
                    
                }

                return !isequal;
                
            }

    };

    // some useful vars
    const double pi = 3.1415926535897;
    string version = "1.1";

    // some quick function overloads
    void print(int str) { putchar(str); }
    void print(const char* str) { printf(str); }
    void print(sal::string str) { printf(str.c_str()); }

    void sleep(int seconds)
    {
        time_t start = time(nullptr);

        while(time(nullptr) - start < seconds) {}

    }

   int c_str_size(const char* c_str)
   {
       int size_c_str = -1;
       while(1)
       {
           size_c_str++;
           if(c_str[size_c_str] == '\0')
           {
               break;
           }

       }
       return size_c_str;
   }

    sal::string to_string(int n)
    {
        const char digit_pairs[201] = {
            "00010203040506070809"
            "10111213141516171819"
            "20212223242526272829"
            "30313233343536373839"
            "40414243444546474849"
            "50515253545556575859"
            "60616263646566676869"
            "70717273747576777879"
            "80818283848586878889"
            "90919293949596979899"
        };

        sal::string s;

        if(n==0)
        {
            s="0";
            return s;
        }

        int sign = -(n<0);
        unsigned int val = (n^sign)-sign;

        int size;
        if(val>=10000)
        {
            if(val>=10000000)
            {
                if(val>=1000000000)
                    size=10;
                else if(val>=100000000)
                    size=9;
                else 
                    size=8;
            }
            else
            {
                if(val>=1000000)
                    size=7;
                else if(val>=100000)
                    size=6;
                else
                    size=5;
            }
        }
        else 
        {
            if(val>=100)
            {
                if(val>=1000)
                    size=4;
                else
                    size=3;
            }
            else
            {
                if(val>=10)
                    size=2;
                else
                    size=1;
            }
        }
        size -= sign;
        s.resize(size);
        char* c = &s[0];
        if(sign)
            *c='-';

        c += size-1;
        while(val>=100)
        {
           int pos = val % 100;
           val /= 100;
           *(short*)(c-1)=*(short*)(digit_pairs+2*pos); 
           c-=2;
        }
        while(val>0)
        {
            *c--='0' + (val % 10);
            val /= 10;
        }
        return s;
    };

}
