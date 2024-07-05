#include <iostream>
#include <memory>
#include <list>
#include <string>

class HString
{
public:
    HString(const std::string& str) : m_str(str) { std::cout << "构造HString[" << m_str << "]" << std::endl; }
    HString(const HString& other) : m_str(other.m_str) { std::cout << "复制构造HString[" << m_str << "]" << std::endl; }
    ~HString() { std::cout << "销毁HString[" << m_str << "]" << std::endl; }
private:
    std::string m_str;
};

class HImage
{
public:
    HImage(const std::string& filename) : m_str(filename) { std::cout << "构造HImage[" << m_str << "]" << std::endl; }
    ~HImage() { std::cout << "销毁HImage[" << m_str << "]" << std::endl; }
private:
    std::string m_str;
};

class HAudioClip
{
public:
    HAudioClip(const std::string& filename) : m_str(filename) { std::cout << "构造HAudioClip[" << m_str << "]" << std::endl; throw 1; }
    ~HAudioClip() { std::cout << "销毁HAudioClip[" << m_str << "]" << std::endl; }
private:
    std::string m_str;
};

/// 写法1.在构造函数中new成员变量，析构函数中delete，有内存泄漏风险
// class BookEntry
// {
// public:

//     BookEntry(const HString& name,
//         const HString& address = HString(""),
//         const std::string& imagefilename = "",
//         const std::string& audiofilename = ""
//     ) : m_name(name), m_address(address), m_image(nullptr), m_audio(nullptr)
//     {
//         if (imagefilename != "")
//         {
//             m_image = new HImage(imagefilename);
//         }

//         if (audiofilename != "")
//         {
//             m_audio = new HAudioClip(audiofilename);
//         }
//     }

//     ~BookEntry()
//     {
//         delete m_audio;
//         delete m_image;
//         std::cout << "销毁BookEntry" << std::endl;
//     }

// private:
//     HString m_name;
//     HString m_address;
//     HImage* m_image;
//     HAudioClip* m_audio;
// };

/// 写法2.在构造函数中new成员变量，析构函数中delete，在构造函数中用try catch，无内存泄漏风险，但是代码重复
// class BookEntry
// {
// public:

//     BookEntry(const HString& name,
//         const HString& address = HString(""),
//         const std::string& imagefilename = "",
//         const std::string& audiofilename = ""
//     ) : m_name(name), m_address(address), m_image(nullptr), m_audio(nullptr)
//     {
//         try
//         {
//             if (imagefilename != "")
//             {
//                 m_image = new HImage(imagefilename);
//             }

//             if (audiofilename != "")
//             {
//                 m_audio = new HAudioClip(audiofilename);
//             }
//         }
//         catch (...)
//         {
//             delete m_audio;
//             delete m_image;
//             throw;
//         }
//     }

//     ~BookEntry()
//     {
//         delete m_audio;
//         delete m_image;
//         std::cout << "销毁BookEntry" << std::endl;
//     }

// private:
//     HString m_name;
//     HString m_address;
//     HImage* m_image;
//     HAudioClip* m_audio;
// };

/// 写法3.在构造函数中new成员变量，析构函数中delete，在构造函数中用try catch，无内存泄漏风险，添加一个私有清理函数，消除重复代码，但是无法初始化 *const 类型变量
// class BookEntry
// {
// public:

//     BookEntry(const HString& name,
//         const HString& address = HString(""),
//         const std::string& imagefilename = "",
//         const std::string& audiofilename = ""
//     ) : m_name(name), m_address(address), m_image(nullptr), m_audio(nullptr)
//     {
//         try
//         {
//             if (imagefilename != "")
//             {
//                 m_image = new HImage(imagefilename);
//             }

//             if (audiofilename != "")
//             {
//                 m_audio = new HAudioClip(audiofilename);
//             }
//         }
//         catch (...)
//         {
//             clean();
//             throw;
//         }
//     }

//     ~BookEntry()
//     {
//         clean();
//         std::cout << "销毁BookEntry" << std::endl;
//     }

// private:
//     void clean()
//     {
//         delete m_audio;
//         delete m_image;
//     }

