//
// Created by mustang on 18-6-10.
//

#ifndef INC_13_4_FOLDER_H
#define INC_13_4_FOLDER_H

#include "set"
#include "iostream"

class Message;

class Folder
{
    friend class Message;

    friend void swap(Message &, Message &);
private:
    std::set<Message *> message;
private:
    void addMsg(Message *m);

    void reMeg(Message *m);
    void add_to_Message(const Folder &ori);

    void remove_from_Messages();

public:
    std::ostream &print(std::ostream &);

    Folder()= default;

    // 拷贝构造
    Folder(const Folder &ori);

    // 拷贝构造时调用的辅助函数

    Folder&operator=(const Folder&ori);
    ~Folder();
};

class Message
{
    friend class Folder;
    friend void swap(Message &lhs, Message &rhs);

private:
    std::string contents;
    std::set<Folder *> folders;

    // 把本Message添加至m所在的所有Folder中
    void add_to_Folder(const Message &m)
    {
        for (auto &it:m.folders)
        {
            it->addMsg(this);
        }
    }

    // 把本Message从所有Folder中删除
    // 双向删除操作
    void rem_from_Folder()
    {
        for ( auto it:folders)
        {
            it->reMeg(this); // 先单向把每一个元素从Folder中删掉
        }
        folders.clear(); // 再执行第二个单向,把本Message中的所有Folder全部清空
    }


    // 添加一个Folder至本message
    // 本函数是工具函数,被拷贝初始化器使用
    void addFolder(Folder *);

    //双向删除本Message和args的Folder的关系
    void remove(Folder*);

public:

    // 构造函数
    explicit Message(const std::string &contents_ = " ") : contents(contents_)
    {}

    // 拷贝构造函数
    Message(const Message &ori) : contents(ori.contents), folders(ori.folders)
    {
        add_to_Folder(ori);
    }

    // 赋值运算符
    Message &operator=(const Message &ori)
    {
        if (&ori == this)
        {
            std::cout << "fuckself" << std::endl;
            return *this;
        }
        contents = ori.contents;
        rem_from_Folder();
        add_to_Folder(ori);
        return *this;
    }

    // 判等运算符
    bool operator==(const Message &ori)
    {
        return this == &ori;
    }

    // 把Message保存在指定的Folder中
    void save(Folder &target);

    void remove(Folder &target);

    ~Message();

    std::ostream& print(std::ostream&);

};
#endif //INC_13_4_FOLDER_H
