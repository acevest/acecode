/*
 * ------------------------------------------------------------------------
 *   File Name: RingBuffer.cpp
 *              Thu Jun 18 16:13:49 2015
 * Description: none
 * ------------------------------------------------------------------------
 */

#include <cstdlib>
#include <string.h>

class RingBuffer
{
public:
    RingBuffer(): buffer_(NULL), in_(0), out_(0), size_(0) {}
    ~RingBuffer() {}

public:
    // Init - 初始化缓冲区
    // @buffer: 已经申请的用作缓冲区的内存指针
    // @size: 缓冲区的大小, 必须是2的整数次幂
    //
    // 通过@buffer传入的内存, 可以是通过Alloc申请的, 也可以是外部自行分配的
    // 后者需要自行释放内存, 不适合通过Free释放
    int Init(unsigned char *buffer, unsigned int size)
    {
        if (!is_power_of_two(size))
            return -1;

        buffer_ = buffer;
        size_ = size;
        in_ = out_ = 0;

        return 0;
    }
    
    // Alloc - 在堆上申请指定大小的缓冲区内存并初始化
    // @size: 缓冲区大小, 会向上调整到2的整数次幂
    //
    // 通过Alloc申请的内存需要通过Free进行释放, 即Alloc和Free要配对使用
    int Alloc(unsigned int size)
    {
        unsigned char *buffer;
        int ret;

        if (!is_power_of_two(size))
            size = roundup_power_of_two(size);

        buffer = new unsigned char[size];
        if (!buffer)
            return -1;

        ret = Init(buffer, size);
        if (ret != 0)
            delete[] buffer;

        return 0;
    }

    // Put - 向缓冲区拷贝指定长度的数据
    // @buffer: 拷贝到缓冲区的数据
    // @len: 数据长度
    //
    // 从@buffer向缓冲区拷贝至多@len字节的数据, 具体拷贝长度依赖缓冲区的
    // 剩余空间大小, 实际拷贝长度通过返回值返回
    unsigned int Put(const unsigned char *buffer, unsigned int len)
    {
        unsigned int l;

        len = min(len, size_ - Len());

        // 从buffer_的in_位置开始写入数据, 直到buffer_的结尾位置
        l = min(len, size_ - (in_ & (size_ - 1)));
        memcpy(buffer_ + (in_ & (size_ - 1)), buffer, l);

        // 把剩余数据从buffer_的起始位置开始写入, 直到完成len字节写入
        memcpy(buffer_, buffer + l, len - l);

        in_ += len;

        return len;
    }

    // Get - 从缓冲区中取出指定长度的数据
    // @buffer: 取出数据的拷贝内存
    // @len: 拷贝内存的长度
    //
    // 向@buffer拷贝至多@len字节的数据, 实际拷贝长度通过返回值返回
    unsigned int Get(unsigned char *buffer, unsigned int len)
    {
        unsigned int l;

        len = min(len, Len());

        // 从buffer_的out_位置开始读出数据, 直到buffer_的结束位置
        l = min(len, size_ - (out_ & (size_ - 1)));
        memcpy(buffer, buffer_ + (out_ & (size_ - 1)), l);

        // 然后从buffer_的起始位置开始读出, 直到完成len字节读出
        memcpy(buffer + l, buffer_, len - l);

        out_ += len;

        return len;
    }
    
    // Len - 返回缓冲区的数据长度
    unsigned int Len()
    {
        return in_ - out_;
    }

    // Reset - 重置缓冲区, 即清空缓冲区数据
    void Reset()
    {
        in_ = out_ = 0;
    }

    // Free - 释放缓冲区内存
    // 释放通过Alloc申请的缓冲区内存, 和Alloc配对使用
    void Free()
    {
        if (buffer_)
        {
            delete[] buffer_;
            buffer_ = NULL;
        }
    }

private:
    template <typename T>
    T min(T a, T b)
    {
        return a > b ? b : a;
    }

    bool is_power_of_two(unsigned int n)
    {
        return (n != 0 && ((n & (n - 1)) == 0));
    }

    unsigned int roundup_power_of_two(unsigned int n)
    {
        unsigned int fls = __builtin_clz(n);
        return 1 << (sizeof(n) * 8 - fls);
    }

private:
    unsigned char   *buffer_;    // 缓冲区指针
    unsigned int    in_;         // 写指针
    unsigned int    out_;        // 读指针
    unsigned int    size_;       // 缓冲区大小
};

int main()
{
    RingBuffer rb;
    rb.Alloc(7);

    unsigned char str[128] = {0};
    int n;

    str[0] = 'a';
    n = rb.Put(str, 1);

    str[1] = 'b';
    n = rb.Put(str, 2);

    str[2] = 'c';
    n = rb.Put(str, 3);

    str[3] = 'd';
    n = rb.Put(str, 4);

    str[4] = 'e';
    n = rb.Put(str, 5);

    n = rb.Get(str, 2);
    n = rb.Get(str, 1);

    rb.Free();

    return 0;
}