// private:
//     HString m_name;
//     HString m_address;
//     HImage* m_image;
//     HAudioClip* m_audio;
// };

/// 写法4.为了能初始化*const，在成员初值列中使用new，析构函数中delete，由于无法使用trycatch，还是有内存泄漏风险。
// class BookEntry
// {
// public:

//     BookEntry(const HString& name,
//         const HString& address = HString(""),
//         const std::string& imagefilename = "",
//         const std::string& audiofilename = ""
//     ) : m_name(name), m_address(address), m_image(imagefilename != "" ? new HImage(imagefilename) : nullptr), m_audio(audiofilename != "" ? new HAudioClip(audiofilename) : nullptr)
//     {
//     }

//     ~BookEntry()
//     {
//         clean();
//         std::cout << "销毁BookEntry" << std::endl;
//     }

// private:
//     void clean()
//     {
//         delete m_audio;
//         delete m_image;
//     }

// private:
//     HString m_name;
//     HString m_address;
//     HImage* const m_image;
//     HAudioClip* const m_audio;
// };

/// 写法5.添加createImage和createAudio私有函数，在成员初值列中调用，无内存泄漏，可以初始化*const，但是太丑了，多了clean createImage createAudio三个函数，构造过程散落在各个函数，以后维护会很难受
// class BookEntry
// {
// public:

//     BookEntry(const HString& name,
//         const HString& address = HString(""),
//         const std::string& imagefilename = "",
//         const std::string& audiofilename = ""
//     ) : m_name(name), m_address(address), m_image(createImage(imagefilename)), m_audio(createAudio(audiofilename))
//     {
//     }

//     ~BookEntry()
//     {
//         clean();
//         std::cout << "销毁BookEntry" << std::endl;
//     }

// private:
//     void clean()
//     {
//         delete m_audio;
//         delete m_image;
//     }

//     HImage* createImage(const std::string& imagefilename)
//     {
//         if (imagefilename != "")
//         {
//             return new HImage(imagefilename);
//         }
//         else
//         {
//             return nullptr;
//         }
//     }

//     HAudioClip* createAudio(const std::string& audiofilename)
//     {
//         try
//         {
//             if (audiofilename != "")
//             {
//                 return new HAudioClip(audiofilename);
//             }
//             else
//             {
//                 return nullptr;
//             }
//         }
//         catch (...)
//         {
//             delete m_image;
//             throw;
//         }
//     }

// private:
//     HString m_name;
//     HString m_address;
//     HImage* const m_image;
//     HAudioClip* const m_audio;
// };


/// 写法6.使用智能指针和成员初值列，至此无内存泄漏，可以初始化const*const，代码简单，逻辑清晰
class BookEntry
{
public:

    BookEntry(const HString& name,
        const HString& address = HString(""),
        const std::string& imagefilename = "",
        const std::string& audiofilename = ""
    ) : m_name(name),
        m_address(address),
        m_image(imagefilename != "" ? new HImage(imagefilename) : nullptr),
        m_audio(audiofilename != "" ? new HAudioClip(audiofilename) : nullptr)
    {
    }

    ~BookEntry()
    {
        std::cout << "销毁BookEntry" << std::endl;
    }

private:
    HString m_name;
    HString m_address;
    const std::unique_ptr<const HImage> m_image;
    const std::unique_ptr<const HAudioClip> m_audio;
};

void test1()
{
    BookEntry jodan(std::string("乔丹"), std::string("芝加哥"), "C:/image.png", "C:/audio.mp3");
}

void test2()
{
    BookEntry* pb = nullptr;
    try
    {
        pb = new BookEntry(std::string("乔丹"), std::string("芝加哥"), "C:/image.png", "C:/audio.mp3");
    }
    catch (...)
    {
        delete pb;
        throw;
    }
    delete pb;
}

void test3()
{
    std::unique_ptr<BookEntry> pb(new BookEntry(std::string("乔丹"), std::string("芝加哥"), "C:/image.png", "C:/audio.mp3"));
}


int main()
{
    try
    {
        test1();  //
        //test2();    //new
        //test3();    //unique_ptr
    }
    catch (...)
    {
        std::cout << "异常" << std::endl;
    }
    return 0;
}